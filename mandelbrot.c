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

	g = (t_Mandm){-2.0, 2.0, -2.0, 2.0, 150, 0, 0, 0, 0, 0};
	while (g.y < HEIGHT)
	{
		g.x = 1;
		while (g.x < WIDTH)
		{
			g.r_p = g.xmin + (g.x - img.mx) * (g.xmax - g.xmin) / (WIDTH - 1);
			g.r_p *= img.zoom;
			g.i_p = g.ymin + (g.y - img.my) * (g.ymax - g.ymin) / (HEIGHT - 1);
			g.i_p *= img.zoom;
			apply_zoom(&img, &g);
			z = (t_Complex){g.r_p, g.i_p};
			c = z;
			g.iterations = set_iteration(z, c, g.max_iterations);
			img.color = select_color(g.iterations, g.max_iterations, img);
			put_pixel_in_img(&img, g.x++, g.y, img.color);
		}
		g.y++;
	}
	mlx_put_image_to_window(img.mlx, img.win, img.image, 0, 0);
}
