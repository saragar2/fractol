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
	int			max_iterations;
	int			iterations;
	double		real_part;
	double		imag_part;
	int			color;
	int			y;
	int			x;
}t_Mandm;

double	complex_magnitude_squared(t_Complex c);
int	    julia_set_iteration(t_Complex z, t_Complex c, int maxIterations);
void	generate_julia_set(void *mlx, void *win, int width, int height);
int     select_color(int iterations, int max_iterations);

#endif
