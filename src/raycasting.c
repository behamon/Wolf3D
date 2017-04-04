/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: behamon <behamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 17:29:51 by behamon           #+#    #+#             */
/*   Updated: 2017/01/10 17:30:04 by behamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	initiate_variables(t_env *e)
{
	e->var.ww = WIDTH;
	e->var.wh = HEIGHT;
	e->var.ray = e->data.dir + e->var.fov / 2;
	if (e->var.ray > 360)
		e->var.ray -= 360;
	e->var.projdist = ((double)e->var.ww / 2) / tan(rad(e->var.fov) / 2);
	e->var.minangle = e->var.fov / e->var.ww;
}

static void	calculate_wall_height(t_env *e)
{
	double	diff_hor_x;
	double	diff_hor_y;
	double	diff_ver_x;
	double	diff_ver_y;

	diff_hor_x = (e->cam.x - e->hit.hx) * (e->cam.x - e->hit.hx);
	diff_hor_y = (e->cam.y - e->hit.hy) * (e->cam.y - e->hit.hy);
	e->d.hor = sqrt(diff_hor_x + diff_hor_y);
	diff_ver_x = (e->cam.x - e->hit.vx) * (e->cam.x - e->hit.vx);
	diff_ver_y = (e->cam.y - e->hit.vy) * (e->cam.y - e->hit.vy);
	e->d.ver = sqrt(diff_ver_x + diff_ver_y);
	if (e->hit.horizontal == 1 && e->hit.vertical == 0)
		e->d.dist = e->d.hor;
	else if (e->hit.horizontal == 0 && e->hit.vertical == 1)
		e->d.dist = e->d.ver;
	else if (e->d.hor < e->d.ver)
		e->d.dist = e->d.hor;
	else
		e->d.dist = e->d.ver;
	e->d.dist = e->d.dist * cos(rad(e->var.ray - e->data.dir));
	e->draw.height = e->var.wal / e->d.dist * e->var.projdist;
}

int			raycasting(t_env *e)
{
	int		x;

	x = 0;
	initiate_variables(e);
	while (x < e->var.ww)
	{
		if (e->var.ray - e->var.minangle < 0)
			e->var.ray += 360;
		perform_dda_x(e);
		perform_dda_y(e);
		calculate_wall_height(e);
		draw_column(e, x);
		e->var.ray -= e->var.minangle;
		x++;
	}
	return (0);
}
