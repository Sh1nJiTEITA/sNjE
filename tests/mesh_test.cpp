#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>


#include <snjVertex.h>
#include <snjMesh.h>
#include <Camera.h>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <assimp/vector3.h>
#include <GLFW/glfw3.h>


TEST_CASE("snjVertex.h", "[snjVertex]")
{

	SECTION("snjVertexr")
	{
		REQUIRE(std::isnan(snjVertexr().x));
		REQUIRE(std::isnan(snjVertexr().y));
		REQUIRE(std::isnan(snjVertexr().z));
		REQUIRE(std::isnan(snjVertexr().nx));
		REQUIRE(std::isnan(snjVertexr().ny));
		REQUIRE(std::isnan(snjVertexr().nz));
		REQUIRE(std::isnan(snjVertexr().s));
		REQUIRE(std::isnan(snjVertexr().t));

		snjVertexr vertex_1(10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f);

		REQUIRE(vertex_1.x == 10.0f);
		REQUIRE(vertex_1.y == 20.0f);
		REQUIRE(vertex_1.z == 30.0f);
		REQUIRE(vertex_1.nx == 40.0f);
		REQUIRE(vertex_1.ny == 50.0f);
		REQUIRE(vertex_1.nz == 60.0f);
		REQUIRE(vertex_1.s == 70.0f);
		REQUIRE(vertex_1.t == 80.0f);

		glm::vec3 pos = glm::vec3(10.0f, 20.0f, 30.0f);
		glm::vec3 norm = glm::vec3(40.0f, 50.0f, 60.0f);
		glm::vec2 tcoo = glm::vec2(70.0f, 80.0f);

		snjVertexr vertex_2(pos, norm, tcoo);

		REQUIRE(vertex_2.x == 10.0f);
		REQUIRE(vertex_2.y == 20.0f);
		REQUIRE(vertex_2.z == 30.0f);
		REQUIRE(vertex_2.nx == 40.0f);
		REQUIRE(vertex_2.ny == 50.0f);
		REQUIRE(vertex_2.nz == 60.0f);
		REQUIRE(vertex_2.s == 70.0f);
		REQUIRE(vertex_2.t == 80.0f);

		vertex_2.x = 44.0f;

		REQUIRE(vertex_2.x == 44.0f);
		REQUIRE(vertex_2.y == 20.0f);
		REQUIRE(vertex_2.z == 30.0f);
		REQUIRE(vertex_2.nx == 40.0f);
		REQUIRE(vertex_2.ny == 50.0f);
		REQUIRE(vertex_2.nz == 60.0f);
		REQUIRE(vertex_2.s == 70.0f);
		REQUIRE(vertex_2.t == 80.0f);



		snjVertexr vertex_3(
			glm::vec3(SNJ_NAN, 3.0f, 10.0f),
			glm::vec3(20.0f, SNJ_NAN, 332.0f),
			glm::vec2(10.0f, SNJ_NAN)
		);

		REQUIRE(vertex_3.CalcStride() == 0);

		REQUIRE(vertex_3.isPos() == false);
		REQUIRE(vertex_3.isNorm() == false);
		REQUIRE(vertex_3.isTex() == false);

		vertex_3.x = 323.0f;
		vertex_3.ny = 20.0f;
		vertex_3.t = 10.0f;

		REQUIRE(vertex_3.CalcStride() == 8);

		REQUIRE(vertex_3.isPos() == true);
		REQUIRE(vertex_3.isNorm() == true);
		REQUIRE(vertex_3.isTex() == true);

		/*REQUIRE(sizeof(snjVertexr) ==
			(
				sizeof(glm::vec3) * 2 +
				sizeof(glm::vec2) +
				sizeof(float&) * 8
			)
		);*/

		struct sss {
			glm::vec3 a;
			glm::vec3 b;
			glm::vec3 c;

			float& x;
			float& y;
			float& z;

			float& nx;
			float& ny;
			float& nz;

			float& s;
			float& t;
		};

		REQUIRE(sizeof(sss) == (sizeof(glm::vec3) * 3) + (sizeof(float&) * 8 * 2) + 4);
	}

	SECTION("snjVertex") {
		REQUIRE(std::isnan(snjVertex().pos.x));
		REQUIRE(std::isnan(snjVertex().pos.y));
		REQUIRE(std::isnan(snjVertex().pos.z));
		REQUIRE(std::isnan(snjVertex().nor.x));
		REQUIRE(std::isnan(snjVertex().nor.x));
		REQUIRE(std::isnan(snjVertex().nor.x));
		REQUIRE(std::isnan(snjVertex().tex.s));
		REQUIRE(std::isnan(snjVertex().tex.t));

		snjVertex vertex_11(10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f);

		REQUIRE(vertex_11.pos.x == 10.0f);
		REQUIRE(vertex_11.pos.y == 20.0f);
		REQUIRE(vertex_11.pos.z == 30.0f);
		REQUIRE(vertex_11.nor.x == 40.0f);
		REQUIRE(vertex_11.nor.y == 50.0f);
		REQUIRE(vertex_11.nor.z == 60.0f);
		REQUIRE(vertex_11.tex.s == 70.0f);
		REQUIRE(vertex_11.tex.t == 80.0f);

		glm::vec3 pos1 = glm::vec3(10.0f, 20.0f, 30.0f);
		glm::vec3 norm1 = glm::vec3(40.0f, 50.0f, 60.0f);
		glm::vec2 tcoo1 = glm::vec2(70.0f, 80.0f);

		snjVertex vertex_22(pos1, norm1, tcoo1);

		REQUIRE(vertex_22.pos.x == 10.0f);
		REQUIRE(vertex_22.pos.y == 20.0f);
		REQUIRE(vertex_22.pos.z == 30.0f);
		REQUIRE(vertex_22.nor.x == 40.0f);
		REQUIRE(vertex_22.nor.y == 50.0f);
		REQUIRE(vertex_22.nor.z == 60.0f);
		REQUIRE(vertex_22.tex.s == 70.0f);
		REQUIRE(vertex_22.tex.t == 80.0f);

		vertex_22.pos.x = 44.0f;

		REQUIRE(vertex_22.pos.x == 44.0f);
		REQUIRE(vertex_22.pos.y == 20.0f);
		REQUIRE(vertex_22.pos.z == 30.0f);
		REQUIRE(vertex_22.nor.x == 40.0f);
		REQUIRE(vertex_22.nor.y == 50.0f);
		REQUIRE(vertex_22.nor.z == 60.0f);
		REQUIRE(vertex_22.tex.s == 70.0f);
		REQUIRE(vertex_22.tex.t == 80.0f);



		snjVertex vertex_33(
			glm::vec3(SNJ_NAN, 3.0f, 10.0f),
			glm::vec3(20.0f, SNJ_NAN, 332.0f),
			glm::vec2(10.0f, SNJ_NAN)
		);

		REQUIRE(vertex_33.CalcStride() == 0);

		REQUIRE(vertex_33.isPos() == false);
		REQUIRE(vertex_33.isNorm() == false);
		REQUIRE(vertex_33.isTex() == false);

		vertex_33.pos.x = 323.0f;
		vertex_33.nor.y = 20.0f;
		vertex_33.tex.t = 10.0f;

		REQUIRE(vertex_33.CalcStride() == 8);

		REQUIRE(vertex_33.isPos() == true);
		REQUIRE(vertex_33.isNorm() == true);
		REQUIRE(vertex_33.isTex() == true);

		REQUIRE(sizeof(snjVertex) == sizeof(glm::vec3) * 2 + sizeof(glm::vec2));
	}
}


