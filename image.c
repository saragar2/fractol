/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:50:15 by saragar2          #+#    #+#             */
/*   Updated: 2023/12/29 11:50:17 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_img(t_3d *d)
{
	int		bpp;
	int		sizeline;
	int		endian;

	
	d->img.image = mlx_new_image(d->img.mlx, WIDTH, HEIGHT);
	d->img.data = mlx_get_data_addr(d->img.image, &bpp, &sizeline, &endian);
	d->img.bpp = bpp;
	d->img.sizeline = sizeline;
	d->img.endian = endian;
}

void	put_pixel_in_img(t_3d *d, int x, int y, int color)
{
	if (x > 0 && y >= 0 && x <= WIDTH && y < HEIGHT)
		*(int *)&d->img.data[(x * d->img.bpp >> 3) + (y * d->img.sizeline)] = color;
}

int	new_zoom(int button, int x, int y, t_3d *d)
{
	(void)x;
	(void)y;
	if (!d->img.zoom)
		d->img.zoom = 1;
	if (button == 4)
		{printf("4\n\n\n");
		d->img.zoom *= 1.1;}
	else if (button == 5)
		{printf("5\n\n\n");
		d->img.zoom *= 0.9;}
	mlx_clear_window(d->img.mlx, d->img.win);
	generate_julia_set(*d);
	return (0);
}