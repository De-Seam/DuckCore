#pragma once
#include <DuckCore/Containers/String.h>
#include <DuckCore/RTTI/RTTIRefClass.h>
#include <DuckCore/Utilities/Utilities.h>

namespace DC
{
class LogCategoryFile final : public LogCategory {};

class File : public RefClass
{
public:
	File(String inPath) : mPath(gMove(inPath)) {}

	virtual void Load(); // Loads mContents from mPath. This will clear potentially existing content.
	virtual void WriteToDisk(); // Writes mContents to mPath. Child classes should override this to update mContents before calling this.

	void SetContents(String inContents);

	const String& GetPath() const { return mPath; }
	const String& GetContents() const { return mContents; }

	String& GetContentsForWriting() { return mContents; }

protected:
	String GetFileExtension() const; // Get the file extension of mPath. This is without the dot. So, "png", not ".png".

	String mContents;

private:
	String mPath;
};
}
