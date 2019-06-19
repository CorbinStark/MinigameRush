#include "dodge.h"

#define GROUND_LEVEL(x) 1080 - x

DodgeState::DodgeState() {

}

//initialize on state being switched to
void DodgeState::enter() {
    timer = 0;
    font = load_neighbors_font(3);
    //always dispose textures in leave(), they are dynamically allocated data. 
    //(Just on GPU RAM instead of CPU RAM)
    Texture walkframes = load_texture("data/art/dodge/man_walk.png", GL_NEAREST);
    walk = create_animation("walkAnim", walkframes, 2, 11*5, 15*5, 7);
    //scale all images for this minigame by 5, since they are VERY small pixel art images.
    //There are better ways to do this, like using a framebuffer, but for the sake of simplicity
    //I will just multiply all widths and heights by 5.
    walk.img.width *= 5;
    walk.img.height *= 5;

    highway = load_texture("data/art/dodge/highway.png", GL_NEAREST);
    highway.width *= 5;
    highway.height *= 5;
    light = load_texture("data/art/dodge/light_double.png", GL_NEAREST);
    light.width *= 5;
    light.height *= 5;

    state = DODGE_PLAYER_IDLE;
    playerX = 500;
    yVelocity = 0;
    playerY = GROUND_LEVEL(walk.img.height);

    //nearest neighbor scaling (looks better with pixel art)
    idle = load_texture("data/art/dodge/man.png", GL_NEAREST); 
    idle.width *= 5;
    idle.height *= 5;
    fall = load_texture("data/art/dodge/man_fall.png", GL_NEAREST);
    fall.width *= 5;
    fall.height *= 5;

    fallLeft = load_texture("data/art/dodge/man_fall_left.png", GL_NEAREST);
    fallLeft.width *= 5;
    fallLeft.height *= 5;

    for(int i = 0; i < NUM_VEHICLES; ++i) {
        vehicles[i].x = -350;
        vehicles[i].speed = random_int(6, 12);

        int rand = random_int(0, 4);
        if(rand == 0)
            vehicles[i].img = load_texture("data/art/dodge/hotdog.png", GL_NEAREST);
        if(rand == 1)
            vehicles[i].img = load_texture("data/art/dodge/taxi.png", GL_NEAREST);
        if(rand == 2)
            vehicles[i].img = load_texture("data/art/dodge/tractor.png", GL_NEAREST);
        if(rand == 3)
            vehicles[i].img = load_texture("data/art/dodge/trucktank.png", GL_NEAREST);
        if(rand == 4)
            vehicles[i].img = load_texture("data/art/dodge/vendor.png", GL_NEAREST);

        vehicles[i].img.width *= 5;
        vehicles[i].img.height *= 5;
        vehicles[i].y = GROUND_LEVEL(vehicles[i].img.height);
    }
}

//code to run every frame
MinigameState DodgeState::update(RenderBatch* batch, vec2 mouse, int speed) {
    timer++;
    draw_rectangle(batch, 0, 0, 1920.0f, 1080.0f, SKYBLUE);

    draw_texture(batch, highway, 50, GROUND_LEVEL(highway.height));
    draw_texture(batch, highway, 1550, GROUND_LEVEL(highway.height));
    draw_texture(batch, light, 350, GROUND_LEVEL(light.height));

    playerY += yVelocity;

    if(state == DODGE_PLAYER_FALL)
        yVelocity += 1.5;
    if(playerY > GROUND_LEVEL(idle.height)) {
        yVelocity = 0;
        state = DODGE_PLAYER_IDLE;
        playerY = GROUND_LEVEL(idle.height);
    }
    
    if(state == DODGE_PLAYER_IDLE)
        draw_texture(batch, idle, playerX, playerY);
    if(state == DODGE_PLAYER_WALK) {
        update_animation(&walk, timer);
        draw_animation(batch, walk, playerX, playerY, goingRight);
    }
    if(state == DODGE_PLAYER_FALL){
        if(goingRight)
            draw_texture(batch, fall, playerX, playerY);
        else
            draw_texture(batch, fallLeft, playerX, playerY);
    }

    if(is_key_down(KEY_RIGHT)) {
        if(state != DODGE_PLAYER_FALL)
            state = DODGE_PLAYER_WALK;
        goingRight = true;
        playerX+=8;
    }
    else if(is_key_down(KEY_LEFT)) {
        if(state != DODGE_PLAYER_FALL)
            state = DODGE_PLAYER_WALK;
        goingRight = false;
        playerX-=8;
    } else if(playerY == GROUND_LEVEL(idle.height)) { 
        state = DODGE_PLAYER_IDLE;
    }
    if(is_key_pressed(KEY_UP) && state != DODGE_PLAYER_FALL) {
        yVelocity = -26;
        state = DODGE_PLAYER_FALL;
    }

    if(timer > 50)
        vehicles[0].x+=vehicles[0].speed;
    if(timer > 400)
        vehicles[1].x+=vehicles[1].speed;
    if(timer > 750)
        vehicles[2].x+=vehicles[2].speed;

    for(int i = 0; i < NUM_VEHICLES; i++) {
        draw_texture(batch, vehicles[i].img, vehicles[i].x, vehicles[i].y);
        Rect vehicle = {(f32)vehicles[i].x, (f32)vehicles[i].y, (f32)vehicles[i].img.width, (f32)vehicles[i].img.height};
        Rect player = {(f32)playerX, (f32)playerY, (f32)idle.width, (f32)idle.height};
        if(colliding(vehicle, player)) {
            //failure!
            return MINIGAME_DEFEAT;
        }
    }

    if(timer > 15 seconds) {
        //victory!
        return MINIGAME_VICTORY;
    }

    //return running if the minigame hasn't ended in a victory or defeat yet.
    return MINIGAME_RUNNING;
}

//dispose data (textures, dynamic data allocated during enter(), etc.) when another state is switched to and this one is inactive
void DodgeState::leave() {
    dispose_font(&font);
    dispose_texture(walk.img);
    dispose_texture(idle);
    dispose_texture(fall);
    dispose_texture(highway);
    dispose_texture(light);

    for(int i = 0; i < NUM_VEHICLES; ++i) {
        dispose_texture(vehicles[i].img);
    }
}

//destructor for when state is removed
DodgeState::~DodgeState() {

}
