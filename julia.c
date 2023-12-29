/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:13:32 by saragar2          #+#    #+#             */
/*   Updated: 2023/12/27 11:13:35 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	complex_magnitude_squared(t_Complex c)
{
	return (c.real * c.real + c.imag * c.imag);
}

int	julia_set_iteration(t_Complex z, t_Complex c, int maxIterations)
{
	int		iterations;
	double	temp_real;
	double	temp_imag;

	iterations = 0;
	while (complex_magnitude_squared(z) < 4.0 && iterations < maxIterations)
	{
		temp_real = z.real * z.real - z.imag * z.imag + c.real;
		temp_imag = 2.0 * z.real * z.imag + c.imag;
		z.real = temp_real;
		z.imag = temp_imag;
		iterations++;
	}
	return (iterations);
}

void	generate_julia_set(void *mlx, void *win, t_Img img)
{
	t_Mandm		g;
	t_Complex	z;
	t_Complex	c;

	g = (t_Mandm){-2.0, 2.0, -2.0, 2.0, HEIGHT, WIDTH, 0, 0, 0, 0, 0, 0, 0};
	g.max_iterations = 150;
	g.y = 0;
	while (g.y < g.height)
	{
		g.x = 0;
		while (g.x < g.width)
		{
			g.real_part = g.xmin + g.x * (g.xmax - g.xmin) / (g.width - 1);
			g.imag_part = g.ymin + g.y * (g.ymax - g.ymin) / (g.height - 1);
			z = (t_Complex){g.real_part, g.imag_part};
			c = (t_Complex){-0.726, 0.162};
			g.iterations = julia_set_iteration(z, c, g.max_iterations);
			g.color = select_color(g.iterations, g.max_iterations);
			put_pixel_in_img(&img, g.x++, g.y, g.color);
		}
		g.y++;
	}
	mlx_key_hook(win, go_exit, (void *)mlx);
	mlx_hook(win, 17, 0, go_exit_cross, (void *)mlx);
	mlx_loop(mlx);
}
