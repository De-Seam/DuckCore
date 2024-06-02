#pragma once

template<typename taFirstType, typename taSecondType>
class Pair
{
public:
	Pair(const taFirstType& inFirst, const taSecondType& inSecond)
		: mFirst(inFirst), mSecond(inSecond) {}

	taFirstType mFirst;
	taSecondType mSecond;
};
