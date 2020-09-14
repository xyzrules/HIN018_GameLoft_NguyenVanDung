#pragma once
#pragma once

#include "GameCharPlayer.h"

class GameCharCM : public GameCharPlayer {
public:
	GameCharCM(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, int playerId);
	~GameCharCM();

private:
	void ActivateSkill();
};