#pragma once
#include <DuckCore/Containers/HashMap.h>
#include <DuckCore/Containers/HashSet.h>
#include <DuckCore/Managers/Manager.h>

namespace DC
{
class CommandLineArgumentsManager : public Manager
{
	MANAGER_BASE_CLASS(CommandLineArgumentsManager)
public:
	CommandLineArgumentsManager(int aArgumentCount, char* aArgumentValues[]);

	bool HasArgument(const String& aArgument) const;
	template<typename taValueType>
	bool FindArgumentValue(const String& aArgument, taValueType& outValue) const; // Value should be default initialized. Returns true if the value was found.

private:
	HashSet<String> mArguments;

	HashMap<String, String> mArgumentValuePairs;
};

template<typename taValueType>
bool CommandLineArgumentsManager::FindArgumentValue(const String& aArgument, taValueType& outValue) const
{
	HashMap<String, String>::IteratorC iter = mArgumentValuePairs.Find(aArgument);
	if (!iter.IsValid())
		return false;

	outValue = FromString<taValueType>(iter.GetValue());
	return true;
}

template<>
inline bool CommandLineArgumentsManager::FindArgumentValue<String>(const String& aArgument, String& outValue) const
{
	HashMap<String, String>::IteratorC iter = mArgumentValuePairs.Find(aArgument);
	if (!iter.IsValid())
		return false;

	outValue = iter.GetValue();
	if (outValue.Length() > 2 && outValue[0] == '\"' && outValue[outValue.Length() - 1] == '\"')
		outValue = outValue.SubStr(1, outValue.Length() - 2);
	return true;
}
}
