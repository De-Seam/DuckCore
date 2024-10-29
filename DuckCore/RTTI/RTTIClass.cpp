#include "RTTIClass.h"

using namespace DC;

bool RTTIClass::IsARTTI(const RTTI& inRTTI) const
{
	return sGetRTTI().GetTypeID() == inRTTI.GetTypeID();
}

Json RTTIClass::Serialize() const 
{
	Json json;
	json["ClassName"] = GetRTTI().GetClassName();
	return json;
}

void RTTIClass::Deserialize(const Json& inJson)
{
	gAssert(inJson["ClassName"] == GetRTTI().GetClassName());
}