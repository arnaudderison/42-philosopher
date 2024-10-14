/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:13:55 by aderison          #+#    #+#             */
/*   Updated: 2024/10/14 16:15:42 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_data *data, int id, const char *status)
{
	long long	current_time;

	if (!data || !status)
	{
		free(data->philo);
		error(NULL_PTR);
	}
	pthread_mutex_lock(&data->m_print);
	current_time = timestamp();
	printf("%lld | %d | %s\n", current_time - data->t_start, id, status);
	pthread_mutex_unlock(&data->m_print);
}
