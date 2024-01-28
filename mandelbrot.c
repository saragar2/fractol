/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:49:43 by saragar2          #+#    #+#             */
/*   Updated: 2024/01/16 18:49:59 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	generate_mandel_set(t_Image img)
{
	t_Mandm		g;
	t_Complex	z;
	t_Complex	c;

	g = (t_Mandm){-2.0, 2.0, -2.0, 2.0, WIDTH, HEIGHT, 150, 0, 0, 0, 0, 0};
	while (g.y < g.height)
	{
		g.x = 1;
		while (g.x < g.width)
		{
			g.real_part = g.xmin + (g.x + img.moveX) * (g.xmax - g.xmin) / (g.width - 1);
			g.real_part *= img.zoom;
			g.imag_part = g.ymin + (g.y - img.moveY) * (g.ymax - g.ymin) / (g.height - 1);
			g.imag_part *= img.zoom;
			z = (t_Complex){g.real_part, g.imag_part};
			c = z;
			g.iterations = set_iteration(z, c, g.max_iterations);
			img.color = select_color(g.iterations, g.max_iterations);
			put_pixel_in_img(&img, g.x++, g.y, img.color);
		}
		g.y++;
	}
	mlx_put_image_to_window(img.mlx, img.win, img.image, 0, 0);
}


