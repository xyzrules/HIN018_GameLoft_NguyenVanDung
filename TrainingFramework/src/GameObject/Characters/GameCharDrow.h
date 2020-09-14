#pragma once

#include "GameCharPlayer.h"

class GameCharDrow : public GameCharPlayer {
public:
	GameCharDrow(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, int playerId);
	~GameCharDrow();

	
private:
	void ActivateSkill();
};