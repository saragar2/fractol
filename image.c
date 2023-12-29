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

void	init_img(t_Img *img)
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

/*
** Put pixel inside the image.
** shifting right 3 bits (>> 3) is a binary operation equivalent to (/ 8).
** casting the memory address into int * and then dereferencing is to speed up
*/

void	put_pixel_in_img(t_Img *img, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
		*(int *)&img->data[(x * img->bpp >> 3) +
			(y * img->sizeline)] = color;
}