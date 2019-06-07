#ifndef MENU_H
#define MENU_H

#include "states.h"
#include "utils.h"
#include "ENGINE/bahamut.h"
#include "dodge.h"
#include <vector>

//list of names of minigame states
const int MINIGAME_COUNT = 5;
//put your own games here, instead of just 5 dodges
const char* MINIGAMES[MINIGAME_COUNT] = {
    "DODGE",
    "DODGE",
    "DODGE",
    "DODGE",
    "DODGE"
};

enum SubMenu {
    MENU_MAIN,
    MENU_PLAY,
    MENU_BOSS,
    MENU_OPTIONS,
    MENU_CREDITS,
    MENU_EXIT
};

struct Menu {
    BitmapFont font;
    std::vector<std::string> minigameOrder;
    SubMenu subMenu;
    StateGroup group;
    int speed;
};

static inline
Menu load_menu() {
    Menu menu = {0};

    menu.speed = 1;
    menu.font = load_neighbors_font(3);

    for(int i = 0; i < 10; i++) {
        menu.minigameOrder.push_back( MINIGAMES[random_int(0, MINIGAME_COUNT-1)] );
    }
    menu.subMenu = MENU_MAIN;

    //add new minigame states here when created.
    menu.group = {0};
    add_state(&menu.group, new DodgeState(), "DODGE");
    set_state(&menu.group, "DODGE");

    return menu;
}

static inline
void main_menu(Menu* menu, RenderBatch* batch, vec2 mouse) {
    draw_rectangle(batch, 0, 0, 1920.0f, 1080.0f, SKYBLUE);

    if(menu->subMenu == MENU_MAIN) {
        int yInitial = (get_virtual_height() / 2) - (((16 * 3) + 15) * 3);

        draw_text(batch, &menu->font, "  Minigame Rush!", (get_virtual_width() / 2) - (get_string_width(&menu->font, "  Minigame Rush!") / 2), 50);

        if (text_button(batch, &menu->font, "  Play Game", &yInitial, mouse)) {
            menu->subMenu = MENU_PLAY;
        }
        if (text_button(batch, &menu->font, "  Options", &yInitial, mouse)) {
            menu->subMenu = MENU_OPTIONS;
        }
        if (text_button(batch, &menu->font, "  Credits", &yInitial, mouse)) {
            menu->subMenu = MENU_CREDITS;
        }
        if (text_button(batch, &menu->font, "  Exit", &yInitial, mouse)) {
            exit(0);
        }
    }
    if(menu->subMenu == MENU_PLAY) {
        //run current minigame, increase speed in subsequent rounds (or maybe halfway through a round, who knows how it will be implemented)
        //speed could also be replaced with "difficulty" instead, it would still be an int so no refactoring required.
        MinigameState result = update_current_state(&menu->group, batch, mouse, menu->speed);

        if(result != MINIGAME_RUNNING) {
            if(menu->minigameOrder.size() == 0) {
                //done with the 10 minigames, start boss minigame
                //on winning boss minigame, go to the next round of minigames, harder now 
                //(in WarioWare this meant speeding everything up so you had less time to react)
                menu->subMenu = MENU_BOSS;
            }
            //set state to current minigame, then pop it off
            set_state(&menu->group, menu->minigameOrder.back().c_str());
            menu->minigameOrder.pop_back();
            if(result == MINIGAME_VICTORY) {
                //add points
            }
            if(result == MINIGAME_DEFEAT) {
                //bad stuff
            }
        }
    }
}

#endif
