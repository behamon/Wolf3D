/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mvt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: behamon <behamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:34:34 by behamon           #+#    #+#             */
/*   Updated: 2017/02/09 13:34:44 by behamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		camera_mouvement_hooks(int keycode, t_env *e)
{
	if (keycode == 123 || keycode == 0)
	{
		if (e->data.dir > 360)
			e->data.dir -= 360;
		e->data.dir += 5;
	}
	if (keycode == 124 || keycode == 2)
	{
		if (e->data.dir < 0)
			e->data.dir += 360;
		e->data.dir -= 5;
	}
}

static void		player_mouvement_hooks(int keycode, t_env *e)
{
	if (keycode == 126 || keycode == 13)
	{
		if (e->map[(int)((e->cam.y - 35 * sin(rad(e->data.dir))) / e->var.wal)]
			[(int)((e->cam.x + 35 * cos(rad(e->data.dir))) / e->var.wal)] != 1)
		{
			e->cam.x += 35 * cos(rad(e->data.dir));
			e->cam.y -= 35 * sin(rad(e->data.dir));
		}
	}
	if (keycode == 125 || keycode == 1)
	{
		if (e->map[(int)((e->cam.y + 35 * sin(rad(e->data.dir))) / e->var.wal)]
			[(int)((e->cam.x - 35 * cos(rad(e->data.dir))) / e->var.wal)] != 1)
		{
			e->cam.x -= 35 * cos(rad(e->data.dir));
			e->cam.y += 35 * sin(rad(e->data.dir));
		}
	}
}

int				mouvement_hooks(int keycode, t_env *e)
{
	player_mouvement_hooks(keycode, e);
	camera_mouvement_hooks(keycode, e);
	if ((int)(e->cam.y / e->var.wal) == e->data.dest_y
		&& ((int)(e->cam.x / e->var.wal) == e->data.dest_x))
		e->gg = 1;
	return (0);
}

int				mouse_hook(int x, int y, t_env *e)
{
	static int		tmp = WIDTH / 2;

	(void)y;
	e->data.dir += 3 * (tmp - x) * e->var.minangle;
	tmp = x;
	return (0);
}
