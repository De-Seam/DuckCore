#include "RTTIClass.h"

using namespace DC;

bool RTTIClass::IsARTTI(const RTTI& inRTTI) const
{
	return sGetRTTI().GetTypeID() == inRTTI.GetTypeID();
}