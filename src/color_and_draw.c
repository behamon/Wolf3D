/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_and_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: behamon <behamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 17:47:10 by behamon           #+#    #+#             */
/*   Updated: 2017/01/03 17:47:13 by behamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		get_texel(t_env *e, int y)
{
	int		offset;
	int		line;
	int		r;
	int		g;
	int		b;

	if (e->d.dist == e->d.hor * cos(rad(e->var.ray - e->data.dir)))
		offset = (int)e->hit.hx % (int)e->var.wal;
	else
		offset = (int)e->hit.vy % (int)e->var.wal;
	line = y / (e->draw.height / e->var.wal);
	if (e->xpm.img[line * e->xpm.sline + offset * 4])
	{
		r = e->xpm.img[line * e->xpm.sline + offset * 4];
		g = e->xpm.img[line * e->xpm.sline + offset * 4 + 1];
		b = e->xpm.img[line * e->xpm.sline + offset * 4 + 2];
	}
	else
		return (0);
	return ((r << 16) + (g << 8) + b);
}

static int		get_texel_2(t_env *e, int y)
{
	int		offset;
	int		line;
	int		r;
	int		g;
	int		b;

	if (e->d.dist == e->d.hor * cos(rad(e->var.ray - e->data.dir)))
		offset = (int)e->hit.hx % (int)e->var.wal;
	else
		offset = (int)e->hit.vy % (int)e->var.wal;
	line = y / (e->draw.height / e->var.wal);
	if (e->xpm2.img[line * e->xpm2.sline + offset * 4])
	{
		r = e->xpm2.img[line * e->xpm2.sline + offset * 4];
		g = e->xpm2.img[line * e->xpm2.sline + offset * 4 + 1];
		b = e->xpm2.img[line * e->xpm2.sline + offset * 4 + 2];
	}
	else
		return (0);
	return ((r << 16) + (g << 8) + b);
}

static void		draw_floor(t_env *e, int x, int y, int stop)
{
	int		floor;
	double	r;
	double	g;
	double	b;

	floor = 0x0808080;
	r = 120;
	g = 120;
	b = 120;
	while (y < HEIGHT)
		y++;
	while (y > stop)
	{
		r -= 0.2;
		g -= 0.2;
		b -= 0.2;
		floor = ((int)r << 16) + ((int)g << 8) + (int)b;
		put_pixel_to_image(x, y, e, (int)floor);
		y--;
	}
}

static void		draw_wall(t_env *e, int x, int y, int stop)
{
	while (y < stop)
	{
		if (e->hit.horizontal == 1 && e->hit.vertical == 0)
			put_pixel_to_image(x, y, e, get_texel_2(e, y - e->draw.start));
		else if (e->hit.horizontal == 0 && e->hit.vertical == 1)
			put_pixel_to_image(x, y, e, get_texel(e, y - e->draw.start));
		else if (e->d.hor < e->d.ver)
			put_pixel_to_image(x, y, e, get_texel_2(e, y - e->draw.start));
		else
			put_pixel_to_image(x, y, e, get_texel(e, y - e->draw.start));
		y++;
	}
}

void			draw_column(t_env *e, int x)
{
	int		y;
	int		stop;
	double	sky;

	y = 0;
	sky = 0x00094D4;
	e->draw.start = (HEIGHT / 2) - (e->draw.height / 2);
	while (y < e->draw.start)
	{
		put_pixel_to_image(x, y, e, (int)sky);
		sky -= 0.2;
		y++;
	}
	stop = HEIGHT - y;
	draw_wall(e, x, y, stop);
	draw_floor(e, x, y, stop);
}
