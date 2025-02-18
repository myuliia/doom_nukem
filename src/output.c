/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 14:10:00 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/23 17:19:09 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			print_usage(void)
{
	ft_putstr("usage: ./doom-nukem {edit, play} {map_name}\n");
	return (0);
}

int			error_message(char *message)
{
	ft_putstr(message);
	ft_putchar('\n');
	return (0);
}

void		draw_fps(t_doom *d, int fps)
{
	char		str[4];
	int			i;
	SDL_Surface	*message;

	i = -1;
	if (fps > 999)
		fps = 999;
	while (++i < 3)
	{
		str[2 - i] = fps % 10 + 48;
		fps /= 10;
	}
	str[3] = 0;
	message = TTF_RenderText_Solid(d->texture.fonts[FPS_F].text_font, \
		str, d->texture.fonts[FPS_F].text_color);
	SDL_BlitSurface(message, NULL, d->sdl.surface, \
		&d->texture.fonts[FPS_F].text_rect);
	SDL_FreeSurface(message);
}
