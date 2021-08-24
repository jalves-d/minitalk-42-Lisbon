/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalves-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:12:06 by jalves-d          #+#    #+#             */
/*   Updated: 2021/08/24 18:08:14 by jalves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	long int	i;
	int			negative;
	long int	num;

	num = 0;
	i = 0;
	negative = 1;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		negative *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * negative);
}

void	send_msg(int bin[], int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (bin[i] == 1)
			kill(pid, SIGUSR1);
		else if (bin[i] == 0)
			kill(pid, SIGUSR2);
		i++;
		usleep(25);
	}
}

void	parssing(int num, int pid)
{
	int	bin[8];
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (num % 2 == 0)
			bin[i] = 0;
		else
			bin[i] = 1;
		num = num / 2;
		i--;
	}
	send_msg(bin, pid);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc < 3)
	{
		write(2, "usage: ./client [pid server] [message]\n", 39);
		exit(0);
	}
	if (ft_atoi(argv[1]) == 0)
		write(2, "Unknow PID.\n", 12);
	else
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] >= 32 && argv[2][i] <= 126)
		{
			parssing(argv[2][i], pid);
			write(1, "ok\n", 3);
			i++;
		}
	}
}
