//#include <catch2/catch_test_macros.hpp>
//#include <catch2/benchmark/catch_benchmark.hpp>
//
//#include <Shader.h>
//#include <Camera.h>
//#include <glm/gtx/transform.hpp>
//
//
//
////TEST_CASE("Shader", "[shader_read]") {
////    //REQUIRE(Shader("", "").__readShader("test.vert") != std::string(""));
////    /*BENCHMARK("Shader 20") {
////        return Shader("", "").__readShader("test.vert");
////    };*/
////
////}
//
//TEST_CASE("CAMERA", "[camera methods]")
//{
//	//REQUIRE(CameraBase().GetDeltaTime() == 0);
//
//	float fov = glm::radians(45.0f);
//	
//	unsigned int window_width = 800;
//	unsigned int  window_height = 600;
//
//	unsigned int* ptr_window_width = &window_width;
//	unsigned int* ptr_window_height = &window_height;
//
//	float near_plane = 0.1f;
//	float far_plane = 100.0f;
//	
//	glm::mat4 projection_1 = glm::perspective(
//		fov,
//		(float)(window_width / window_height),
//		near_plane,
//		far_plane
//	);
//
//	SECTION("Class method gets the same result") {
//		CameraBase cam_base(
//			glm::vec3(0.0f, 0.0f, -3.0f),
//			glm::vec3(0.0f, 0.0f, 0.0f),
//			glm::vec3(0.0f, 1.0f, 0.0f),
//			ptr_window_width,
//			ptr_window_height
//		);
//		
//		REQUIRE(cam_base.GetProjection() == projection_1);
//
//		window_width = 1920;
//		window_height = 1024;
//
//		glm::mat4 projection_2 = glm::perspective(
//			fov,
//			(float)(window_width / window_height),
//			near_plane,
//			far_plane
//		);
//
//		REQUIRE(cam_base.GetProjection() == projection_2);
//	}
//
//	
//	
//
//}


//TEST_CASE("Factorials are computed", "[factorial]") {
//    REQUIRE(Factorial(1) == 1);
//    REQUIRE(Factorial(2) == 2);
//    REQUIRE(Factorial(3) == 6);
//    REQUIRE(Factorial(10) == 3628800);
//}