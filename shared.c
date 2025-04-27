// [shared.c]
// you should define the shared variable declared in the header here.

#include "shared.h"
#include "utility.h"
#include "game.h"
// #include "scene_menu.h"

ALLEGRO_FONT* font_pirulen_32;
ALLEGRO_FONT* font_pirulen_24;
ALLEGRO_SAMPLE* winBGM = NULL;
ALLEGRO_SAMPLE* gameoverBGM = NULL;
ALLEGRO_SAMPLE* themeMusic = NULL;
ALLEGRO_SAMPLE* settingMusic = NULL;
ALLEGRO_SAMPLE* PACMAN_MOVESOUND = NULL;
ALLEGRO_SAMPLE* PACMAN_DEATH_SOUND = NULL;
ALLEGRO_SAMPLE* PACMAN_EATFRUIT_SOUND = NULL;
ALLEGRO_SAMPLE* PACMAN_GHOST_SOUND = NULL;
ALLEGRO_SAMPLE* PACMAN_ANGRY_SOUND = NULL;
ALLEGRO_SAMPLE* PACMAN_LUCKY_SOUND = NULL;
ALLEGRO_FONT* menuFont = NULL;
ALLEGRO_FONT* minecraftFont = NULL;
ALLEGRO_FONT* minecraftFont2 = NULL;

int fontSize = 30;
int minecraftSize = 40;
int minecraftSize2 = 20;

float music_volume = 0.5;
float effect_volume = 0.5;
bool gameDone = false;

/*
    A way to accelerate is load assets once.
    And delete them at the end.
    This method does provide you better management of memory.
    
*/
void shared_init(void) {
    
    minecraftFont2 = load_font("Assets/Minecraft2.ttf", minecraftSize2);
    minecraftFont = load_font("Assets/Minecraft2.ttf", minecraftSize);
    menuFont = load_font("Assets/Minecraft.ttf", fontSize);
    winBGM = load_audio("Assets/Music/Win.ogg");
    gameoverBGM = load_audio("Assets/Music/Gameover.ogg");
    themeMusic = load_audio("Assets/Music/original_theme.ogg");
    settingMusic = load_audio("Assets/Music/pacman_intermission.ogg");
    PACMAN_MOVESOUND = load_audio("Assets/Music/pacman-chomp.ogg");
    PACMAN_DEATH_SOUND = load_audio("Assets/Music/pacman_death.ogg");
    PACMAN_EATFRUIT_SOUND = load_audio("Assets/Music/pacman_eatfruit.ogg");
    PACMAN_GHOST_SOUND = load_audio("Assets/Music/pacman_eatghost.ogg");
    PACMAN_ANGRY_SOUND = load_audio("Assets/Music/angry.ogg");
    PACMAN_LUCKY_SOUND = load_audio("Assets/Music/lucky.ogg");
}

void shared_destroy(void) {

    al_destroy_font(minecraftFont2);
    al_destroy_font(minecraftFont);
    al_destroy_font(menuFont);
    al_destroy_sample(winBGM);
    al_destroy_sample(gameoverBGM);
    al_destroy_sample(themeMusic);
    al_destroy_sample(settingMusic);
    al_destroy_sample(PACMAN_MOVESOUND);
    al_destroy_sample(PACMAN_DEATH_SOUND);
    al_destroy_sample(PACMAN_EATFRUIT_SOUND);
    al_destroy_sample(PACMAN_GHOST_SOUND);
    al_destroy_sample(PACMAN_ANGRY_SOUND);
    al_destroy_sample(PACMAN_LUCKY_SOUND);
}
