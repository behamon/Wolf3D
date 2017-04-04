/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: behamon <behamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 18:02:34 by behamon           #+#    #+#             */
/*   Updated: 2016/12/27 18:02:46 by behamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				exit_hook(int button, t_env *e)
{
	int i;

	i = 0;
	(void)button;
	exit(1);
	free_env(e);
	return (0);
}

int				key_hooks(int keycode, t_env *e)
{
	if (keycode == 53)
	{
		exit(1);
		free_env(e);
	}
	if (e->gg == 1)
	{
		ft_putendl("GG !");
		exit(1);
		free_env(e);
	}
	return (0);
}
