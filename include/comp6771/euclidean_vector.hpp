#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what)
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// Constructors
		euclidean_vector();

		explicit euclidean_vector(int);

		euclidean_vector(int, double);

		euclidean_vector(std::vector<double>::const_iterator, std::vector<double>::const_iterator);

		euclidean_vector(std::initializer_list<double>);

		euclidean_vector(euclidean_vector const&);

		euclidean_vector(euclidean_vector&&);

		//Destructor

		auto operator=(euclidean_vector const&) -> euclidean_vector&;

		auto operator=(euclidean_vector&&) noexcept -> euclidean_vector&;

		auto operator[](int) const noexcept-> double;

		auto operator[](int) noexcept -> double&;

		auto operator+() const -> euclidean_vector;

		auto operator-() const -> euclidean_vector;

		auto operator+=(euclidean_vector const&) -> euclidean_vector&;

		auto operator-=(euclidean_vector const&) -> euclidean_vector&;

		auto operator*=(double) -> euclidean_vector&;

		auto operator/=(double) -> euclidean_vector&;

		explicit operator std::vector<double>() const;

		explicit operator std::list<double>() const;

		//Member functions
		auto at(int) const -> double;

		auto at(int) -> double&;

		auto dimensions() const noexcept -> int;

		friend auto operator==(euclidean_vector const&, euclidean_vector const&) -> bool;

		friend auto operator!=(euclidean_vector const&, euclidean_vector const&) -> bool;

		friend auto operator+(euclidean_vector const&, euclidean_vector const&) -> euclidean_vector;

		friend auto operator-(euclidean_vector const&, euclidean_vector const&) -> euclidean_vector;

		friend auto operator*(euclidean_vector const&, double) -> euclidean_vector;

		friend auto operator*(double, euclidean_vector const&) -> euclidean_vector;

		friend auto operator/(euclidean_vector const&, double) -> euclidean_vector;

		friend auto operator<<(std::ostream&, euclidean_vector const&) -> std::ostream&;
	private:
		// ass2 spec requires we use std::unique_ptr<double[]>
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitude_;
		int dimension_;
	};
	//Utiliyy functions
	auto euclidean_norm(euclidean_vector const& v) -> double;

	auto unit(euclidean_vector const& v) -> euclidean_vector;

	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;
} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
