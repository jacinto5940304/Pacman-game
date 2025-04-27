#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "scene_menu_object.h"
#include "scene_settings.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "scene_win.h"
#include "utility.h"
#include "shared.h"

#include "scene_settings.h"

/* Internal Variables*/

static ALLEGRO_BITMAP* gameTitle = NULL;
static ALLEGRO_SAMPLE_ID menuBGM;
static int gameTitleW ;
static int gameTitleH ;

// [HACKATHON 3]
// TARGET : use a clickable button to enter setting scene.
// For `Button` struct(object) is defined in `scene_menu_object.h` and `scene_menu_object.c`
// STRONGLY recommend you trace both of them first.

//    [HACKATHON 3-1]
//    TODO: Declare variable for button
//    Uncomment and fill the code below
//static Button btnSettings;

static void init() {


    
    gameTitle = load_bitmap("Assets/win.png");
    gameTitleW = al_get_bitmap_width(gameTitle);
    gameTitleH = al_get_bitmap_height(gameTitle);
    stop_bgm(menuBGM);
    menuBGM = play_bgm(winBGM, music_volume);
    
    
    
}


static void draw() {

    al_clear_to_color(al_map_rgb(255, 255, 255));

    const float scale = 0.7;
    const float offset_w = (SCREEN_W >> 1) - 0.5 * scale * gameTitleW;
    const float offset_h = (SCREEN_H >> 1) - 0.5 * scale * gameTitleH;

    //draw title image
    al_draw_scaled_bitmap(
        gameTitle,
        0, 0,
        gameTitleW, gameTitleH,
        offset_w, offset_h,
        gameTitleW * scale, gameTitleH * scale,
        0
    );
    al_draw_text(
        menuFont,
        al_map_rgb(0, 0, 0),
        SCREEN_W/2,
        SCREEN_H - 150,
        ALLEGRO_ALIGN_CENTER,
        "PRESS \"ENTER\" TO CONTINUE"
    );
}



static void destroy() {
    stop_bgm(menuBGM);
    al_destroy_bitmap(gameTitle);
    
}

static void on_key_down(int keycode) {

    switch (keycode) {
        case ALLEGRO_KEY_ENTER:
            game_change_scene(scene_menu_create());
            break;
        default:
            break;
    }
}

// TODO: Add more event callback functions such as update, ...

// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

// The only function that is shared across files.
Scene scene_win_create(void) {

    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.name = "Win";
    scene.initialize = &init;
    scene.draw = &draw;
    scene.destroy = &destroy;
    scene.on_key_down = &on_key_down;



    // TODO: Register more event callback functions such as keyboard, mouse, ...
    game_log("Menu scene created");
    return scene;
}
