/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:56:23 by mbentale          #+#    #+#             */
/*   Updated: 2025/05/25 11:21:47 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Initializes the ENV_VARs from the provided array.
 *
 * ```c
 * // Example usage:
 * char *env[] = {"KEY1=VALUE1", "KEY2=VALUE2", NULL};
 * t_list *env_list = env_init(env);
 * ```
 *
 * @param env The array of ENV_VARs.
 *
 * @return A linked list of ENV_VAR nodes.
 */
t_list	*env_init(char **__env)
{
	int		pos;
	char	*key;
	char	*value;
	t_list	*env;
	size_t	i;

	env = NULL;
	i = 0;
	while (__env[i])
	{
		pos = ft_strchr(__env[i], '=') - __env[i];
		key = ft_substr(__env[i], 0, pos);
		value = ft_substr(__env[i], pos + 1, ft_strlen(__env[i]) - pos);
		ft_lstadd_back(&env, ft_lstnew(env_new(key, value)));
		i++;
	}
	return (env);
}

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
