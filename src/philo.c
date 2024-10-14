/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:11:58 by aderison          #+#    #+#             */
/*   Updated: 2024/10/14 17:18:57 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->info->m_dead);
	if (nb)
		philo->info->stop = 1;
	if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->m_dead);
	return (0);
}

void	*check_death(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	ft_usleep(philo->info->t_die + 1);
	pthread_mutex_lock(&philo->info->m_eat);
	pthread_mutex_lock(&philo->info->m_stop);
	if (timestamp() - philo->last_eat > (long)(philo->info->t_die)
		&& !is_dead(philo, 0) && philo->id != 0)
	{
		pthread_mutex_unlock(&philo->info->m_eat);
		print(philo->info, philo->id, "died");
		freeall(philo->info);
		exit(EXIT_SUCCESS);
	}
	pthread_mutex_unlock(&philo->info->m_eat);
	pthread_mutex_unlock(&philo->info->m_stop);
	return (NULL);
}

void	*philo_life(void *phi)
{
	t_philo		*philo;
	t_data		*data;
	pthread_t	t;

	philo = (t_philo *)phi;
	data = philo->info;
	if (philo->id % 2 == 0)
		ft_usleep(data->t_eat / 2);
	while (!is_dead(philo, 0))
	{
		pthread_create(&t, NULL, check_death, phi);
		philo_eat(philo);
		pthread_detach(t);
		if (philo->times_eaten == philo->info->n_eat && philo->info->n_eat != -1)
		{
			pthread_mutex_unlock(&philo->info->m_stop);
			is_dead(philo, 1);
			return (NULL);
		}
	}
	return (NULL);
}
