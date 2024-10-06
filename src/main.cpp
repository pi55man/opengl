#include <glad/glad.h> 
#include <GLFW/glfw3.h> 
#include <iostream>
#include "Shader.hpp"
#include "Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

//runs when window size is changed and sets the viewport to the current width and height
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow* window, Shader& shader){
    static std::string uniform = "range";
    static GLint loc = glGetUniformLocation(shader.ID,"range");
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS){
        GLfloat params[1];
        glGetUniformfv(shader.ID,loc,params);
        if(params[0]<1.0f){
        shader.setFloat(uniform,params[0]+=0.01f);
        }
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
        GLfloat params[1];
        glGetUniformfv(shader.ID,loc,params);
        if(params[0]>0.0f){
            shader.setFloat(uniform,params[0]-=0.01f);
        }
    }
}
int success;
char infolog[512];

int main() {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // opengl 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "pulse", NULL, NULL);
    if (!window) {
        std::cout << "glfw window failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    //makes current window the active context for glfw operations
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "failed to initialize glad" << std::endl;
        return -1;
    }

    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float recVert[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    
    unsigned int VBO;
    glGenBuffers(1,&VBO);

    unsigned int EBO;
    glGenBuffers(1,&EBO);

    unsigned int VAOone;
    glGenVertexArrays(1,&VAOone);
    glBindVertexArray(VAOone);
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(recVert),recVert,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);

    //color
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    //tex
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    //unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    //------------hardware info------------
    int nr;
    glad_glGetIntegerv(GL_MAX_VERTEX_ATTRIBS,&nr);
    std::cout <<"number of max attrs: "<<nr<<std::endl;
    const GLubyte* vendor = glad_glGetString(GL_VENDOR);
    const GLubyte* renderer = glad_glGetString(GL_RENDERER);
    std::cout<<"gpu in use: "<<vendor<<" "<<renderer<<std::endl;

    //-------------creates shader-----------
    Shader shader("/home/arin/code/opengl/src/shaders/vertex_shader.vs","/home/arin/code/opengl/src/shaders/fragment_shader.fs");
    
    stbi_set_flip_vertically_on_load(true);
    unsigned int tex;
    unsigned int smile;
    glGenTextures(1,&tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,tex);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


    Image flower("/home/arin/code/opengl/flower.jpg",0);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,flower.width,flower.height,0,GL_RGB,GL_UNSIGNED_BYTE,flower.load());
    glGenerateMipmap(GL_TEXTURE_2D);
    flower.free();

    glGenTextures(1,&smile);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,smile);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


    Image smiley("/home/arin/code/opengl/src/smiley.png",0);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,smiley.width,smiley.height,0,GL_RGBA,GL_UNSIGNED_BYTE,smiley.load());
    glGenerateMipmap(GL_TEXTURE_2D);
    smiley.free();   

    stbi_image_free(smiley.load());

    shader.use();
    glUniform1i(glad_glGetUniformLocation(shader.ID, "texture1"),0);
    glUniform1i(glad_glGetUniformLocation(shader.ID, "texture2"),1);
    //-------------render loop---------------
    while(!glfwWindowShouldClose(window)){
//checks if escape is pressed and closes window
        std::string r = "range";
        processInput(window,shader);

        glClearColor(0.0,0.05,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,tex);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,smile);

        glBindVertexArray(VAOone);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAOone);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glfwTerminate(); 
    return 0;
}



