/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:13:32 by saragar2          #+#    #+#             */
/*   Updated: 2023/12/27 11:13:35 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	complex_magnitude_squared(t_Complex z)
{
	return (z.real * z.real + z.imag * z.imag);
}

int	set_iteration(t_Complex z, t_Complex c, int maxIterations) //called in the base functions, discovers how many
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
		temp_imag = 2.0 * z.real * z.imag + c.imag; //imaginary part of the next iteration
		z.real = temp_real;
		z.imag = temp_imag;
		iterations++;
	}
	return (iterations);
}

void	generate_julia_set(t_Image img) //base function to generate julia fractal, called in main and some other image functions in a recursive way
{
	t_Mandm		g;
	t_Complex	z;
	t_Complex	c;

	g = (t_Mandm){-2.0, 2.0, -2.0, 2.0, 150, 0, 0, 0, 0, 0}; //´declaration of all the Mandm variables
	while (g.y < HEIGHT) //this and the next while are made to go through each pixel of the image
	{
		g.x = 1;
		while (g.x < WIDTH)
		{
			g.r_p = g.xmin + (g.x - img.mx) * (g.xmax - g.xmin) / (WIDTH - 1); //formula to create the real part of the complex 
			g.r_p *= img.zoom; //applying the zoom to the real part of the complex
			g.i_p = g.ymin + (g.y - img.my) * (g.ymax - g.ymin) / (HEIGHT - 1); //same but for the imaginary part
			g.i_p *= img.zoom;
			apply_zoom(&img, &g); //call to the function from image.c
			z = (t_Complex){g.r_p, g.i_p}; //creation of the complex
			c = (t_Complex){-0.484, 0.597}; //a constant complex number, which decides the structure of the fractal
			g.iterations = set_iteration(z, c, g.max_iterations);
			img.color = select_color(g.iterations, g.max_iterations, img);
			put_pixel_in_img(&img, g.x++, g.y, img.color);
		}
		g.y++;
	}
	mlx_put_image_to_window(img.mlx, img.win, img.image, 0, 0);
}
