#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct s_pair
{
    int		key;
    char	*value;
}	t_pair;

void	ft_putstr(char *letters);
char	*get_key(int fd);
int		get_bef_100(int nbr);
int		get_aft_100(int nbr);
int		ft_atoi(char *string);
t_pair	*process(char *file);
void	ft_print(int n, t_pair *ptr, int *first);

void	ft_putstr(char *letters)
{
	while (*letters)
		write(1, letters++, 1);
}

char	*get_key(int file)
{
	int		index;
	char	letter;
	char	*key;

	index = 0;
	key = malloc(sizeof(char) * 128);
	if (!key)
		exit(1);
	read(file, &letter, 1);
	while (letter == '\n')
		read(file, &letter, 1);
	while (letter >= '0' && letter <= '9')
	{
		key[index++] = letter;
		read(file, &letter, 1);
	}
	key[index] = '\0';
	return (key);
}

char	*get_value(int file, char letter)
{
	int		index;
	char	*string;

	index = 0;
	string = malloc(sizeof(char) * 128);
	if (!string)
		exit(1);
	while (letter != '\n' && letter != EOF)
	{
		string[index++] = letter;
		read(file, &letter, 1);
	}
	string[index] = '\0';
	return (string);
}

char	*ft_strdup(char *src)
{
	int		index;
	char	*dst;

	index = 0;
	while (src[index] != '\0')
		index++;
	dst = malloc(sizeof(char) * (index + 1));
	if (!dst)
		return (0);
	index = 0;
	while (src[index] != '\0')
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (dst);
}

void	ft_print(int n, t_pair *ptr, int *first)
{
	int	i;
	int	number;
	int	next_number;

	i = 0;
	number = get_aft_100(n);
	next_number = n - number;
	if (number >= 100)
		ft_print(n / number, ptr, first);
	if (*first == 0)
		write(1, " ", 1);
	*first = 0;
	while (ptr[i].key != -1)
	{
		if (ptr[i].key == number)
		{
			ft_putstr(ptr[i].value);
			break ;
		}
		i++;
	}
	if (ptr[i].key == -1)
		write(1, "Error: Value not found\n", 24);
	if (next_number > 0)
		ft_print(next_number, ptr, first);
}

int	get_bef_100(int nbr)
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
	return (nbr);
}

int	get_aft_100(int nbr)
{
	if (nbr >= 1000000000)
		return (1000000000);
	else if (nbr >= 1000000)
		return (1000000);
	else if (nbr >= 1000)
		return (1000);
	else if (nbr >= 100)
		return (100);
	return (get_bef_100(nbr));
}

int	ft_atoi(char *string)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	if (*string == '-')
		sign = 0;
	else if (*string == '+')
		string++;
	while (*string >= '0' && *string <= '9')
	{
		result = result * 10 + (*string - '0');
		string++;
	}
	if (sign == 0)
		return (-result);
	return (result);
}

t_pair	*process(char *file)
{
	int		index;
	int		fileid;
	t_pair	*ptr;
	char	letter;
	char	*temp;

	index = 0;
	fileid = open(file, O_RDONLY);
	if (fileid == -1)
	{
		write(1, "Error: Could not open file\n", 29);
		exit(1);
	}
	ptr = malloc(sizeof(t_pair) * 33);
	if (!ptr)
		exit(1);
	while (index < 32)
	{
		ptr[index].key = ft_atoi(get_key(fileid));
		read(fileid, &letter, 1);
		while (letter == ' ')
			read(fileid, &letter, 1);
		if (letter == ':')
			read(fileid, &letter, 1);
		while (letter == ' ')
			read(fileid, &letter, 1);
		temp = get_value(fileid, letter);
		ptr[index].value = ft_strdup(temp);
		free(temp);
		index++;
	}
	ptr[index].key = -1;
	close(fileid);
	return (ptr);
}

int	main(int argc, char **argv)
{
	t_pair	*p;
	int		addr_first;
	int		*first;

	addr_first = 1;
	first = &addr_first;
	if (argc == 2)
	{
		if (ft_atoi(argv[1]) < 0)
		{
			write(1, "Error\n", 6);
			return (0);
		}
		p = process("dict.txt.txt");
		ft_print(ft_atoi(argv[1]), p, first);
		free(p);
	}
	return (0);
}

