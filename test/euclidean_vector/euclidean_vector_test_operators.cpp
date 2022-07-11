#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>
#include <sstream>
#include <list>
#include <memory>
#include <vector>


/*
Operations
*/

TEST_CASE("Copy Assignment"){
	auto const a = std::vector<double>{3.01, 4.25, 4214, 421.32, 42.312, 5332563, 523.123, 23.524, 11};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const a2 = a1;

	CHECK(a1.dimensions() == a2.dimensions());
	CHECK(a1.at(3) == a2.at(3));
	CHECK(a1.at(5) == a2.at(5));

	auto const b = std::vector<double>{2.51, 42.5, 323.52, 421.3, 4214};
	auto const b1 = comp6771::euclidean_vector(b.begin(), b.end());
	auto const b2 = b1;

	CHECK(b1.dimensions() == b2.dimensions());
	CHECK(b1.at(0) == b2.at(0));
	CHECK(b1.at(3) == b2.at(3));
}

TEST_CASE("Move Assignment"){
	auto const a = std::vector<double>{3.01, 4.25, 4214, 421.32, 42.312, 5332563, 523.123, 23.524, 11};
	auto a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const a2 = std::move(a1);

	CHECK(a1.dimensions() == 0);
	CHECK(a2.dimensions() == 9);
	CHECK(a2.at(0) == 3.01);
	CHECK(a2.at(1) == 4.25);

	auto const b = std::vector<double>{2.51, 42.5, 323.52, 421.3, 4214};
	auto b1 = comp6771::euclidean_vector(b.begin(), b.end());
	auto const b2 = std::move(b1);

	CHECK(b1.dimensions() == 0);
	CHECK(b2.dimensions() == 5);
	CHECK(b2.at(0) == 2.51);
	CHECK(b2.at(3) == 421.3);
}

TEST_CASE("Subscript"){
	auto const a = std::vector<double>{3.01, 4.25, 4214, 421.32, 42.312, 5332563, 523.123, 23.524, 11};
	auto a1 = comp6771::euclidean_vector(a.begin(), a.end());
	for (auto i = 0; i < static_cast<int>(a.size()); ++i){
		a1[i] = i;
	}
	for (auto j = 0; j < static_cast<int>(a.size()); ++j){
		a1[j] = j;
	}

	auto const b = std::vector<double>{2.51, 42.5, 323.52, 421.3, 4214};
	auto b1 = comp6771::euclidean_vector(b.begin(), b.end());
	b1[0] = 3.1;
	b1[4] = 321;
	CHECK(b1.at(0) == 3.1);
	CHECK(b1.at(4) == 321);
}

TEST_CASE("Unary plus"){
	auto const a = std::vector<double>{3.01, 4.25, 4214, 421.32, 42.312, 5332563, 523.123, 23.524, 11};
	auto a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto a2 = +a1;
	CHECK(a2.dimensions() == a1.dimensions());
	+a1;
	CHECK(a1.dimensions() == 9);


	auto const b = std::vector<double>{2.51, 42.5, 323.52, 421.3, 4214};
	auto b1 = comp6771::euclidean_vector(b.begin(), b.end());
	auto b2 = +b1;
	CHECK(b2.dimensions() == b2.dimensions());
	+b1;
	CHECK(b2.dimensions() == 5);
}

TEST_CASE("Negation"){
	auto const a = std::vector<double>{3.01, 4.25, 4214, 421.32, 42.312, 5332563, 523.123, 23.524, 11};
	auto a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto a2 = -a1;
	CHECK(a2.dimensions() == a1.dimensions());
	-a1;
	CHECK(a1.dimensions() == 9);
	for (auto i = 0; i < static_cast<int>(a.size()); ++i){
		CHECK(a1.at(i) == a.at(static_cast<std::size_t>(i)));
	}

	auto b = std::vector<double>{2.51, 42.5, 323.52, 421.3, 4214};
	auto b1 = comp6771::euclidean_vector(b.begin(), b.end());
	auto b2 = -b1;
	for (auto i = 0; i < static_cast<int>(b.size()); ++i){
		CHECK(b2.at(i) == -(b.at(static_cast<std::size_t>(i))));
	}
}

TEST_CASE("Compound Addition"){
	auto a = std::vector<double>{0.1, 0.2, 0.3};
	auto a1 = comp6771::euclidean_vector(a.begin(), a.end());

	auto b = std::vector<double>{0.1, 0.3, 0.4};
	auto b1 = comp6771::euclidean_vector(b.begin(), b.end());

	a1 += b1;
	CHECK (a1.at(0) == 0.2);
	CHECK (a1.at(1) == 0.5);
	CHECK (a1.at(2) == 0.7);

	//Testing for exceptions
	auto c = std::vector<double>{0.1, 0.1, 0.2, 0.3};
	auto c1 = comp6771::euclidean_vector(c.begin(), c.end());
	REQUIRE_THROWS_WITH(a1 += c1, "Dimensions of LHS(3) and RHS(4) do not match");
}

TEST_CASE("Compound Subtraction"){
	auto a = std::vector<double>{0.1, 0.5, 0.6};
	auto a1 = comp6771::euclidean_vector(a.begin(), a.end());

	auto b = std::vector<double>{0.1, 0.2, 0.3};
	auto b1 = comp6771::euclidean_vector(b.begin(), b.end());

	a1 -= b1;
	CHECK (a1.at(0) == 0.0);
	CHECK (a1.at(1) == 0.3);
	CHECK (a1.at(2) == 0.3);

	//Testing for exceptions
	auto c = std::vector<double>{0.1, 0.1, 0.2, 0.3};
	auto c1 = comp6771::euclidean_vector(c.begin(), c.end());
	REQUIRE_THROWS_WITH(a1 -= c1, "Dimensions of LHS(3) and RHS(4) do not match");
}

TEST_CASE("Compound Multiplication"){
	auto a = std::vector<double>{0.01, 0.5, 0.61};
	auto a1 = comp6771::euclidean_vector(a.begin(), a.end());
	a1 *= 3;
	CHECK(a1.at(0) == 0.03);
	CHECK(a1.at(1) == 1.5);
	CHECK(a1.at(2) == 1.83);
}

TEST_CASE("Compound Division"){
	auto a = std::vector<double>{0.1, 0.5, 0.61};
	auto a1 = comp6771::euclidean_vector(a.begin(), a.end());
	a1 /= 2;
	CHECK(a1.at(0) == 0.05);
	CHECK(a1.at(1) == 0.25);
	CHECK(a1.at(2) == 0.305);

	//Testing for exceptions
	REQUIRE_THROWS_WITH(a1/0, "Invalid vector division by 0");
}

TEST_CASE("Vector Type Conversion"){
	auto const a = std::vector<double>{3.01, 4.25, 4214, 421.32, 42.312, 5332563, 523.123, 23.524, 11};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const a2 = static_cast<std::vector<double>>(a1);

	for(auto i = 0; i < static_cast<int>(a.size()); ++i){
		CHECK(a1.at(i) == a2.at(static_cast<std::size_t>(i)));
	}

}

TEST_CASE("List Type Conversion"){
	auto const a = std::list<double>{3.01, 4.25, 4214, 421.32, 42.312, 5332563, 523.123, 23.524, 11};
	auto const a1 = comp6771::euclidean_vector{3.01, 4.25, 4214, 421.32, 42.312, 5332563, 523.123, 23.524, 11};
	auto a2 = static_cast<std::list<double>>(a1);

	for(auto i = 0; i < static_cast<int>(a.size()); ++i){
		CHECK(a1.at(i) == a2.front());
		a2.pop_front();
	}
}
