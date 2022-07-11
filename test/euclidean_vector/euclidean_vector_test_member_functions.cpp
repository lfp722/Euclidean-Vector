#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>
#include <sstream>
#include <list>
#include <memory>
#include <vector>


/*
Member function
*/

TEST_CASE("Euclidean vector.at(index) const"){
	auto const a = std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	CHECK(a1.at(0) == 1.0);
	CHECK(a1.at(2) == 3.0);

	//CHECK FOR THE EXCEPTIONS
	//x < 0
	REQUIRE_THROWS_WITH(a1.at(-1), "Index -1 is not valid for this euclidean_vector object");
	//x > number of dimensions
	REQUIRE_THROWS_WITH(a1.at(11), "Index 11 is not valid for this euclidean_vector object");
}

TEST_CASE("Euclidean vector.at()"){
	auto const a = std::vector<double>{1.0, 3.0, 5.0, 7.0, 5.0, 11.4};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	CHECK(a1.at(0) == 1.0);
	CHECK(a1.at(2) == 5.0);

	//CHECK FOR THE EXCEPTIONS
	//x < 0
	REQUIRE_THROWS_WITH(a1.at(-1), "Index -1 is not valid for this euclidean_vector object");
	//x > number of dimensions
	REQUIRE_THROWS_WITH(a1.at(11), "Index 11 is not valid for this euclidean_vector object");
}

TEST_CASE("Euclidean Vector.dimensions()"){
	auto const a = std::vector<double>{1.0, 3.0, 5.0, 7.0, 5.0, 11.4};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	CHECK(a1.dimensions() == 6);

	auto const b = std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0};
	auto const b1 = comp6771::euclidean_vector(b.begin(), b.end());
	CHECK(b1.dimensions() == 5);
}