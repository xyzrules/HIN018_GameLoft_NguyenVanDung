#pragma once
#include "gamestatebase.h"

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);

	void Update(float deltaTime);
	void Draw();
	
	void SetNewPostionForBullet();

private:
	void Gameplay();
	void SpawnPlayer(int playerId, Vector2 playerPos);
	void SpawnEnemy();
	void SpawnProjectile(int playerChar, int projectileType, Vector2 pos);
	void ProcessCollision(std::shared_ptr<GameCharacter> char1, std::shared_ptr<GameCharacter> char2);

	std::vector<std::shared_ptr<GameCharPlayer>> m_listPlayer;
	std::vector<std::shared_ptr<GameProjectile>> m_listProjectile;
	std::vector<std::shared_ptr<GameCharEnemy>> m_listEnemy;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;
};

