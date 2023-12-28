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
		return (0);
	if (strcmp(argv[1], "julia") != 0 && strcmp(argv[1], "mandelbrot") != 0) //---HAY UN STRCMP
	{
		printf("Parámetro no válido. Utiliza \"julia\" o \"mandelbrot\""); //---HAY UN PRINTF
		return (0);
	}
	return (1);
}

int main(int argc, char *argv[])
{
	void *mlx;
	void *win;

	if (code_error(argc, argv) == 0)
		return (0);
	mlx = mlx_init();
	if (strcmp(argv[1], "julia") == 0) //---HAY UN STRCMP
	{
		win = mlx_new_window(mlx, 1000, 1000, "Conjunto de Julia");
		generate_julia_set(mlx, win);
	}
	return (0);
}