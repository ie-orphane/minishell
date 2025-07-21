/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:48:05 by ielyatim          #+#    #+#             */
/*   Updated: 2025/07/21 14:57:50 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	__isvalid_key(char *str)
{
	if (!*str || ft_isdigit(*str))
		return (false);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

static void	__show(t_env *env)
{
	printf("declare -x %s", env->key);
	if (env->value)
		printf("=\"%s\"", env->value);
	printf("\n");
}

int	ft_export(char **args, t_list **env)
{
	char	*key;
	char	*value;
	int		status;

	status = 0;
	if (!*args)
		ft_lstiter(*env, __show);
	while (*args)
	{
		if (!ft_strchr(*args, '='))
		{
			key = ft_strdup(*args);
			value = NULL;
		}
		else
		{
			key = ft_substr(*args, 0, ft_strchr(*args, '=') - *args);
			value = expand(ft_strdup(ft_strchr(*args, '=') + 1));
		}
		if (!__isvalid_key(key))
		{
			status = 1;
			free(key);
			free(value);
			printf("export: `%s': not a valid identifier\n", *(args++));
			continue ;
		}
		env_set(env, key, value);
		args++;
	}
	return (status);
}
