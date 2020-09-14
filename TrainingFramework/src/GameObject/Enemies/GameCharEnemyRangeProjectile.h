#pragma once
#include "GameCharEnemy.h"

class GameCharEnemyRangeProjectile : public GameCharEnemy {
public:
	GameCharEnemyRangeProjectile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	~GameCharEnemyRangeProjectile();

private:

};
