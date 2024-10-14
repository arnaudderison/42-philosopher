/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:33:33 by aderison          #+#    #+#             */
/*   Updated: 2024/10/14 17:18:02 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_init(t_data *data)
{
	int	i;

	data->t_start = timestamp();
	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].fork_r = NULL;
		data->philo[i].info = data;
		data->philo[i].times_eaten = 0;
		pthread_mutex_init(&(data->philo[i].fork_l), NULL);
		if (i == data->nb_philo - 1)
			data->philo[i].fork_r = &data->philo[0].fork_l;
		else
			data->philo[i].fork_r = &data->philo[i + 1].fork_l;
		if (pthread_create(&data->philo[i].thread, NULL, philo_life,
				(void *)&data->philo[i]) != 0)
			return (-1);
	}
	i = -1;
	while (++i < data->nb_philo)
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
	return (0);
}

int	data_init(t_data *data, char **argv)
{
	if (ft_atoi(argv[1]) > MAX_PHILOSOPHERS)
		error(LIMIT_PHILO);
	if (!argv || !*argv || !data)
		error(UNKNOWN);
	pthread_mutex_init(&data->m_print, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	pthread_mutex_init(&data->m_dead, NULL);
	pthread_mutex_init(&data->m_stop, NULL);
	data->philo_eat = 0;
	data->nb_philo = ft_atoi(argv[1]);
	if (data->nb_philo < 1)
		return (error(LIMIT_PHILO), 1);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->n_eat = -1;
	data->stop = 0;
	if (argv[5])
		data->n_eat = ft_atoi(argv[5]);
	if (argv[5] && data->n_eat == 0)
		return (1);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		error(MALLOC);
	return (0);
}
