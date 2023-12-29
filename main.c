/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:05:23 by saragar2          #+#    #+#             */
/*   Updated: 2023/12/27 18:05:25 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <string.h>

int go_exit(int keycode, void *param)
{
	(void)param;
	if (keycode == 53)
    	exit(0);
    return 0;
}
int go_exit_cross(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	code_error(int argc, char **argv)
{
	if (argc == 1)
	{
		printf("Utiliza \"julia\" o \"mandelbrot\" para ejecutar el programa");
		return (0);
	}
	if (strcmp(argv[1], "julia") != 0 && strcmp(argv[1], "mandelbrot") != 0) //---HAY UN STRCMP
	{
		printf("Parámetro no válido. Utiliza \"julia\" o \"mandelbrot\""); //---HAY UN PRINTF
		return (0);
	}
	return (1);
}

int main(int argc, char *argv[])
{
	t_Img	img;

	if (code_error(argc, argv) == 0)
		return (0);
	img.mlx = mlx_init();
	if (strcmp(argv[1], "julia") == 0) //---HAY UN STRCMP
	{
		img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Conjunto de Julia");
		init_img(&img);
		generate_julia_set(img.mlx, img.win, img);
	}
	return (0);
}