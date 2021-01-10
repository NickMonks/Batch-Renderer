#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);


    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;
    { // We create a new scope here. The reason is because whenever vertexbuffer calls the destructor, it will cause an infinite loop in the glGetError
        // due to the fact that, in the while() window the glTerminateWindow is destroyed, so it destroys the vertexbuffer already. This is rare since we normally
        // wont create a vertexbuffer there. Another solution is heap allocate the object. 


        float positions[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, // 0 (the other two elements are the texture coordinate system!)
            0.5f, -0.5f,  1.0f, 0.0f,// 1
            0.5f,  0.5f,  1.0f, 1.0f,// 2
            -0.5f, 0.5f,  0.0f, 1.0f// 3
        };

        // use of indices for our vertex buffer - basically saying how our vertex should be arranged when creating triangles
        unsigned int indices[] = {
            0,1,2,
            2,3,0
        };


        /* ------- VERTEXARRAY ------------*/

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));


        /* ------- LAYOUT (VERTEX ATTR) ------------*/

        VertexBufferLayout layout;
        layout.Push<float>(2); // we add the positions to our buffer layout
        layout.Push<float>(2); // we add the texture coordinate system
        va.AddBuffer(vb, layout);

        /* ------- INDEXBUFFER ------------*/
        IndexBuffer ib(indices, 6);

        /* ------- SHADER AND UNIFORMS ------------*/

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        /* ------- TEXTURES ------------*/
        Texture texture("res/textures/png_example.png");
        texture.Bind();

        // after binding the texture, we need to set a uniform to pass it to the shader. We set it to 0, since we bonded it to slot 0
        // in the line above this one.
        shader.setUniform1fi("u_Texture", 0);

        //after that, we need to map and tell the fragment shader which area should rasterize from the texture.
        // that means, specify from which vertex from our rectangle, what area of the texture should be and interpolate. 
        //To do so, we need to define the texture coordinate system.

        // that will be defined in our positions array. 

        /* ------- RENDERER ------------*/
        Renderer renderer;

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();
        

        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            shader.Bind();
            shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            renderer.Draw(va, ib, shader); // normally we wouldnt pass a shader, we would pass a material (which is a shader + all uniforms). 

            //glDrawArrays(GL_TRIANGLES, 0, 6);
            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }
    glfwTerminate();
    return 0;
}