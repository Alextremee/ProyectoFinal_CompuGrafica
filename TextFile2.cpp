//Legasov
//Proyecto Final
//Fecha de entrega: 
//numeros de cuenta

#include <sstream>
#include <iomanip>


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
void Animation(float t);

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

float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};

//keyboard map
bool keys[1024];
bool firstMouse = true;

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame


// Variables de animación por keyframes
int animFrame,animFrame2,animFrame3 = 0;              // Índice del frame actual de la animación
float frameTimer = 0.0f;
float frameDuration = 0.05f;    // Duración de cada frame (ajústala para cambiar la velocidad)

// Parámetros de la animación de la pirámide en espiral
float radioEspiral = 6.0f;        // radio de la trayectoria
float velocidadAngular = 1.0f;    // velocidad de giro en la espiral
float velocidadAscenso = 0.5f;    // velocidad de ascenso
float velocidadRotacion = 60.0f;  // grados por segundo de rotación sobre su eje
float x = 0.0f;
float z = 0.0f;
float rotacionPropia = 0;
	// Control de estados
	int estadoPiramide = 0;    // 0: reposo, 1: subiendo, 2: bajando
	float tiempoInicioEstado = 0.0f;
	float altura = 0.0f;
	float alturaMaxima = 12.0f; // altura máxima que alcanzará
bool ufo_aux = false;

