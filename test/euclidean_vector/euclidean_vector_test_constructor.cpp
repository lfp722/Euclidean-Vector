#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>
#include <sstream>
#include <list>
#include <memory>
#include <vector>

/*
CONSTRUCTOR
*/
TEST_CASE("Default Constructor") {
	auto const a = comp6771::euclidean_vector();
	CHECK(a.at(0) == 0.0);
	CHECK(a.dimensions() == 1);

	auto const b = comp6771::euclidean_vector();
	CHECK(b.at(0) == 0.0);
	CHECK(b.dimensions() == 1);
}

TEST_CASE("Single-argument Constructor"){
	auto const a = comp6771::euclidean_vector(1);
	CHECK(a.at(0) == 0);
	CHECK(a.dimensions() == 1);

	auto const b = comp6771::euclidean_vector(2);
	CHECK(b.at(1) == 0);
	CHECK(b.dimensions() == 2);

	auto const c = comp6771::euclidean_vector(3);
	CHECK(c.at(2) == 0);
	CHECK(c.dimensions() == 3);
}

TEST_CASE("Constructor given number of dimensions and magnitude"){
	auto const a = comp6771::euclidean_vector(1, 30.1);
	CHECK(a.at(0) == 30.1);
	CHECK(a.dimensions() == 1);

	auto const b = comp6771::euclidean_vector(5, 17.1);
	CHECK(b.at(2) == 17.1);
	CHECK(b.dimensions() == 5);

	auto const c = comp6771::euclidean_vector(17, 22.5);
	CHECK(c.at(3) == 22.5);
	CHECK(c.dimensions() == 17);
}

TEST_CASE("Constructor given iterator"){
	auto const a = std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	CHECK(a1.dimensions() == static_cast<int>(a.size()));
	CHECK(a1.at(0) == 1.0);
	CHECK(a1.at(2) == 3.0);

	auto const b = std::vector<double>{1.0, 3.0, 5.0, 7.0, 5.0, 11.4};
	auto const b1 = comp6771::euclidean_vector(b.begin(), b.end());
	CHECK(b1.dimensions() == static_cast<int>(b.size()));
	CHECK(b1.at(3) == 7.0);
	CHECK(b1.at(2) == 5.0);

	auto const c = std::vector<double>{11.0, 2.0, 3.0};
	auto const c1 = comp6771::euclidean_vector(c.begin(), c.end());
	CHECK(c1.dimensions() == static_cast<int>(c.size()));
	CHECK(c1.at(0) == 11.0);
	CHECK(c1.at(2) == 3.0);
}

TEST_CASE("Constructor given list"){
	auto const a = comp6771::euclidean_vector{3.0, 2.2, 5.3, 4.4, 5.7};
	CHECK(a.at(0) == 3.0);
	CHECK(a.at(3) == 4.4);

	auto const b = comp6771::euclidean_vector{11.0, 2.2, 5.3};
	CHECK(b.at(0) == 11.0);
	CHECK(b.at(2) == 5.3);

	auto const c = comp6771::euclidean_vector{3.0, 23.2, 4.3, 4.4, 5.7, 8.7};
	CHECK(c.at(1) == 23.2);
	CHECK(c.at(3) == 4.4);
}

TEST_CASE("Copy Constructor"){
	auto const a = std::vector<double>{3.01, 4.25, 4214, 421.32, 42.312, 5332563, 523.123, 23.524, 11};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const a2 = comp6771::euclidean_vector(a1);
	auto const a3 = comp6771::euclidean_vector(a2);

	CHECK(a1.dimensions() == static_cast<int>(a.size()));
	CHECK(a1.dimensions() == a2.dimensions());
	CHECK(a2.dimensions() == static_cast<int>(a.size()));
	CHECK(a3.dimensions() == a2.dimensions());
	CHECK(a3.dimensions() == static_cast<int>(a.size()));

	CHECK(a2.at(3) == 421.32);
	CHECK(a2.at(0) == 3.01);

	CHECK(a3.at(0) == 3.01);
	CHECK(a3.at(5) == 5332563);
}

TEST_CASE("Move Constructor"){
	auto const a = std::vector<double>{3.01, 4.25, 4214, 421.32, 42.312, 5332563, 523.123, 23.524, 11};
	auto a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const a2 = comp6771::euclidean_vector(std::move(a1));
	CHECK(a1.dimensions() == 0);
	CHECK(a2.dimensions() == 9);
}