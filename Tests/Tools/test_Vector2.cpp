#include <catch2/catch_all.hpp>
#include <Tools/Vector2.h>

TEST_CASE( "Vector2 Creation", "[Vector2]"){

    tools::Vector2I vector0;
    REQUIRE((vector0.x == 0 and vector0.y == 0));

    tools::Vector2I vector1(5, 6);
    REQUIRE((vector1.x == 5 and vector1.y == 6));

    tools::Vector2F vector2(5.5f, 6.6f);
    REQUIRE((vector2.x == 5.5f and vector2.y == 6.6f));

    tools::Vector2I vector3(vector2);
    REQUIRE((vector3.x == 5 and vector3.y == 6));
}

TEST_CASE( "Vector2 operations", "[Vector2]" ) {
    tools::Vector2I vector1 = {1, 2};
    tools::Vector2I vector2 = {2, 3};

    SECTION( "Comparing vectors" ) {
        REQUIRE(vector1 == vector1);
        REQUIRE(vector1 != vector2);

        vector1 = {2, 3,};
        REQUIRE(vector1 == vector2);
    }

    SECTION( "Adding/Subtracting vectors" ) {
        REQUIRE(vector1 + vector2 == tools::Vector2I(3, 5));
        vector2 = {-2, 3};

        REQUIRE(vector1 + vector2 == tools::Vector2I(-1, 5));

        vector1 += vector2;
        REQUIRE(vector1 == tools::Vector2I(-1, 5));

        vector1 -= vector2;
        REQUIRE(vector1 == tools::Vector2I(1, 2));

        REQUIRE(vector1 - vector2 == tools::Vector2I(3, -1));

        REQUIRE((vector1 -= vector2) == tools::Vector2I(3, -1));

        REQUIRE(-vector1 == tools::Vector2I(-3, 1));
    }

    SECTION("Multiplication/Division"){
        REQUIRE(vector1 * 2 == tools::Vector2I(2, 4));
        REQUIRE( 2 * vector1 == tools::Vector2I(2, 4));
        REQUIRE( (vector1 *= 2) == tools::Vector2I(2, 4));
        REQUIRE( (vector1 *= 5) == tools::Vector2I(10, 20));

        REQUIRE( (vector1 / 3) == tools::Vector2I(3, 6));
        REQUIRE( (vector1 / 7) == tools::Vector2I(1, 2));
        REQUIRE( (vector1 /= 7) == tools::Vector2I(1, 2));
    }
}