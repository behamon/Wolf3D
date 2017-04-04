/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: behamon <behamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 19:45:00 by behamon           #+#    #+#             */
/*   Updated: 2016/12/27 19:45:11 by behamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		image_ops(t_env *e)
{
	raycasting(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (1);
}

static int		xpm_images_loader(t_env *e)
{
	int fd;

	if ((fd = open("tex/tex2.xpm", O_RDONLY)) < 0)
		return (0);
	if ((fd = open("tex/tex3.xpm", O_RDONLY)) < 0)
		return (0);
	if (!(e->xpm.xpm = mlx_xpm_file_to_image(e->mlx, "tex/tex2.xpm",
			&e->xpm.w, &e->xpm.h)))
		return (0);
	if (!(e->xpm2.xpm = mlx_xpm_file_to_image(e->mlx, "tex/tex3.xpm",
			&e->xpm.w, &e->xpm.h)))
		return (0);
	if (!(e->xpm.img = mlx_get_data_addr(e->xpm.xpm, &e->xpm.bpp,
			&e->xpm.sline, &e->xpm.e)))
		return (0);
	if (!(e->xpm2.img = mlx_get_data_addr(e->xpm2.xpm, &e->xpm2.bpp,
			&e->xpm2.sline, &e->xpm2.e)))
		return (0);
	return (1);
}

static int		launch_mlx(t_env *e)
{
	if (!(e->mlx = mlx_init()))
		return (0);
	e->cam.x = (e->data.pos_x) * e->var.wal + (e->var.wal / 2);
	e->cam.y = (e->data.pos_y) * e->var.wal + (e->var.wal / 2);
	e->win = mlx_new_window(e->mlx, WIDTH, HEIGHT, "wolf3d - behamon");
	e->img = mlx_new_image(e->mlx, WIDTH, HEIGHT);
	e->img_data = mlx_get_data_addr(e->img, &e->bpp, &e->sline, &e->endian);
	if (!xpm_images_loader(e))
	{
		ft_putendl("Texture error.");
		return (1);
	}
	mlx_hook(e->win, 2, 3, mouvement_hooks, e);
	mlx_hook(e->win, 6, 1L << 6, mouse_hook, e);
	mlx_loop_hook(e->mlx, image_ops, e);
	mlx_key_hook(e->win, key_hooks, e);
	mlx_hook(e->win, 17, 1, exit_hook, e);
	mlx_loop(e->mlx);
	return (1);
}

int				wolf_init(char *mapname)
{
	t_env	*e;

	if (!(e = (t_env*)malloc(sizeof(t_env))))
		return (0);
	e->mapname = mapname;
	e->var.wal = 256;
	e->var.fov = 60;
	e->data.dir = 0;
	e->data.pos_x = 1;
	e->data.pos_y = 1;
	e->gg = 0;
	if (!(file_loader(e)))
		return (0);
	if (!(launch_mlx(e)))
		return (0);
	free_env(e);
	return (1);
}
