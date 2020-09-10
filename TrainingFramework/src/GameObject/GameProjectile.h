#pragma once
#include "GameCharacter.h"

enum PROJECTILE_TYPE {
	PROJECTILE_NORMAL = 0,
	PROJECTILE_CM_SKILL,
	PROJECTILE_LINA_SKILL,
	PROJECTILE_DROW_1,
	PROJECTILE_DROW_2,
	PROJECTILE_DROW_3,
	PROJECTILE_DROW_4,
};

class GameProjectile :
	public GameCharacter
{
public: 
	GameProjectile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	GameProjectile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, int projectileType);
	~GameProjectile();

	void Update(GLfloat deltaTime);
	bool CheckProjectileOutOfBounds();

private:
	GLint m_projectileChar;
	GLint m_projectileType;	
};