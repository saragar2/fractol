
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

int	move_left_right(int keycode, t_Image *img)
{
	if (!img->mx)
		img->mx = 0;
	if (!img->my)
		img->my = 0;
	if (keycode == 65363)
		img->mx -= 0.5 * img->zoom;
	else if (keycode == 65361)
		img->mx += 0.5 * img->zoom;
	else if (keycode == 65364)
		img->my -= 0.5 * img->zoom;
	else if (keycode == 65362)
		img->my += 0.5 * img->zoom;
	change_color(keycode, img);
	mlx_clear_window(img->mlx, img->win);
	if (f_strcmp(img->type, "julia") == 0)
		generate_julia_set(*img);
	else if (f_strcmp(img->type, "mandelbrot") == 0)
		generate_mandel_set(*img);
	else if (f_strcmp(img->type, "bs") == 0)
		generate_bs_set(*img);
	return (0);
}

int	new_zoom(int button, int x, int y, t_Image *img)
{
	(void)x;
	(void)y;
	if (!img->zoom)
		img->zoom = 1;
	img->old_zoom = img->zoom;
	if (button == 5)
		img->zoom *= 1.2;
	else if (button == 4)
		img->zoom *= 0.8;
	else
	{
		img->zoom = 1;
		img->mx = 0;
		img->my = 0;
		img->multip = 0;
	}
	mlx_clear_window(img->mlx, img->win);
	if (f_strcmp(img->type, "julia") == 0)
		generate_julia_set(*img);
	else if (f_strcmp(img->type, "mandelbrot") == 0)
		generate_mandel_set(*img);
	else if (f_strcmp(img->type, "bs") == 0)
		generate_bs_set(*img);
	return (0);
}

void	apply_zoom(t_Image *img, t_Mandm *g)
{
	if (img->old_zoom != img->zoom || img->zoom == 1)
	{
		g->r_p -= img->mx;
		g->i_p -= img->my;
	}
}
