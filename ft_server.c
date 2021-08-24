/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:12:33 by jalves-d          #+#    #+#             */
/*   Updated: 2021/08/24 17:15:50 by jalves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd((n * -1), fd);
	}
	else if (n > 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(((n % 10) + '0'), fd);
	}
	else if (n > 0)
		ft_putchar_fd((n + '0'), fd);
	else
		ft_putchar_fd('0', fd);
}

void	convertbin(int *bin)
{
	int						i;
	int						base;
	int						convert;
	static unsigned char	c;

	base = 1;
	i = 7;
	convert = 0;
	while (i >= 0)
	{
		convert = convert + (base * bin[i]);
		i--;
		base = (base * 2);
	}
	c = convert;
	write(1, &c, 1);
}

void	get_signal(int i)
{
	int			bin[8];
	static int	j;
	int			w;

	w = 0;
	if (i == SIGUSR1)
		bin[j] = 1;
	if (i == SIGUSR2)
		bin[j] = 0;
	j++;
	if (j > 7)
	{
		convertbin(bin);
		j = 0;
		while (w < 8)
		{
			bin[w] = 0;
			w++;
		}
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 1)
	{
		write(1, "usage: ./server\n", 16);
		return (1);
	}
	else
	{
		pid = getpid();
		signal(SIGUSR1, get_signal);
		signal(SIGUSR2, get_signal);
		ft_putnbr_fd(pid, 1);
		ft_putchar_fd('\n', 1);
		while (1)
			pause();
	}
}
