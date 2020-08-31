#include "GameCharEnemy.h"

GameCharEnemy::GameCharEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	:GameCharacter(model, shader, texture)
{
}

GameCharEnemy::~GameCharEnemy()
{
}
