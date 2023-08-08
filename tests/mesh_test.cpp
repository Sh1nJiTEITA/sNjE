#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>


#include <snjVertex.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <assimp/vector3.h>


TEST_CASE("snjVertex")
{

	REQUIRE(std::isnan(snjVertex().x));
	REQUIRE(std::isnan(snjVertex().y));
	REQUIRE(std::isnan(snjVertex().z));
	REQUIRE(std::isnan(snjVertex().nx));
	REQUIRE(std::isnan(snjVertex().ny));
	REQUIRE(std::isnan(snjVertex().nz));
	REQUIRE(std::isnan(snjVertex().s));
	REQUIRE(std::isnan(snjVertex().t));
	
	snjVertex vertex_1(10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f);

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
	
	snjVertex vertex_2(pos, norm, tcoo);

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



	snjVertex vertex_3(
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

	REQUIRE(sizeof(pos) == sizeof(float) * 3);

	std::cout << sizeof(vertex_1) << std::endl;
	std::cout << sizeof(vertex_2) << std::endl;
	std::cout << sizeof(snjVertex) << std::endl;
	REQUIRE(sizeof(vertex_1) == sizeof(float) * 8);


}