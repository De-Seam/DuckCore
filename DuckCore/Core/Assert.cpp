#include <DuckCore/Core/Assert.h>

#include <DuckCore/Core/Log.h>
#include <DuckCore/RTTI/RTTIClass.h>

using namespace DC;

class LogCategoryAsserts final : public LogCategory
{
	RTTI_CLASS(LogCategoryAsserts, LogCategory)
};

void LogAssert(const String& aBase, const String& aMessage)
{
	Log(ELogLevel::Error, aBase + aMessage);
}
