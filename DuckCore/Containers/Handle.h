#pragma once
#include <DuckCore/RTTI/Ref.h>

namespace DC
{
// Handle is a class that in its destructor automatically unregisters itself
class Handle : public RefClass
{
public:
	Handle(int inID) : mID(inID) {}

	bool operator==(const Handle& inOther) const { return mID == inOther.mID; }

	int GetID() const { return mID; }

private:
	int mID = -1;
};
}
