#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Grid.cpp"
#include "../algorithms/ISpreadModel.hpp"
#include "../algorithms/spreadModel_1.hpp"
#include "Surface.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

std::string loadShaderSource(const char* filepath);
unsigned int compileShader(unsigned int type, const std::string& source);
unsigned int createShaderProgram(const char* vertexPath, const char* fragmentPath);



int main() {
    if(!glfwInit()){
        cerr << "Failed to initalize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "ForestFireSim", nullptr, nullptr);
    if(window == nullptr){
        cerr << "Failed to create GLFW Window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // load openGL functions using glad
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        cerr << "Failed to initialize GLAD\n";
        return -1;
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int W=80; int H=60;
    float cellwidth = 2.0f/W;
    float cellheight = 2.0f/H;
    
    float vertices[] = {
        0.0f, 0.0f, 0.0f,
        cellwidth, 0.0f, 0.0f,
        cellwidth, cellheight, 0.0f,

        0.0f, 0.0f, 0.0f,
        0.0f, cellheight, 0.0f,
        cellwidth, cellheight, 0.0f,
    };
    
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    GLuint shader = createShaderProgram("src/vertex_shader.glsl", "src/fragment_shader.glsl");
    glUseProgram(shader);
    

    GLint offset = glGetUniformLocation(shader, "offset");

    glUniform2f(glGetUniformLocation(shader, "cellSize"), cellwidth, cellheight);
    glUniform2f(glGetUniformLocation(shader, "borderThickness"), cellwidth * 0.05f, cellheight*0.05f); // adjust as needed



    Surface surface = Surface(W, H);

    Cell* cell = surface.getCell(0, 0);
    int ros = cell->getRos();

    cout << "Example of cell 0,0 ros is : " << ros << "\n";

    surface.ignite(surface, 5, 6);
    std::cout << "GRID [0, 0] burning status : " << surface.getCell(0, 0)->status() << "\n";

    float lastUpdateTime = glfwGetTime();
    float updateInterval = 0.1f; // seconds between simulation updates

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        for(int i=0; i<W; i++){
            for(int j=0; j<H; j++){
                GLfloat x = -1.0f + i*cellwidth;
                GLfloat y = -1.0f + j*cellheight;
                
                Cell* curr_cell = surface.getCell(i, j);
                
                // conditional colored rendering of each cell
                if(curr_cell->status() == 1){
                    GLint isburning = glGetUniformLocation(shader, "isBurning_fromcpu");
                    glUniform1f(isburning, 1); // set burning to true for frag shader
                    glUniform2f(glGetUniformLocation(shader, "burning_pos_fromcpu"), x, y);
                }else{
                    glUniform1f(glGetUniformLocation(shader, "isBurning_fromcpu"), 0); // set burning to false for frag shader
                }

                glUniform2f(offset, x, y);
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
        }
        
        float currenttime = glfwGetTime();
        if(currenttime - lastUpdateTime >= updateInterval){
            surface.update(surface);
            lastUpdateTime = currenttime;
        }
        
        // glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

std::string loadShaderSource(const char* filepath){
    std::ifstream file(filepath);
    if(!file.is_open()){
        std::cerr << "error opening file" << "\n";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();

}

unsigned int compileShader(unsigned int type, const std::string& source){
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    std::cout << "Compiling: " << source << std::endl;

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        GLint logsize = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);
        std::vector<GLchar> errorlog(logsize);
        glGetShaderInfoLog(shader, logsize, &logsize, &errorlog[0]);
        std::cout << "Shader compilation error: " << std::endl;
        for(auto ch:errorlog){
            cout << ch;
        } 
    }
    return shader;
}
unsigned int createShaderProgram(const char* vertexPath, const char* fragmentPath){
    std::string vertexSrc = loadShaderSource(vertexPath);
    std::string fragmentSrc = loadShaderSource(fragmentPath);

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}
