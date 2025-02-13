#include <DuckCore/Core/LogManager.h>
#include <DuckCore/Threads/ScopedMutex.h>

namespace DC
{
void LogManager::Log(const RTTI& inLogCategoryRTTI, ELogLevel inLevel, const char* inMessage)
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

	ScopedMutexLock lock(mLogMutex);
	mLogEntries.Add(gMove(entry));
}

MutexProtectedPtr<const Array<LogManager::LogEntry>> LogManager::GetLogArray()
{
	return { mLogMutex, &mLogEntries };
}

void LogManager::SetLogFilePath(const String& inFilePath)
{
	ScopedMutexLock lock(mLogMutex);
	SetLogFilePathInternal(inFilePath);
}

void LogManager::WriteLogToFile()
{
	if (mLogFile == nullptr)
		SetLogFilePathInternal(cDefaultLogFilePath);
	gAssert(mLogFile != nullptr);

	ScopedMutexLock lock(mLogMutex);

	String log_contents;
	for (const LogEntry& entry : mLogEntries)
	{
		log_contents += entry.mMessage;
		log_contents += "\n";
	}

	mLogFile->SetContents(log_contents);
	mLogFile->WriteToDisk();
}

void LogManager::SetLogFilePathInternal(const String& inFilePath)
{
	gAssert(mLogMutex.IsLockedByCurrentThread());
	gAssert(false);
}
}
