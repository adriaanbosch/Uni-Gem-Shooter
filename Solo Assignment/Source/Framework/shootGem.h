#ifndef __SHOOTGEM_H__
#define __SHOOTGEM_H__
#include "gem.h"
#include "gameobject.h"
class ShootGem : public Gem
{
	//Member Methods:
public:
	ShootGem();
	~ShootGem();
	bool Initialise(Sprite* sprite);
	void removeGemShot();
protected:


private:

	//Member Data:
public:

protected:


private:
};

#endif //__SHOOTGEM_H__
