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
	if (argc != 2)
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
	//t_Image	img;
	t_3d	d;

	d.img.zoom = 1.0;
	if (code_error(argc, argv) == 0)
		return (0);
	d.img.mlx = mlx_init();
	if (strcmp(argv[1], "julia") == 0) //---HAY UN STRCMP
	{
		d.img.win = mlx_new_window(d.img.mlx, WIDTH, HEIGHT, "Conjunto de Julia");
		init_img(&d);
		generate_julia_set(d);
	}
	else
	{
		d.img.win = mlx_new_window(d.img.mlx, WIDTH, HEIGHT, "Conjunto de Mandelbrot");
		init_img(&d);
		generate_mandel_set(d);
	}
	mlx_mouse_hook(d.img.win, new_zoom, &d);
	mlx_key_hook(d.img.win, go_exit, (void *)d.img.mlx);
	mlx_hook(d.img.win, 17, 0, go_exit_cross, (void *)d.img.mlx);
	mlx_loop(d.img.mlx);
	return (0);
}
