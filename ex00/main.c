#include "my_header.h"

void	ft_print(int n, pair *ptr, int *first)
{
	int i;
	int number;

	i = 0;
	number = get_aft_100(n);
	if (number >= 100)
		ft_print(n / number, ptr, first);
	if (*first == 0)
		write(1, " ", 1);
	*first = 0;
	while (ptr[i].key != number)
		i++;
	ft_putstr(ptr[i].value);
	if (number != 0 && (n % number != 0))
		ft_print(n % number, ptr, first);
}

int	main(int argc, char **argv)
{
	pair *p;
	int *first;
	int addr_first;

	addr_first = 1;
	first = &addr_first;
	if (argc == 2)
	{
		if (ft_atoi(argv[1]) < 0)
		{
			write(1, "Error\n", 6);
			return (0);
		}
		p = process("dict.txt");
		ft_print(ft_atoi(argv[1]), p, first);
        free(p);
	}
	return (0);
}


