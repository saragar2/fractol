#include "fractol.h"

int	mandel_set_iteration(t_Complex z, int c, int maxIterations)
{
	int		iterations;
	double	temp_real;
	double	temp_imag;

	iterations = 0;
	while (complex_magnitude_squared(z) < 4.0 && iterations < maxIterations)
	{
		temp_real = z.real * z.real - z.imag * z.imag + c;
		temp_imag = 2.0 * z.real * z.imag + c;
		z.real = temp_real;
		z.imag = temp_imag;
		iterations++;
	}
	return (iterations);
}

void	generate_mandel_set(t_3d d)
{
	t_Mandm		g;
	t_Complex	z;
	int			c;

	g = (t_Mandm){-2.0, 2.0, -2.0, 2.0, WIDTH, HEIGHT, 0, 0, 0, 0, 0, 0, 0};

	g.max_iterations = 150;
	g.y = 0;
	while (g.y < g.height)
	{
		g.x = 0;
		while (g.x < g.width)
		{
			g.real_part = g.xmin + g.x * (g.xmax - g.xmin) / (g.width - 1);
			g.real_part *= d.img.zoom;
			g.imag_part = g.ymin + g.y * (g.ymax - g.ymin) / (g.height - 1);
			g.imag_part *= d.img.zoom;
			z = (t_Complex){g.real_part, g.imag_part};
			c = 1;
			g.iterations = mandel_set_iteration(z, c, g.max_iterations);
			g.color = select_color(g.iterations, g.max_iterations);
			put_pixel_in_img(&d, g.width - g.x++, g.y, g.color);
		}
		g.y++;
	}
	mlx_put_image_to_window(d.img.mlx, d.img.win, d.img.image, 0, 0);
}