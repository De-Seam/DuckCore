#pragma once
#include <DuckCore/Containers/Array.h>
#include <DuckCore/Containers/File/TextFile.h>
#include <DuckCore/Core/Log.h>
#include <DuckCore/Manager/Manager.h>
#include <DuckCore/Threads/Mutex.h>
#include <DuckCore/Threads/MutexProtectedPtr.h>

namespace DC
{
class LogManager : public Manager
{
	MANAGER_BASE_CLASS(LogManager)
public:
	static constexpr const char* cDefaultLogFilePath = "Logs/log.txt";

	struct LogEntry
	{
		const RTTI* mCategory;
		ELogLevel mLevel;
		String mMessage;
	};

	void Log(const RTTI& inLogCategoryRTTI, ELogLevel inLevel, const char* inMessage);

	MutexProtectedPtr<const Array<LogEntry>> GetLogArray(); // (Async) returns the error of log entries.

	void SetLogFilePath(const String& inFilePath); // (Async) sets the file path for the log file.
	void WriteLogToFile(); // (Async) writes the log to the log file.

private:
	void SetLogFilePathInternal(const String& inFilePath);

	Array<LogEntry> mLogEntries;
	Mutex mLogMutex;

	Ref<TextFile> mLogFile;
};
}
