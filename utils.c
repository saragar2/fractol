/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:02:25 by saragar2          #+#    #+#             */
/*   Updated: 2024/01/16 21:02:29 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	f_printf(char const *str)
{
	int	cntrl;

	while (*str != '\0')
		cntrl = write(1, str++, 1);
	if (cntrl == -1)
		return ;
}

int	f_strcmp(const char *s1, const char *s2)
{
	int	cont;

	cont = 0;
	while (*s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		cont = (unsigned char)*s1 - (unsigned char)*s2;
	return (cont);
}

void	color_fix(int *iterations, int *blue)
{
	if (*iterations >= 255)
	{
		*blue = 0;
		*iterations -= 255;
	}
	else
	{
		*blue -= *iterations;
		*iterations = 0;
	}
}

void	init_img_soft(t_Image *i, char **argv)
{
	i->win = NULL;
	i->mlx = mlx_init();
	i->color = 0;
	i->zoom = 1;
	i->old_zoom = 0;
	i->mx = 0;
	i->my = 0;
	i->type = argv[1];
	i->multip = 0;
}
