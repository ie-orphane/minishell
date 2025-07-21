/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:25:36 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/21 19:29:25 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
	t_list	*tmp;
	char	*joined;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	arr = malloc(sizeof(char *) * (i + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		joined = build_key_value((t_env *)env->content);
		arr[i++] = joined;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}
