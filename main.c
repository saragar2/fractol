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

int	go_exit(int keycode, void *param)
{
	(void)param;
	if (keycode == 53)
		exit(0);
	return (0);
}

int	go_exit_cross(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int	code_error(int argc, char **argv)
{
	if (argc != 2)
	{
		f_printf("Utiliza \"julia\" o \"mandelbrot\"");
		return (0);
	}
	if (f_strcmp(argv[1], "julia") != 0 && f_strcmp(argv[1], "mandelbrot") != 0)
	{
		f_printf("Utiliza \"julia\" o \"mandelbrot\"");
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_Image	img;

	img.type = argv[1];
	img.zoom = 1.0;
	if (code_error(argc, argv) == 0)
		return (0);
	img.mlx = mlx_init();
	if (f_strcmp(img.type, "julia") == 0)
	{
		img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Julia");
		init_img(&img);
		generate_julia_set(img);
	}
	else
	{
		img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Mandelbrot");
		init_img(&img);
		generate_mandel_set(img);
	}
	mlx_mouse_hook(img.win, new_zoom, &img);
	mlx_key_hook(img.win, go_exit, (void *)img.mlx);
	mlx_hook(img.win, 17, 0, go_exit_cross, (void *)img.mlx);
	mlx_loop(img.mlx);
	return (0);
}
