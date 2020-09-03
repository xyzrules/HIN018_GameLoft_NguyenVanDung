#pragma once
#include "AnimationSprite.h"
class GameProjectile :
	public AnimationSprite
{
public: 
	GameProjectile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	GameProjectile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, float loopPoint);
	GameProjectile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, int projectileType, int projectileChar);
	~GameProjectile();

	void Update(GLfloat deltaTime);
	bool CheckProjectileOutOfBounds();

private:
	GLint m_projectileType;
	GLint m_projectileChar;
};