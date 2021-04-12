#pragma once

namespace Utils
{
	//template <class T>
	//inline int signOf(T n)
	//{
	//	return (n > 0) - (n < 0);
	//}

	inline int signOf(int n)
	{
		return (n > 0) - (n < 0);
	}

	inline int signOf(float n)
	{
		return (n > 0) - (n < 0);
	}

	inline void lowerCase(std::string& str)
	{
		std::transform(str.begin(), str.end(), str.begin(), tolower);
	}
}