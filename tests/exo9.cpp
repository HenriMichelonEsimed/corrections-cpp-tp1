#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

import exo9;
using namespace exo9;

TEST_CASE("Exo9_1", "[BinaryTree]") {
    auto tree = BinaryTree<std::string>{};
    
    auto vec_test = [&](std::vector<std::string> result, const std::uint64_t size) {
        std::vector<std::string> vec;
        tree.Traversal([&](const std::string& i) {
            vec.push_back(i);
            return false;
        });
        REQUIRE(vec == result);
        REQUIRE(tree.GetSize() == size);
    };

    vec_test({}, 0);
    REQUIRE_FALSE(tree.Contains("C++"));
    tree.Insert("C++");
    vec_test({"C++"}, 1);
    REQUIRE(tree.Contains("C++"));
    tree.Insert("ASM");
    vec_test({"ASM", "C++"}, 2);
    tree.Insert("GO");
    vec_test({"ASM", "C++", "GO"}, 3);
    REQUIRE_FALSE(tree.Contains("Rust"));
    tree.Insert("Rust");
    vec_test({"ASM", "C++", "GO", "Rust"}, 4);
    tree.Insert("JavaScript");
    vec_test({"ASM", "C++", "GO", "JavaScript", "Rust"}, 5);
    REQUIRE(tree.Contains("Rust"));
    REQUIRE(tree.Contains("C++"));
    REQUIRE(tree.Contains("JavaScript"));
    REQUIRE_FALSE(tree.Contains("C#"));
    tree.Clear();
    vec_test({}, 0);
}

TEST_CASE("Exo9_2", "[Map]") {
    auto map = Map<std::string, std::uint64_t>{};
    REQUIRE(map.GetSize() == 0);
    REQUIRE_FALSE(map.Contains("Jean"));
    map.Put("Jean", 18);
    REQUIRE(map.GetSize() == 1);
    REQUIRE(map.Contains("Jean"));
    map.Put("Georges", 20);
    REQUIRE(map.GetSize() == 2);
    REQUIRE(map.Contains("Jean"));
    REQUIRE(map.Contains("Georges"));
    REQUIRE_FALSE(map.Contains("Jeanne"));
    REQUIRE(map.Get("Jean") == 18);
    REQUIRE(map.Get("Georges") == 20);
    map.Put("Jean", 8);
    REQUIRE(map.Contains("Jean"));
    REQUIRE(map.Contains("Georges"));
    REQUIRE_FALSE(map.Contains("Jeanne"));
    REQUIRE(map.Get("Jean") == 8);
    REQUIRE(map.Get("Georges") == 20);
    map.Clear();
    REQUIRE(map.GetSize() == 0);
    REQUIRE_FALSE(map.Contains("Jean"));
}
