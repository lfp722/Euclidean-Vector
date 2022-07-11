#include <comp6771/euclidean_vector.hpp>

#include <catch2/catch.hpp>
#include <sstream>
#include <list>
#include <memory>
#include <vector>


/*
Friends
*/

TEST_CASE("Equal"){
	auto const a = std::vector<double>{3.01, 4.25, 4214, 421.32, 42.312, 5332563, 523.123, 23.524, 11};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const a2 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const a3 = comp6771::euclidean_vector();
	auto bool1 = (a1 == a2);
	//bool2 should return false
	auto bool2 = (a1 == a3);
	CHECK(bool1);
	CHECK(!bool2);

	auto const b = std::vector<double>{2.51, 42.5, 323.52, 421.3, 4214};
	auto const b1 = comp6771::euclidean_vector(b.begin(), b.end());
	auto const b2 = comp6771::euclidean_vector(b.begin(), b.end());
	auto bool3 = (b1 == b2);
	auto bool4 = (b1 == a3);
	CHECK(bool3);
	CHECK(!bool4);
}

TEST_CASE("Not Equal"){
	auto const a = std::vector<double>{3.01, 4.25, 4214, 421.32, 42.312, 5332563, 523.123, 23.524, 11};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const a2 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const a3 = comp6771::euclidean_vector();
	auto bool1 = (a1 != a2);
	auto bool2 = (a1 != a3);
	CHECK(!bool1);
	CHECK(bool2);

	auto const b = std::vector<double>{2.51, 42.5, 323.52, 421.3, 4214};
	auto const b1 = comp6771::euclidean_vector(b.begin(), b.end());
	auto const b2 = comp6771::euclidean_vector(b.begin(), b.end());
	auto bool3 = (b1 != b2);
	auto bool4 = (b1 != a3);
	CHECK(!bool3);
	CHECK(bool4);
}

TEST_CASE("Addition"){
	auto const a = std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0};
	auto const b = std::vector<double>{2.0, 3.0, 4.0, 5.0, 6.0};
	auto const c = std::vector<double>{3.0, 5.0, 7.0, 9.0, 11.0};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const b1 = comp6771::euclidean_vector(b.begin(), b.end());
	auto const c1 = comp6771::euclidean_vector(c.begin(), c.end());
	CHECK(c1 == a1+b1);

	auto const d = std::vector<double>{11.0, 22.0, 33.0, 44.0, 55.0};
	auto const e = std::vector<double>{22.0, 33.0, 44.0, 55.0, 66.0};
	auto const f = std::vector<double>{33.0, 55.0, 77.0, 99.0, 121.0};
	auto const d1 = comp6771::euclidean_vector(d.begin(), d.end());
	auto const e1 = comp6771::euclidean_vector(e.begin(), e.end());
	auto const f1 = comp6771::euclidean_vector(f.begin(), f.end());
	CHECK(f1 == d1+e1);

	//CHECK FOR THE EXCEPTIONS
	auto const exc = std::vector<double>{1.0, 2};
	auto const exc1 = comp6771::euclidean_vector(exc.begin(), exc.end());
	REQUIRE_THROWS_WITH(a1+exc1, "Dimensions of LHS(5) and RHS(2) do not match");
	REQUIRE_THROWS_WITH(d1+exc1, "Dimensions of LHS(5) and RHS(2) do not match");
}

TEST_CASE("Subtraction"){
	auto const a = std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0};
	auto const b = std::vector<double>{2.0, 3.0, 4.0, 5.0, 6.0};
	auto const c = std::vector<double>{1.0, 1.0, 1.0, 1.0, 1.0};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const b1 = comp6771::euclidean_vector(b.begin(), b.end());
	auto const c1 = comp6771::euclidean_vector(c.begin(), c.end());
	CHECK(c1 == b1-a1);

	auto const d = std::vector<double>{1.0, 2.0, 11, 23};
	auto const e = std::vector<double>{10.0, 12, 23.0, 44};
	auto const f = std::vector<double>{9, 10, 12, 21};
	auto const d1 = comp6771::euclidean_vector(d.begin(), d.end());
	auto const e1 = comp6771::euclidean_vector(e.begin(), e.end());
	auto const f1 = comp6771::euclidean_vector(f.begin(), f.end());
	CHECK(f1 == e1-d1);

	//CHECK FOR THE EXCEPTIONS
	auto const exc = std::vector<double>{1.0, 2};
	auto const exc1 = comp6771::euclidean_vector(exc.begin(), exc.end());
	REQUIRE_THROWS_WITH(a1-exc1, "Dimensions of LHS(5) and RHS(2) do not match");
	REQUIRE_THROWS_WITH(d1-exc1, "Dimensions of LHS(4) and RHS(2) do not match");
}

TEST_CASE("Multiply"){
	auto const a = std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const a2 = std::vector<double>{3, 6, 9, 12, 15};
	auto const a3 = comp6771::euclidean_vector(a2.begin(), a2.end());
	auto ret1 = a1 * 3;
	CHECK(ret1 == a3);

	auto const b = std::vector<double>{1.0, 2.0, 11, 23};
	auto const b1 = comp6771::euclidean_vector(b.begin(), b.end());
	auto const b2 = std::vector<double>{2, 4, 22, 46};
	auto const b3 = comp6771::euclidean_vector(b2.begin(), b2.end());
	auto ret2 = b1 * 2;
	CHECK(ret2 == b3);

	//scalar can be either side of vector
	auto ret3 = 3 * a1;
	auto ret4 = 2 * b1;

	CHECK(ret3 == a3);
	CHECK(ret4 == b3);
}

TEST_CASE("Divide"){
	auto const a = std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const b = std::vector<double>{0.5, 1.0, 1.5, 2.0, 2.5};
	auto const b1 = comp6771::euclidean_vector(b.begin(), b.end());
	CHECK(b1 == (a1/2));

	auto const c = std::vector<double>{1.0, 2.0, 11, 23};
	auto const c1 = comp6771::euclidean_vector(c.begin(), c.end());
	auto const d = std::vector<double>{0.2, 0.4, 2.2, 4.6};
	auto const d1 = comp6771::euclidean_vector(d.begin(), d.end());
	CHECK(d1 == (c1/5));

	//CHECK FOR THE EXCEPTIONS
	REQUIRE_THROWS_WITH(a1/0, "Invalid vector division by 0");
	REQUIRE_THROWS_WITH(c1/0, "Invalid vector division by 0");
}

TEST_CASE("Output Stream"){
	auto const a = std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0};
	auto const a1 = comp6771::euclidean_vector(a.begin(), a.end());
	auto const a2 = "[1 2 3 4 5]";
	auto a3 = std::stringstream();
	a3 << a1;
	CHECK(a2 == a3.str());

	auto const b = std::vector<double>{1.0, 2.0, 11, 23};
	auto const b1 = comp6771::euclidean_vector(b.begin(), b.end());
	auto const b2 = "[1 2 11 23]";
	auto b3 = std::stringstream();
	b3 << b1;
	CHECK(b2 == b3.str());
}
