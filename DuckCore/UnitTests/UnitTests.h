#pragma once
#include <DuckCore/Core/Types.h>

namespace DC
{
namespace UnitTests
{

enum class ETestResult : uint8
{
	Success,
	Failure
};
ETestResult RunAllTests();

}
}
