/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:25:36 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/24 09:54:52 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_error(char *cmd, char *msg)
{
	ft_putstr_fd("larrysh: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	update_exit_status(int status)
{
	if (WIFEXITED(status))
		g_global.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_global.exit_status = 128 + WTERMSIG(status);
}

void	free_2d(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

static char	*build_key_value(t_env *env)
{
	char	*joined;

	joined = malloc(ft_strlen(env->key) + ft_strlen(env->value) + 2);
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, env->key, ft_strlen(env->key) + 1);
	joined[ft_strlen(env->key)] = '=';
	ft_strlcpy(joined + ft_strlen(env->key) + 1, env->value,
		ft_strlen(env->value) + 1);
	return (joined);
}

char	**env_to_array(t_list *env)
{
	char	**arr;
	int		i;
	char	*joined;

	arr = malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		joined = build_key_value((t_env *)env->content);
		if (!joined)
			return (free_2d(arr), NULL);
		arr[i++] = joined;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
