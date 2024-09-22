#ifndef _MY_HEADER_H
#define _MY_HEADER_H_

#include <stdlib.h>
//#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct pair
{
    int key;
    char* value;
}           pair;

void	ft_putstr(char *letters);
char	*get_key(int fd);
int get_bef_100(int nbr);
int get_aft_100(int nbr);
int	ft_atoi(char *string);
pair	*process(char *file);


#endif