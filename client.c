/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:01:03 by sataskin          #+#    #+#             */
/*   Updated: 2024/04/26 17:12:54 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"

void	sender(char c, pid_t pid)
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
		usleep(100);
		i--;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	i = 0;
	if (argc != 3)
	{
		ft_putstr_fd("Correct format is ./client <pid> <string>\n", 1);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	while (argv[2][i] != '\0')
	{
		sender(argv[2][i], pid);
		i++;
	}
	sender('\0', pid);
	return (0);
}
