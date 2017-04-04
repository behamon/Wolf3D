/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: behamon <behamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:45:35 by behamon           #+#    #+#             */
/*   Updated: 2017/02/21 16:45:36 by behamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static char		**get_file(char *mapname, char **map)
{
	char	*line;
	int		fd;
	int		i;
	int		height;

	i = 0;
	if ((height = map_height(mapname)) == 0)
		return (0);
	if (!(map = (char**)malloc(sizeof(char*) * (height + 1))))
		return (0);
	if (!(fd = open(mapname, O_RDONLY)))
		return (0);
	while ((get_next_line(fd, &line)) == 1)
	{
		map[i] = ft_strdup(line);
		ft_strdel(&line);
		i++;
	}
	ft_strdel(&line);
	map[i] = NULL;
	close(fd);
	return (map);
}

static int		middle_check(char **map, int j, int len)
{
	int		i;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		if (map[i][0] != '1')
			return (0);
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != ' '
				&& map[i][j] != '1' && map[i][j] != '9')
				return (0);
			j++;
		}
		if (map[i][len] != '1')
			return (0);
		if (j - 1 != len)
			return (0);
		i++;
	}
	return (1);
}

static int		parse_map(char **map, char *mapname)
{
	int		j;
	int		len;
	int		height;

	j = 0;
	if (map[1][2] == '1' || (height = map_height(mapname)) == 0)
		return (0);
	while (map[0][j])
	{
		if (map[0][j] != '1' && map[0][j] != ' ')
			return (0);
		j++;
	}
	len = j - 1;
	if (!middle_check(map, j, len))
		return (0);
	j = 0;
	while (map[height - 1][j])
	{
		if (map[height - 1][j] != '1' && map[height - 1][j] != ' ')
			return (0);
		j++;
	}
	return (1);
}

int				check_file(char *mapname)
{
	char	**map;
	int		i;
	int		height;

	i = 0;
	map = NULL;
	if (!(map = get_file(mapname, map)))
		return (0);
	if (!parse_map(map, mapname))
		return (0);
	height = map_height(mapname);
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map[i]);
	free(map);
	return (1);
}
