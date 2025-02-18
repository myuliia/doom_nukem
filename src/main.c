/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 13:51:28 by apavlov           #+#    #+#             */
/*   Updated: 2019/09/03 16:35:20 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			editor_mod(t_doom *doom, char *file_name)
{
	ft_map_editor(doom, file_name);
	return (0);
}

int			game_mod(t_doom *doom, char *file_name)
{
	if (file_name == NULL)
		start_loop(doom);
	else if (doom->file_name == NULL)
	{
		doom->difficulty = 2;
		doom->start_quit = 1;
		doom->file_name = ft_strdup(file_name);
	}
	else
		doom->start_quit = 1;
	if (read_file(doom, doom->file_name) == 0)
		return (error_message("Error with file") + 1);
	if (game_loop(doom) == 0)
		return (error_message("Something really sad is happened") + 1);
	return (0);
}

static void	start_loop_2(t_doom *doom)
{
	doom->start_quit = 0;
	chose_dificulty(doom);
	while (doom->start_quit == 0)
	{
		draw_menu(doom);
		dificulty_events(doom);
		SDL_UpdateWindowSurface(doom->sdl.window);
	}
	free_menu(doom);
}

void		start_loop(t_doom *doom)
{
	doom->start_quit = 0;
	set_mouse(doom);
	show_start(doom);
	while (doom->start_quit == 0)
	{
		draw_menu(doom);
		start_events(doom);
		SDL_UpdateWindowSurface(doom->sdl.window);
	}
	free_menu(doom);
	doom->start_quit = 0;
	chose_level(doom);
	while (doom->file_name == NULL)
	{
		draw_menu(doom);
		level_events(doom);
		SDL_UpdateWindowSurface(doom->sdl.window);
	}
	free_menu(doom);
	start_loop_2(doom);
}

int			main(int argc, char **argv)
{
	t_doom	doom;

	ft_bzero(&doom, sizeof(t_doom));
	srand(time(NULL));
	if (argc == 3 || argc == 2)
	{
		if (ft_strcmp(argv[1], "edit") == 0)
			return (editor_mod(&doom, argv[2]));
		else if (ft_strcmp(argv[1], "play") == 0)
		{
			if (init_sdl(&doom.sdl) == 0)
				return (error_message("Error with SDL init") + 1);
			if (load_all(&doom.texture,
				doom.sdl.surface->format->format, &doom) == 0)
				return (error_message("Error with textures") + 1);
			return (game_mod(&doom, argv[2]));
		}
		else
			print_usage();
	}
	else
		print_usage();
	return (0);
}
