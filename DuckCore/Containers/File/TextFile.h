#pragma once
// DuckCore includes
#include <DuckCore/Containers/File/File.h>

namespace DC
{
class TextFile final : public File
{
public:
	explicit TextFile(String aPath, Flags aFlags = {}) : File(Move(aPath), aFlags) {}
};
}