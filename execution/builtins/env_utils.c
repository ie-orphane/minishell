/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mb11junior <mb11junior@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 09:17:35 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/31 15:31:33 by mb11junior       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/**
 * @brief Creates a new ENV_VAR node.
 *
 * @param key The key of the ENV_VAR.
 * @param value The value of the ENV_VAR.
 *
 * @return A pointer to the newly created ENV_VAR node.
 */
t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	return (new);
}

/**
 * @brief Frees the allocated ENV_VAR node.
 *
 * @param content The content of the node to be freed.
 *
 */
void	env_free(void *content)
{
	t_env	*env;

	env = (t_env *)content;
	free(env->key);
	free(env->value);
	free(env);
}

/**
 * @brief Gets the value of an ENV_VAR by its key.
 *
 * ```c
 * // Example usage:
 * char *value = env_get(env, "ENV_KEY");
 * if (value)
 *     printf("ENV_KEY: %s\n", value);
 * else
 *     printf("ENV_KEY not found\n");
 * ```
 *
 * @param env The linked list of ENV_VARs.
 * @param key The key of the ENV_VAR to retrieve.
 *
 * @return The value of the ENV_VAR, or NULL if not found.
 */
char	*env_get(t_list *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(((t_env *)env->content)->key, key) == 0)
			return (((t_env *)env->content)->value);
		env = env->next;
	}
	return (NULL);
}

/**
 * @brief Sets the value of an ENV_VAR by its key.
 *
 * If the key already exists, it updates the value.
 * If the key does not exist, it creates a new ENV_VAR.
 *
 * ```c
 * // Example usage:
 * env_set(&env, "ENV_KEY", "new_value");
 * ```
 *
 * @param env The linked list of ENV_VARs.
 * @param key The key of the ENV_VAR to set.
 * @param value The value to set for the ENV_VAR.
 */
void	env_set(t_list **env, char *key, char *value)
{
	t_list	*node;

	node = *env;
	while (node)
	{
		if (ft_strcmp(((t_env *)node->content)->key, key) == 0)
		{
			if (value == NULL)
				return ;
			((t_env *)node->content)->value = value;
			return ;
		}
		node = node->next;
	}
	ft_lstadd_back(env, ft_lstnew(env_new(key, value)));
}

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
