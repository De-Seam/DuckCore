#pragma once
#ifndef _SHIP

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

#endif