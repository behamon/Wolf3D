/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: behamon <behamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 17:26:37 by behamon           #+#    #+#             */
/*   Updated: 2017/01/19 17:26:40 by behamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	init_dda_x(t_env *e)
{
	e->dda.delta_x = e->var.wal / tan(rad(e->var.ray));
	if (e->var.ray > 0 && e->var.ray < 180)
	{
		e->dda.first_y = (int)(e->cam.y / e->var.wal) * e->var.wal - 1;
		e->dda.step_y = -1;
	}
	else
	{
		e->dda.first_y = (int)(e->cam.y / e->var.wal)
			* e->var.wal + e->var.wal;
		e->dda.step_y = 1;
		e->dda.delta_x = -e->dda.delta_x;
	}
	if (e->var.ray > 90 && e->var.ray < 270)
		e->dda.first_x = e->cam.x + (e->cam.y - e->dda.first_y)
			/ tan(rad(e->var.ray)) + 1;
	else
		e->dda.first_x = e->cam.x + (e->cam.y - e->dda.first_y)
			/ tan(rad(e->var.ray));
}

int			perform_dda_x(t_env *e)
{
	int		n;

	n = 0;
	init_dda_x(e);
	e->hit.horizontal = 0;
	while (e->hit.horizontal == 0)
	{
		e->hit.hx = e->dda.first_x + n * e->dda.delta_x;
		e->hit.hy = e->dda.first_y + n * e->dda.step_y * e->var.wal;
		if (e->hit.hx < 0 || e->hit.hx > (e->width - 1) * e->var.wal)
			return (0);
		if (e->map[(int)(e->hit.hy / e->var.wal)]
			[(int)(e->hit.hx / e->var.wal)] > 0)
			e->hit.horizontal = 1;
		n++;
	}
	return (1);
}

static void	init_dda_y(t_env *e)
{
	e->dda.delta_y = e->var.wal * tan(rad(e->var.ray));
	if (e->var.ray > 90 && e->var.ray < 270)
	{
		e->dda.first_x = (int)(e->cam.x / e->var.wal) * e->var.wal - 1;
		e->dda.step_x = -1;
	}
	else
	{
		e->dda.first_x = (int)(e->cam.x / e->var.wal)
			* e->var.wal + e->var.wal;
		e->dda.step_x = 1;
		e->dda.delta_y = -e->dda.delta_y;
	}
	if (e->var.ray > 0 && e->var.ray < 180)
		e->dda.first_y = e->cam.y + (e->cam.x - e->dda.first_x)
			* tan(rad(e->var.ray)) + 1;
	else
		e->dda.first_y = e->cam.y + (e->cam.x - e->dda.first_x)
			* tan(rad(e->var.ray));
}

int			perform_dda_y(t_env *e)
{
	int		n;

	n = 0;
	init_dda_y(e);
	e->hit.vertical = 0;
	while (e->hit.vertical == 0)
	{
		e->hit.vx = e->dda.first_x + n * e->dda.step_x * e->var.wal;
		e->hit.vy = e->dda.first_y + n * e->dda.delta_y;
		if (e->hit.vy < 0 || e->hit.vy > (e->height - 1) * e->var.wal)
			return (0);
		if (e->map[(int)(e->hit.vy / e->var.wal)]
			[(int)(e->hit.vx / e->var.wal)] > 0)
			e->hit.vertical = 1;
		n++;
	}
	return (1);
}
