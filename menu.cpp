#include "menu.h"

MenuState::MenuState() {

}

//initialize on state being switched to
void MenuState::enter() {
    font = load_neighbors_font(3);
}
//code to run every frame
void MenuState::update(RenderBatch* batch, vec2 mouse) {
    draw_rectangle(batch, 0, 0, 1920.0f, 1080.0f, SKYBLUE);

    i32 yInitial = (get_window_height() / 2) - (((16 * 3) + 15) * 3);

    draw_text(batch, &font, "  Minigame Rush!", (get_window_width() / 2) - (get_string_width(&font, "  Minigame Rush!") / 2), 50);

    if (text_button(batch, &font, "  Play Game", &yInitial, mouse)) {

    }
    if (text_button(batch, &font, "  Options", &yInitial, mouse)) {

    }
    if (text_button(batch, &font, "  Credits", &yInitial, mouse)) {

    }
    if (text_button(batch, &font, "  Exit", &yInitial, mouse)) {
        exit(0);
    }
}
//dispose data (textures, dynamic data allocated during enter(), etc.) when another state is switched to and this one is inactive
void MenuState::leave() {
    dispose_font(&font);
}

//destructor for when state is removed
MenuState::~MenuState() {

}
