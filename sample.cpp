//
//
//                  SAMPLE CODE, USE THIS AS A TEMPLATE FOR YOUR MINIGAMES
//
//

#include "sample.h"

SampleState::SampleState() {
    samplePersistentVariable = new int;
}

//initialize on state being switched to
void SampleState::enter() {
    sampleVariable = new int;
}

//code to run every frame
MinigameState SampleState::update(RenderBatch* batch, vec2 mouse, int speed) {
    if(is_key_pressed(KEY_V) /*if win condition */)
        return MINIGAME_VICTORY;
    if(is_key_pressed(KEY_D) /*if lose condition */)
        return MINIGAME_DEFEAT;

    //insert game here

    //return running if the minigame hasn't ended in a victory or defeat yet.
    return MINIGAME_RUNNING;
}

//dispose data (textures, dynamic data allocated during enter(), etc.) when another state is switched to and this one is inactive
void SampleState::leave() {
    delete sampleVariable;
}

//destructor for when state is removed
SampleState::~SampleState() {
    delete samplePersistentVariable;
}
