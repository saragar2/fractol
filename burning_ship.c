#include "fractol.h"

int	bs_set_iteration(t_Complex z, t_Complex c, int maxIterations) //called in the base functions, discovers how many
//iterationes are needed so the complex tends to infinity
{
	int		iterations;
	double	temp_real;
	double	temp_imag;

	iterations = 0;
	while (complex_magnitude_squared(z) < 4.0 && iterations < maxIterations) //checks if the square of the complex
	//is bigger than the max magnitude and if iterations re lower than the maximum number
	{
		temp_real = z.real * z.real - z.imag * z.imag + c.real; //real part of the next iteration
		temp_imag = fabs(2.0 * z.real * z.imag) + c.imag; //imaginary part of the next iteration
		z.real = temp_real;
		z.imag = temp_imag;
		iterations++;
	}
	return (iterations);
}

void	generate_bs_set(t_Image img)
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

			g.iterations = bs_set_iteration(z, c, g.max_iterations);
			img.color = select_color(g.iterations, g.max_iterations, img);
			put_pixel_in_img(&img, g.x++, g.y, img.color);
		}
		g.y++;
	}
	mlx_put_image_to_window(img.mlx, img.win, img.image, 0, 0);
}