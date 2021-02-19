// COMP710 GP 2D Framework 2020
#ifndef __GAME_H__
#define __GAME_H__
#include<vector>
#include<array>
// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class Gem;
class GameObject;

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
	void GameObjectShootingGems();
	void GemShot();
	void Aim(int angle);
	void SwitchGems();
	void CheckCollision(int i);
	void ForListLoop(int, float);
	void GameSprites();
	void HexGrid();
	float CalcAngleVel();
	void PlayerLoss(int i);
	void RoofLower();
	void GemLower(int i);
	void EmptySpot();
	void SplashScreen(BackBuffer& backBuffer);
	void MainMenu(BackBuffer& backBuffer);
	void PauseMenu(BackBuffer& backBuffer);
	void MenuInput(int input);
	void GameActive(BackBuffer& backBuffer);

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
	Sprite * rock1;
	Sprite * rock2;
	Sprite * rock3;
	Sprite * rock4;
	Sprite * wallSprite1;
	Sprite * wallSprite2;
	Sprite * wallPlate1;
	Sprite * wallPlate2;
	Sprite * deadZone;
	Sprite * roof;
	Sprite * logo;
	Sprite * button1;
	Sprite * button2;
	Sprite * buttonSelect;
	GameObject * aimLine;
	GameObject * object1;
	std::vector<Gem*> objectlist;
	std::vector<float> hexGridX; // had to much trouble creating a 2D vector
	//std::vector<float> hexGridY;
	Gem * gem;
	Gem * shootingGem;
	Gem * movingGem;
	Gem * currentGem;
	Gem * nextGem;
	Gem * swapGem;
	bool onStartup;
	bool menu;
	bool isPaused;
	bool movingGemBool;
	bool gameActive;
protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;
	int roofCount;

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
