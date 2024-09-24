#include <cmath>
#include <glad/glad.h> 
#include <GLFW/glfw3.h> 
#include <iostream>
#include "Shader.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)){
        glfwSetWindowShouldClose(window, true);
    }
}

int success;
char infolog[512];

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    //hhader shader("/home/arin/code/opengl/src/shaders/vertex_shader.vs","/home/arin/code/opengl/src/shaders/fragment_shader.fs");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // OpenGL 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "pulse", NULL, NULL);
    if (!window) {
        std::cout << "glfw window failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "failed to initialize glad" << std::endl;
        return -1;
    }

    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
        //first triangle
      0.0f,0.5f,0.0f,       0.0f,1.0f,0.0f,
      0.5f,-0.5f,0.0f,      0.0f,1.0f,0.0f,
     -0.5f,-0.5f,0.0f,      0.0f,0.0f,1.0f
    };

    float vert[] = {
        0.5f,-0.5f,0.0f,
     -0.5f,-0.5f,0.0f,
     -0.5f, 0.5f,0.0f
    };

    unsigned int indices[] = {
        0,1,3,
        1,2,3
    };

    unsigned int VBO;
    glGenBuffers(1,&VBO);

    unsigned int VAOone;
    glGenVertexArrays(1,&VAOone);
    glBindVertexArray(VAOone);

    //unsigned int EBO;
    //glGenBuffers(1,&EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    //position
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    //color
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    unsigned int VAOtwo;
    glGenVertexArrays(1,&VAOtwo);
    glBindVertexArray(VAOtwo);

    unsigned int VBOtwo;
    glGenBuffers(1,&VBOtwo);
    glBindBuffer(GL_ARRAY_BUFFER,VBOtwo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vert),vert,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    //------------hardware info------------
    int nr;
    glad_glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&nr);
    std::cout <<"number of max attrs: "<<nr<<std::endl;
    const GLubyte* vendor = glad_glGetString(GL_VENDOR);
    const GLubyte* renderer = glad_glGetString(GL_RENDERER);
    std::cout<<"gpu in use: "<<vendor<<" "<<renderer<<std::endl;
    


    Shader shader("/home/arin/code/opengl/src/shaders/vertex_shader.vs","/home/arin/code/opengl/src/shaders/fragment_shader.fs");
    //-------------render loop---------------
    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.5,0.1,0.8f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //glad_glUseProgram(shaderProgram);
        shader.use();
        //update frag shader
        float currtime = glfwGetTime();
        float colorval = (sin(currtime)/2.0f) + 0.5f;

        glBindVertexArray(VAOone);
        glDrawArrays(GL_TRIANGLES,0,3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAOone);
    glDeleteVertexArrays(1,&VAOtwo);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&VBOtwo);
    glfwTerminate(); 
    return 0;
}
