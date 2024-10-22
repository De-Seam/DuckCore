#pragma once

#define gEnsureTrue(inCondition) \
if (!(inCondition)) \
{ \
	gAssert(false && "Condition failed: " #inCondition); \
}

class UnitTestBase
{
public:
	virtual void Run() = 0;

protected:
};
