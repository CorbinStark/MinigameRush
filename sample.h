//
//
//                  SAMPLE CODE, USE THIS AS A TEMPLATE FOR YOUR MINIGAMES
//
//

#ifndef SAMPLE_H
#define SAMPLE_H

#include "states.h"
#include "utils.h"
#include "ENGINE/bahamut.h"
#include <vector>

//struct, everything public, don't overcomplicate things.
struct SampleState : public State {
    //initialize on creation
    SampleState();

    //initialize on state being switched to
    void enter();
    //code to run every frame
    MinigameState update(RenderBatch* batch, vec2 mouse, int speed);
    //dispose data (textures, dynamic data allocated during enter(), etc.) when another state is switched to and this one is inactive
    void leave();

    //destructor for when state is removed
    ~SampleState();

    //  VARIABLES  //
    int* sampleVariable;
    int* samplePersistentVariable;
};

#endif
