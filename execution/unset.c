/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:03:23 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/25 11:42:56 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	__envcmp_key(char *key, t_env *content)
{
	return (ft_strcmp(key, ((t_env *)content)->key));
}

int	ft_unset(char **args, t_list **env)
{
	while (*args)
	{
		ft_lstremove_if(env, *args, __envcmp_key, env_free);
		args++;
	}
	return (0);
}
