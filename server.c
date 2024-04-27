/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sataskin <sataskin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:01:06 by sataskin          #+#    #+#             */
/*   Updated: 2024/04/27 16:48:38 by sataskin         ###   ########.fr       */
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
	{
		temp = ft_strdup(buf);
		if (!temp)
			exit (1);
	}
	else
	{
		temp = ft_strjoin(str, buf);
		if (!temp)
		{
			free(str);
			exit (1);
		}
		free(str);
	}
	return (temp);
}

static void	receiver(int signal, siginfo_t *info, void *context)
{
	static char	*str = NULL;
	static char	ch;
	static int	i;

	(void)context;
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
			kill(info->si_pid, SIGUSR1);
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
	pid_t				pid;
	struct sigaction	s_a;

	pid = getpid();
	ft_putstr_fd("PID is = ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	ft_memset(&s_a, 0, sizeof(s_a));
	s_a.sa_sigaction = receiver;
	s_a.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_a, 0);
	sigaction(SIGUSR2, &s_a, 0);
	while (1)
		pause();
	return (0);
}
