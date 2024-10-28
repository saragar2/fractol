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

int	key_control(int keycode, t_Image *img)
{
	if (keycode == 65307)
		on_destroy(img);
	if (keycode == 65361 || keycode == 65362 || keycode == 65363 || keycode == 65364 \
	|| keycode == 65451 || keycode == 65453)
		move_left_right(keycode, img);
	return (0);
}

int	go_exit_cross(t_Image *img)
{
	on_destroy(img);
	return (0);
}

int	code_error(int argc, char **argv, t_Image *img)
{
	if (argc != 2)
	{
		f_printf("use \"julia\", \"mandelbrot\" or \"bs\" (for burning ship)");
		on_destroy(img);
		return (0);
	}
	if (f_strcmp(argv[1], "julia") != 0 && f_strcmp(argv[1], "mandelbrot") != 0 \
	&& f_strcmp(argv[1], "bs") != 0)
	{
		f_printf("use \"julia\", \"mandelbrot\" or \"bs\" (for burning ship)");
		on_destroy(img);
		return (0);
	}
	return (1);
}

void select_fractal(t_Image *img)
{
	if (f_strcmp(img->type, "julia") == 0)
	{
		img->win = mlx_new_window(img->mlx, WIDTH, HEIGHT, "Julia");
		init_img(img);
		generate_julia_set(*img);
	}
	else if (f_strcmp(img->type, "mandelbrot") == 0)
	{
		img->win = mlx_new_window(img->mlx, WIDTH, HEIGHT, "Mandelbrot");
		init_img(img);
		generate_mandel_set(*img);
	}
	else
	{
		img->win = mlx_new_window(img->mlx, WIDTH, HEIGHT, "Burning ship");
		init_img(img);
		generate_bs_set(*img);
	}
}

int	on_destroy(t_Image *i)
{
	if (i == NULL)
		exit(0);
	if (i->mlx && i->win)
	{
		if (i->image)
			mlx_destroy_image(i->mlx, i->image);
		mlx_destroy_window(i->mlx, i->win);
	}
	if (i->mlx)
	{
		mlx_loop_end(i->mlx);
		mlx_destroy_display(i->mlx);
		free(i->mlx);
	}
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_Image	img;

	init_img_soft(&img, argv);
	if (code_error(argc, argv, &img) == 0)
		return (0);
	select_fractal(&img);
	mlx_mouse_hook(img.win, new_zoom, &img);
	mlx_hook(img.win, 2, 1L << 0, key_control, &img);
	mlx_hook(img.win, 17, 0, go_exit_cross, &img);
	mlx_loop(img.mlx);
	on_destroy(&img);
	return (0);
}
