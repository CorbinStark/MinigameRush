#include "bahamut.h"
#include "states.h"
#include "menu.h"

int main() {
	init_window(1200, 900, "Minigame Rush", false, true, true);
	set_fps_cap(60);
	set_clear_color(SKYBLUE);
	set_vsync(true);

	RenderBatch* batch = &create_batch();
	Shader basic = load_default_shader_2D();

	StateGroup group = { 0 };
	add_state(&group, new MenuState(), "menu");
	set_state(&group, "menu");

	while (window_open()) {
		vec2 mouse = get_mouse_pos();
		set_viewport(0, 0, get_window_width(), get_window_height());

		begin_drawing();
		begin2D(batch, basic);
			upload_mat4(basic, "projection", orthographic_projection(0, 0, get_window_width(), get_window_height(), -1, 1));
			update_current_state(&group, batch, mouse);
		end2D(batch);
		end_drawing();
	}

	dispose_batch(batch);
	dispose_window();
}