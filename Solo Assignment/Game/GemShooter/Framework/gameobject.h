// COMP710 GP 2D Framework 2020 from entity altered
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

// Forward Declarations
class BackBuffer;
class Sprite;

class GameObject
{
	
	//Member Methods:
public:
	bool Initialise(Sprite* sprite);
	GameObject();
	~GameObject();

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void AimAngle(int angle);

	void SetDead(bool dead);
	bool IsDead() const;

	bool IsCollidingWith(GameObject& e);

	void SetPosition(float x, float y);
	void SetPositionX(float x);
	void SetPositionY(float y);

	float GetPositionX() const;
	float GetPositionY() const;

	float GetHorizontalVelocity() const;
	void SetHorizontalVelocity(float x);

	float GetVerticalVelocity() const;
	void SetVerticalVelocity(float y);
protected:
	
	
	
private:
	GameObject(const GameObject& entity);
	GameObject& operator=(const GameObject& entity);
	
	//Member Data:
public:
	
protected:
	char object_type;
	bool dynamite_breakable;
	Sprite* m_pSprite;

	float m_x;
	float m_y;

	float m_velocityX;
	float m_velocityY;

	bool m_dead;

private:
};
#endif //__GAMEOBJECT_H__

