#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>
#include <sstream>
#include <list>
#include <memory>
#include <vector>


TEST_CASE("Euclidean Norm"){
	//https://edstem.org/au/courses/8629/discussion/924335
	//vectors of the norm will clealy be representable
	//this function works for the endless one
	auto const a = std::vector<double>{2.0, 2.0, 2.0, 2.0};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	CHECK(comp6771::euclidean_norm(a1) == 4);

	//if dimension is 0, norm will be 0
	auto const b = comp6771::euclidean_vector();
	CHECK(comp6771::euclidean_norm(b) == 0);
}

TEST_CASE("Euclidean vector unit"){
	auto const a = std::vector<double>{2.0, 2.0, 2.0, 2.0};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const b = std::vector<double>{0.5, 0.5, 0.5, 0.5};
	auto const b1 = comp6771::euclidean_vector(b.begin(), b.end());
	CHECK(comp6771::unit(a1) == b1);


	//CHECK FOR THE EXCEPTIONS
	auto const exp = comp6771::euclidean_vector(0);
	REQUIRE_THROWS_WITH(comp6771::unit(exp), "euclidean_vector with no dimensions does not have a unit vector");

	auto const exp1 = std::vector<double>{0, 0, 0, 0};
	auto const exp2 = comp6771::euclidean_vector(exp1.begin(), exp1.end());
	REQUIRE_THROWS_WITH(comp6771::unit(exp2), "euclidean_vector with zero euclidean normal does not have a unit vector");
}

TEST_CASE("Euclidean Vector dot product"){
	auto const a = std::vector<double>{2.0, 2.0, 2.0, 2.0};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const b = std::vector<double>{2.0, 2.0, 2.0, 2.0};
	auto const b1 = comp6771::euclidean_vector(b.begin(), b.end());

	CHECK(comp6771::dot(a1, b1) == 16);

	auto const c = std::vector<double>{1.0, 2.0, 3.0, 4.0};
	auto const c1 = comp6771::euclidean_vector(c.begin(), c.end());
	auto const d = std::vector<double>{4.0, 3.0, 2.0, 1.0};
	auto const d1 = comp6771::euclidean_vector(d.begin(), d.end());

	CHECK(comp6771::dot(c1, d1) == 20);

	//CHECK FOR THE EXCEPTIONS
	auto const exp1 = std::vector<double>{1.0, 2.0, 3.0, 4.0};
	auto const exp2 = comp6771::euclidean_vector(exp1.begin(), exp1.end());
	auto const exp3 = std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0};
	auto const exp4 = comp6771::euclidean_vector(exp3.begin(), exp3.end());

	REQUIRE_THROWS_WITH(comp6771::dot(exp2, exp4), "Dimensions of LHS(4) and RHS(5) do not match");

}