/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: behamon <behamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 18:00:37 by behamon           #+#    #+#             */
/*   Updated: 2017/01/03 16:25:15 by behamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include "./libft/libft.h"

# define WIDTH 1000
# define HEIGHT 600

# define PI 3.1415926

typedef struct	s_data
{
	double		pos_x;
	double		pos_y;
	double		dir;
	double		dest_x;
	double		dest_y;
}				t_data;

typedef	struct	s_cam
{
	double		x;
	double		y;
}				t_cam;

typedef	struct	s_var
{
	int			ww;
	int			wh;
	double		fov;
	double		wal;
	double		projdist;
	double		minangle;
	double		ray;
}				t_var;

typedef	struct	s_dda
{
	double		first_x;
	double		first_y;
	int			step_x;
	int			step_y;
	double		delta_x;
	double		delta_y;
}				t_dda;

typedef	struct	s_dist
{
	double		ver;
	double		hor;
	double		dist;
}				t_dist;

typedef	struct	s_draw
{
	int			height;
	int			start;
	int			end;
}				t_draw;

typedef	struct	s_hit
{
	int			vertical;
	int			horizontal;
	double		vx;
	double		vy;
	double		hx;
	double		hy;
}				t_hit;

typedef	struct	s_xpm
{
	void		*xpm;
	char		*img;
	int			h;
	int			w;
	int			bpp;
	int			sline;
	int			e;
}				t_xpm;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_data;
	char		*mapname;
	int			**map;
	int			height;
	int			width;
	int			bpp;
	int			sline;
	int			endian;
	int			gg;
	t_xpm		xpm;
	t_xpm		xpm2;
	t_data		data;
	t_hit		hit;
	t_cam		cam;
	t_var		var;
	t_dda		dda;
	t_dist		d;
	t_draw		draw;
}				t_env;

/*
** wolf_init.c
*/

int				wolf_init(char	*mapname);

/*
** file_loader.c
*/

int				file_loader(t_env *e);

/*
** hooks_tools.c
*/

int				exit_hook(int button, t_env *e);
int				key_hooks(int keycode, t_env *e);
int				level_hook(int keycode, t_env *e);

/*
** hooks_mvt.c
*/

int				mouvement_hooks(int keycode, t_env *e);
int				mouse_hook(int x, int y, t_env *e);

/*
** utilities.c
*/

int				map_height(char *mapname);
double			rad(double deg);
void			put_pixel_to_image(int x, int y, t_env *e, unsigned int c);
void			free_env(t_env *e);

/*
** get_config.c
*/

int				get_config(t_env *e, char *line, int i);

/*
** color_and_draw.c
*/

void			draw_column(t_env *e, int x);

/*
** raycasting.g
*/

int				raycasting(t_env *e);

/*
** dda_functions.c (Digital Differential Analysis)
*/

int				perform_dda_x(t_env *e);
int				perform_dda_y(t_env *e);

/*
** check_file.c
*/

int				check_file(char *mapname);

#endif
