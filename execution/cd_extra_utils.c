/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_extra_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:59:10 by mbentale          #+#    #+#             */
/*   Updated: 2025/05/20 15:03:12 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_error(char **args)
{
	ft_putstr_fd("larrysh: cd: ", STDERR);
	if (args[2])
		ft_putendl_fd("too many arguments", STDERR);
	else
		ft_putendl_fd(strerror(errno), STDERR);
}

static int	key_match(t_env *env, const char *key, int len)
{
	return (ft_strncmp(env->value, key, len) == 0 && env->value[len] == '=');
}

static int	is_in_env(t_env *env, char *value)
{
	char	*key;
	int		len;

	if (!value)
		return (0);
	len = 0;
	while (value[len] && value[len] != '=')
		len++;
	key = ft_substr(value, 0, len);
	if (!key)
		return (0);
	while (env)
	{
		if (key_match(env, key, len))
		{
			free(key);
			return (1);
		}
		env = env->next;
	}
	free(key);
	return (0);
}

static int	env_add(t_env **env, char *value)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (0);
	}
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return (1);
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int	check_key_exist(t_env **env, char *value)
{
	if (!is_in_env(*env, value))
		return ((env_add(env, value)));
	return (1);
}
