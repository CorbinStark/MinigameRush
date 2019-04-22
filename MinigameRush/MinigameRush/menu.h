#ifndef MENU_H
#define MENU_H

#include "states.h"
#include "bahamut.h"
#include "utils.h"

const int NUM_OPTIONS = 4;

struct MenuState : public State {
	MenuState() {
		font = { 0 };
	}

	void enter() {
		font = load_neighbors_font(3);
	}

	void update(RenderBatch* batch, vec2 mouse) {
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

	void leave() {
		dispose_font(&font);
	}

	~MenuState() {

	}

	BitmapFont font;
};

#endif