#include <DuckCore/Core/Log.h>

#include <DuckCore/Containers/Array.h>
#include <DuckCore/Containers/HashMap.h>
#include <DuckCore/Containers/String.h>
#include <DuckCore/Containers/File/TextFile.h>
#include <DuckCore/Core/Assert.h>
#include <DuckCore/Core/Core.h>
#include <DuckCore/Managers/Managers.h>
#include <DuckCore/Threads/ScopedMutex.h>

#include <cstdio>

namespace DC
{
Array<LogEntry> gLogEntries;
Mutex gLogEntriesMutex;
Ref<TextFile> gLogFile;
Mutex gLogFileMutex;

void LogInternal(const RTTI& aLogCategoryRTTI, ELogLevel aLevel, const char* aMessage)
{
	LogEntry entry;
	entry.mMessage = aLogCategoryRTTI.GetClassName();
	entry.mMessage = entry.mMessage.SubStr(11, entry.mMessage.Length());

	switch (aLevel)
	{
	case ELogLevel::Info:
		entry.mMessage = String("[Info] [") + entry.mMessage + "] " + aMessage;
		break;
	case ELogLevel::Warning:
		entry.mMessage = String("[Warning] [") + entry.mMessage + "] " + aMessage;
		break;
	case ELogLevel::Error:
		entry.mMessage = String("[Error] [") + entry.mMessage + "] " + aMessage;
		break;
	}
	entry.mCategory = &aLogCategoryRTTI;
	entry.mLevel = aLevel;

	printf("%s", *entry.mMessage);
	printf("\n");

	defer({
		ScopedMutexLock entries_lock(gLogEntriesMutex);
		gLogEntries.Add(Move(entry));
	});

	ScopedMutexLock file_lock;

	if (!gLogFileMutex.TryLock())
		return;

	file_lock.SetLockedMutex(gLogFileMutex);

	if (gLogFile == nullptr)
	{
		File::Flags flags;
		flags.SetFlag<File::FKeepOpen>(true);
		gLogFile = new TextFile("Logs/log.txt", flags);
	}
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
	return { gLogEntriesMutex, &gLogEntries };
}
}
