/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:11:58 by aderison          #+#    #+#             */
/*   Updated: 2024/10/11 03:17:07 by aderison         ###   ########.fr       */
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
		&& !is_dead(philo, 0))
	{
		pthread_mutex_unlock(&philo->info->m_eat);
		pthread_mutex_unlock(&philo->info->m_stop);
		print(philo->info, philo->id, "died");
		exit(1);
		return (NULL);
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
		if (philo->times_eaten == philo->info->n_eat)
		{
			pthread_mutex_unlock(&philo->info->m_stop);
			is_dead(philo, 1);
			return (NULL);
		}
	}
	return (NULL);
}
