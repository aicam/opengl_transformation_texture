// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <GLFW/glfw3.h>

#include <iostream>
// glm library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "libs/Transformation.h"
#include "libs/VertexBuffer.h"
#include "libs/VertexArray.h"
#include "libs/IndexBuffer.h"
#include "libs/Shader.h"
#include "libs/Renderer.h"
#include "libs/Texture.h"
// here junks

unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
glm::mat4 transformation = glm::mat4(1.0f);
short selectedIndex = -1;
bool wired = false;
Transformation transformationClass;
unsigned int VBO, VAO, EBO;

float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
};

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (selectedIndex == -1)
        return;
    double xposd, yposd;
    glfwGetCursorPos(window, &xposd, &yposd);
    float xpos = ((float) xposd / SCR_WIDTH) * 2 - 1;
    float ypos = -(((float) yposd / SCR_HEIGHT) * 2 - 1);

    vertices[selectedIndex * (sizeof(vertices) / (sizeof(float) * 4))] = xpos;
    vertices[selectedIndex * (sizeof(vertices) / (sizeof(float) * 4)) + 1] = ypos;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

//    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * selectedIndex * 3, sizeof(float) * 3,
//                    vertices + selectedIndex * 3);
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        if (wired) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        wired = !wired;
    }
    transformationClass.pressedKey(key);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        selectedIndex = -1;
        return;
    }
    if (button != GLFW_MOUSE_BUTTON_LEFT || action != GLFW_PRESS)
        return;

    double xposd, yposd;
    glfwGetCursorPos(window, &xposd, &yposd);
    float xpos = ((float) xposd / SCR_WIDTH) * 2 - 1;
    float ypos = -(((float) yposd / SCR_HEIGHT) * 2 - 1);
    float thresh = 0.02f;

    selectedIndex = -1;
    for (int i = 0; i < 4; i++) {
        float x = vertices[i * (sizeof(vertices) / (sizeof(float) * 4))], y = vertices[(i * (sizeof(vertices) / (sizeof(float) * 4))) + 1];
        if (std::abs(x - xpos) < thresh && std::abs(y - ypos) < thresh) {
            selectedIndex = i;
//            std::cout << xpos << " " << ypos << " | " << x << " " << y << " " << selectedIndex << std::endl;
            return;
        }
    }
}
// here junks


GLFWwindow* InitWindow()
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow( 1024, 768, "HW2", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return nullptr;

    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return nullptr;
    }

    std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}

int main( void )
{
    GLFWwindow* window = InitWindow();
    if (!window)
        return -1;

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    {
        VertexArray va;


        Shader shader("/home/ali/CLionProjects/thecherno_opengl/ep17-textures/res/shaders/Basic.shader");
        shader.Bind();

        Texture texture("/home/ali/CLionProjects/thecherno_opengl/ep17-textures/res/textures/background.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);
        Renderer renderer;
        IndexBuffer ib(indices, 6);
        VertexBufferLayout layout;
        // position
        layout.AddFloat(3);
        // color
        layout.AddFloat(3);
        // text coord
        layout.AddFloat(2);
        do {
            transformation = transformationClass.transform(transformation, vertices);
            shader.SetUniformMat4f("MVP", transformation);
            VertexBuffer vb(vertices, 8 * 4 * sizeof(float));
            va.AddBuffer(vb, layout);
            processInput(window);
            renderer.Clear();
            renderer.Draw(va, ib, shader);

            // Swap buffers
            glfwSwapBuffers(window);
            glfwPollEvents();
        } // Check if the ESC key was pressed or the window was closed
        while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                glfwWindowShouldClose(window) == 0 );
    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

