//Legasov
//Proyecto Final
//Fecha de entrega: 
//numeros de cuenta


#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"

// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"


// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH =1200, HEIGHT = 800;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;

// Set up vertex data (and buffer(s)) and attribute pointers
float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

// Light attributes
glm::vec3 lightPos(1.0f, 2.0f, -5.0f);

//keyboard map
bool keys[1024];
bool firstMouse = true;

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Proyecto Final - Legasov", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	//-----------------------------------------------------------------------------------------------------------------

	// Build and compile our shader program
	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

	//Load Models

    Model Dog((char*)"Models/RedDog.obj");
	Model Piso((char*)"Models/piso.obj");
	/*Model garage((char*)"Models/garage/parkhaus.obj");
	Model dodge((char*)"Models/dodgeCharger/dodge2.obj");
	Model hotwheel((char*)"Models/hotwheels/hotwheels.obj");
	Model audir8((char*)"Models/Audi_R8_V10/audi.obj");
	Model audi((char*)"Models/audir8/audi.obj");
	Model tesla((char*)"Models/tesla/tesla.obj");
	Model lamp((char*)"Models/lamp/lamp.obj");
	Model lamp2((char*)"Models/lamp2/lamp2.obj");*/

	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);
	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//-------------------------------------------------------------------------------------------------------------------

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

		// Luz direccional tipo sol
		glm::vec3 dirLightDirection(-0.2f, -1.0f, -0.3f); // dirección del sol
		glm::vec3 dirLightAmbient(0.3f, 0.3f, 0.35f);    // color ambiental suave
		glm::vec3 dirLightDiffuse(0.8f, 0.8f, 0.75f);    // color difuso del sol
		glm::vec3 dirLightSpecular(0.5f, 0.5f, 0.5f);    // reflejo especular

		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), dirLightDirection.x, dirLightDirection.y, dirLightDirection.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), dirLightAmbient.r, dirLightAmbient.g, dirLightAmbient.b);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), dirLightDiffuse.r, dirLightDiffuse.g, dirLightDiffuse.b);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), dirLightSpecular.r, dirLightSpecular.g, dirLightSpecular.b);

		// Luz ambiental global (para exteriores)
		glm::vec3 globalAmbientColor(0.6f, 0.6f, 0.7f);  // color del ambiente exterior
		float globalAmbientStrength = 0.2f;              // intensidad de la luz ambiental

		glUniform3f(glGetUniformLocation(lightingShader.Program, "globalAmbientColor"), globalAmbientColor.r, globalAmbientColor.g, globalAmbientColor.b);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "globalAmbientStrength"), globalAmbientStrength);

		//Point light 1
		glm::vec3 lightColor;
		//glm::vec3 Light1 = glm::vec3(1.0f, 0.85f, 0.7f); // Luz cálida
		glm::vec3 Light1 = glm::vec3(0.0f, 0.0f, 0.0f); // Luz cálida
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);

		//--- LUZ 1 (La original) ---
		glm::vec3 lightPos1 = glm::vec3(1.0f, 0.0f, 2.5f);
		glm::vec3 target1 = glm::vec3(-3.0f, 0.0f, -1.5f);
		glm::vec3 dir1 = glm::normalize(target1 - lightPos1);
		// Nota cómo el nombre del uniform ahora incluye el índice "[0]"
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].position"), lightPos1.x, lightPos1.y, lightPos1.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].direction"), dir1.x, dir1.y, dir1.z);
		// --- LUZ 1 (Morada Neón) ---
		/*glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].diffuse"), 5.0f, 0.5f, 6.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].specular"), 5.0f, 0.5f, 6.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].ambient"), 5.0f, 0.5f, 6.0f);*/
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].linear"), 0.14f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].quadratic"), 0.07f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].cutOff"), glm::cos(glm::radians(30.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].outerCutOff"), glm::cos(glm::radians(35.0f)));

		// --- LUZ 2 (Índice 1 - Simétrica) ---
		glm::vec3 lightPos2 = glm::vec3(-1.0f, 0.0f, 2.5f);
		glm::vec3 target2 = glm::vec3(3.0f, 0.0f, -1.5f);
		glm::vec3 dir2 = glm::normalize(target2 - lightPos2);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].position"), lightPos2.x, lightPos2.y, lightPos2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].direction"), dir2.x, dir2.y, dir2.z);
		// --- LUZ 2 (Azul Neón) ---
		/*glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].diffuse"), 0.0f, 3.0f, 6.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].specular"), 0.0f, 3.0f, 6.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].ambient"), 0.0f, 3.0f, 6.0f);*/
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].linear"), 0.14f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].quadratic"), 0.07f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].cutOff"), glm::cos(glm::radians(30.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].outerCutOff"), glm::cos(glm::radians(35.0f)));


		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 16.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model(1);
		////Carga de modelo 
        view = camera.GetViewMatrix();	
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);

		model = glm::mat4(1);
		//glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
	    Dog.Draw(lightingShader);
		//glDisable(GL_BLEND);  //Desactiva el canal alfa 

		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		
		// Draw the light object (using light's vertex attributes)
		for (GLuint i = 0; i < 1; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, lightPos);
			//model = glm::scale(model, glm::vec3(0.09f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();

	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}