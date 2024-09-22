#include "my_header.h"

int get_bef_100(int nbr)
{
    if (nbr >= 90)
		return (90);
	else if (nbr >= 80)
		return (80);
	else if (nbr >= 70)
		return (70);
	else if (nbr >= 60)
		return (60);
	else if (nbr >= 50)
		return (50);
	else if (nbr >= 40)
		return (40);
	else if (nbr >= 30)
		return (30);
	else if (nbr >= 20)
		return (20);
	else if (nbr <= 20)
		return (nbr );
	else
		return (0);
}

int get_aft_100(int nbr)
{
    if (nbr >= 1000000000)
		return (1000000000);
	else if (nbr >= 1000000)
		return (1000000);
	else if (nbr >= 1000)
		return (1000);
	else if (nbr >= 100)
		return (100);
	else
		return (get_bef_100(nbr));
}

int ft_isspace(char** s)
{
    if (**s && (**s == ' ' || **s == '\n' || **s == '\t' ||
			**s == '\v' || **s == '\f' || **s == '\r'))
            {
                ++(*s);
                return (1);
            }
    else
        return (0);
}

int get_sign(char** s)
{
    int sign = 1;
    if (**s == '-')
    {
        sign = 0;
        ++(*s);
    }
    else if (**s == '+')
        ++(*s);
    return sign;
}

int	ft_atoi(char *string)
{
	int	result;
	int	sign;

	sign = 0;
	result = 0;
	while (ft_isspace(&string))
	;
	sign = get_sign(&string);
	while (*string && (*string >= '0' && *string <= '9'))
	{
		result = result * 10 + (*string - '0');
		++string;
	}
    if (sign)
        return (result);
    return (-result);
}