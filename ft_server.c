
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

void	convertbin(int bin[])
{
	int		i;
	int		base;
	int		convert;
	char	c;

	base = 1;
	i = 7;
	convert = 0;
	while (i > 0)
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

	if (i == SIGUSR1)
		bin[j] = 1;
	if (i == SIGUSR2)
		bin[j] = 0;
	j++;
	if (j > 7)
	{
		convertbin(bin);
		j = 0;
	}
}

int		main(int argc, char **argv)
{
	pid_t pid;

	if (argc != 1)
	{
		write(STDERR_FILENO, "usage: ./server\n", 16);
		return (1);
	}
	else
	{
		pid = getpid();
		ft_putnbr_fd(pid, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		while (42)
		{
			signal(SIGUSR1, get_signal);
			signal(SIGUSR2, get_signal);
		}
	}
}
