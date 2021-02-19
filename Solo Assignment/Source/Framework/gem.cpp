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
	gemColour = 0;
}
bool Gem::IsSameColour(const char* colour) {
	if (this->gemColour == colour)
	{
		return true;
	}
}
void LinkedColouredGems() {

}

const char* Gem::GemRandom()
{
	int rannum = 1 + rand() % 5;
	switch (rannum)
	{
	case 1:
		gemColour = "blue";
		return "gemblue.png";
		break;
	case 2:
		gemColour = "red";
		return "gemred.png";
		break;
	case 3:
		gemColour = "yellow";
		return "gemyellow.png";
		break;
	case 4:
		gemColour = "green";
		return "gemgreen.png";
		break;
	case 5:
		gemColour = "purple";
		return "gempurple.png";
		break;
	default:
		gemColour = "blue";
		return "gemblue.png";
		break;
	}
}
const char*
Gem::GetGemColour() 
{
	return (gemColour);
}