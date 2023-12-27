#include "fractol.h"

// Función para calcular el módulo cuadrado de un número complejo
double	complex_magnitude_squared(t_Complex c)
{
	return (c.real * c.real + c.imag * c.imag);
}

// Función para realizar una iteración en el conjunto de Julia
int	julia_set_iteration(t_Complex z, t_Complex c, int maxIterations)
{
	int		iterations;
	double	temp_real;
	double	temp_imag;

	iterations = 0;
	while (complex_magnitude_squared(z) < 4.0 && iterations < maxIterations)
	{
		temp_real = z.real * z.real - z.imag * z.imag + c.real;
		temp_imag = 2.0 * z.real * z.imag + c.imag;
		z.real = temp_real;
		z.imag = temp_imag;
		iterations++;
	}
	return (iterations);
}

// Función para generar el conjunto de Julia utilizando minilibX
void	generate_julia_set(void *mlx, void *win, int width, int height)
{
	t_Mandm		g;
	t_Complex	z;
	t_Complex	c;

	g = (t_Mandm){-2.0, 2.0, -2.0, 2.0, 0, 0, 0, 0, 0, 0, 0};
	g.max_iterations = 150;
	g.y = 0;
	while (g.y < height)
	{
		g.x = 0;
		while (g.x < width)
		{
			g.real_part = g.xmin + g.x * (g.xmax - g.xmin) / (width - 1);
			g.imag_part = g.ymin + g.y * (g.ymax - g.ymin) / (height - 1);
			z = (t_Complex){g.real_part, g.imag_part};
			c = (t_Complex){-0.661, -0.346};
			g.iterations = julia_set_iteration(z, c, g.max_iterations);
			g.color = select_color(g.iterations, g.max_iterations);
			mlx_pixel_put(mlx, win, g.x, g.y, g.color);
			g.x++;
		}
		g.y++;
	}
	//mlx_key_hook(win, exit, 0);
	mlx_loop(mlx);
}

int main() {
    void *mlx;
     void *win;

     mlx = mlx_init();
    win = mlx_new_window(mlx, 1000, 1000, "Conjunto de Julia");

     generate_julia_set(mlx, win, 1000, 1000);

     return 0;
}