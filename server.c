/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:01:06 by sataskin          #+#    #+#             */
/*   Updated: 2024/04/26 17:13:19 by sataskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"

static char	*save_char(char *str, char c)
{
	char	*temp;
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	if (str == NULL)
		str = ft_strdup(buf);
	else
	{
		temp = str;
		str = ft_strjoin(temp, buf);
		free(temp);
	}
	return (str);
}

static void	receiver(int signal)
{
	static char	*str;
	static char	ch;
	static int	i;

	if (signal == SIGUSR1)
		ch = ch | 1;
	i++;
	if (i == 8)
	{
		if (ch == '\0')
		{
			ft_putendl_fd(str, 1);
			free(str);
			str = NULL;
		}
		else
			str = save_char(str, ch);
		i = 0;
		ch = 0;
	}
	ch = ch << 1;
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putstr_fd("PID is = ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	signal(SIGUSR1, receiver);
	signal(SIGUSR2, receiver);
	while (1)
		pause();
	return (0);
}
