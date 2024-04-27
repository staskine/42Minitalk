/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:01:03 by sataskin          #+#    #+#             */
/*   Updated: 2024/04/27 16:48:18 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"

void	sender(char c, int pid)
{
	int		i;
	char	temp;

	i = 7;
	while (i >= 0)
	{
		temp = c >> i;
		if ((temp & 1) == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(400);
		i--;
	}
}

void	checker(int pid)
{
	if (pid == SIGUSR1)
	{
		exit (0);
	}
	exit (1);
}

int	main(int argc, char **argv)
{
	int		pid;
	int		i;

	i = 0;
	if (argc != 3)
	{
		ft_putstr_fd("Correct format is ./client <pid> <string>\n", 1);
		return (1);
	}
	signal(SIGUSR1, checker);
	pid = ft_atoi(argv[1]);
	if (kill(pid, 0) == -1)
	{
		ft_putstr_fd("THIS IS THE WRONG PID", 2);
		exit(1);
	}
	while (argv[2][i] != '\0')
	{
		sender(argv[2][i], pid);
		i++;
	}
	sender('\0', pid);
	return (0);
}
