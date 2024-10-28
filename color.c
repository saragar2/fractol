/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:12:59 by saragar2          #+#    #+#             */
/*   Updated: 2023/12/27 11:13:03 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	rgb_to_hex(int red, int green, int blue)
{
	int	hex_color;

	//error control
	if (red < 0)
		red = 0;
	else if (red > 255)
		red = 255;
	if (green < 0)
		green = 0;
	else if (green > 255)
		green = 255;
	if (blue < 0)
		blue = 0;
	else if (blue > 255)
		blue = 255;
	hex_color = (red << 16) | (green << 8) | blue;
	return (hex_color);
}

void	second_aux(int *iterations, int *red, int *green, int *blue)
{
	if (*iterations >= 255)
	{
		*green = 0;
		*iterations -= 255;
		if (*iterations >= 255)
		{
			*red = 255;
			*iterations -= *red;
			color_fix(iterations, blue);
		}
		else
		{
			*red = *iterations;
			*iterations = -1;
		}
	}
	else
	{
		*green -= *iterations;
		*iterations = -1;
	}
}

void	first_aux(int *iterations, int *red, int *green, int *blue)
{
	if (*iterations >= 255)
	{
		*red = 0;
		*iterations -= 255;
		if (*iterations >= 255)
		{
			*blue = 255;
			*iterations -= *blue;
			second_aux(iterations, red, green, blue);
		}
		else
		{
			*blue = *iterations;
			*iterations = -1;
		}
	}
	else
	{
		*red -= *iterations;
		*iterations = -1;
	}
}

int	select_color(int iterations, int max_iterations, t_Image img)
{
	t_Rgb	col;

	col = (t_Rgb){0, 0, 0, 0};
	if (iterations == max_iterations)
		return (col.final_color = rgb_to_hex(col.red, col.green, col.blue));
	iterations *= 20 + img.multip;
	if (iterations <= 255)
		return (col.final_color = rgb_to_hex(iterations, col.green, col.blue));
	while (iterations >= 0)
	{
		col.red = 255;
		iterations -= col.red;
		if (iterations >= 255)
		{
			col.green = 255;
			iterations -= col.green;
			first_aux(&iterations, &col.red, &col.green, &col.blue);
		}
		else
		{
			col.green = iterations;
			iterations = -1;
		}
	}
	return (col.final_color = rgb_to_hex(col.red, col.green, col.blue));
}

void	change_color(int keycode, t_Image *img)
{
	if (!img->multip)
		img->multip = 0;
	if (keycode == 65451)
		img->multip += 1;
	if (keycode == 65453)
		img->multip -= 1;
}
