#include "Resources.h"
#include "SDL_macros.h"

vector<Resources::FontInfo> Resources::fonts_{
	//
			{ ARIAL16, "resources/fonts/ARIAL.ttf", 16 }, //
			{ ARIAL24, "resources/fonts/ARIAL.ttf", 24 } //
};

vector<Resources::ImageInfo> Resources::images_{
	//
			{ Asteroid, "resources/images/asteroid.png"}, //
			{ Fighter, "resources/images/airplanes.png"}, //
			{ Health, "resources/images/heart.png"}, //
			{ Bullet, "resources/images/whiterect.png"}, //
};

vector<Resources::TextMsgInfo> Resources::messages_{
	//
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

