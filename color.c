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

int	rgb_to_hex(int red, int green, int blue) //transforms the rgb color got in the previous functions to hex
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

	//using byte shifting, we place the "numbers" we got in their correct place so it turns an hex number,
	//and return it to take it back in both julia and mandelbrot generate function
	hex_color = (red << 16) | (green << 8) | blue;
	return (hex_color);
}

void	second_aux(int *iterations, int *red, int *green) //called inside first_aux, in this file
{
	if (*iterations >= 255)
	{
		*green = 0;
		*iterations -= 255;
		if (*iterations >= 255)
		{
			*red = 255;
			*iterations -= *red;
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

void	first_aux(int *iterations, int *red, int *green, int *blue) //called inside select_color, in this file
{
	if (*iterations >= 255)
	{
		*red = 0;
		*iterations -= 255;
		if (*iterations >= 255)
		{
			*blue = 255;
			*iterations -= *blue;
			second_aux(iterations, red, green);
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

int	select_color(int iterations, int max_iterations, t_Image img) //originally, this was an algorythm made of 80 lines,
//but because of norminette i had to split it into three functions: select_color, first_aux, and second_aux
{
	t_Rgb	col;

	col = (t_Rgb){0, 0, 0, 0}; //declares red, green, blue and final_color

	if (iterations == max_iterations) //in case we reach max iterations, we will call rgb_to_hex with all values 0 so we get black
		return (col.final_color = rgb_to_hex(col.red, col.green, col.blue));

	iterations *= 15 + img.multip; //the max number of iterations is a little low, so we need to increase it with Multip,
	//a variable that may change in change_color, at the end of the file
	if (iterations <= 255) //in case the iterations are lower than 255, we return the final color done by rgb_to_hex
	//using iterations instead of red, so it would be the same
		return (col.final_color = rgb_to_hex(iterations, col.green, col.blue));

	//there starts the algorythm. Knowing how rgb works, we increase or decrease the variables red, green and blue depending on the iterations.
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

void	change_color(int keycode, t_Image *img) //function called in move_left_right, in image.c
{
	if (!img->multip) //we initialize multip in case it wasnt
		img->multip = 0;
	if (keycode == 69) //in case we press "+", multip increases by one
		img->multip += 1;
	if (keycode == 78) //if we press "-", multip decreases by one
		img->multip -= 1;
}
