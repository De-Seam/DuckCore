#pragma once
#include <DuckCore/UnitTests/UnitTest.h>

namespace DC
{
namespace UnitTests
{

class UnitTestArray : public UnitTest
{
public:
	virtual void Run(Array<Error>& outErrors) override;
};

}
}
