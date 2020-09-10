#pragma once
#include "GameCharEnemy.h"

class GameCharEnemyMelee : public GameCharEnemy {
public:
	GameCharEnemyMelee(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	~GameCharEnemyMelee();

	void Update(GLfloat deltaTime);
private:

};