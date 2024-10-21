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

# include <unistd.h>
# include <stdlib.h>
# include "./mlx_linux/mlx.h"
# include <stdio.h>
# include <math.h>

typedef struct s_Complex
{
	double	real;
	double	imag;
}	t_Complex;

typedef struct s_Mandm
{
	double		xmin;
	double		xmax;
	double		ymin;
	double		ymax;
	int			max_iterations;
	int			iterations;
	double		r_p;
	double		i_p;
	int			y;
	int			x;
}	t_Mandm;

typedef struct s_Rgb
{
	int	red;
	int	green;
	int	blue;
	int	final_color;
}	t_Rgb;

typedef struct s_Image
{
	void	*mlx;
	void	*win;
	int		*image;
	char	*data;
	int		color;
	int		bpp;
	int		sizeline;
	int		endian;
	double	zoom;
	double	old_zoom;
	double	mx;
	double	my;
	char	*type;
	int		multip;
}	t_Image;

double	complex_magnitude_squared(t_Complex z);
int		set_iteration(t_Complex z, t_Complex c, int maxIterations);
void	generate_julia_set(t_Image img);
int		select_color(int iterations, int max_iterations, t_Image img);
void	first_aux(int *iterations, int *red, int *green, int *blue);
void	second_aux(int *iterations, int *red, int *green, int *blue);
int		rgb_to_hex(int red, int green, int blue);
int		key_control(int keycode, t_Image *param);
int		go_exit_cross(t_Image *param);
void	init_img(t_Image *img);
void	init_img_soft(t_Image *i, char **argv);
void	put_pixel_in_img(t_Image *img, int x, int y, int color);
int		new_zoom(int button, int x, int y, t_Image *img);
void	generate_mandel_set(t_Image img);
void	f_printf(char const *str);
int		f_strcmp(const char *s1, const char *s2);
int		move_left_right(int keycode, t_Image *img);
void	invert_color(t_Image *img);
void	apply_zoom(t_Image *img, t_Mandm *g);
void	change_color(int keycode, t_Image *img);
void	color_fix(int *iterations, int *blue);
void	generate_bs_set(t_Image img);
int		bs_set_iteration(t_Complex z, t_Complex c, int maxIterations);
void	select_fractal(t_Image *img);
int		on_destroy(t_Image *i);

# ifndef WIDTH
#  define WIDTH 500
# endif
# ifndef HEIGHT
#  define HEIGHT 500
# endif

#endif
