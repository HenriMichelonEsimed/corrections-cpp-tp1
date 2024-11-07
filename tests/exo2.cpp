#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

import exo2;
using namespace exo2;

TEST_CASE("Exo2", "[Vector]") {
    auto v1 = Vector{12.34, 34.56, 56.78};
    REQUIRE(v1.ToString() == "(12.34,34.56,56.78)");
    const auto v2 = Vector{1.1, 2.2, 3.3};
    v1.Sum1(v2);
    REQUIRE(v1.ToString() == "(13.44,36.76,60.08)");
    v1.Sum2(v2);
    REQUIRE(v1.ToString() == "(14.54,38.96,63.38)");
}
