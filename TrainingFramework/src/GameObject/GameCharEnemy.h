#pragma once
#include "GameCharacter.h"
class GameCharEnemy :
	public GameCharacter
{
public:
	GameCharEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~GameCharEnemy();
};
