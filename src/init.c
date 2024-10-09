/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:33:33 by aderison          #+#    #+#             */
/*   Updated: 2024/10/09 19:00:47 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_init(t_data *data, char **argv)
{
	if (ft_atoi(argv[1]) > MAX_PHILOSOPHERS)
		error(LIMIT_PHILO);
	if (!argv || !*argv || !data)
		error(UNKNOWN);
	pthread_mutex_init(&data->m_print, NULL);
	pthread_mutex_init(&data->m_stop, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	pthread_mutex_init(&data->m_dead, NULL);
	data->philo_eat = 0;
	data->nb_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->n_eat = ft_atoi(argv[5]);
	if (argv[5] && data->n_eat == 0)
		return (1);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		error(MALLOC);
	return (0);
}
