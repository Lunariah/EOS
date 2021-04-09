#pragma once

namespace utils
{
	inline int signOf(float n)
	{
		return (n > 0) - (n < 0);
	}
	inline int signOf(int n)
	{
		return (n > 0) - (n < 0);
	}
}