#ifndef MINITALK_H
# define MINITALK_H

#include <unistd.h>
#include <signal.h>

int	ft_atoi(const char *str);
void	send_msg(int bin[], int pid);
void	parssing(int num, int pid);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	get_signal(int i);
void	convertbin(int bin[]);


#endif
