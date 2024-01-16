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
#include <string.h>

void	init_img(t_Image *img)
{
	int		bpp;
	int		sizeline;
	int		endian;

	
	img->image = mlx_new_image(img->mlx, WIDTH, HEIGHT);
	img->data = mlx_get_data_addr(img->image, &bpp, &sizeline, &endian);
	img->bpp = bpp;
	img->sizeline = sizeline;
	img->endian = endian;
}

void	put_pixel_in_img(t_Image *img, int x, int y, int color)
{
	if (x > 0 && y >= 0 && x <= WIDTH && y < HEIGHT)
		*(int *)&img->data[(x * img->bpp >> 3) + (y * img->sizeline)] = color;
}

int	new_zoom(int button, int x, int y, t_Image *img)
{
	(void)x;
	(void)y;
	if (!img->zoom)
		img->zoom = 1;
	if (button == 4)
		img->zoom *= 1.2;
	else if (button == 5)
		img->zoom *= 0.8;
	mlx_clear_window(img->mlx, img->win);
	if (strcmp(img->type, "julia") == 0) //------HAY UN STRCMP
		generate_julia_set(*img);
	else
		generate_mandel_set(*img);
	return (0);
}
