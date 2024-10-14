/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:49:36 by aderison          #+#    #+#             */
/*   Updated: 2024/10/14 14:53:35 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(unsigned int count, ...)
{
	va_list	args;
	void	**tmp;

	va_start(args, count);
	while (count--)
	{
		tmp = va_arg(args, void **);
		if (*tmp)
		{
			free(*tmp);
			*tmp = NULL;
		}
	}
	va_end(args);
}
