#include <DuckCore/Containers/String.h>

using namespace DC;

uint64 String::Hash() const
{
	static std::hash<std::string> sHasher;
	return sHasher(mString);
}