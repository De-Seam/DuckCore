#include <DuckCore/Core/Log.h>

#include <DuckCore/Containers/Array.h>
#include <DuckCore/Containers/HashMap.h>
#include <DuckCore/Containers/String.h>
#include <DuckCore/Containers/File/TextFile.h>
#include <DuckCore/Core/Assert.h>
#include <DuckCore/Manager/Managers.h>
#include <DuckCore/Threads/ScopedMutex.h>

#include <cstdio>

namespace DC
{
Array<LogEntry> gLogEntries;
Mutex gMutex;
Ref<TextFile> gLogFile;
Mutex gLogFileMutex;

void LogInternal(const RTTI& aLogCategoryRTTI, ELogLevel aLevel, const char* aMessage)
{
	String category_name = aLogCategoryRTTI.GetClassName();
	category_name = category_name.SubStr(11, category_name.Length());

	LogEntry entry;
	switch (aLevel)
	{
	case ELogLevel::Info:
		entry.mMessage = String("[Info] ") + category_name + aMessage;
		break;
	case ELogLevel::Warning:
		entry.mMessage = String("[Warning] ") + category_name + aMessage;
		break;
	case ELogLevel::Error:
		entry.mMessage = String("[Error] ") + category_name + aMessage;
		break;
	}
	entry.mCategory = &aLogCategoryRTTI;
	entry.mLevel = aLevel;

	printf(*entry.mMessage);
	printf("\n");

	{
		ScopedMutexLock lock(gMutex);
		gLogEntries.Add(Move(entry));
	}

	ScopedMutexLock lock;

	if (!gLogFileMutex.TryLock())
		return;

	lock.SetLockedMutex(gLogFileMutex);

	if (gLogFile == nullptr)
		gLogFile = new TextFile("Logs/log.txt", (uint8)File::EFlags::KeepOpen);
	gLogFile->GetContentsForWriting() += entry.mMessage + "\n";
	gLogFile->WriteToDisk();
}

void Log(ELogLevel aLevel, const char* aMessage)
{
	Log<LogCategoryDefault>(aLevel, aMessage);
}

void Log(const char* aMessage)
{
	Log<LogCategoryDefault>(ELogLevel::Info, aMessage);
}

MutexProtectedPtr<const Array<LogEntry>> GetLogArray()
{
	return { gMutex, &gLogEntries };
}
}
