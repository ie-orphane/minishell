/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:03:23 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/22 10:03:24 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	__envcmp_key(char *key, _t_env *content)
{
	return (ft_strcmp(key, ((_t_env *)content)->key));
}

int	ft_unset(char **args, t_list **env)
{
	while (*args)
	{
		ft_lstremove_if(env, *args, __envcmp_key, _env_free);
		args++;
	}
	return (0);
}
