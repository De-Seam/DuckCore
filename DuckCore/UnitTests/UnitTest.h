#pragma once
#include <DuckCore/Containers/Array.h>

#define UNIT_TEST_ERROR(message) { Error error; error.mFileName = __FILE__; error.mLineNumber = __LINE__; error.mFunctionName = __FUNCTION__; error.mMessage = message; outErrors.Add(error); outErrors.Add(error); }
#define UNIT_TEST_VERIFY(condition, message) if (!(condition)) { UNIT_TEST_ERROR(message); }

namespace DC
{
namespace UnitTests
{

struct Error
{
	String mFileName;
	int mLineNumber;
	String mFunctionName;

	String mMessage;
};

class UnitTest
{
public:
	virtual void Run(Array<Error>& outErrors) = 0;
};

}
}
