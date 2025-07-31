/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mb11junior <mb11junior@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:06:14 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/31 14:44:22 by mb11junior       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_data	*ft_datanew(char **args, char **redirs)
{
	t_data	*data;

	data = ft_malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->args = args;
	data->redirs = redirs;
	return (data);
}

void	ft_dataclear(void *__data)
{
	t_data	*data;

	if (!__data)
		return ;
	data = __data;
	if (data->args)
	{
		ft_strsclear(data->args);
		data->args = NULL;
	}
	if (data->redirs)
	{
		ft_strsclear(data->redirs);
		data->redirs = NULL;
	}
	free(data);
	data = NULL;
}
