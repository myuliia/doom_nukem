/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 12:09:33 by apavlov           #+#    #+#             */
/*   Updated: 2019/08/28 19:53:19 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int			win_spr_event(t_doom *d, t_sprite *sprite)
{
	(void)sprite;
	d->game.win = 1;
	d->ui.gun_num = 2;
	Mix_HaltChannel(-1);
	Mix_PlayMusic(d->sound.music[6], 1);
	return (0);
}

int			talk_event(t_doom *d, t_sprite *sprite)
{
	if (sprite->num_of_sound > -1)
		if (!(Mix_Playing(4)))
			Mix_PlayChannel(4, d->sound.mobsound[sprite->num_of_sound], 0);
	return (0);
}

int			give_event(t_doom *d, t_sprite *sprite)
{
	static int click = 0;

	if (sprite->num_of_sound > -1 && click == 0)
	{
		Mix_PlayChannel(4, d->sound.mobsound[3], 0);
		click++;
	}
	else if (click == 1 && d->game.picked_key[2] == 0)
	{
		d->game.picked_key[2] = 1;
		Mix_PlayChannel(6, d->sound.pickup[2], 0);
	}
	else if (!(Mix_Playing(4)))
		Mix_PlayChannel(4, d->sound.mobsound[4], 0);
	return (0);
}

int			toxic_event(t_doom *d, t_sprite *sprite)
{
	static Uint32	start_time = 0;
	static int		i = 0;
	static Uint32	toxicity_rate = 20000;

	if (start_time < toxicity_rate)
	{
		d->map.sprites[sprite->spr_num].changes = 1;
		if (((start_time + d->game.dt) / 100) > (start_time / 100))
			d->map.inverse_colors = !d->map.inverse_colors;
		if (((start_time + d->game.dt) / 100) > (start_time / 100))
			d->map.fog_color = d->changes.fog_colors[i++ % 9];
		start_time += d->game.dt;
	}
	else
	{
		d->map.sprites[sprite->spr_num].changes = 0;
		d->map.inverse_colors = d->changes.start_inversion_type;
		i = 0;
		start_time = 0;
		d->map.fog_color = d->changes.map_fog_color_before;
	}
	return (0);
}
