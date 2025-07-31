/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mb11junior <mb11junior@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:48:05 by ielyatim          #+#    #+#             */
/*   Updated: 2025/07/31 15:16:54 by mb11junior       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	isvalid_key(char *str)
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

static void	show_export(t_env *env)
{
	printf("declare -x %s", env->key);
	if (env->value)
		printf("=\"%s\"", env->value);
	printf("\n");
}

static void	set_key_value(char **args, char **key, char **value)
{
	if (!ft_strchr(*args, '='))
	{
		*key = ft_strdup(*args);
		*value = NULL;
	}
	else
	{
		*key = ft_substr(*args, 0, ft_strchr(*args, '=') - *args);
		*value = expand(ft_strdup(ft_strchr(*args, '=') + 1));
	}
}

int	ft_export(char **args, t_list **env)
{
	char	*key;
	char	*value;
	int		status;

	status = 0;
	if (!*args)
		ft_lstiter(g_global.env, show_export);
	while (*args)
	{
		set_key_value(args, &key, &value);
		if (!isvalid_key(key))
		{
			status = 1;
			printf("export: `%s': not a valid identifier\n", *(args++));
			continue ;
		}
		env_set(env, key, value);
		args++;
	}
	return (status);
}