GLuint loadCubemap(std::vector<std::string> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (GLuint i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}
 
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
	Shader skyboxShader("Shader/skybox.vs", "Shader/skybox.frag");

	// Skybox VAO
	GLuint skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindVertexArray(0);

	// ------------------ Cargar cubemap ------------------
	std::vector<std::string> faces
	{
		/*"skybox/right.jpg",
		"skybox/left.jpg",
		"skybox/top.jpg",
		"skybox/bottom.jpg",
		"skybox/front.jpg",
		"skybox/back.jpg"*/

		"skybox/posx.jpg",
		"skybox/negx.jpg",
		"skybox/posy.jpg",
		"skybox/negy.jpg",
		"skybox/posz.jpg",
		"skybox/negz.jpg"
	};
	GLuint cubemapTexture = loadCubemap(faces); // Se llama solo 1 vez

	//Load Models
    /Model Dog((char)"Models/RedDog.obj");
	Model Piso((char*)"Models/piso.obj");
	Model lamp((char*)"Models/lamp/lamp.obj");*/

	Model Techo((char*)"Models/museo/techo.obj");
	Model Museo((char*)"Models/museo/museo.obj");
	//Model salaEgipcia((char*)"Models/salaEgipcia/salaEgipcia.obj");
	//Model EstatuaCentral((char*)"Models/estatuacentral/estatuacentral.obj");
	//Model salaCyber((char*)"Models/salaCyber/salaCyber.obj");
	//Model salaRomana((char*)"Models/salaRomana/salaRomana.obj");
	//Model salaNeon((char*)"Models/salaNeon/salaNeon.obj");
	//Model esfera((char*)"Models/salaNeon/esfera.obj");
	//Model piramide((char*)"Models/salaEgipcia/piramide.obj");

	/*std::vector<Model> robotFrames;
	for (int i = 0; i < 81; i++) {
		std::ostringstream ss;
		ss << "Models/salaNeon/robot/frame_" << std::setw(3) << std::setfill('0') << i << ".obj";
		robotFrames.push_back(Model((GLchar*)ss.str().c_str()));
	}

	std::vector<Model> alienFrames;
	for (int i = 0; i < 101; i++) {
		std::ostringstream ss;
		ss << "Models/salaEgipcia/ufo/frame_" << std::setw(3) << std::setfill('0') << i << ".obj";
		alienFrames.push_back(Model((GLchar*)ss.str().c_str()));
	}*/

	//std::vector<Model> lanzadorFrames;
	//for (int i = 0; i < 121; i++) {
	//	std::ostringstream ss;
	//	ss << "Models/salaRomana/lanzador2/frame_" << std::setw(3) << std::setfill('0') << i << ".obj";
	//	lanzadorFrames.push_back(Model((GLchar*)ss.str().c_str()));
	//}


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

	// Light attributes
	//glm::vec3 lightPos(0.0f, 0.0f, 0.0f); 
	glm::vec3 lightPos4(16.9f, 3.0f, 15.6f);
	glm::vec3 lightPos(-15.5f, 2.0f, -17.0f);

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
		//Animation();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//-------------------------------------------------------------------------------------------------------------------
								//************* DEFINICION DE FUENTES DE LUZ

		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();
		glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

		 //Luz direccional tipo sol
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

		//---------------------------LUZ UFO--------------------------------------------------
		if (estadoPiramide != 0) {
			// Color base tipo plasma azul
			glm::vec3 Light1 = glm::vec3(0.3f, 0.7f, 1.0f);
			// Pulso uniforme de intensidad (entre 0.6 y 1.0)
			float intensity = 0.6f + 0.4f * sin(glfwGetTime() * 3.0f);
			// Aplica el pulso al color
			glm::vec3 lightColor = Light1 * intensity;

			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"),
				lightPos.x, lightPos.y, lightPos.z);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"),
				lightColor.x * 0.4f, lightColor.y * 0.4f, lightColor.z * 0.4f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"),
				lightColor.x, lightColor.y, lightColor.z);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"),
				1.0f, 1.0f, 1.0f);

			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
			glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.0075f);

		}
		else {
			// Apaga la luz cuando la nave está inactiva (estado 0)
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
		}


		////---------------------------------------LUZ NEON------------------------------
		glm::vec3 lightColor;
		glm::vec3 Light1 = glm::vec3(1.0f, 0.85f, 0.7f); // Luz cálida
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);

		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), lightPos4.x, lightPos4.y, lightPos4.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), lightColor.x, lightColor.y, lightColor.z);
		/*glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.032f);*/
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.07f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.017f);


		//--- LUZ 1---
		/*glm::vec3 lightPos1 = glm::vec3(1.0f, 0.0f, 2.5f);
		glm::vec3 target1 = glm::vec3(-3.0f, 0.0f, -1.5f);
		glm::vec3 dir1 = glm::normalize(target1 - lightPos1);*/

		//// Nota cómo el nombre del uniform ahora incluye el índice "[0]"
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].position"), lightPos1.x, lightPos1.y, lightPos1.z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].direction"), dir1.x, dir1.y, dir1.z);

		//// --- LUZ 1 (Morada Neón) ---
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].diffuse"), 5.0f, 5.0f, 6.0f);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].specular"), 5.0f, 5.0f, 6.0f);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].ambient"), 5.0f, 5.0f, 6.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].constant"), 1.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].linear"), 0.14f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].quadratic"), 0.07f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].cutOff"), glm::cos(glm::radians(30.0f)));
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].outerCutOff"), glm::cos(glm::radians(35.0f)));

		// --- LUZ 2 (Índice 1 - Simétrica) ---
		//glm::vec3 lightPos2 = glm::vec3(-1.0f, 0.0f, 2.5f);
		//glm::vec3 target2 = glm::vec3(3.0f, 0.0f, -1.5f);
		//glm::vec3 dir2 = glm::normalize(target2 - lightPos2);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].position"), lightPos2.x, lightPos2.y, lightPos2.z);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].direction"), dir2.x, dir2.y, dir2.z);
		//// --- LUZ 2 (Azul Neón) ---
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].diffuse"), 0.0f, 3.0f, 6.0f);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].specular"), 0.0f, 3.0f, 6.0f);
		//glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].ambient"), 0.0f, 3.0f, 6.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].constant"), 1.0f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].linear"), 0.14f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].quadratic"), 0.07f);
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].cutOff"), glm::cos(glm::radians(30.0f)));
		//glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].outerCutOff"), glm::cos(glm::radians(35.0f)));

					//************* --- LUZ SPOTLIGHT (MONALISA) ---
		glm::vec3 lightPos1 = glm::vec3(-29.0f, 7.9f, -1.2f);  // más arriba 
		glm::vec3 target1 = glm::vec3(-28.0f, 4.0f, -1.2f);  // centrado en el cuadro
		glm::vec3 dir1 = glm::normalize(target1 - lightPos1);

		// Posición y dirección
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].position"), lightPos1.x, lightPos1.y, lightPos1.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].direction"), dir1.x, dir1.y, dir1.z);

		// --- COLOR (cálido, tipo luz halógena de galería) ---
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].ambient"), 1.05f, 1.04f, 1.03f);  // muy tenue
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].diffuse"), 1.9f, 1.8f, 1.6f);    // cálido
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[0].specular"), 1.0f, 0.9f, 0.7f);   // reflejo brillante

		// --- ATENUACIÓN (para simular foco de galería) ---
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].quadratic"), 0.032f);

		// --- ÁNGULO DEL CONO ---
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].cutOff"), glm::cos(glm::radians(20.0f)));   // 
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[0].outerCutOff"), glm::cos(glm::radians(25.0f))); // 

					// ***************--- LUZ SPOTLIGHT (DAVID) ---
		glm::vec3 lightPos2 = glm::vec3(29.0f, 7.9f, -1.2f);   // simétrica respecto al eje X
		glm::vec3 target2 = glm::vec3(28.0f, 4.0f, -1.2f);     // centrada igual que la otra
		glm::vec3 dir2 = glm::normalize(target2 - lightPos2);

		// Posición y dirección
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].position"), lightPos2.x, lightPos2.y, lightPos2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].direction"), dir2.x, dir2.y, dir2.z);

		// --- COLOR (igual al spotlight original) ---
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].ambient"), 1.05f, 1.04f, 1.03f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].diffuse"), 1.9f, 1.8f, 1.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[1].specular"), 1.0f, 0.9f, 0.7f);

		// --- ATENUACIÓN ---
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].quadratic"), 0.032f);

		// --- ÁNGULO DEL CONO ---
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].cutOff"), glm::cos(glm::radians(20.0f)));   // 
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[1].outerCutOff"), glm::cos(glm::radians(25.0f))); // 

					// ********** --- LUZ SPOTLIGHT Centro (mar de nubes) ---
		//glm::vec3 lightPos3 = glm::vec3(0.0f, 8.5f, -29.5f);   // frente al cuadro, centrada
		glm::vec3 lightPos3 = glm::vec3(0.0f, 7.9f, -29.5f);
		glm::vec3 target3 = glm::vec3(0.0f, 4.0f, -28.5f);      // apunta al cuadro central
		glm::vec3 dir3 = glm::normalize(target3 - lightPos3);

		// Posición y dirección
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[2].position"), lightPos3.x, lightPos3.y, lightPos3.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[2].direction"), dir3.x, dir3.y, dir3.z);

		// --- COLOR (mismo tono cálido de galería) ---
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[2].ambient"), 1.05f, 1.04f, 1.03f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[2].diffuse"), 1.9f, 1.8f, 1.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLights[2].specular"), 1.0f, 0.9f, 0.7f);

		// --- ATENUACIÓN ---
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[2].linear"), 0.09f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[2].quadratic"), 0.032f);

		// --- ÁNGULO DEL CONO ---
		/*glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[2].cutOff"), glm::cos(glm::radians(19.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[2].outerCutOff"), glm::cos(glm::radians(22.0f)));*/
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[2].cutOff"), glm::cos(glm::radians(20.0f)));   // 
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLights[2].outerCutOff"), glm::cos(glm::radians(25.0f))); // 
		
		//---------------------------------------------------------++++++++++++++++++++++++++++++++++++++++
													//DIBUJO DE MODELOS
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

		//// Ya con todos los modelos cargados:
		//frameTimer += deltaTime;
		//if (frameTimer >= frameDuration) {
		//	frameTimer = 0.0f;

		//	/*if (!robotFrames.empty())
		//		animFrame = (animFrame + 1) % static_cast<int>(robotFrames.size());

		//	if (!alienFrames.empty())
		//		animFrame2 = (animFrame2 + 1) % static_cast<int>(alienFrames.size());*/

		//	//if (!lanzadorFrames.empty())
		//	//	animFrame3 = (animFrame3 + 1) % static_cast<int>(lanzadorFrames.size());
		//}


		glm::mat4 model = glm::mat4(1.0f); // Matriz identidad
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f)); // Escalar a la mitad		
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Museo.Draw(lightingShader);

		//model = glm::mat4(1.0f); // Matriz identidad
		//model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f)); // Escalar a la mitad		
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//salaEgipcia.Draw(lightingShader);

		//model = glm::mat4(1.0f); // Matriz identidad
		//model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f)); // Escalar a la mitad		
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//EstatuaCentral.Draw(lightingShader);

		//model = glm::mat4(1.0f); // Matriz identidad
		//model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f)); // Escalar a la mitad		
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//salaRomana.Draw(lightingShader);

		//model = glm::mat4(1.0f); // Matriz identidad
		//model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f)); // Escalar a la mitad		
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//salaNeon.Draw(lightingShader);

		//// Dibujar el robot animado
		//model = glm::mat4(1.0f); // Matriz identidad
		//model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f)); // Escalar a la mitad		
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//robotFrames[animFrame].Draw(lightingShader);

		//// Dibujar el lanzador romano animado
		//model = glm::mat4(1.0f); // Matriz identidad
		//model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f)); // Escalar a la mitad		
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//lanzadorFrames[animFrame3].Draw(lightingShader);

		//if (animFrame2 >= static_cast<int>(alienFrames.size()) - 1) {
		//	ufo_aux = false;
		//}
		//if (estadoPiramide == 3 && ufo_aux) {
		//	model = glm::mat4(1.0f); // Matriz identidad
		//	model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f)); // Escalar a la mitad		
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//	alienFrames[animFrame2].Draw(lightingShader);
		//}
		//else {
		//	model = glm::mat4(1.0f);
		//	model = glm::scale(model, glm::vec3(0.25f));
		//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//	glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//	alienFrames[0].Draw(lightingShader);
		//}

		//model = glm::mat4(1.0f); // Matriz identidad
		//model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f)); // Escalar a la mitad		
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//salaCyber.Draw(lightingShader);

		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(16.9f, 3.0f, 15.6f)); 
		//model = glm::rotate(model, glm::radians(45.0f) * currentFrame, glm::vec3(0.0f, 1.0f, 0.0f));  
		//model = glm::scale(model, glm::vec3(0.25f));  
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//esfera.Draw(lightingShader);

		//// ---------------------- PIRÁMIDE EN ESPIRAL ----------------------
		//float t = glfwGetTime(); // tiempo global en segundos
		//Animation(t);

		//// Si han pasado 10 segundos y está en reposo, pasa al estado de ascenso
		//if (estadoPiramide == 0 && t - tiempoInicioEstado >= 10.0f) {
		//	estadoPiramide = 1;
		//	tiempoInicioEstado = t;
		//}

		//if (estadoPiramide == 2 || estadoPiramide == 3) {
		//	rotacionPropia = velocidadRotacion * t;
		//	x = radioEspiral * cos(velocidadAngular * t);
		//	z = radioEspiral * sin(velocidadAngular * t);
		//}

		//model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(-15.5, 0, -17)); // posición base
		//model = glm::translate(model, glm::vec3(x, altura, z));
		//model = glm::rotate(model, glm::radians(rotacionPropia), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.25f));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//piramide.Draw(lightingShader);

		//model = glm::mat4(1.0f); // Matriz identidad
		//model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f)); // Escalar a la mitad
		//glEnable(GL_BLEND); // Activar canal alfa
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		//Techo.Draw(lightingShader);
		//glDisable(GL_BLEND);


		glDepthFunc(GL_LEQUAL);  // Cambiar la función de profundidad
		skyboxShader.Use();
		glm::mat4 viewSky = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remover translación
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(viewSky));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // Restaurar función de profundidad

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
		for (GLuint i = 1; i < 2; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, lightPos4);
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

