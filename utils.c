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

void	f_printf(char const *str) //a very basic function that prints strings
{
	while (*str != '\0')
		write(1, str++, 1);
}

int	f_strcmp(const char *s1, const char *s2) //compares two strings to see if they are different
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
