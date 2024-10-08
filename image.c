
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

void	init_img(t_Image *img) //used to create an image and get its information. Used in the Main funnction
{
	int		bpp;
	int		sizeline;
	int		endian;

	img->image = mlx_new_image(img->mlx, WIDTH, HEIGHT); //creates the new image
	img->data = mlx_get_data_addr(img->image, &bpp, &sizeline, &endian); //obtains all the information about the image we just created

	//places the info inside the struct
	img->bpp = bpp;
	img->sizeline = sizeline;
	img->endian = endian;
}

void	put_pixel_in_img(t_Image *img, int x, int y, int color) //my own way to print a pixel in the image
{
	if (x > 0 && y >= 0 && x <= WIDTH && y < HEIGHT)
		*(int *)&img->data[(x * img->bpp >> 3) + (y * img->sizeline)] = color; //place the color by calculating
		//the vertical and horizontal offset in bytes
}

int	move_left_right(int keycode, t_Image *img) //called by key_control in main.c, chooses the movement or the color change
{
	//initialize in case it wasnt
	if (!img->mx)
		img->mx = 0;
	if (!img->my)
		img->my = 0;

	if (keycode == 114) //move right pressing the right arrow
		img->mx += 0.5 * img->zoom; //saves the move for X, that is also countered by the zoom so when we use the movement its relative to the zoom
	else if (keycode == 113)
		img->mx -= 0.5 * img->zoom;//move left
	else if (keycode == 111)
		img->my -= 0.5 * img->zoom; //move up
	else if (keycode == 116)
		img->my += 0.5 * img->zoom; //move down
	change_color(keycode, img); //calling the change_color function, in color.c, which checks if we pressed "+" or "-"

	//clears the window and resets by calling the base function
	mlx_clear_window(img->mlx, img->win);
	if (f_strcmp(img->type, "julia") == 0) //checks wich fractal are we doing
		generate_julia_set(*img);
	else
		generate_mandel_set(*img);
	return (0);
}

int	new_zoom(int button, int x, int y, t_Image *img) //called by the mouse zoom in the main function when we do something on the mouse
{
	(void)x;
	(void)y;
	if (!img->zoom) //initialize
		img->zoom = 1;
	img->old_zoom = img->zoom; //saves a copy to compare if there are any changes in the function apply_zoom
	if (button == 5) //if we zoom in, zoom increases
		img->zoom *= 1.2;
	else if (button == 4) //same for zoom out
		img->zoom *= 0.8;

	//for every other thing done in the mouse (clicking) we reset the fractal to its default values
	else
	{
		img->zoom = 1;
		img->mx = 0;
		img->my = 0;
		img->multip = 0;
	}

	//same as in move_left_right, refreshing and recalling
	mlx_clear_window(img->mlx, img->win);
	if (f_strcmp(img->type, "julia") == 0)
		generate_julia_set(*img);
	else
		generate_mandel_set(*img);
	return (0);
}

void	apply_zoom(t_Image *img, t_Mandm *g) //called in the base function so the zome works correctly
{
	//extracting the movement in the real and imaginary part to counter it from the complex number
	if (img->old_zoom != img->zoom || img->zoom == 1)
	{
		g->r_p -= img->mx;
		g->i_p -= img->my;
	}
}
