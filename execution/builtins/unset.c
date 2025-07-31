/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mb11junior <mb11junior@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:03:23 by ielyatim          #+#    #+#             */
/*   Updated: 2025/07/31 15:09:01 by mb11junior       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	envcmp_key(char *key, t_env *content)
{
	return (ft_strcmp(key, ((t_env *)content)->key));
}

int	ft_unset(char **args, t_list **env)
{
	while (*args)
	{
		ft_lstremove_if(env, *args, envcmp_key, NULL);
		args++;
	}
	return (0);
}
