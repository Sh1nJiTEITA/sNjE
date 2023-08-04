
#include "main.h"

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

unsigned int width = 800;
unsigned int height = 600;

float xpos = width/2;
float ypos = height/2;

FreeFlightCamera cam(
	glm::vec3(0.0f, 0.0f, -3.0f),
	glm::vec3(0.0f, 0.0f, -1.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	&width,
	&height
);

int main()
{
	try {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
		if (window == NULL)
		{
			throw LocalException("Failed to create GLFW window");
			return -1;
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw LocalException("Failed to initialize GLAD");
			return -1;
		}
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);


		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		Shader test_shader("test.vert", "test.frag");
		Shader lamp_shader("lamp.vert", "lamp.frag");


		// OpenGL Additional properties:
		glEnable(GL_DEPTH_TEST);


		std::vector<float> vertices = {
			 -0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
		};

		unsigned int VBO;

		// CUBE
		unsigned int cubeVAO;
		
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &VBO);

		
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		
		

		// LIGHT SOURCE
		unsigned int lampVAO;
		
		glGenVertexArrays(1, &lampVAO);
		
		glBindVertexArray(lampVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(1);


		cam.BindMousePos(&xpos, &ypos);

		while (!glfwWindowShouldClose(window))
		{
			processInput(window);
			
			cam.UpdateDeltaTime();
			

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Test
			//rot = glm::rotate(rot, (float)glfwGetTime(), glm::vec3(1.0f, 0.5f, 0.0f));
			


			
			// Start rendering
			
			// Lights
			glm::vec3 light_source_color = glm::vec3(1.0f, 1.0f, 1.0f);
			glm::vec3 cube_color = glm::vec3(0.5f, 0.5f, 0.5f);

			//float delta_time = glm::sin((float)glfwGetTime());

			light_source_color.r *= glm::sin((float)glfwGetTime());
			light_source_color.g *= glm::sin((float)glfwGetTime() + glm::radians(90.0f));
			light_source_color.b *= glm::sin((float)glfwGetTime() + glm::radians(180.0f));
			

			// CUBE
			glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::mat4 cubeModel = glm::translate(glm::mat4(1.0f), cubePos);

			test_shader.Use();

			test_shader.SetMat4("rot", cubeModel);
			test_shader.SetMat4("view", cam.GetView());
			test_shader.SetMat4("projection", cam.GetProjection());

			test_shader.SetVec3("light_color", light_source_color);
			test_shader.SetVec3("model_color", cube_color);

			glBindVertexArray(cubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

			// LIGHT_SOURCE
			glm::vec3 lightPos = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), lightPos);
			lightModel = glm::scale(lightModel, glm::vec3(0.2f, 0.2f, 0.2f));

			lamp_shader.Use();

			lamp_shader.SetMat4("rot", lightModel);
			lamp_shader.SetMat4("view", cam.GetView());
			lamp_shader.SetMat4("projection", cam.GetProjection());

			lamp_shader.SetVec3("light_color", light_source_color);

			glBindVertexArray(lampVAO);
			glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

			// End rendering

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}
	catch (const LocalException& error)
	{
		std::cout << error.what() << std::endl;
	}

	glfwTerminate();
	
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	xpos = static_cast<float>(xposIn);
	ypos = static_cast<float>(yposIn);

	cam.UpdateMouse();
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


	// Fre flight Cam
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.GoStraight();

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.GoBack();

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.GoLeft();

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.GoRight();

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cam.GoUp();

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cam.GoDown();

}