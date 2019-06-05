#ifndef MENU_H
#define MENU_H

#include "states.h"
#include "utils.h"
#include "ENGINE/bahamut.h"
#include <vector>

enum SubMenu {
    MENU_MAIN,
    MENU_PLAY,
    MENU_OPTIONS,
    MENU_CREDITS,
    MENU_EXIT
};

//struct, everything public, don't overcomplicate things.
struct MenuState : public State {
    //initialize on creation
    MenuState();

    //initialize on state being switched to
    void enter();
    //code to run every frame
    void update(RenderBatch* batch, vec2 mouse);
    //dispose data (textures, dynamic data allocated during enter(), etc.) when another state is switched to and this one is inactive
    void leave();

    //destructor for when state is removed
    ~MenuState();

    //  VARIABLES  //
    BitmapFont font;
    std::vector<std::string> minigameOrder;
    SubMenu subMenu;
};

#endif
