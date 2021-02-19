// COMP710 GP 2D Framework 2020
#ifndef __GAME_H__
#define __GAME_H__
#include<vector>
// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class Gem;
class GameObject;
class ShootGem;

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool DoGameLoop();
	void Quit();
	void GameObjectListed();
	void GameObjectShootingList();
	void GemShot();
	void Aim(int angle);
	void SwitchGems();

protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	

private:
	Game(const Game& game);
	Game& operator=(const Game& game);

	Game();

	//Member Data:
public:
	Sprite * m_pSprite;
	Sprite * pSprite;
	Sprite * wallSprite1;
	Sprite * wallSprite2;
	Sprite * deadZone;
	Sprite * roof;
	GameObject * aimLine;
	GameObject * object1;
	std::vector<GameObject*> objectlist;
	std::vector<GameObject*> shootingList;
	Gem * gem1;
	ShootGem * shootingGem;
protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;
	

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	__int64 m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

private:

};

#endif // __GAME_H__
