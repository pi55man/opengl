#include <cmath>
#include <glad/glad.h> 
#include <GLFW/glfw3.h> 
#include <iostream>

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


const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   vertexColor = aColor;\n"
    "}\0";

const char* fragShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(vertexColor,1.0);\n"
    "}\n\0";

const char* fragShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 color;\n"
    "void main()\n"
    "{\n"
    "   FragColor =color;\n"
    "}\n\0";


int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

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

   
    unsigned int vertexShader;
    vertexShader = glad_glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    
    glad_glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
    if(!success){
    glGetShaderInfoLog(vertexShader,512,NULL,infolog);
    std::cout<<infolog<<std::endl;
    }

    unsigned int fragShader;
    fragShader = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader,1,&fragShaderSource,NULL);
    glCompileShader(fragShader);

    unsigned int fragShader2;
    fragShader2 = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader2,1,&fragShaderSource2,NULL);
    glCompileShader(fragShader2);

    glad_glGetShaderiv(fragShader,GL_COMPILE_STATUS,&success);
    if(!success){
    glGetShaderInfoLog(fragShader,512,NULL,infolog);
    std::cout<<"frag shader failed: "<<infolog<<std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glad_glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    
    unsigned int shaderProgram2;
    shaderProgram2 = glad_glCreateProgram();
    glAttachShader(shaderProgram2,vertexShader);
    glAttachShader(shaderProgram2,fragShader2);
    glLinkProgram(shaderProgram2);
    glGetProgramiv(shaderProgram2,GL_LINK_STATUS,&success);
 
 
    if(!success){
        glGetProgramInfoLog(shaderProgram,512,NULL,infolog);
        std::cout<<"program failed: " << infolog<<std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
    glDeleteShader(fragShader2);

    float vertices[] = {
        //first triangle
      0.0f,0.5f,0.0f,       1.0f,0.0f,0.0f,
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
    
    //-------------render loop---------------
    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.5,0.1,0.8f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        //update frag shader
        float currtime = glfwGetTime();
        float colorval = (sin(currtime)/2.0f) + 0.5f;

        glBindVertexArray(VAOone);
        glDrawArrays(GL_TRIANGLES,0,3);

        glUseProgram(shaderProgram2);
        
        int colorLoc2 = glGetUniformLocation(shaderProgram2,"color");
        glUniform4f(colorLoc2,colorval,0.0f,0.0f,1.0f);

       // glBindVertexArray(VAOtwo);
     //   glDrawArrays(GL_TRIANGLES,0,3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&VAOone);
    glDeleteVertexArrays(1,&VAOtwo);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&VBOtwo);
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgram2);
    glfwTerminate(); 
    return 0;
}
