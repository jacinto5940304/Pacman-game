
#include "ghost.h"
#include "pacman_obj.h"
#include "map.h"
#include "game.h"
/* Shared variables */
#define GO_OUT_TIME 256
extern uint32_t GAME_TICK_CD;
extern uint32_t GAME_TICK;
extern ALLEGRO_TIMER* game_tick_timer;
extern const int cage_grid_x, cage_grid_y;

/* Declare static function prototypes */
static void ghost_red_move_script_FREEDOM(Ghost* ghost, Map* M);
static void ghost_pink_move_script_FREEDOM(Ghost* ghost, Map* M, Pacman* pacman);
static void ghost_blue_move_script_FREEDOM(Ghost* ghost, Map* M);
static void ghost_orange_move_script_FREEDOM(Ghost* ghost, Map* M);

static void ghost_red_move_script_BLOCKED(Ghost* ghost, Map* M);

static void ghost_red_move_script_FREEDOM(Ghost* ghost, Map* M) {

//    static Directions probal[4], proba2[4]; // possible movement
//    int cnt1 = 0, cnt2 = 0;
//    for (Directions i = 1; i <= 4; i++){
//        if (ghost_movable(ghost, M, i, true)){
//            probal[cnt1++] = i;
//            if (ghost->objData.preMove == 1 && i != 4) proba2[cnt2++] = i;
//            if (ghost->objData.preMove == 2 && i != 3) proba2[cnt2++] = i;
//            if (ghost->objData.preMove == 3 && i != 2) proba2[cnt2++] = i;
//            if (ghost->objData.preMove == 4 && i != 1) proba2[cnt2++] = i;
//        }
//
//        if (cnt1 == 1) ghost_NextMove(ghost, probal[generateRandomNumber(0, cnt1 - 1)]);
//        else ghost_NextMove (ghost, proba2[ generateRandomNumber (0, cnt2 - 1)]);
//    }
    static Directions proba[4], curDir; // possible movement
    int cnt = 0;
    for (Directions i = 1; i <= 4; i++)
        if (ghost_movable(ghost, M, i, true)&&(i!=4-ghost->objData.preMove+1))     proba[cnt++] = i;
    if(cnt == 0) curDir = 4-ghost->objData.preMove+1;
    else curDir = proba[generateRandomNumber(0, cnt-1)];
    ghost_NextMove(ghost, curDir);
    ghost->objData.preMove = curDir;
}

static void ghost_pink_move_script_FREEDOM(Ghost* ghost, Map* M, Pacman* pacman) {

    Directions shortestDirection = shortest_path_direc(M, ghost->objData.Coord.x, ghost->objData.Coord.y, pacman->objData.Coord.x, pacman->objData.Coord.y);
    static Directions proba[4], curDir; // possible movement
    int cnt = 0;
    for (Directions i = 1; i <= 4; i++)
        if (ghost_movable(ghost, M, i, true)&&(i == shortestDirection)) proba[cnt++] = i;
    if(cnt == 0) curDir = 4-ghost->objData.preMove+1;
    else curDir = proba[generateRandomNumber(0, cnt-1)];
    ghost_NextMove(ghost, curDir);
    ghost->objData.preMove = curDir;
}

static void ghost_blue_move_script_FREEDOM(Ghost* ghost, Map* M) {

    static Directions proba[4], curDir; // possible movement
    int cnt = 0;
    for (Directions i = 1; i <= 4; i++)
        if (ghost_movable(ghost, M, i, true)&&(i!=4-ghost->objData.preMove+1))     proba[cnt++] = i;
    if(cnt == 0) curDir = 4-ghost->objData.preMove+1;
    else curDir = proba[generateRandomNumber(0, cnt-1)];
    ghost_NextMove(ghost, curDir);
    ghost->objData.preMove = curDir;
}

static void ghost_orange_move_script_FREEDOM(Ghost* ghost, Map* M) {

    static Directions proba[4], curDir; // possible movement
    int cnt = 0;
    for (Directions i = 1; i <= 4; i++)
        if (ghost_movable(ghost, M, i, true)&&(i!=4-ghost->objData.preMove+1))     proba[cnt++] = i;
    if(cnt == 0) curDir = 4-ghost->objData.preMove+1;
    else curDir = proba[generateRandomNumber(0, cnt-1)];
    ghost_NextMove(ghost, curDir);
    ghost->objData.preMove = curDir;
}



