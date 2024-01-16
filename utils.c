#include "fractol.h"

void	fractol_printf(char const *str)
{
	while (*str != '\0')
		write(1, str++, 1);
}

int	fractol_strcmp(const char *s1, const char *s2)
{
	int	cont;

	cont = 0;
	while (*s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		cont = (unsigned char)*s1 - (unsigned char)*s2;
	return (cont);
}