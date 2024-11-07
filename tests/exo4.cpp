#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

import exo4;
using namespace exo4;

TEST_CASE("Exo4", "[Shape]") {
    const auto circle = Circle{1.2};
    REQUIRE(std::format("{0:.2f}", circle.Perimeter()) == "7.54");
}
