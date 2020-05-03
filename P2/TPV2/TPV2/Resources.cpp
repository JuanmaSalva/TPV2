#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	//
			{ ARIAL16, "resources/fonts/ARIAL.ttf", 16 }, //
			{ ARIAL24, "resources/fonts/ARIAL.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_{
	//
			{ Blank, "resources/images/blank.png" }, //
			{ TennisBall, "resources/images/tennis_ball.png" }, //
			{ KeyBoardIcon, "resources/images/keyboard.png" }, //
			{ MouseIcon, "resources/images/mouse.png" }, //
			{ AIIcon, "resources/images/ai.png" }, //
			{ SpaceShips, "resources/images/spaceships.png" }, //
			{ Airplanes, "resources/images/airplanes.png"}, //
			{ Star, "resources/images/star.png" }, //
			{ PacMan, "resources/images/pacman.png" }, //
			{ Asteroid, "resources/images/asteroid.png"}, //
			{ Heart, "resources/images/heart.png"},//
			{ White, "resources/images/whiterect.png"}
};

vector<Resources::TextMsgInfo> Resources::messages_{
	//
			{ HelloWorld, "Hello World", { COLOR(0xaaffffff) }, ARIAL16 }, //
			{ PressAnyKey, "Press Any Key to Start", { COLOR(0xaaffbbff) }, ARIAL24 }, //
			{ GameOver, "Game Over", { COLOR(0xffffbbff) }, ARIAL24 } //
};

vector<Resources::MusicInfo> Resources::musics_{
	//
				{ imperial_march, "resources/sound/imperial_march.wav" } //
};

vector<Resources::SoundInfo> Resources::sounds_{
	//
			{ Gun_Shot, "resources/sound/GunShot.wav" }, //
			{ Explosion, "resources/sound/explosion.wav" }
};

