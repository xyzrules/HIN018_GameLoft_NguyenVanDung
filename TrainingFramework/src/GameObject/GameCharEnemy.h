#pragma once
#include "GameCharacter.h"

class GameCharEnemy :
	public GameCharacter
{
public:
	GameCharEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	~GameCharEnemy();

	virtual void Update(GLfloat deltaTime);
	bool CheckEnemyHitAncient();
	virtual bool EnemySpecial();
protected:
	GLfloat m_moveSpeedMultiplyer;
private:
};