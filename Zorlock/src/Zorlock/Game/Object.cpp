#include "ZLpch.h"
#include "Object.h"


Zorlock::Object::Object() : transform(CreateRef<TRANSFORM>())
{
	name = "Object";
}

Zorlock::Object::Object(std::string name) : name(name), transform(CreateRef<TRANSFORM>())
{

}

Zorlock::Object::~Object()
{
}
