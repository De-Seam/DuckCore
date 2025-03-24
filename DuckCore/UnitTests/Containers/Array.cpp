#include <DuckCore/UnitTests/Containers/Array.h>

namespace DC
{
namespace UnitTests
{
void UnitTestArray::Run(Array<Error>& outErrors)
{
	Array<int> int_array;
	int_array.Reserve(10);

	UNIT_TEST_VERIFY(int_array.Capacity() == 10, "Array capacity should be 10.");
}

}
}