#include <Example/Example.hpp>

#include <CContainers/String.hpp>

#include <cstdio>

int main()
{
	String string = "Test";
	string += " string";

	printf("%s", *string);

	return 0;
}
