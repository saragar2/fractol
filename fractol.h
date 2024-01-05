/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:13:18 by saragar2          #+#    #+#             */
/*   Updated: 2023/12/27 11:13:21 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <mlx.h>

typedef struct s_Complex
{
	double	real;
	double	imag;
}t_Complex;

typedef struct s_Mandm
{
	double		xmin;
	double		xmax;
	double		ymin;
	double		ymax;
	int			width;
	int			height;
	int			max_iterations;
	int			iterations;
	double		real_part;
	double		imag_part;
	int			color;
	int			y;
	int			x;
}t_Mandm;

typedef struct s_Rgb
{
	int	red;
	int	green;
	int	blue;
	int	final_color;
}t_Rgb;

typedef struct s_Image
{
	void	*mlx;
	void	*win;
	int		*image;
	char	*data;
	int		bpp;
	int		sizeline;
	int		endian;
	double	zoom;
}t_Image;

typedef struct		s_3d
{
	t_Image			img;
}t_3d;

double	complex_magnitude_squared(t_Complex c);
int		julia_set_iteration(t_Complex z, t_Complex c, int maxIterations);
void	generate_julia_set(t_3d d);
int		select_color(int iterations, int max_iterations);
void	first_aux(int *iterations, int *red, int *green, int *blue);
void	second_aux(int *iterations, int *red, int *green);
int		rgb_to_hex(int red, int green, int blue);
int		go_exit(int keycode, void *param);
int		go_exit_cross(void *param);
void	init_img(t_3d *d);
void	put_pixel_in_img(t_3d *d, int x, int y, int color);
int		new_zoom(int button, int x, int y, t_3d *d);

# ifndef WIDTH
#  define WIDTH 1000
# endif
# ifndef HEIGHT
#  define HEIGHT 1000
# endif

#endif
