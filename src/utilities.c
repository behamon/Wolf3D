/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: behamon <behamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 18:17:29 by behamon           #+#    #+#             */
/*   Updated: 2016/12/27 18:17:32 by behamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
** Count number of lines in file (minus map-data)
*/

int		map_height(char *mapname)
{
	char	*line;
	size_t	n_lines;
	int		i;
	int		fd;

	n_lines = 0;
	i = 0;
	if ((fd = open(mapname, O_RDONLY)) <= 0)
		return (0);
	while ((get_next_line(fd, &line)) == 1)
	{
		ft_strdel(&line);
		n_lines++;
	}
	ft_strdel(&line);
	close(fd);
	return (n_lines);
}

/*
** Converts degrees to radians
*/

double	rad(double deg)
{
	return (deg * PI / 180.0);
}

/*
** put pixels to image (lol)
*/

void	put_pixel_to_image(int x, int y, t_env *e, unsigned int c)
{
	int		i;

	i = (x * 4) + (y * e->sline);
	e->img_data[i] = c;
	e->img_data[++i] = c >> 8;
	e->img_data[++i] = c >> 16;
}

/*
** frees map and t_env
*/

void	free_env(t_env *e)
{
	int		i;

	i = 0;
	while (i < e->height)
	{
		free(e->map[i]);
		e->map[i] = NULL;
		i++;
	}
	free(e->map);
	free(e);
	e->map = NULL;
}
