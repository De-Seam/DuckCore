#pragma once
// DuckCore includes
#include <DuckCore/RTTI/Ref.h>
#include <DuckCore/RTTI/RTTIClass.h>

namespace DC
{

class RTTIRefClass : public RTTIClass, public RefClass
{
	RTTI_CLASS(RTTIRefClass, RTTIClass)
public:
	
};

}
