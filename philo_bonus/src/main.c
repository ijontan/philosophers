/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:00:51 by itan              #+#    #+#             */
/*   Updated: 2023/03/20 15:03:30 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_child(pid_t *pids, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			free(pids);
			printf("Child %d is created\n", i);
			usleep(500000);
			printf("Child %d is dead\n", i);
			exit(0);
		}
		i++;
	}
	return (0);
}

void	kill_all_child(pid_t *pids, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
}

int	waitdead(pid_t *pids, int num)
{
	int	status;
	int	i;

	i = 0;
	while (i < num)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	return (0);
}

int	main(int ac, char const **av)
{
	pid_t	*pids;

	pids = ft_calloc(5, sizeof(pid_t));
	(void)ac;
	(void)av;
	create_child(pids, 5);
	kill_all_child(pids, 5);
	waitdead(pids, 5);
	free(pids);
	return (0);
}
