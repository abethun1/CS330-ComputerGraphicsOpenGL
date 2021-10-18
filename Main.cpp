#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include"stb_image.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"



const unsigned int width = 800;
const unsigned int height = 800;



// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //    Part of object and its index fpr the vertex

		-0.5f, 0.5f,  0.0f,     0.0f,0.0f,0.0f,  0.0f, 0.0f,     1.0f, 1.0f, 1.0f, // Front Triangle / Top Left 0
		 0.5f, 0.5f,  0.0f,     0.0f,0.0f,0.0f,	 0.0f, 0.0f,     1.0f, 1.0f, 1.0f, // Front Triangle / Top Right 1
		 0.0f,-0.5f, -0.75f,    0.0f,0.0f,0.0f,	 0.0f, 0.0f,     1.0f, 1.0f, 1.0f, // Front Triangle / Bottom 2 
		-0.5f, 0.5f, -1.5f,     0.0f,0.0f,0.0f,	 0.0f, 0.0f,     1.0f, 1.0f, 1.0f, // Back Triangle / Top Left 3
		 0.5f, 0.5f, -1.5f,     0.0f,0.0f,0.0f,	 0.0f, 0.0f,     1.0f, 1.0f, 1.0f, // Back Triangle / Top Right 4
		 0.0f,-0.5f, -0.75f,    0.0f,0.0f,0.0f,	 0.0f, 0.0f,     1.0f, 1.0f, 1.0f, // Back Triangle / Bottom 5
							
		-0.5f, 0.5f,  0.0f,     0.0f,0.0f,0.0f,	 0.0f, 0.0f,     1.0f, 1.0f, 1.0f, // Left Triangle / Top Left 6
		-0.5f, 0.5f, -1.5f,     0.0f,0.0f,0.0f,	 0.0f, 0.0f,     1.0f, 1.0f, 1.0f, // Left Triangle / Top Right 7 
		 0.0f,-0.5f, -0.75f,    0.0f,0.0f,0.0f,	 0.0f, 0.0f,     1.0f, 1.0f, 1.0f, // Left Triangle / Bottom 8
		 0.5f, 0.5f,  0.0f,     0.0f,0.0f,0.0f,	 0.0f, 0.0f,     1.0f, 1.0f, 1.0f, // Right Triangle / Top Left 9
		 0.5f, 0.5f, -1.5f,     0.0f,0.0f,0.0f,  0.0f, 0.0f,     1.0f, 1.0f, 1.0f, // Right Triangle / Top Right 10 
		 0.0f, -0.5f, -0.75f,   0.0f,0.0f,0.0f,	 0.0f, 0.0f,     1.0f, 1.0f, 1.0f,  // Right Triangle / Bottom 11
													
		//Rectangular prisim verts							
		-1.5f,  -0.45f,  0.0f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //top left 12
		-1.5f,  -0.75f,  0.0f,	0.0f, 0.0f, 0.0f, 	  0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //bottom left 13
		 1.5f,  -0.45f,  0.0f,	0.0f, 0.0f, 0.0f, 	  0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  // top right 14
		-1.5f,  -0.75f,  0.0f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //bottom left repeat 15
		 1.5f,  -0.45f,  0.0f,	0.0f, 0.0f, 0.0f, 	  0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  // top right repeat 16
		 1.5f,  -0.75f,  0.0f,	0.0f, 0.0f, 0.0f, 	  0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //bottom right 17
												    					  		 
		-1.5f,  -0.45f,  -1.5f, 0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back top left 18
		-1.5f,  -0.75f,  -1.5f, 0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back bottom left 19
		 1.5f,  -0.45f,  -1.5f, 0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back top right 20
		-1.5f,  -0.75f,  -1.5f, 0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back bottom left repeat 21
		 1.5f,  -0.45f,  -1.5f, 0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back top right repeat 22
		 1.5f,  -0.75f,  -1.5f, 0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back bottom right 23
								   										 		 
		-1.5f,  -0.45f,  0.0f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //top left 24
		-1.5f,  -0.45f, -1.5f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  // back top left 25
		 1.5f,  -0.45f,  0.0f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  // top right 26
		-1.5f,  -0.45f, -1.5f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  // back top left 27
		 1.5f,  -0.45f,  0.0f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  // top right 28
		 1.5f,  -0.45f, -1.5f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back top right 29
								    											 
		-1.5f,  -0.75f,  0.0f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //bottom left 30
		-1.5f,  -0.75f, -1.5f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back bottom left 21
		 1.5f,  -0.75f,  0.0f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //bottom right 32
		-1.5f,  -0.75f, -1.5f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back bottom left 33
		 1.5f,  -0.75f,  0.0f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //bottom right 34
		 1.5f,  -0.75f, -1.5f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back bottom right 35
								     									  		
		 1.5f,  -0.45f,  0.0f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  // top right 36
		 1.5f,  -0.45f, -1.5f,  0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back top right 37
		 1.5f,  -0.75f,  0.0f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //bottom right 38
		 1.5f,  -0.45f, -1.5f,  0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back top right 39
		 1.5f,  -0.75f,  0.0f,	0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //bottom right 40
		 1.5f,  -0.75f, -1.5f,  0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back bottom right 41
								     											 
		 -1.5f,  -0.45f,  0.0f, 0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //top left 42
		 -1.5f,  -0.45f, -1.5f, 0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back top left 43
		 -1.5f,  -0.75f,  0.0f, 0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //bottom left 44
		 -1.5f,  -0.45f, -1.5f, 0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back top left 45
		 -1.5f,  -0.75f,  0.0f, 0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //bottom left 46
		 -1.5f,  -0.75f, -1.5f, 0.0f, 0.0f, 0.0f,     0.0f, 0.0f,	-1.0f,-1.0f, -1.0f,  //back bottom left 47

		 //Screen										 
		-1.3f,  -0.44f,  -0.1f,	 0.83f, 0.70f, 0.44f,	0.0f, 0.0f,		-0.8f, 0.5f, 1.0f,  //top left 48
		-1.3f,  -0.44f, -1.4f,	 0.83f, 0.70f, 0.44f,	0.0f, 0.0f,		-0.8f, 0.5f, 1.0f,  // back top left 49
		 1.3f,  -0.44f,  -0.1f,	 0.92f, 0.86f, 0.76f,	0.0f, 0.0f,		-0.8f, 0.5f, 1.0f,  // top right 50
		-1.3f,  -0.44f, -1.4f,	 0.83f, 0.70f, 0.44f,	0.0f, 0.0f,		 0.0f, 0.5f, 1.8f,  // back top left 51
		 1.3f,  -0.44f,  -0.1f,	 0.83f, 0.70f, 0.44f,	0.0f, 0.0f,		 0.0f, 0.5f, 1.8f,  // top right 52
		 1.3f,  -0.44f, -1.4f,	 0.92f, 0.86f, 0.76f,	0.0f, 0.0f,		 0.0f, 0.5f, 1.8f,  //back top right 53
					
		 //Plane									 
		-5.5f,  -0.76f,  5.0f,  0.6f, 0.6f, 0.6f,	 0.0f, 0.0f,		0.0f, -1.0f, -1.0f,  //top left 54
		-5.5f,  -0.76f, -6.5f,  0.6f, 0.6f, 0.6f,	 0.0f, 0.0f,		0.0f, -1.0f, -1.0f,  // back top left 55
		 5.5f,  -0.76f,  5.0f,  0.6f, 0.6f, 0.6f,	 0.0f, 0.0f,		0.0f, -1.0f, -1.0f,  // top right 56
		-5.5f,  -0.76f, -6.5f,  0.6f, 0.6f, 0.6f,	 0.0f, 0.0f,		0.0f, -1.0f, -1.0f,  // back top left 57
		 5.5f,  -0.76f,  5.0f,  0.6f, 0.6f, 0.6f,	 0.0f, 0.0f,		0.0f, -1.0f, -1.0f,  // top right 58
		 5.5f,  -0.76f, -6.5f,  0.6f, 0.6f, 0.6f,	 0.0f, 0.0f,		0.0f, -1.0f, -1.0f,  //back top right 59

		 //Earth
		-0.2f, 0.3f, -0.5f,    0.83f, 0.70f, 0.44f,  -0.5f, 0.0f,     -0.8f, 0.5f, 1.0f, // 60
		 0.2f, 0.3f, -0.5f,    0.83f, 0.70f, 0.44f,	 -1.0f, 0.0f,     -0.8f, 0.5f, 1.0f, // 61
		 0.0f, 0.5f, -0.7f,    0.92f, 0.86f, 0.76f,	 -0.75f, 1.0f,     -0.8f, 0.5f, 1.0f, // 62 top front   //-1 -.25 50 1
		
		-0.2f, 0.3f, -0.5f,    0.83f, 0.70f, 0.44f,  -0.5f, 0.0f,      0.0f, 0.5f, 1.8f, // 63
		 0.2f, 0.3f, -0.5f,    0.83f, 0.70f, 0.44f,	 -1.0f, 0.0f,    0.0f, 0.5f, 1.8f, // 64
		 0.0f, 0.0f, -0.7f,    0.92f, 0.86f, 0.76f,	 -0.75f, -1.0f,   0.0f, 0.5f, 1.8f, // 65 bottom front

		 0.2f, 0.3f, -0.5f,    0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,    -0.8f, 0.5f, 1.0f, // 66
		 0.2f, 0.3f, -0.9f,    0.83f, 0.70f, 0.44f,	 0.5f, 0.0f,    -0.8f, 0.5f, 1.0f, // 67
		 0.0f, 0.5f, -0.7f,    0.92f, 0.86f, 0.76f,	 0.75f, 1.0f,    -0.8f, 0.5f, 1.0f, // 68 top right

		 0.2f, 0.3f, -0.5f,      0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, 0.5f, 1.8f, // 69
		 0.2f, 0.3f, -0.9f,      0.83f, 0.70f, 0.44f,	 0.5f, 0.0f,       0.0f, 0.5f, 1.8f, // 70
		 0.0f, 0.0f, -0.7f,      0.92f, 0.86f, 0.76f,	 0.75f, -1.0f,      0.0f, 0.5f, 1.8f, // 71 bottom right

		-0.2f, 0.3f, -0.5f,     0.83f, 0.70f, 0.44f,     -0.5f, 0.0f,    -0.8f, 0.5f, 1.0f, // 72
		-0.2f, 0.3f, -0.9f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,    -0.8f, 0.5f, 1.0f, // 73
		 0.0f, 0.5f, -0.7f,     0.92f, 0.86f, 0.76f,	 -0.25, 1.0f,    -0.8f, 0.5f, 1.0f, // 74 top left

		-0.2f, 0.3f, -0.5f,      0.83f, 0.70f, 0.44f,    -0.5f, 0.0f,     0.0f, 0.5f, 1.8f, // 75
		-0.2f, 0.3f, -0.9f,      0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, 1.8f, // 76
		 0.0f, 0.0f, -0.7f,      0.92f, 0.86f, 0.76f,	 -0.25, -1.0f,     0.0f, 0.5f, 1.8f, // 77 bottom left

		-0.2f, 0.3f, -0.9f,     0.83f, 0.70f, 0.44f,    0.0f, 0.0f,		-0.8f, 0.5f, 1.0f, // 78
		0.2f, 0.3f, -0.9f,		0.83f, 0.70f, 0.44f,	0.5f, 0.0f,		-0.8f, 0.5f, 1.0f, // 79
		0.0f, 0.5f, -0.7f,		0.92f, 0.86f, 0.76f,	0.25f, 1.0f,		-0.8f, 0.5f, 1.0f, // 80 top back

		-0.2f, 0.3f, -0.9f,      0.83f, 0.70f, 0.44f,   0.0f, 0.0f,	      0.0f, 0.5f, 1.8f, // 81
		 0.2f, 0.3f, -0.9f,      0.83f, 0.70f, 0.44f,	0.5f, 0.0f,	      0.0f, 0.5f, 1.8f, // 82
		0.0f, 0.0f, -0.7f,       0.92f, 0.86f, 0.76f,	0.25f, -1.0f,      0.0f, 0.5f, 1.8f, // 83 bottom back

};														                                     



// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom side
	3, 4, 5, // Bottom side
	6, 7, 8,
	9, 10, 11,
	12, 13, 14,
	15, 16, 17,
	18, 19, 20,
	21, 22, 23,
	24, 25, 26,
	27, 28, 29,
	30, 31, 32,
	33, 34, 35,
	36, 37, 38,
	39, 40, 41,
	42, 43, 44,
	45, 46, 47,
	48, 49, 50,
	51, 52, 53,
	54, 55, 56,
	57, 58, 59,
	60, 61, 62,
	63, 64, 65,
	66, 67, 68,
	69, 70, 71,
	72, 73, 74,
	75, 76, 77,
	78, 79, 80,
	81, 82, 83,
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

//Makes the light cube
GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "Antonio Bethune Final", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);



	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Generates Vertex Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();





	glm::vec4 lightColor = glm::vec4(0.8f, 0.8f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(-0.2f, 10.7f, -0.2f);
	glm::mat4 lightModel = glm::mat4(0.5f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);


	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	//============================================================================================================================
	//texture
	int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load("mh_terrestrial__30c.png", &widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "text0");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);

	//============================================================================================================================
	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);


		// Tells OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Exports the camera Position to the Fragment Shader for specular lighting
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		// Export the camMatrix to the Vertex Shader of the pyramid
		camera.Matrix(shaderProgram, "camMatrix");
		// Binds texture so that is appears in rendering
		glBindTexture(GL_TEXTURE_2D, texture);
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);



		// Tells OpenGL which Shader Program we want to use
		lightShader.Activate();
		// Export the camMatrix to the Vertex Shader of the light cube
		camera.Matrix(lightShader, "camMatrix");
		// Bind the VAO so OpenGL knows to use it
		lightVAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &texture);
	shaderProgram.Delete();
	lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}