void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void processInput(GLFWwindow* window);

unsigned int width = 800;
unsigned int height = 600;

bool first_mouse = true;

bool isCursor = false;

float xpos;
float ypos;

FreeFlightCamera cam(
	glm::vec3(0.0f, 0.0f, -3.0f),
	glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(0.0f, 1.0f, 0.0f),
	&width,
	&height
);


TEST_CASE("Mesh")
{
	std::vector<float> raw_vertices = {
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


	std::vector<unsigned int> indices = {
		0,1,2,
		3,4,5,
		6,7,8,
		9,10,11,
		12,13,14,
		15,16,17,
		18,19,20,
		21,22,23,
		24,25,26,
		27,28,29,
		30,31,32,
		33,34,35
	};

	std::vector<snjVertex> vertices;

	for (int i = 0; i < raw_vertices.size(); i += 8)
	{
		snjVertex vert(
			raw_vertices[i],
			raw_vertices[i + 1],
			raw_vertices[i + 2],

			raw_vertices[i + 3],
			raw_vertices[i + 4],
			raw_vertices[i + 5],

			raw_vertices[i + 6],
			raw_vertices[i + 7]
		);

		vertices.push_back(vert);
	}

	/*for (auto& it : vertices)
	{
		std::cout << it << std::endl;
	}*/

	std::vector<snjTexture> textures = {
		snjTexture("FDSFSDFSDF", SNJ_DIFFUSE_TEXTURE),
		snjTexture("240318i94", SNJ_DIFFUSE_TEXTURE),
		snjTexture("gdfg1239", SNJ_SPECULAR_TEXTURE),
		snjTexture("2313123123", SNJ_SPECULAR_TEXTURE)
	};

	

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		throw LocalException("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw LocalException("Failed to initialize GLAD");
	}

	snjMesh mesh_1(vertices, indices, textures);
	
	Shader shader_1("test_shader.vert", "test_shader.frag");

	

	

	cam.BindMousePos(&xpos, &ypos);
	
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		cam.UpdateDeltaTime();
		

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		mesh_1.draw(shader_1);

		shader_1.SetModel(glm::mat4(1.0f));
		shader_1.SetProjection(cam.GetProjection());
		shader_1.SetView(cam.GetView());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}




}










void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		if (isCursor)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			isCursor = false;
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			isCursor = true;
		}
	}
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
};

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	xpos = static_cast<float>(xposIn);
	ypos = static_cast<float>(yposIn);

	if (first_mouse)
	{
		first_mouse = false;

		xpos = static_cast<float>(xposIn);
		ypos = static_cast<float>(yposIn);
		return;
	}

	cam.UpdateMouse();
}
