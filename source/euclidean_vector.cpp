// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include <comp6771/euclidean_vector.hpp>
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>
#include <utility>
#include <iterator>
#include <list>
#include <experimental/iterator>

namespace comp6771 {
	// Implement solution here
	euclidean_vector::euclidean_vector(){
		this -> dimension_ = 1;
		this -> magnitude_ = std::make_unique<double[]>(1);
	}

	euclidean_vector::euclidean_vector(int dimensions){
		this -> dimension_ = dimensions;
		this -> magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(dimensions));
	}

	euclidean_vector::euclidean_vector(int dimensions, double value){
		this -> dimension_ = dimensions;
		this -> magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(dimensions));
		std::fill(this->magnitude_.get(), this->magnitude_.get() + dimensions, value);
	}

	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator begin, std::vector<double>::const_iterator end) {
		this -> dimension_ = static_cast<int>(end - begin);
		this -> magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(end-begin));
		std::copy_n(begin, this->dimension_, this->magnitude_.get());
	}

	euclidean_vector::euclidean_vector(std::initializer_list<double> list_){
		this -> dimension_ = static_cast<int>(list_.size());
		this -> magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(list_.size()));
		std::copy_n(list_.begin(), this->dimension_, this->magnitude_.get());
	}

	euclidean_vector::euclidean_vector(euclidean_vector const& prev) {
		this -> dimension_ = prev.dimension_;
		//this -> magnitude_ = prev.magnitude_;
		this->magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(prev.dimension_));
		std::copy_n(prev.magnitude_.get(), prev.dimension_, this->magnitude_.get());
	}


	euclidean_vector::euclidean_vector(euclidean_vector&& prev) {
		this -> dimension_ = std::exchange(prev.dimension_, 0);
		this -> magnitude_ = std::exchange(prev.magnitude_, nullptr);
	}

	//Destructor

	auto euclidean_vector::operator=(euclidean_vector const& prev) -> euclidean_vector&{
		auto ret = euclidean_vector(prev);
		std::swap(*this, ret);
		return *this;
	}

	auto euclidean_vector::operator=(euclidean_vector&& prev) noexcept -> euclidean_vector&{
		std::swap(*this, prev);
		prev.magnitude_.reset();
		prev.dimension_ = 0;
		return *this;
	}

	auto euclidean_vector::operator[](int index) const noexcept -> double {
		assert(0 <= index && index <= this->dimension_);
		return this->magnitude_[static_cast<std::size_t>(index)];
	}


	auto euclidean_vector::operator[](int index) noexcept -> double&{
		assert(0 <= index && index <= this->dimension_);
		return this -> magnitude_[static_cast<std::size_t>(index)];
	}

	auto euclidean_vector::operator+() const -> euclidean_vector{
		return *this;
	}

	auto euclidean_vector::operator-() const -> euclidean_vector{
		auto ret = euclidean_vector(*this);
		//std::transform(ret.magnitude_.get(), ret.magnitude_.get() + ret.dimension_.get(), ret.magnitude_.get(), std::negate<>());
		std::transform(ret.magnitude_.get(), ret.magnitude_.get() + ret.dimension_, ret.magnitude_.get(), std::negate<>());
		return ret;
	}

	auto euclidean_vector::operator+=(euclidean_vector const& given) -> euclidean_vector&{
		//check for the error
		if (this->dimension_ != given.dimension_){
			auto error_msg = "Dimensions of LHS(" + std::to_string(this->dimension_) + ") and RHS(" + std::to_string(given.dimension_) + ") do not match";
			throw euclidean_vector_error(error_msg);
		}
		std::transform(this -> magnitude_.get(), this -> magnitude_.get() + this -> dimension_, given.magnitude_.get(), this->magnitude_.get(), std::plus<>());
		return *this;
	}

	auto euclidean_vector::operator-=(euclidean_vector const& given) -> euclidean_vector&{
		//check for the error
		if (this->dimension_ != given.dimension_){
			auto error_msg = "Dimensions of LHS(" + std::to_string(this->dimension_) + ") and RHS(" + std::to_string(given.dimension_) + ") do not match";
			throw euclidean_vector_error(error_msg);
		}
		std::transform(this -> magnitude_.get(), this -> magnitude_.get() + this -> dimension_, given.magnitude_.get(), this->magnitude_.get(), std::minus<>());
		return *this;
	}

	auto euclidean_vector::operator*=(double num) -> euclidean_vector&{
		//https://www.tutorialspoint.com/bind-function-and-placeholders-in-cplusplus
		//used bind function in order to multiply each magnitudes by num
		auto i = std::placeholders::_1;
		std::transform(this->magnitude_.get(), this->magnitude_.get() + this->dimension_, this->magnitude_.get(), std::bind(std::multiplies(), i,num));
		return *this;
	}

	auto euclidean_vector::operator/=(double num) -> euclidean_vector&{
		//check for the error
		if(num == 0){
			auto error_msg = "Invalid vector division by 0";
			throw euclidean_vector_error(error_msg);
		}
		//https://www.tutorialspoint.com/bind-function-and-placeholders-in-cplusplus
		//used bind function in order to divide each magnitudes by num
		auto i = std::placeholders::_1;
		std::transform(this->magnitude_.get(), this->magnitude_.get() + this->dimension_, this->magnitude_.get(), std::bind(std::divides(), i,num));
		return *this;
	}

	euclidean_vector::operator std::vector<double>() const{
		return std::vector<double>(magnitude_.get(), magnitude_.get() + dimension_);
	}

	euclidean_vector::operator std::list<double>() const{
		return std::list<double>(magnitude_.get(), magnitude_.get() + dimension_);
	}

	//Member functions
	auto euclidean_vector::at(int index) const -> double{
		//check for the errors first
		if(index < 0 || index >= this->dimension_){
			auto error_msg = "Index " + std::to_string(index) +" is not valid for this euclidean_vector object";
			throw euclidean_vector_error(error_msg);
		}
		return magnitude_[static_cast<std::size_t>(index)];
	}

	auto euclidean_vector::at(int index) -> double&{
		//check for the errors first
		if(index < 0 || index >= this->dimension_){
			auto error_msg = "Index " + std::to_string(index) +" is not valid for this euclidean_vector object";
			throw euclidean_vector_error(error_msg);
		}
		return magnitude_[static_cast<std::size_t>(index)];
	}

	auto euclidean_vector::dimensions() const noexcept -> int{
		int ret = static_cast<int>(this->dimension_);
		return ret;
	}

	// Friends
	auto operator==(euclidean_vector const& fst, euclidean_vector const& snd) -> bool{
		if (fst.dimension_ != snd.dimension_){
			return false;
		}
		auto num_dim = static_cast<int>(fst.dimensions());
		for (auto i = 0; i < num_dim; ++i){
			if (fst.at(i) != snd.at(i)){
				return false;
			}
		}
		return true;
	}

	auto operator!=(euclidean_vector const& fst, euclidean_vector const& snd) -> bool{
		if (fst.dimension_ != snd.dimension_){
			return true;
		}
		auto num_dim = static_cast<int>(fst.dimensions());
		for (auto i = 0; i < num_dim; ++i){
			if (fst.at(i) != snd.at(i)){
				return true;
			}
		}
		return false;
	}

	auto operator+(euclidean_vector const& fst, euclidean_vector const& snd) -> euclidean_vector{
		//check for the erros first
		auto x = fst.dimension_;
		auto y = snd.dimension_;
		if (x != y){
			auto error_msg = "Dimensions of LHS("+std::to_string(x)+") and RHS("+std::to_string(y)+") do not match";
			throw euclidean_vector_error(error_msg);
		}
		auto thd = euclidean_vector(fst);
		thd += snd;
		return thd;
	}

	auto operator-(euclidean_vector const& fst, euclidean_vector const& snd) -> euclidean_vector{
		//check for the erros first
		auto x = fst.dimension_;
		auto y = snd.dimension_;
		if (x != y){
			auto error_msg = "Dimensions of LHS("+std::to_string(x)+") and RHS("+std::to_string(y)+") do not match";
			throw euclidean_vector_error(error_msg);
		}
		auto thd = euclidean_vector(fst);
		thd -= snd;
		return thd;
	}

	auto operator*(euclidean_vector const& fst, double snd) -> euclidean_vector{
		auto thd = euclidean_vector(fst);
		thd *= snd;
		return thd;
	}

	auto operator*(double snd, euclidean_vector const& fst) -> euclidean_vector{
		auto thd = euclidean_vector(fst);
		thd *= snd;
		return thd;
	}

	auto operator/(euclidean_vector const& fst, double snd) -> euclidean_vector{
		//check for the erros first
		if (snd == 0){
			auto error_msg = "Invalid vector division by 0";
			throw euclidean_vector_error(error_msg);
		}
		auto thd = euclidean_vector(fst);
		thd /= snd;
		return thd;
	}

	auto operator<<(std::ostream& ret, euclidean_vector const& fst) -> std::ostream&{
		ret << "[";
		std::copy(fst.magnitude_.get(), fst.magnitude_.get() + fst.dimension_, std::experimental::make_ostream_joiner(ret, " "));
		ret << "]";
		return ret;
	}

	auto euclidean_norm(euclidean_vector const& v) -> double{
		auto norm = 0.0;
		if(v.dimensions() == 0){
			return norm;
		}
		for (auto i = 0; i < v.dimensions(); ++i){
			auto j = v.at(i) * v.at(i);
			norm += j;
		}
		return std::sqrt(norm);
	}

	auto unit(euclidean_vector const& v) -> euclidean_vector{
		//throw error first
		if(v.dimensions() == 0){
			auto error_msg = "euclidean_vector with no dimensions does not have a unit vector";
			throw euclidean_vector_error(error_msg);
		}
		if(euclidean_norm(v) == 0){
			auto error_msg = "euclidean_vector with zero euclidean normal does not have a unit vector";
			throw euclidean_vector_error(error_msg);
		}
		return v/euclidean_norm(v);
	}

	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double{
		//throw error first
		if(x.dimensions() != y.dimensions()){
			auto error_msg = "Dimensions of LHS("+std::to_string(x.dimensions())+") and RHS("+std::to_string(y.dimensions())+") do not match";
			throw euclidean_vector_error(error_msg);
		}
		auto ret = 0.0;
		for (auto i = 0; i < x.dimensions(); ++i){
			auto j = x.at(i) * y.at(i);
			ret += j;
		}
		return ret;
	}
} // namespace comp6771
