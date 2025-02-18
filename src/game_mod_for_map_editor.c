/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mod_for_map_editor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 14:04:01 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/31 18:32:16 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static int	init_game_window_for_editor(t_sdl *sdl)
{
	if (!(sdl->window = SDL_CreateWindow("DOOM", 100, \
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, \
		WIN_HEIGHT, SDL_WINDOW_SHOWN)))
		return (error_message((char *)SDL_GetError()));
	if (!(sdl->surface = SDL_GetWindowSurface(sdl->window)))
		return (error_message((char *)SDL_GetError()));
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetWindowGrab(sdl->window, 1);
	SDL_SetRelativeMouseMode(1);
	return (1);
}

int			game_mod_editor(t_doom *doom)
{
	if (init_game_window_for_editor(&doom->sdl) == 0)
		return (error_message("Error with SDL init") + 1);
	if (game_loop_for_editor(doom) == 0)
		return (error_message("Something really sad is happened") + 1);
	return (0);
}

static void	free_game_param(t_doom *doom)
{
	free(doom->render.rendered_sectors);
	free(doom->sr.sprites);
	free(doom->render.ztop);
	free(doom->render.zbottom);
	free(doom->render.queue);
	SDL_ShowCursor(SDL_ENABLE);
	SDL_SetWindowGrab(doom->sdl.window, 0);
	SDL_SetRelativeMouseMode(0);
	SDL_FreeSurface(doom->sdl.surface);
	doom->sdl.surface = 0;
	SDL_DestroyWindow(doom->sdl.window);
	doom->sdl.window = 0;
}

void		game_pause(t_doom *doom)
{
	SDL_Rect	bigger;

	if (doom->game.pause == 0)
	{
		game_events(doom);
		prepare_to_rendering(&doom->render, *doom);
		draw_skybox(doom);
		draw_screen(doom);
		bigger = (SDL_Rect){(WIN_WIDTH / 2) - 15, (WIN_HEIGHT / 2) - 15, 0, 0};
		SDL_BlitSurface(doom->editor.images[16].image,
		NULL, doom->sdl.surface, &bigger);
	}
}

int			game_loop_for_editor(t_doom *doom)
{
	if (!init_game_params(doom))
		return (0);
	init_moves(doom);
	while (doom->game.quit != 1)
	{
		doom->ui.prev_time = SDL_GetTicks();
		player_events(doom);
		if (!doom->map.editing)
		{
			free_game_param(doom);
			return (1);
		}
		game_pause(doom);
		doom->ui.curr_time = SDL_GetTicks();
		doom->game.dt = doom->ui.curr_time - doom->ui.prev_time;
		doom->ui.fps = doom->game.dt / 1000.0;
		if (doom->game.pause == 0 && doom->game.hp_level > 0)
			draw_fps(doom, (int)(1.0 / doom->ui.fps));
		SDL_UpdateWindowSurface(doom->sdl.window);
	}
	return (1);
}
