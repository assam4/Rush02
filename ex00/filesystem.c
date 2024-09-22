#include "my_header.h"

void	ft_putstr(char *letters)
{
	while (*letters)
		write(1, letters++, 1);
}

char	*get_key(int file)
{
	int	index;
	char	letter;
	char	*key;

	if (!(key = malloc(sizeof(char) * 128)))
	    exit(1);
	index = 0;
	read(file, &letter, 1);
	while (letter == '\n')
		read(file, &letter, 1);
	while (letter >= '0' && letter <= '9')
	{
		key[index++] = letter;
		read(file, &letter, 1);
	}
	return (key);
}

char    *get_value(int file, char letter)
{
    int index;
    char    *string;

    if (!(string = malloc(sizeof(char) * 128)))
		exit(1);
	index = 0;
	while (letter != '\n')
	{
		string[index] = letter;
		read(file, &letter, 1);
		++index;
	}
	return (string);
} 

char	*ft_strdup(char *src)
{
	int		index;
	int		count;
	char		*dst;

	count = 0;
	while (src[count] != '\0')
		++count;
	if (!(dst = (char *)malloc(sizeof(char) * (count + 1))))
		return (0);
	index = 0;
	while (index < count)
	{
		dst[index] = src[index];
		++index;
	}
	dst[index] = '\0';
	return (dst);
}

pair	*process(char *file)
{
	int	index;
	int	fileid;
	char	letter;
	pair	*ptr;
	char *temp;

	fileid = open(file, O_RDONLY);
	if (fileid == -1 || !(ptr = malloc(sizeof(pair) * 33)))
		exit(1);
	index = 0;
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
		++index;
	}
	close(fileid);
	return (ptr);
}
