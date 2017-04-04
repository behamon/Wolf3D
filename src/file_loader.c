/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_loader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: behamon <behamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 19:07:10 by behamon           #+#    #+#             */
/*   Updated: 2017/02/23 19:07:13 by behamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		free_table(char **nbrs)
{
	int i;

	i = 0;
	while (nbrs[i])
	{
		free(nbrs[i]);
		i++;
	}
	free(nbrs);
}

static int		fill_line(char *line, t_env *e, int i)
{
	char	**nbrs;
	int		n;

	nbrs = ft_strsplit(line, ' ');
	n = 0;
	e->width = 0;
	while (nbrs[e->width])
		e->width++;
	if (!(e->map[i] = (int*)malloc(sizeof(int) * e->width)))
		return (0);
	while (nbrs[n])
	{
		e->map[i][n] = ft_atoi(nbrs[n]);
		if (e->map[i][n] == 9)
		{
			e->data.dest_x = n;
			e->data.dest_y = i;
		}
		if (e->map[i][n] > 9 || e->map[i][n] < 0)
			return (0);
		n++;
	}
	free_table(nbrs);
	return (1);
}

static int		get_map(t_env *e, int fd)
{
	int			i;
	char		*line;

	i = 0;
	line = NULL;
	if (!(e->map = (int**)malloc(sizeof(int*) * e->height)))
		return (0);
	while ((get_next_line(fd, &line)) == 1)
	{
		if (!fill_line(line, e, i))
			return (0);
		ft_strdel(&line);
		i++;
	}
	ft_strdel(&line);
	return (1);
}

int				file_loader(t_env *e)
{
	int		fd;

	if ((e->height = map_height(e->mapname)) == 0)
		return (0);
	if (!(fd = open(e->mapname, O_RDONLY)))
		return (0);
	if (!(get_map(e, fd)))
		return (0);
	close(fd);
	return (1);
}
