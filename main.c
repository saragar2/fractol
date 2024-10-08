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

int	key_control(int keycode, void *param)//function called in main to organize the hooks
{
	if (keycode == 9) //if "ESC" is pressed, the program closes in a clean way
		exit(0);
	if (keycode == 114 || keycode == 113 || keycode == 111 || keycode == 116 \
	|| keycode == 69 || keycode == 78) //if any arrow or the "+" or "-" are pressed, we enter
	//to move_left_right, in image.c
		move_left_right(keycode, param);
	return (0);
}

int	go_exit_cross(void *param) //called in the main. It closes the program
{
	(void)param;
	exit(0);
	return (0);
}

int	code_error(int argc, char **argv) //called by the main function, checks main errors and prints
//an erorr code before returning 0
{
	//checks if there is more or less than two arguments
	if (argc != 2)
	{
		f_printf("Use \"julia\" or \"mandelbrot\"");
		return (0);
	}

	//checks if the argv is different from the wanted
	if (f_strcmp(argv[1], "julia") != 0 && f_strcmp(argv[1], "mandelbrot") != 0)
	{
		f_printf("use \"julia\" or \"mandelbrot\"");
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_Image	img;

	img.type = argv[1]; //saving the argument we got frm CLI
	img.zoom = 1.0;
	if (code_error(argc, argv) == 0) //if theres any error in the vaues got by CLI, returns 0
		return (0);
	img.mlx = mlx_init();
	if (f_strcmp(img.type, "julia") == 0)
	{
		img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Julia"); //creates a new window
		init_img(&img);  //call to mlx_init, in image.c, which initialize the image
		generate_julia_set(img); //calls the base function for julia fractal
	}
	else
	{
		//(same as for julia, but for mandelbrot)
		img.win = mlx_new_window(img.mlx, WIDTH, HEIGHT, "Mandelbrot");
		init_img(&img);
		generate_mandel_set(img);
	}
	//all hooks and their loop
	mlx_mouse_hook(img.win, new_zoom, &img); //call to new_zoom, in image.c, when something is done with the mouse
	mlx_key_hook(img.win, key_control, &img); //call to key_control, in this file, when any key is pressed
	mlx_hook(img.win, 17, 0, go_exit_cross, (void *)img.mlx); //call to go_exit_cross, in this file, when
	//the cross on the top of the window is clicked
	mlx_loop(img.mlx);
	return (0);
}
