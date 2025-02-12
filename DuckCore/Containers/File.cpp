#include <DuckCore/Containers/File.h>

#include <DuckCore/Core/Log.h>
#include <DuckCore/Utilities/Utilities.h>

#include <fstream>
#include <DuckCore/Core/Assert.h>

using namespace DC;

void File::Load()
{
	gLog(String::sFormatted("Loading file %s", *mPath));

	mContents = "";

	std::ifstream file(mPath.CStr());
	if (!file.is_open())
	{
		gLog<LogCategoryFile>(ELogLevel::Warning, String::sFormatted("Unable to open file %s for reading. The file will be created instead.", *mPath));
		return;
	}

	mContents = std::string(std::istreambuf_iterator<char>(file), {});

	file.close();
}

void File::WriteToDisk()
{
	std::ofstream file(*mPath);
	if (!file.is_open())
	{
		gAssert(false);
		gLog<LogCategoryFile>(ELogLevel::Error, String::sFormatted("Unable to open file %s for writing", *mPath));
		return;
	}

	file << *mContents;
	file.close();
}

void File::SetContents(String inContents)
{
	mContents = gMove(inContents);
}

String File::GetFileExtension() const
{
	const int dot_pos = mPath.FindLastCharOccurence('.');
	if (dot_pos == -1)
		return "";

	return mPath.SubStr(dot_pos + 1, mPath.Length() - 1);
}
