#pragma once
#include "GameCharEnemy.h"

class GameCharEnemyRange : public GameCharEnemy {
public:
	GameCharEnemyRange(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	~GameCharEnemyRange();

	void Update(GLfloat deltaTime);
	bool EnemySpecial();
private:
	bool m_enemyProjectileReady;
	GLfloat m_enemyAttackTimer;
	
};
