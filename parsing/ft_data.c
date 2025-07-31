/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:06:14 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/24 10:47:30 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_data	*ft_datanew(char **args, char **redirs)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
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
