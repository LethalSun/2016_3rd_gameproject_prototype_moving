#pragma once
namespace BFE_IDCA_DEFINE
{
	enum CHARACTER_STATE
	{
		STATE_STOP = 0,
		STATE_MOVE = 1,
		STATE_ATTACK = 2
	};

	enum INPUT
	{
		KEY_UP = 1,
		KEY_DOWN = 2,
		KEY_RIGHT = 4,
		KEY_LEFT = 8,
		KEY_A = 16
	};

	enum ACTIONS {
		NO_MOVE = 0,
		TOP = 1,
		BOTTOM = 2,
		//ERROR_INPUT1 = 3,
		LEFT = 8,
		TOP_RIGTH = 5,
		BOTTOM_RIGHT = 6,
		RIGHT = 4,
		TOP_LEFT = 9,
		BOTTOM_LEFT = 10,
		DIRECTION_BIT = 15,
		ATTACK = 16,
		GET_ACTION_BIT = 240
		//ERROR_INPUT2 = 12,
		//ERROR_INPUT3 = 7,
		//ERROR_INPUT4 = 11,
		//ERROR_INPUT5 = 13,
		//ERROR_INPUT6 = 14,
		//ERROR_INPUT7 = 15,
	};

	const int PIXEL_PER_SECOND = 100;
	const int NUM_OF_SPRITE_FILE_PER_ACTIONS = 10;
	const float ANIMATION_SPEED = 0.1f;
	const float HIT_ANIMATION_SPEED = 0.1f;
	const int ATTACK_RANGE_X = 37;
	const int ATTACK_RANGE_Y = 47;
	const char ARCH_BISHOP_FILE_NAME[] = "archbishop";
	const char SPRITE_FRAME_FILE_EXTENTION[] = ".png";
	const char PLIST_FILE_NAME[] = "spriteFrameIdca.plist";
}