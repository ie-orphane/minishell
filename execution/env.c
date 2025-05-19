/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:56:23 by mbentale          #+#    #+#             */
/*   Updated: 2025/05/17 08:28:06 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl(env->value);
		env = env->next;
	}
	if (env)
		ft_putendl(env->value);
	return (EXIT_SUCCESS);
}

static t_env	*new_env_node(char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

t_env	*init_env(char **env)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new;

	head = NULL;
	tail = NULL;
	while (*env)
	{
		new = new_env_node(*env);
		if (!new)
		{
			free_env_list(head);
			return (NULL);
		}
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
		env++;
	}
	return (head);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->value);
		free(env);
		env = tmp;
	}
}
