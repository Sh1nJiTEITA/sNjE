
#include "main.h"

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);


unsigned int width = 800;
unsigned int height = 600;

float xpos = width/2;
float ypos = height/2;

FreeFlightCamera cam(
	glm::vec3(0.0f, 0.0f, -3.0f),
	glm::vec3(0.0f, 0.0f, 1.0f),
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
		Shader test_shader("std_object.vert", "std_object.frag");
		Shader lamp_shader("lamp.vert", "lamp.frag");


		// OpenGL Additional properties:
		glEnable(GL_DEPTH_TEST);


		std::vector<float> vertices = {
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
		};

		unsigned int VBO;

		// CUBE
		unsigned int cubeVAO;
		
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &VBO);

		
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// LIGHT SOURCE
		unsigned int lampVAO;
		
		glGenVertexArrays(1, &lampVAO);
		
		glBindVertexArray(lampVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		unsigned int diffuseMap = loadTexture("textures/redstone_lamp_on.png");
		unsigned int specularMap = loadTexture("textures/redstone_lamp_on.png");
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(1);



		cam.BindMousePos(&xpos, &ypos);

		while (!glfwWindowShouldClose(window))
		{
			processInput(window);
			
			cam.UpdateDeltaTime();
			

			//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Test
			//rot = glm::rotate(rot, (float)glfwGetTime(), glm::vec3(1.0f, 0.5f, 0.0f));
			


			
			
			
		// Lights //
				
			// Cube Material //
			glm::vec3 emerald_ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f);
			glm::vec3 emerald_diffuse = glm::vec3(0.07568f, 0.61424, 0.07568);
			glm::vec3 emerald_specular = glm::vec3(0.633f, 0.727811f, 0.633f);
			float emerald_shininess = 0.6f * 128.0f;

			glm::vec3 black_plastic_ambient = glm::vec3(0.0f, 0.0f,	0.0f);
			glm::vec3 black_plastic_diffuse = glm::vec3(0.01f, 0.01f, 0.01f);
			glm::vec3 black_plastic_specular = glm::vec3(0.50f, 0.50f, 0.50f);
			float black_plastic_shininess = 0.25 * 128.0f;

			/*glm::vec3 emerald_ambient = glm::vec3(1.0f, 0.5f, 0.31f);
			glm::vec3 emerald_diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
			glm::vec3 emerald_specular = glm::vec3(0.5f, 0.5f, 0.5f);
			float emerald_shininess = 32.0f;*/


			// Light Source //
			glm::vec3 light_source_color = glm::vec3(1.0f, 1.0f, 1.0f);

			//light_source_color.r *= glm::sin((float)glfwGetTime());
			//light_source_color.g *= glm::sin((float)glfwGetTime() * 0.5f);
			//light_source_color.b *= glm::sin((float)glfwGetTime() * 0.2f);

			glm::vec3 light_ambient = light_source_color * glm::vec3(0.2f * 0.5f);
			glm::vec3 light_diffuse = light_source_color * glm::vec3(0.5f);
			glm::vec3 light_specular = glm::vec3(1.0f, 1.0f, 1.0f);

			// float delta_time = glm::sin((float)glfwGetTime());
			// Changes in light //
			
			
		// Positions //
			// Cube //
				
				
			glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::mat4 cubeModel = glm::translate(glm::mat4(1.0f), cubePos);

			// Light Source //
			float time_value = (float)glfwGetTime();
			float light_source_rotate_radius = 2.0f;
			glm::vec3 lightPos = light_source_rotate_radius * glm::vec3(
				-2,//glm::sin(time_value), 
				1, 
				-2//glm::cos(time_value)
			); 
				
			glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), lightPos);
			lightModel = glm::scale(lightModel, glm::vec3(0.2f, 0.2f, 0.2f));

		// Start rendering
			// CUBE //
			test_shader.Use();

			test_shader.SetMat4("rot", cubeModel);
			test_shader.SetMat4("view", cam.GetView());
			test_shader.SetMat4("projection", cam.GetProjection());

			//test_shader.SetVec3("light_color", light_source_color);
			// Material
				//test_shader.SetVec3("material.ambient", emerald_ambient);
				//test_shader.SetVec3("material.diffuse", emerald_diffuse);
				//test_shader.SetVec3("material.specular", emerald_specular);

				//test_shader.SetFloat("material.shininess", emerald_shininess);
			
			// Material + texture
			test_shader.SetVec3("material_tex.ambient", emerald_ambient);
			test_shader.SetInt("material_tex.diffuse", 0);
			test_shader.SetInt("material_tex.specular", 1);

			test_shader.SetFloat("material_tex.shininess", 64.0f);

			//// Light
			//test_shader.SetVec3("light.position", lightPos);

			//test_shader.SetVec3("light.ambient", light_ambient);
			//test_shader.SetVec3("light.diffuse", light_diffuse);
			//test_shader.SetVec3("light.specular", light_specular);
			//
			//// DLight
			//test_shader.SetVec3("Dlight.direction", -0.0f, -10.0f, -0.0f);
			//test_shader.SetVec3("Dlight.ambient", light_ambient);
			//test_shader.SetVec3("Dlight.diffuse", light_diffuse);
			//test_shader.SetVec3("Dlight.specular", light_specular);

			//// PLight
			//test_shader.SetVec3("Plight.position", lightPos);
			//test_shader.SetVec3("Plight.ambient", 0.2f, 0.2f, 0.2f);
			//test_shader.SetVec3("Plight.diffuse", 0.5f, 0.5f, 0.5f);
			//test_shader.SetVec3("Plight.specular", 1.0f, 1.0f, 1.0f);
			//test_shader.SetFloat("Plight.constant", 1.0f);
			//test_shader.SetFloat("Plight.linear", 0.09f);
			//test_shader.SetFloat("Plight.quadratic", 0.032f);
			glm::vec3 pointLightPositions[] = {
				glm::vec3(0.7f,  0.2f,  2.0f),
				glm::vec3(2.3f, -3.3f, -4.0f),
				glm::vec3(-4.0f,  2.0f, -12.0f),
				glm::vec3(0.0f,  0.0f, -3.0f)
			};


			test_shader.SetVec3("Dlight.direction", -0.2f, -1.0f, -0.3f);
			test_shader.SetVec3("Dlight.ambient", 0.05f, 0.05f, 0.05f);
			test_shader.SetVec3("Dlight.diffuse", 0.4f, 0.4f, 0.4f);
			test_shader.SetVec3("Dlight.specular", 0.5f, 0.5f, 0.5f);
			// point light 1
			test_shader.SetVec3("Plight[0].position", pointLightPositions[0]);
			test_shader.SetVec3("Plight[0].ambient", 0.05f, 0.05f, 0.05f);
			test_shader.SetVec3("Plight[0].diffuse", 0.8f, 0.8f, 0.8f);
			test_shader.SetVec3("Plight[0].specular", 1.0f, 1.0f, 1.0f);
			test_shader.SetFloat("Plight[0].constant", 1.0f);
			test_shader.SetFloat("Plight[0].linear", 0.09f);
			test_shader.SetFloat("Plight[0].quadratic", 0.032f);
			// point light 2
			test_shader.SetVec3("Plight[1].position", pointLightPositions[1]);
			test_shader.SetVec3("Plight[1].ambient", 0.05f, 0.05f, 0.05f);
			test_shader.SetVec3("Plight[1].diffuse", 0.8f, 0.8f, 0.8f);
			test_shader.SetVec3("Plight[1].specular", 1.0f, 1.0f, 1.0f);
			test_shader.SetFloat("Plight[1].constant", 1.0f);
			test_shader.SetFloat("Plight[1].linear", 0.09f);
			test_shader.SetFloat("Plight[1].quadratic", 0.032f);
			// point light 3
			test_shader.SetVec3("Plight[2].position", pointLightPositions[2]);
			test_shader.SetVec3("Plight[2].ambient", 0.05f, 0.05f, 0.05f);
			test_shader.SetVec3("Plight[2].diffuse", 0.8f, 0.8f, 0.8f);
			test_shader.SetVec3("Plight[2].specular", 1.0f, 1.0f, 1.0f);
			test_shader.SetFloat("Plight[2].constant", 1.0f);
			test_shader.SetFloat("Plight[2].linear", 0.09f);
			test_shader.SetFloat("Plight[2].quadratic", 0.032f);
			// point light 4
			test_shader.SetVec3("Plight[3].position", pointLightPositions[3]);
			test_shader.SetVec3("Plight[3].ambient", 0.05f, 0.05f, 0.05f);
			test_shader.SetVec3("Plight[3].diffuse", 0.8f, 0.8f, 0.8f);
			test_shader.SetVec3("Plight[3].specular", 1.0f, 1.0f, 1.0f);
			test_shader.SetFloat("Plight[3].constant", 1.0f);
			test_shader.SetFloat("Plight[3].linear", 0.09f);
			test_shader.SetFloat("Plight[3].quadratic", 0.032f);
			// Slight
			test_shader.SetVec3("Slight.position", cam.pos);
			test_shader.SetVec3("Slight.direction", cam.front);
			test_shader.SetVec3("Slight.ambient", 0.0f, 0.0f, 0.0f);
			test_shader.SetVec3("Slight.diffuse", 1.0f, 1.0f, 1.0f);
			test_shader.SetVec3("Slight.specular", 1.0f, 1.0f, 1.0f);
			test_shader.SetFloat("Slight.constant", 1.0f);
			test_shader.SetFloat("Slight.linear", 0.09f);
			test_shader.SetFloat("Slight.quadratic", 0.032f);
			test_shader.SetFloat("Slight.cut_off", glm::cos(glm::radians(12.5f)));
			test_shader.SetFloat("Slight.outer_cut_off", glm::cos(glm::radians(15.0f)));


			test_shader.SetVec3("view_pos", cam.pos);
			
			
			glActiveTexture(GL_TEXTURE0); // Activate texture
			glBindTexture(GL_TEXTURE_2D, diffuseMap);

			glActiveTexture(GL_TEXTURE1); // Activate texture
			glBindTexture(GL_TEXTURE_2D, specularMap);

			std::vector<glm::vec3> cubs_pos = {
				glm::vec3(0.0f,  0.0f,  0.0f),
				glm::vec3(2.0f,  5.0f, -15.0f),
				glm::vec3(-1.5f, -2.2f, -2.5f),
				glm::vec3(-3.8f, -2.0f, -12.3f),
				glm::vec3(2.4f, -0.4f, -3.5f),
				glm::vec3(-1.7f,  3.0f, -7.5f),
				glm::vec3(1.3f, -2.0f, -2.5f),
				glm::vec3(1.5f,  2.0f, -2.5f),
				glm::vec3(1.5f,  0.2f, -1.5f),
				glm::vec3(-1.3f,  1.0f, -1.5f)
			};

			
			for (int i = 0; i < cubs_pos.size(); ++i)
			{
				glm::mat4 single_pos_mat = glm::mat4(1.0f);
				single_pos_mat = glm::translate(single_pos_mat, cubs_pos[i]);

				glm::vec3 roti = glm::vec3(1.0f, 0.3f, 0.5f);

				single_pos_mat = glm::rotate(single_pos_mat, glm::radians(i * 30.0f), roti);

				test_shader.SetMat4("rot", single_pos_mat);


				glBindVertexArray(cubeVAO);
				glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 8);
			}

			

			// PLATFORM

			/*glm::vec3 platform_pos = glm::vec3(0.0f, -0.7f, 0.0f);
			glm::mat4 platform_model = glm::mat4(1.0f);
			glm::vec3 platform_color = glm::vec3(0.3f, 0.3f, 0.3f);
			
			platform_model = glm::scale(platform_model, glm::vec3(10.0f, 10.0f, 10.0f));
			platform_model = glm::translate(platform_model, platform_pos);


			test_shader.SetVec3("model_color", platform_color);

			test_shader.SetMat4("rot", platform_model);
			glBindVertexArray(cubeVAO);
			glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 8);*/

			// LIGHT_SOURCE
			lamp_shader.Use();

			
			lamp_shader.SetMat4("view", cam.GetView());
			lamp_shader.SetMat4("projection", cam.GetProjection());

			lamp_shader.SetVec3("light_color", light_source_color);

			for (int i = 0; i < 4; ++i)
			{
				glm::mat4 local_light_model = glm::translate(glm::mat4(1.0f), pointLightPositions[i]);
				local_light_model = glm::scale(local_light_model, glm::vec3(0.2f, 0.2f, 0.2f));

				lamp_shader.SetMat4("rot", local_light_model);
				glBindVertexArray(lampVAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

			

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

unsigned int loadTexture(const char* path)
{
	unsigned int texture_id;
	glGenTextures(1, &texture_id);

	int t_width, t_height, nr_components;
	unsigned char* data = stbi_load(path, &t_width, &t_height, &nr_components, 0);

	if (data)
	{
		GLenum format;
		if (nr_components == 1)
			format = GL_RED;
		else if (nr_components == 3)
			format = GL_RGB;
		else if (nr_components == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, t_width, t_height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(data);

	}
	else
	{
		throw LocalException("Smt in loading texture");
		stbi_image_free(data);
	}
	return texture_id;
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