/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:56:23 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/21 19:32:50 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_env(t_list *env)
{
	while (env)
	{
		if (((t_env *)env->content)->value)
			printf("%s=%s\n", ((t_env *)env->content)->key,
				((t_env *)env->content)->value);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
