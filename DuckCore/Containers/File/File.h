#pragma once
#include <DuckCore/Containers/String.h>
#include <DuckCore/Core/Log.h>
#include <DuckCore/RTTI/Ref.h>
#include <DuckCore/Utilities/Utilities.h>

#include <fstream>

namespace DC
{
class LogCategoryFile final : public LogCategory {};

class File : public RefClass
{
public:
	enum class EFlags : uint8
	{
		KeepOpen = 1 << 0, // Keep the file open after loading it.
		ReadOnly = 1 << 1, // Open the file in read-only mode.
		WriteOnly = 1 << 2, // Open the file in write-only mode.
	};

	explicit File(String aPath, uint8 aFlags = 0) : mPath(gMove(aPath)), mFlags(aFlags) {}

	virtual void Load(); // Loads mContents from mPath. This will clear potentially existing content.
	virtual void WriteToDisk(); // Writes mContents to mPath. Child classes should override this to update mContents before calling this.

	void SetContents(String aContents);

	const String& GetPath() const { return mPath; }
	const String& GetContents() const { return mContents; }

	String& GetContentsForWriting() { return mContents; }

	bool ShouldKeepFileOpen() const { return (uint8)mFlags & (uint8)EFlags::KeepOpen; }
	bool IsReadOnly() const { return (uint8)mFlags & (uint8)EFlags::ReadOnly; }
	bool IsWriteOnly() const { return (uint8)mFlags & (uint8)EFlags::WriteOnly; }

protected:
	String GetFileExtension() const; // Get the file extension of mPath. This is without the dot. So, "png", not ".png".

	String mContents;

private:
	std::fstream mFile;

	String mPath;
	uint8 mFlags = 0;
};
}