void Animation(float t) {
	switch (estadoPiramide) {
	case 0:
		altura = 0.0f;
		break;
	
	case 1:
		rotacionPropia = velocidadRotacion * t;
		altura += 0.5f * deltaTime;
		if (altura >= 5) {
			estadoPiramide = 2;          // pasa al siguiente estado (espiral)
			tiempoInicioEstado = t;
		}
		break;

	case 2:
		// SUBIENDO
		altura += 0.5f * deltaTime;
		if (altura >= alturaMaxima) {
			altura = alturaMaxima;
			estadoPiramide = 3;
			tiempoInicioEstado = t;

			//Reiniciamos animación de alien al entrar al estado 3
			animFrame2 = 0;
			frameTimer = 0.0f;
			ufo_aux = true;
		}
		break;

	case 3:
		// BAJANDO
		altura -= 0.5f * deltaTime;
		if (altura <= 0.0f) {
			altura = 0.0f;
			estadoPiramide = 4; 
			tiempoInicioEstado = t;
		}

		break;

	case 4:
		// REGRESANDO AL ORIGEN (desde donde empezó su espiral)
	{
		// --- Regreso lineal al origen (sin espiral) ---
		float velocidadRegreso = 2.0f; // controla la velocidad del regreso

		// Movimiento lineal hacia el origen en X y Z
		if (x > 0.0f) x -= velocidadRegreso * deltaTime;
		else if (x < 0.0f) x += velocidadRegreso * deltaTime;

		if (z > 0.0f) z -= velocidadRegreso * deltaTime;
		else if (z < 0.0f) z += velocidadRegreso * deltaTime;

		// Evita que oscile al pasar por cero
		if (fabs(x) < 0.05f) x = 0.0f;
		if (fabs(z) < 0.05f) z = 0.0f;

		// Cuando llega al origen, vuelve al estado inicial
		if (x == 0.0f && z == 0.0f) {
			estadoPiramide = 0;
			tiempoInicioEstado = t;
		}
	}
	break;
	}

}
