/***************************************************************************
 * FILENAME:    button.c
 * DESCRIPTION: Handles the button functionality.
 *
 * ENVIRONMENT:
 *     macOS Catalina 10.15.7
 *     Visual Studio Code 1.56.2
 * AUTHORS:
 *     Kevin Colour
 * DATES:
 *     Created: 13Sep2021
***************************************************************************/

#include "main.h"

#ifdef EMCC
	#include <emscripten.h>
#endif

void	*button_domain_change(SDLX_button *self, SDL_UNUSED void *meta, SDL_UNUSED size_t length)
{
	int	*num;

	num = self->meta;
	if (SDLX_GAME_RELEASE(g_GameInput, g_GameInput_prev, primleft)) { *num -= 10; }
	if (SDLX_GAME_RELEASE(g_GameInput, g_GameInput_prev, primright)) { *num += 10; }
	return (NULL);
}

void	*button_slider_change(SDLX_button *self, SDL_UNUSED void *meta, SDL_UNUSED size_t length)
{
	clerps	**active;
	int	move_to;

	active = self->meta;
	if (*active == NULL)
		return (NULL);

	if (g_GameInput.GameInput.button_primright != 0)
	{
		move_to = (*active)->slider_b.sprite._dst.x + self->meta_length;
		if (- 9 * SLIDER_SCALE < move_to && move_to < WIN_WIDTH / 2 - 9 * SLIDER_SCALE)
			(*active)->slider_b.sprite._dst.x = move_to;
	}

	return (NULL);
}

#ifdef EMCC

EM_JS(char*, js_paste, (), {
    return Asyncify.handleAsync(async () => {
        document.getElementById("clipping").focus();
        const str = await navigator.clipboard.readText();
        document.getElementById("canvas").focus();
        const size = lengthBytesUTF8(str) + 1;
        const rtn = _malloc(size);
        stringToUTF8(str, rtn, size);
        return rtn;
    });
});

#endif

void	*button_paste(SDLX_button *button, SDL_UNUSED void *meta, SDL_UNUSED size_t length)
{
	char		*paste_text;
	int			color;
	clerps		**active;
	size_t		offset;

	color = 0;
	offset = 0;
	paste_text = NULL;
	active = button->meta;
	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, primleft))
	{

#ifdef EMCC
		paste_text = js_paste();
#else
		paste_text = SDL_GetClipboardText();
#endif

		if (isdigit(paste_text[0]) == SDL_FALSE)
			offset = 1;

		if (*active != NULL)
			SDL_sscanf(&(paste_text[offset]), "%x", &((*active)->s_color));

		SDL_free(paste_text);
	}
	return (NULL);
}

void	*button_add_slider(SDLX_button *button, SDL_UNUSED void *meta, SDL_UNUSED size_t length)
{
	t_clerp_m	*manager;
	int			*id;

	id = button->meta1;
	manager = button->meta;
	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, primleft))
		curve_add(manager, id, 0xFFFFFF);

	return (NULL);
}

void	*button_remove_slider(SDLX_button *button, SDL_UNUSED void *meta, SDL_UNUSED size_t length)
{
	t_clerp_m	*manager;
	int			*id;

	id = button->meta1;
	manager = button->meta;
	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, primleft))
		curve_remove(manager, id);

	return (NULL);
}

void	*button_slider(SDLX_button *button, SDL_UNUSED void *meta, SDL_UNUSED size_t length)
{
	int		*active_id;
	clerps	*actual;

	active_id = button->meta;
	actual = (void *)button - offsetof(clerps, slider_b);
	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, primleft))
		*(active_id) = actual->x;

	return (NULL);
}

void	*button_generate(SDLX_button *button, SDL_UNUSED void *meta, SDL_UNUSED size_t length)
{
	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, primleft))
		button->isTriggered = SDL_TRUE;

	return (NULL);
}

void	*button_view_output(SDLX_button *button, SDL_UNUSED void *meta, SDL_UNUSED size_t length)
{
	char	**string_ptr;
	SDL_bool	*popup_isDisabled;

	string_ptr = button->meta;
	popup_isDisabled = button->meta1;
	if (SDLX_GAME_PRESS(g_GameInput, g_GameInput_prev, primleft))
	{
		*popup_isDisabled = SDL_FALSE;
		button->isTriggered = SDL_TRUE;
		SDL_Log("[Saved]: %s", *string_ptr);
	}

	return (NULL);
}