static void ghost_red_move_script_BLOCKED(Ghost* ghost, Map* M) {

    switch (ghost->objData.preMove)
    {
    case UP:
        if (ghost->objData.Coord.y == 10)
            ghost_NextMove(ghost, DOWN);
        else
            ghost_NextMove(ghost, UP);
        break;
    case DOWN:
        if (ghost->objData.Coord.y == 12)
            ghost_NextMove(ghost, UP);
        else
            ghost_NextMove(ghost, DOWN);
        break;
    default:
        ghost_NextMove(ghost, UP);
        break;
    }
}

void ghost_red_move_script(Ghost* ghost, Map* M, Pacman* pacman) {
    if (!movetime(ghost->speed))
        return;
        switch (ghost->status)
        {
        case ANGRY:
            ghost_pink_move_script_FREEDOM(ghost, M, pacman);
            break;
        case BLOCKED:
            ghost_red_move_script_BLOCKED(ghost, M);
            if (al_get_timer_count(game_tick_timer) > GO_OUT_TIME)
                ghost->status = GO_OUT;
            break;
        case FREEDOM:
            ghost_red_move_script_FREEDOM(ghost, M);
            break;
        case GO_OUT:
            ghost_move_script_GO_OUT(ghost, M);
            break;
        case GO_IN:
            ghost_move_script_GO_IN(ghost, M);
            if (M->map[ghost->objData.Coord.y][ghost->objData.Coord.x] == 'B') {
                ghost->status = GO_OUT;
                ghost->speed = 2;
            }
            break;
        case FLEE:
            ghost_move_script_FLEE(ghost, M, pacman);
            break;
        default:
            break;
        }

        if(ghost_movable(ghost, M, ghost->objData.nextTryMove, false)){
            ghost->objData.preMove = ghost->objData.nextTryMove;
            ghost->objData.nextTryMove = NONE;
        }
        else if (!ghost_movable(ghost, M, ghost->objData.preMove, false))
            return;

        switch (ghost->objData.preMove) {
        case RIGHT:
            ghost->objData.Coord.x += 1;
            break;
        case LEFT:
            ghost->objData.Coord.x -= 1;
            break;
        case UP:
            ghost->objData.Coord.y -= 1;
            break;
        case DOWN:
            ghost->objData.Coord.y += 1;
            break;
        default:
            break;
        }
        ghost->objData.facing = ghost->objData.preMove;
        ghost->objData.moveCD = GAME_TICK_CD;
}

void ghost_pink_move_script(Ghost* ghost, Map* M, Pacman* pacman) {
    if (!movetime(ghost->speed))
        return;
        switch (ghost->status)
        {
        case ANGRY:
            ghost_pink_move_script_FREEDOM(ghost, M, pacman);
            break;
        case BLOCKED:
            ghost_red_move_script_BLOCKED(ghost, M);
            if (al_get_timer_count(game_tick_timer) > GO_OUT_TIME)
                ghost->status = GO_OUT;
            break;
        case FREEDOM:
            ghost_pink_move_script_FREEDOM(ghost, M, pacman);
            break;
        case GO_OUT:
            ghost_move_script_GO_OUT(ghost, M);
            break;
        case GO_IN:
            ghost_move_script_GO_IN(ghost, M);
            if (M->map[ghost->objData.Coord.y][ghost->objData.Coord.x] == 'B') {
                ghost->status = GO_OUT;
                ghost->speed = 2;
            }
            break;
        case FLEE:
            ghost_move_script_FLEE(ghost, M, pacman);
            break;
        default:
            break;
        }

        if(ghost_movable(ghost, M, ghost->objData.nextTryMove, false)){
            ghost->objData.preMove = ghost->objData.nextTryMove;
            ghost->objData.nextTryMove = NONE;
        }
        else if (!ghost_movable(ghost, M, ghost->objData.preMove, false))
            return;

        switch (ghost->objData.preMove) {
        case RIGHT:
            ghost->objData.Coord.x += 1;
            break;
        case LEFT:
            ghost->objData.Coord.x -= 1;
            break;
        case UP:
            ghost->objData.Coord.y -= 1;
            break;
        case DOWN:
            ghost->objData.Coord.y += 1;
            break;
        default:
            break;
        }
        ghost->objData.facing = ghost->objData.preMove;
        ghost->objData.moveCD = GAME_TICK_CD;
}

