// [HACKATHON 3-9]
// TODO: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
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
#include "utility.h"
#include "shared.h"

#include "scene_settings.h"

// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.
static ALLEGRO_BITMAP* settingBackground = NULL;
static ALLEGRO_SAMPLE_ID settingsMusic;
static int settingBackgroundW ;
static int settingBackgroundH ;


static Button btnMusicUp, btnMusicDown, btnEffectUp, btnEffectDown, back;

static void init() {

    
    btnMusicUp = button_create(150, 550, 170, 100, "Assets/musicUp1.png", "Assets/musicUp2.png");
    btnMusicDown = button_create(150, 650, 170, 100, "Assets/musicDown1.png", "Assets/musicDown2.png");
    btnEffectUp = button_create(500, 550, 170, 100, "Assets/effectUp1.png", "Assets/effectUp2.png");
    btnEffectDown = button_create(500, 650, 170, 100, "Assets/effectDown1.png", "Assets/effectDown2.png");
    back = button_create(0, 20, 200, 70, "Assets/back1.png", "Assets/back2.png");
    
    
    settingBackground = load_bitmap("Assets/settingBackground.png");
    settingBackgroundW = al_get_bitmap_width(settingBackground);
    settingBackgroundH = al_get_bitmap_height(settingBackground);
    stop_bgm(settingsMusic);
    settingsMusic = play_bgm(settingMusic, music_volume);
    

}


static void draw(void) {

    al_clear_to_color(al_map_rgb(245, 246, 246));
    //  調圖檔比例
    const float scale = 0.5;
    const float offset_w = (SCREEN_W >> 1) - 0.5 * scale * settingBackgroundW;
    const float offset_h = (SCREEN_H >> 1) - 0.5 * scale * settingBackgroundH -80;

    //draw title image
    al_draw_scaled_bitmap(settingBackground, 0, 0, settingBackgroundW, settingBackgroundH, offset_w,offset_h,  settingBackgroundW * scale, settingBackgroundH * scale, 0);
    
    char music[100];
    snprintf(music, sizeof(music), "%0.f", music_volume*10);
    al_draw_text(
        menuFont,
        al_map_rgb(0, 0, 0),
        100,
        650,
        ALLEGRO_ALIGN_LEFT,
        music
    );
    
    char effect[100];
    snprintf(effect, sizeof(effect), "%0.f", effect_volume*10);
    al_draw_text(
        menuFont,
        al_map_rgb(0, 0, 0),
        450,
        650,
        ALLEGRO_ALIGN_LEFT,
        effect
    );
        // [HACKATHON 3-3]
        // TODO: Draw button
        // Uncomment and fill the code below
        drawButton(btnMusicUp);
        drawButton(btnMusicDown);
        drawButton(btnEffectUp);
        drawButton(btnEffectDown);
        drawButton(back);

}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
    //    [HACKATHON 3-7]
    //    TODO: Update button's status(hovered), and utilize the function `pnt_in_rect`, which you just implemented
    //    Uncomment and fill the code below
    btnMusicUp.hovered = buttonHover(btnMusicUp,mouse_x,mouse_y);
    btnMusicDown.hovered = buttonHover(btnMusicDown,mouse_x,mouse_y);
    btnEffectUp.hovered = buttonHover(btnEffectUp,mouse_x,mouse_y);
    btnEffectDown.hovered = buttonHover(btnEffectDown,mouse_x,mouse_y);
    back.hovered = buttonHover(back,mouse_x,mouse_y);
    
}


//    [HACKATHON 3-8]
//    TODO: When btnSettings clicked, switch to settings scene
//  `game_change_scene` is defined in `game.h`.
//  You can check line 121 `scene_menu.c` to see how to use this function.
//  And find the corresponding function for `scene_setting`
//     Utilize the member defined in struct `Button`.
//  The logic here is
//  `if clicked the mouse` && `mouse position is in the area of button`
//           `Enter the setting scene`
//    Uncomment and fill the code below

static void on_mouse_down() {
    if (btnMusicUp.hovered && music_volume < 0.99){
        music_volume += 0.1;
        game_log("musicUp");
        stop_bgm(settingsMusic);
        settingsMusic = play_bgm(settingMusic, music_volume);
        
    }
    else if (btnMusicDown.hovered && music_volume > 0.1){
        music_volume -= 0.1;
        game_log("musicDown");
        stop_bgm(settingsMusic);
        settingsMusic = play_bgm(settingMusic, music_volume);
    }
    else if (btnEffectUp.hovered && effect_volume < 0.99){
        effect_volume += 0.1;
        game_log("effectUp");
        stop_bgm(settingsMusic);
        settingsMusic = play_bgm(settingMusic, music_volume);
    }
    else if (btnEffectDown.hovered && effect_volume > 0.1){
        effect_volume -= 0.1;
        game_log("effectDown");
        stop_bgm(settingsMusic);
        settingsMusic = play_bgm(settingMusic, music_volume);
    }
    if (back.hovered){
        stop_bgm(settingsMusic);
        game_change_scene(scene_menu_create());
    }
    game_log("musicVolume = %1.f, effectVolume = %1.f", music_volume, effect_volume);
}

//not used yet
static void destroy() {
    stop_bgm(settingsMusic);
    al_destroy_bitmap(settingBackground);
    //    [HACKATHON 3-10]
    //    TODO: Destroy button images
    //    Uncomment and fill the code below

    al_destroy_bitmap(btnMusicUp.hovered_img);
    al_destroy_bitmap(btnMusicUp.default_img);
    al_destroy_bitmap(btnMusicDown.hovered_img);
    al_destroy_bitmap(btnMusicDown.default_img);
    al_destroy_bitmap(btnEffectUp.hovered_img);
    al_destroy_bitmap(btnEffectUp.default_img);
    al_destroy_bitmap(btnEffectDown.hovered_img);
    al_destroy_bitmap(btnEffectDown.default_img);

}

static void on_key_down(int keycode) {

    switch (keycode) {
        case ALLEGRO_KEY_ENTER:
            game_change_scene(scene_main_create());
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
Scene scene_settings_create(void) {

    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.name = "Settings";
    scene.initialize = &init;
    scene.draw = &draw;
    scene.destroy = &destroy;
    scene.on_mouse_move = &on_mouse_move;
    scene.on_mouse_down = &on_mouse_down;

    game_log("Settings scene created");
    return scene;
}
