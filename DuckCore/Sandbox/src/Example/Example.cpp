#include <Example/Example.h>

#include <CContainers/Array.h>
#include <CContainers/String.h>

#include <cstdio>

int main()
{
	Array<int> array;
	array.Add(1);
	array.Add(4);

	for (uint32 i = 0; i < array.GetSize(); i++)
	{
		printf("%d", array[i]);
	}

	String string = "Test";
	string += " string";
	if (string.Contains("est"))
	{
		printf("Contains");
	}

	printf("%s", *string);

	return 0;
}
