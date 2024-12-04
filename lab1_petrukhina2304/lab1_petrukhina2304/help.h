#pragma once
#pragma once
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <format>

std::string input_string(std::istream& in = std::cin);

template <typename T>
T input_number(std::istream& in = std::cin);

template <typename T>
T get_correct_number(T a, T b, bool included = true, std::istream& in = std::cin);

template <typename T>
T get_positive_number(std::istream& in = std::cin);

bool confirm(std::string);


class redirect_output_wrapper
{
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}
	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};
