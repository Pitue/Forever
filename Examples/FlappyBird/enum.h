#ifndef __FOREVER_FLAPPYBIRD_H__
#define __FOREVER_FLAPPYBIRD_H__

#include <stdint.h>

enum Textures : uint_least8_t{
	ICON = 0,
	TEXT_0,
	TEXT_1,
	TEXT_2,
	TEXT_3,
	TEXT_4,
	TEXT_5,
	TEXT_6,
	TEXT_7,
	TEXT_8,
	TEXT_9,
	BACKGROUND_DAY,
	BACKGROUND_NIGHT,
	BASE,
	BLUEBIRD_DOWNFLAP,
	BLUEBIRD_MIDFLAP,
	BLUEBIRD_UPFLAP,
	GAMEOVER,
	MESSAGE,
	PIPE_GREEN,
	PIPE_RED,
	REDBIRD_DOWNFLAP,
	REDBIRD_MIDFLAP,
	REDBIRD_UPFLAP,
	YELLOWBIRD_DOWNFLAP,
	YELLOWBIRD_MIDFLAP,
	YELLOWBIRD_UPFLAP
};

#endif // !__FOREVER_FLAPPYBIRD_H__
