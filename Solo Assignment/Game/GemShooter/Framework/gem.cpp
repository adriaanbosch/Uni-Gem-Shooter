#include "gem.h"
#include <vector>


Gem::Gem() 
{
	GameObject();
}
Gem::~Gem()
{

}
bool Gem::Initialise(Sprite* sprite)
{
	return GameObject::Initialise(sprite);
}

const char* Gem::GemRandom()
{
	int rannum = 1 + rand() % 5;
	switch (rannum)
	{
	case 1:
		return "gemblue.png";
		break;
	case 2:
		return "gemred.png";
		break;
	case 3:
		return "gemyellow.png";
		break;
	case 4:
		return "gemgreen.png";
		break;
	case 5:
		return "gempurple.png";
		break;
	default:
		return "gemblue.png";
		break;
	}
}