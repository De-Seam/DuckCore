#include <DuckCore/Managers/CommandLineArgumentsManager.h>

#include <DuckCore/Core/Log.h>

namespace DC
{
CommandLineArgumentsManager::CommandLineArgumentsManager(int aArgumentCount, char* aArgumentValues[])
{
	for (int i = 0; i < aArgumentCount; ++i)
		mArguments.Add(aArgumentValues[i]);

	for (const String& argument : mArguments)
	{
		int equals_sign_index = argument.FindFirstCharOccurence('=');
		if (equals_sign_index == -1)
			continue;

		if (equals_sign_index == argument.Length() - 1)
		{
			Log<LogCategoryDefault>(ELogLevel::Warning, String::sFormatted("Invalid command line argument: %s", *argument));
			gAssert(false);
			continue;
		}

		String argument_name = argument.SubStr(0, equals_sign_index);
		String argument_value = argument.SubStr(equals_sign_index + 1, argument.Length() - 1);

		if (HashMap<String, String>::Iterator iter = mArgumentValuePairs.Find(argument))
		{
			Log<LogCategoryDefault>(ELogLevel::Warning, String::sFormatted("Duplicate command line argument: %s. Two given values: %s and %s", *argument_name, *argument_value, *iter.GetValue()));
			gAssert(false);
			continue;
		}

		mArgumentValuePairs[argument_name] = argument_value;
	}
}

bool CommandLineArgumentsManager::HasArgument(const String& aArgument) const
{
	return mArguments.Contains(aArgument) || mArgumentValuePairs.Contains(aArgument);
}
}
