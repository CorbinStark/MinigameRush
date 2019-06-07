#ifndef DODGE_H
#define DODGE_H

#include "states.h"
#include "utils.h"
#include "ENGINE/bahamut.h"
#include <vector>

struct Vehicle {
    int x;
    int y;
    int speed;
    Texture img;
};

enum DodgePlayerState {
    DODGE_PLAYER_IDLE,
    DODGE_PLAYER_WALK,
    DODGE_PLAYER_FALL
};

const int NUM_VEHICLES = 3;

//struct, everything public, don't overcomplicate things.
struct DodgeState : public State {
    //initialize on creation
    DodgeState();

    //initialize on state being switched to
    void enter();
    //code to run every frame
    MinigameState update(RenderBatch* batch, vec2 mouse);
    //dispose data (textures, dynamic data allocated during enter(), etc.) when another state is switched to and this one is inactive
    void leave();

    //destructor for when state is removed
    ~DodgeState();

    //  VARIABLES  //
    BitmapFont font;

    bool goingRight;
    int playerX;
    int playerY;
    float yVelocity;
    int timer;

    DodgePlayerState state;
    Animation walk;
    Texture idle;
    Texture fall;
    Texture fallLeft;

    Texture highway;
    Texture light;

    Vehicle vehicles[NUM_VEHICLES];
};

#endif
