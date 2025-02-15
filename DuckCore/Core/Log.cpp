#include <DuckCore/Core/Log.h>

#include <DuckCore/Containers/Array.h>
#include <DuckCore/Containers/HashMap.h>
#include <DuckCore/Containers/String.h>
#include <DuckCore/Core/Assert.h>
#include <DuckCore/Core/LogManager.h>
#include <DuckCore/Manager/Managers.h>
#include <DuckCore/Threads/ScopedMutex.h>

#include <cstdio>

namespace DC
{
Mutex gMutex;
Array<LogEntry> gLogEntries;
Ref<TextFile> gLogFile;

void gLogInternal(const RTTI& inLogCategoryRTTI, ELogLevel inLevel, const char* inMessage)
{
	String category_name = inLogCategoryRTTI.GetClassName();
	category_name = category_name.SubStr(11, category_name.Length());

	LogEntry entry;
	switch (inLevel)
	{
	case ELogLevel::Info:
		entry.mMessage = String("[Info] ") + category_name + inMessage;
		break;
	case ELogLevel::Warning:
		entry.mMessage = String("[Warning] ") + category_name + inMessage;
		break;
	case ELogLevel::Error:
		entry.mMessage = String("[Error] ") + category_name + inMessage;
		break;
	}
	entry.mCategory = &inLogCategoryRTTI;
	entry.mLevel = inLevel;

	printf(*entry.mMessage);
	printf("\n");

	ScopedMutexLock lock(gMutex);
	gLogEntries.Add(gMove(entry));

	if (gLogFile == nullptr)
		gLogFile = new TextFile("Logs/log.txt", (uint8)File::EFlags::KeepOpen);
	gLogFile->GetContentsForWriting() += entry.mMessage + "\n";
	gLogFile->WriteToDisk();
}

void gLog(ELogLevel inLevel, const char* inMessage)
{
	gLog<LogCategoryDefault>(inLevel, inMessage);
}

void gLog(const char* inMessage)
{
	gLog<LogCategoryDefault>(ELogLevel::Info, inMessage);
}

MutexProtectedPtr<const Array<LogEntry>> gGetLogArray()
{
	return { gMutex, &gLogEntries };
}
}
