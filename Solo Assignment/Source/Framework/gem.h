#ifndef __GEM_H__
#define __GEM_H__
#include "gameobject.h"
class Gem : public GameObject
{
	//Member Methods:
public:
	Gem();
	~Gem();
	const char* GemRandom();
	bool Initialise(Sprite* sprite);
	bool IsSameColour(const char* colour);
	void LinkedColourGems();
	const char* GetGemColour();
protected:
	

private:

	//Member Data:
public:
	
protected:
	const char* gemColour;

private:
};

#endif //__GEM_H__

