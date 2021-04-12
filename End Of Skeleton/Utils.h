#pragma once

namespace Utils
{
	template <class T>
	inline int signOf(T n)
	{
		return (n > 0) - (n < 0);
	}

	inline void lowerCase(std::string& str)
	{
		std::transform(str.begin(), str.end(), str.begin(), tolower);
	}
}