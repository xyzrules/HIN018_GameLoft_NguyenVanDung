/*
#include "GSIntro.h"
#include "GSMenu.h"
*/
#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSCharacterSelect.h"
#include "GSCredits.h"
#include "GSOption.h"
#include "GSInGamePause.h"
#include "GSEndGame.h"

#include "GameStatebase.h"

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateTypes stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case STATE_INVALID:
		break;
	case STATE_Intro:
		gs = std::make_shared<GSIntro>();
		break;
	case STATE_Menu:
		gs = std::make_shared<GSMenu>();
		break;
	case STATE_Play:
		gs = std::make_shared<GSPlay>();
		break;
	case STATE_CharacterSelect:
		gs = std::make_shared<GSCharacterSelect>();
		break;
	case STATE_Credits:
		gs = std::make_shared<GSCredits>();
		break;
	case STATE_Option:
		gs = std::make_shared<GSOption>();
		break;
	case STATE_InGamePause:
		gs = std::make_shared<GSInGamePause>();
		break;
	case STATE_EndGame:
		gs = std::make_shared<GSEndGame>();
		break;
	default:
		break;
	}
	return gs;
}