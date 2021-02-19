#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

class gameobject
{
	// Forward Declarations
	class BackBuffer;
	class Sprite;

	//Member Methods:
public:
	bool Initialise();
protected:
	void Draw(BackBuffer& backBuffer);
	gameobject();
	~gameobject();
private:

	//Member Data:
public:

	char object_type;
	bool dynamite_breakable;
protected:


private:
};
#endif //__GAMEOBJECT_H__
