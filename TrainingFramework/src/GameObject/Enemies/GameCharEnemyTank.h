#pragma once
#include "GameCharEnemy.h"

class GameCharEnemyTank : public GameCharEnemy {
public:
	GameCharEnemyTank(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	~GameCharEnemyTank();
private:

};
