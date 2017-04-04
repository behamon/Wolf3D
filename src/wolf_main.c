/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: behamon <behamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 18:39:00 by behamon           #+#    #+#             */
/*   Updated: 2016/12/27 20:34:45 by behamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	safety_check(char *arg)
{
	if (ft_strequ(arg, "1"))
	{
		if (!check_file("maps/map1") || !wolf_init("maps/map1"))
			return (0);
	}
	else if (ft_strequ(arg, "2"))
	{
		if (!check_file("maps/map2") || !wolf_init("maps/map2"))
			return (0);
	}
	else if (ft_strequ(arg, "3"))
	{
		if (!check_file("maps/map3") || !wolf_init("maps/map3"))
			return (0);
	}
	else
		ft_putendl("usage: ./wolf3d [1 | 2 | 3]");
	return (1);
}

int			main(int ac, char **av)
{
	if (ac == 2)
	{
		if (!safety_check(av[1]))
			ft_putendl("Error.");
	}
	else
		ft_putendl("usage: ./wolf3d [1 | 2 | 3]");
	return (0);
}
