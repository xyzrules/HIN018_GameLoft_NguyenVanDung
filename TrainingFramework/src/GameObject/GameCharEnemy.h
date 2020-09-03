#pragma once
#include "GameCharacter.h"
#include "GameCharPlayer.h"

class GameCharEnemy :
	public GameCharacter
{
public:
	GameCharEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	GameCharEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, GLfloat moveSpeedVertical, GLfloat moveSpeedHorizontal);
	~GameCharEnemy();

	void Update(GLfloat deltaTime, GameCharPlayer &player);

	GLint GetEnemyId();
	void SetEnemyId(GLint enemyId);

	GLint GetEnemyCharacter();
	void SetEnemyCharacter(GLint enemyCharacter);

private:
	void ChasePlayer(GameCharPlayer &player);

	GLint m_enemyId;
	GLint m_enemyCharacter;
};

