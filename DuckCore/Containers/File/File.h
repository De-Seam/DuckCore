#pragma once
#include <DuckCore/Containers/BitFlags.h>
#include <DuckCore/Containers/String.h>
#include <DuckCore/Core/Log.h>
#include <DuckCore/RTTI/Ref.h>
#include <DuckCore/Utilities/Json.h>
#include <DuckCore/Utilities/Utilities.h>

#include <fstream>

namespace DC
{
class LogCategoryFile final : public LogCategory {};

class File : public RefClass
{
public:
	class FKeepOpen {}; // Keep the file open after loading it.
	class FReadOnly {}; // Only allow reading from the file.
	class FWriteOnly {}; // Only allow writing to the file.
	using Flags = BitFlags<FKeepOpen, FReadOnly, FWriteOnly>;

	explicit File(String aPath, Flags aFlags = {}) : mPath(Move(aPath)), mFlags(aFlags) {}
	explicit File(const Json& aJson, Flags aFlags = {});
	Json ToJson() const;

	virtual void Load(); // Loads mContents from mPath. This will clear potentially existing content.
	virtual void WriteToDisk(); // Writes mContents to mPath. Child classes should override this to update mContents before calling this.
	void ClearCachedContents(); // Clears mContents. This will not write to disk.

	void SetContents(String aContents); // Set mContents to aContents. This will not write to disk.

	const String& GetPath() const { return mPath; }
	const String& GetContents() const { return mContents; }

	String& GetContentsForWriting() { return mContents; }

	bool ShouldKeepFileOpen() const { return mFlags.GetFlag<FKeepOpen>();}
	bool IsReadOnly() const { return mFlags.GetFlag<FReadOnly>(); }
	bool IsWriteOnly() const { return mFlags.GetFlag<FWriteOnly>(); }

protected:
	String GetFileExtension() const; // Get the file extension of mPath. This is without the dot. So, "png", not ".png".

	String mContents;

private:
	std::fstream mFile;

	String mPath;
	Flags mFlags;
};
}
