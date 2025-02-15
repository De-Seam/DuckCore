#pragma once
// DuckCore includes
#include <DuckCore/Containers/File/File.h>

namespace DC
{
class TextFile final : public File
{
public:
	explicit TextFile(String inPath, uint8 inFlags = 0) : File(gMove(inPath), inFlags) {}
};
}