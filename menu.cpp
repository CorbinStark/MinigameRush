#include "menu.h"

//list of names of minigame states
const int MINIGAME_COUNT = 5;
const char* MINIGAMES[MINIGAME_COUNT] = {
    "DODGE",
    "DODGE",
    "DODGE",
    "DODGE",
    "DODGE"
};

MenuState::MenuState() {
    //randomize the order of the minigames
    for(int i = 0; i < 10; i++) {
        minigameOrder.push_back( MINIGAMES[random_int(0, MINIGAME_COUNT-1)] );
    }
    subMenu = MENU_MAIN;
}

//initialize on state being switched to
void MenuState::enter() {
    font = load_neighbors_font(3);
}
//code to run every frame
void MenuState::update(RenderBatch* batch, vec2 mouse) {
    draw_rectangle(batch, 0, 0, 1920.0f, 1080.0f, SKYBLUE);

    if(subMenu == MENU_MAIN) {
        int yInitial = (get_virtual_height() / 2) - (((16 * 3) + 15) * 3);

        draw_text(batch, &font, "  Minigame Rush!", (get_virtual_width() / 2) - (get_string_width(&font, "  Minigame Rush!") / 2), 50);

        if (text_button(batch, &font, "  Play Game", &yInitial, mouse)) {
            subMenu = MENU_PLAY;
        }
        if (text_button(batch, &font, "  Options", &yInitial, mouse)) {
            subMenu = MENU_OPTIONS;
        }
        if (text_button(batch, &font, "  Credits", &yInitial, mouse)) {
            subMenu = MENU_CREDITS;
        }
        if (text_button(batch, &font, "  Exit", &yInitial, mouse)) {
            exit(0);
        }
    }
    if(subMenu == MENU_PLAY) {
        if(minigameOrder.size() == 0) {
            //done with the 10 minigames, start boss minigame
            //on winning boss minigame, go to the next round of minigames, harder now 
            //(in WarioWare this meant speeding everything up so you had less time to react)
        }
        //set state to current minigame, then pop it off
        set_state(parent, minigameOrder.back().c_str());
        minigameOrder.pop_back();
    }
}
//dispose data (textures, dynamic data allocated during enter(), etc.) when another state is switched to and this one is inactive
void MenuState::leave() {
    dispose_font(&font);
}

//destructor for when state is removed
MenuState::~MenuState() {

}
