#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>


#include <snjVertex.h>
#include <glm/vec3.hpp>
#include <assimp/vector3.h>


TEST_CASE("snjVertex")
{

	REQUIRE(std::isnan(snjVertex().x));
	REQUIRE(std::isnan(snjVertex().y));
	REQUIRE(std::isnan(snjVertex().z));

	snjVertex vertex_1(10.0f, 20.0f, 30.0f);

	REQUIRE(vertex_1.x == 10.0f);
	REQUIRE(vertex_1.y == 20.0f);
	REQUIRE(vertex_1.z == 30.0f);

	glm::vec3 vec = glm::vec3(10.0f, 20.0f, 30.0f);
	snjVertex vertex_2(vec);

	REQUIRE(vertex_2.x == 10.0f);
	REQUIRE(vertex_2.y == 20.0f);
	REQUIRE(vertex_2.z == 30.0f);

	vertex_2.x = 44.0f;

	REQUIRE(vertex_2.x == 44.0f);
	REQUIRE(vertex_2.y == 20.0f);
	REQUIRE(vertex_2.z == 30.0f);

	float x_1 = vertex_2.ptr_pack()[0];
	float y_1 = vertex_2.ptr_pack()[1];
	float z_1 = vertex_2.ptr_pack()[2];

	REQUIRE(vertex_2.x == x_1);
	REQUIRE(vertex_2.y == y_1);
	REQUIRE(vertex_2.z == z_1);

	REQUIRE(snjVertex().isFilled() == false);
	REQUIRE(vertex_1.isFilled() == true);

	vertex_1.y = SNJ_NAN;

	REQUIRE(vertex_1.isFilled() == false);
	
	aiVector3D aivec(10.0f, 20.0f, 30.0f);

	snjVertex vertex_3(aivec);

	REQUIRE(vertex_3.x == 10.0f);
	REQUIRE(vertex_3.y == 20.0f);
	REQUIRE(vertex_3.z == 30.0f);

}