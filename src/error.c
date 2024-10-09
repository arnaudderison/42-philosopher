/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:29:20 by aderison          #+#    #+#             */
/*   Updated: 2024/10/09 19:04:40 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		++i;
	return (i);
}

static int	ft_putstr_fd(const char *str, int fd)
{
	if (!str)
		return (0);
	return (write(fd, str, ft_strlen(str)));
}

static void	helper(void)
{
	printf(YELLOW "Usage: ./philo <number_of_philosophers> <time_to_die>\
    <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_eat] \
    \n\n" RESET);
	printf("Arguments:\n");
	printf("  \t number_of_philosophers:   The number of philosophers and also \
the number of forks\n");
	printf("  time_to_die (in milliseconds):   If a philosopher doesn't start \
eating 'time_to_die'\n");
	printf("                                   milliseconds after starting their\
last meal or the beginning\n");
	printf("                                   of the simulation, it dies\n");
	printf("    time_to_eat (in milliseconds): The time it takes for a \
philosopher to eat\n");
	printf("  time_to_sleep (in milliseconds): The time the philosopher will \
spend sleeping\n");
	printf("  [number_of_times_each_philosopher_eat] (optional argument):\n");
	printf("                                  If all philosophers eat at least \
'number_of_times_each_philosopher_must_eat'\n");
	printf("                                  times,\
the simulation will stop. If not specified, the simulation\n");
	printf("                                  will stop only at the death of a \
philosopher.\n");
	printf(BLUE "\nAll arguments must be positive integers.\n" RESET);
}

void	error(enum error err)
{
	if (err == SUCCESS)
		return ;
	if (err == COUNT_ARGS)
		ft_putstr_fd(RED "⚠️  Invalid number of arguments\n" RESET, 2);
	if (err == INVALID_ARGS)
		ft_putstr_fd(RED "⚠️  Invalid arguments\n" RESET, 2);
	if (err == LIMIT_PHILO)
		ft_putstr_fd(RED "⚠️  The number of philo must be <= 200\n" RESET, 2);
	if (err == MALLOC)
	{
		ft_putstr_fd(RED "🆘  Malloc error...\n" RESET, 2);
		exit(EXIT_FAILURE);
	}
	if (err == UNKNOWN)
		ft_putstr_fd(RED "🆘  Internal error...\n" RESET, 2);
	helper();
	exit(EXIT_SUCCESS);
}
