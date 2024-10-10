/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:00:58 by aderison          #+#    #+#             */
/*   Updated: 2024/10/09 22:56:43 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (COUNT_ARGS);
	if (!argv || !*argv)
		return (UNKNOWN);
	i = 0;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (INVALID_ARGS);
			j++;
		}
	}
	return (SUCCESS);
}

void	freeall(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philo[i].fork_l);
		pthread_mutex_destroy(data->philo[i].fork_r);
	}
	free(data->philo);
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_stop);
	pthread_mutex_destroy(&data->m_eat);
	pthread_mutex_destroy(&data->m_dead);
}

int	main(int argc, char **argv)
{
	int		err;
	t_data	data;

	err = valid_args(argc, argv);
	error(err);
	data_init(&data, argv);
    philo_init(&data);
	freeall(&data);
	return (0);
}
