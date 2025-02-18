#include <DuckCore/Core/Assert.h>

#include <DuckCore/Core/Log.h>
#include <DuckCore/RTTI/RTTIClass.h>

using namespace DC;

class LogCategoryAsserts final : public LogCategory
{
	RTTI_CLASS(LogCategoryAsserts, LogCategory)
};

void gLogAssert(const String& aMessage)
{
	gLog<LogCategoryAsserts>(ELogLevel::Error, aMessage);
}
