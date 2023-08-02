#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>

#include <Shader.h>


TEST_CASE("Shader", "[shader_read]") {
    REQUIRE(Shader("", "").__readShader("test.vert") != std::string(""));
    /*BENCHMARK("Shader 20") {
        return Shader("", "").__readShader("test.vert");
    };*/

}


//TEST_CASE("Factorials are computed", "[factorial]") {
//    REQUIRE(Factorial(1) == 1);
//    REQUIRE(Factorial(2) == 2);
//    REQUIRE(Factorial(3) == 6);
//    REQUIRE(Factorial(10) == 3628800);
//}