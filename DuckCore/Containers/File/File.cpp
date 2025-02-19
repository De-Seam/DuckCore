#include <DuckCore/Containers/File/File.h>

#include <DuckCore/Core/Assert.h>
#include <DuckCore/Core/Log.h>
#include <DuckCore/Utilities/Utilities.h>

namespace DC
{
void File::Load()
{
	gAssert(!IsWriteOnly());

	gLog(String::sFormatted("Loading file %s", *mPath));

	mContents = "";

	if (!mFile.is_open())
		mFile.open(*mPath, std::fstream::in | std::fstream::out | std::fstream::trunc);

	if (!mFile.is_open())
	{
		gLog<LogCategoryFile>(ELogLevel::Info, String::sFormatted("Unable to open file %s for reading. The file will be created instead.", *mPath));
		return;
	}

	mContents = std::string(std::istreambuf_iterator<char>(mFile), {});

	if (!ShouldKeepFileOpen())
		mFile.close();
}

void File::WriteToDisk()
{
	gAssert(!IsReadOnly());
	
	if (!mFile.is_open())
	{
		mFile.open(*mPath, std::fstream::in | std::fstream::out | std::fstream::trunc);
		if (!mFile.is_open())
		{
			// If we failed to create the file, try to create the directory first.
			std::filesystem::path parent_path = std::filesystem::path(*mPath).parent_path();
			if (std::filesystem::create_directories(parent_path))
			{
				WriteToDisk();
				mFile.open(*mPath, std::fstream::in | std::fstream::out | std::fstream::trunc);
			}
		}
	}

	if (!mFile.is_open())
	{
		gAssert(false);
		gLog<LogCategoryFile>(ELogLevel::Error, String::sFormatted("Unable to open file %s for writing", *mPath));
		return;
	}

	mFile << *mContents;

	if (!ShouldKeepFileOpen())
		mFile.close();
}

void File::SetContents(String aContents)
{
	mContents = gMove(aContents);
}

String File::GetFileExtension() const
{
	const int dot_pos = mPath.FindLastCharOccurence('.');
	if (dot_pos == -1)
		return "";

	return mPath.SubStr(dot_pos + 1, mPath.Length() - 1);
}
}
