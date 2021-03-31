#pragma once

namespace utils
{
	inline int signOf(float n)
	{
		if (n > 0) return 1;
		if (n < 0) return -1;
		else return 0;
	}
	inline int signOf(int n)
	{
		if (n > 0) return 1;
		if (n < 0) return -1;
		else return 0;
	}
}