void ghost_blue_move_script(Ghost* ghost, Map* M, Pacman* pacman) {
    if (!movetime(ghost->speed))
        return;
        switch (ghost->status)
        {
        case ANGRY:
            ghost_pink_move_script_FREEDOM(ghost, M, pacman);
            break;
        case BLOCKED:
            ghost_red_move_script_BLOCKED(ghost, M);
            if (al_get_timer_count(game_tick_timer) > GO_OUT_TIME)
                ghost->status = GO_OUT;
            break;
        case FREEDOM:
            ghost_blue_move_script_FREEDOM(ghost, M);
            break;
        case GO_OUT:
            ghost_move_script_GO_OUT(ghost, M);
            break;
        case GO_IN:
            ghost_move_script_GO_IN(ghost, M);
            if (M->map[ghost->objData.Coord.y][ghost->objData.Coord.x] == 'B') {
                ghost->status = GO_OUT;
                ghost->speed = 2;
            }
            break;
        case FLEE:
            ghost_move_script_FLEE(ghost, M, pacman);
            break;
        default:
            break;
        }

        if(ghost_movable(ghost, M, ghost->objData.nextTryMove, false)){
            ghost->objData.preMove = ghost->objData.nextTryMove;
            ghost->objData.nextTryMove = NONE;
        }
        else if (!ghost_movable(ghost, M, ghost->objData.preMove, false))
            return;

        switch (ghost->objData.preMove) {
        case RIGHT:
            ghost->objData.Coord.x += 1;
            break;
        case LEFT:
            ghost->objData.Coord.x -= 1;
            break;
        case UP:
            ghost->objData.Coord.y -= 1;
            break;
        case DOWN:
            ghost->objData.Coord.y += 1;
            break;
        default:
            break;
        }
        ghost->objData.facing = ghost->objData.preMove;
        ghost->objData.moveCD = GAME_TICK_CD;
}

void ghost_orange_move_script(Ghost* ghost, Map* M, Pacman* pacman) {
    if (!movetime(ghost->speed))
        return;
        switch (ghost->status)
        {
        case ANGRY:
            ghost_pink_move_script_FREEDOM(ghost, M, pacman);
            break;
        case BLOCKED:
            ghost_red_move_script_BLOCKED(ghost, M);
            if (al_get_timer_count(game_tick_timer) > GO_OUT_TIME)
                ghost->status = GO_OUT;
            break;
        case FREEDOM:
            ghost_orange_move_script_FREEDOM(ghost, M);
            break;
        case GO_OUT:
            ghost_move_script_GO_OUT(ghost, M);
            break;
        case GO_IN:
            ghost_move_script_GO_IN(ghost, M);
            if (M->map[ghost->objData.Coord.y][ghost->objData.Coord.x] == 'B') {
                ghost->status = GO_OUT;
                ghost->speed = 2;
            }
            break;
        case FLEE:
            ghost_move_script_FLEE(ghost, M, pacman);
            break;
        default:
            break;
        }

        if(ghost_movable(ghost, M, ghost->objData.nextTryMove, false)){
            ghost->objData.preMove = ghost->objData.nextTryMove;
            ghost->objData.nextTryMove = NONE;
        }
        else if (!ghost_movable(ghost, M, ghost->objData.preMove, false))
            return;

        switch (ghost->objData.preMove) {
        case RIGHT:
            ghost->objData.Coord.x += 1;
            break;
        case LEFT:
            ghost->objData.Coord.x -= 1;
            break;
        case UP:
            ghost->objData.Coord.y -= 1;
            break;
        case DOWN:
            ghost->objData.Coord.y += 1;
            break;
        default:
            break;
        }
        ghost->objData.facing = ghost->objData.preMove;
        ghost->objData.moveCD = GAME_TICK_CD;
}
