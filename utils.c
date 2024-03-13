#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	long int	c;
	int	a;

	a = 1;
	c = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			a = a * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		c = (str[i] - '0') + (c * 10);
		i++; 
	}
	if ((c * a) > 2147483647 || (c * a) <= 0 || str[i] != '\0')
		return (-1);
	else
		return (c * a);
}
