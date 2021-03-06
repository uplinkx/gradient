/***************************************************************************
 * FILENAME:    main_scene.h
 * DESCRIPTION: Header file for the shared struct in the main scene.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 21Sep2021
***************************************************************************/

#ifndef MAIN_SCENE_H
# define MAIN_SCENE_H

#include "main.h"

typedef struct	s_main_scene
{
	SDLX_button	slider_inc;
	SDLX_button	slider_dec;

	clerps		color_start;
	clerps		color_end;
	SDLX_button	sliders_start;
	SDLX_button	sliders_end;
	SDLX_button	add;
	SDLX_button	del;

	int			scale;
	SDLX_button	resolution;
	SDLX_button	help;

	t_color_sel	color_selector;
	SDLX_button	color_choose;
	SDLX_Sprite	color_slider;

	t_clerp_m	curves;
	int			active_id;
	clerps		*active;

	int			bar_c[WIN_WIDTH * 3];

	SDLX_button	paste;
	SDLX_button	save_file;

	t_switcher	paste_meta;
}				t_main_scene;

void	update_buttons(t_main_scene *scene);
void	draw_slider_color(int color, SDL_Rect *color_rect, int x, SDL_Renderer *renderer);

#endif