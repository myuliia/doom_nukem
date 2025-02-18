/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuliia <myuliia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 15:18:31 by myuliia           #+#    #+#             */
/*   Updated: 2019/09/02 19:50:56 by myuliia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static	void	pick_map_sprites(t_doom *doom, int i)
{
	IMG[4].exist++;
	IMG[4].im_x[i] = (MAP_SPRT[i].coord.x * SCL) - 50;
	IMG[4].im_y[i] = (MAP_SPRT[i].coord.y * SCL) - 50;
}

static	void	pick_buttons(t_doom *doom, int i)
{
	if (i != 2)
	{
		IMG[i].im_x = (double *)malloc(sizeof(double) * 100);
		IMG[i].im_y = (double *)malloc(sizeof(double) * 100);
		ft_null_items(doom, i, 0);
		ft_null_items(doom, i, 1);
		IMG[i].exist = 0;
	}
}

void			ft_prepare_editor(t_doom *doom, int i)
{
	INIT4(DEDI.is_sector, 1, DEDI.ind_text, 5, \
		DEDI.press.ind_action, 5, DEDI.fl_or_ceil, 1);
	while (++i < NB_BUTTONS)
		pick_buttons(doom, i);
	if (doom->player.coord.x && doom->player.coord.y)
	{
		IMG[1].exist = 1;
		IMG[1].im_x[1] = (doom->player.coord.x * SCL) - 50;
		IMG[1].im_y[1] = (doom->player.coord.y * SCL) - 50;
		INIT2(IMG[4].exist, 0, i, -1);
		while (++i < (int)doom->map.num_sprites)
			pick_map_sprites(doom, i);
		ft_null_items(doom, 4, IMG[4].exist);
		IMG[3].exist = doom->map.num_paint;
		ft_null_items(doom, 3, doom->map.num_paint);
		i = -1;
		while (++i < (int)doom->map.num_paint)
		{
			IMG[3].im_x[i] = (doom->map.paint[i].v1.x * SCL) - 50;
			IMG[3].im_y[i] = (doom->map.paint[i].v1.y * SCL) - 50;
		}
	}
	INIT5(DEDI.fline.num_line1, -1, DEDI.fline.num_line2, -1, \
		DEDI.fline.sec1, -1, DEDI.fline.sec2, 1, DEDI.which_wall, 1);
}

void			ft_render_editor(t_doom *doom)
{
	ft_render_interface(doom);
	ft_render_previous(doom);
	ft_render_other(doom);
}

int				check_points(t_doom *doom)
{
	if (comp_real(MAX(MAPSEC[DEDI.fline.sec1].vert[DEDI.fline.num_line1].x,\
	MAPSEC[DEDI.fline.sec1].vert[DEDI.fline.num_line1 + 1].x),\
	MAX(MAPSEC[DEDI.k].vert[DEDI.i].x, \
	MAPSEC[DEDI.k].vert[DEDI.i + 1].x), 1) &&
	comp_real(MIN(MAPSEC[DEDI.fline.sec1].vert[DEDI.fline.num_line1].x, \
	MAPSEC[DEDI.fline.sec1].vert[DEDI.fline.num_line1 + 1].x), \
	MIN(MAPSEC[DEDI.k].vert[DEDI.i].x, \
	MAPSEC[DEDI.k].vert[DEDI.i + 1].x), 1) &&
	comp_real(MAX(MAPSEC[DEDI.fline.sec1].vert[DEDI.fline.num_line1].y, \
	MAPSEC[DEDI.fline.sec1].vert[DEDI.fline.num_line1 + 1].y), \
	MAX(MAPSEC[DEDI.k].vert[DEDI.i].y, \
	MAPSEC[DEDI.k].vert[DEDI.i + 1].y), 1) &&
	comp_real(MIN(MAPSEC[DEDI.fline.sec1].vert[DEDI.fline.num_line1].y, \
	MAPSEC[DEDI.fline.sec1].vert[DEDI.fline.num_line1 + 1].y), \
	MIN(MAPSEC[DEDI.k].vert[DEDI.i].y, \
	MAPSEC[DEDI.k].vert[DEDI.i + 1].y), 1))
	{
		return (1);
	}
	return (0);
}
