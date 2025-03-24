#include <DuckCore/UnitTests/UnitTests.h>

#include <DuckCore/Containers/Array.h>
#include <DuckCore/Containers/UniquePtr.h>
#include <DuckCore/UnitTests/Containers/Array.h>
#include <DuckCore/UnitTests/UnitTest.h>

namespace DC
{
namespace UnitTests
{

ETestResult RunAllTests()
{
	static Array<UniquePtr<UnitTest>> sUnitTests;
	sUnitTests.Add(MakeUnique<UnitTestArray>());

	bool any_errors = false;
	for (UnitTest* test : sUnitTests)
	{
		Array<Error> errors;
		test->Run(errors);

		if (errors.IsEmpty())
			continue;

		any_errors = true;

		for (const Error& error : errors)
			printf("Error: %s\nOn file %s, line %d in function %s", *error.mMessage, *error.mFileName, error.mLineNumber, *error.mFunctionName);
	}

	gAssert(!any_errors);
	return any_errors ? ETestResult::Failure : ETestResult::Success;
}

}
}
