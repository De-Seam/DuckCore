#include <Example/Example.h>

#include <CContainers/String.h>

#include <cstdio>

int main()
{
	String string = "Test";
	string += " string";

	printf("%s", *string);

	return 0;
}
