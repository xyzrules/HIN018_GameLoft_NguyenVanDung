#pragma once

#include "GameCharPlayer.h"

class GameCharWind : public GameCharPlayer {
public:
	GameCharWind(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	~GameCharWind();

private:

};