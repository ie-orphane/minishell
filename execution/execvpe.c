/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execvpe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:28:06 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/16 11:34:16 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int is_executable(char *path)
{
	struct stat st;

	if (access(path, X_OK) != 0)
		return (0);
	if (stat(path, &st) != 0)
		return (0);
	return (S_ISREG(st.st_mode));
}

static char *join_path(const char *dir, const char *file)
{
	char *res;

	res = malloc(ft_strlen(dir) + ft_strlen(file) + 2);
	if (!res)
		return (NULL);
	ft_strlcpy(res, dir, ft_strlen(dir) + 1);
	res[ft_strlen(dir)] = '/';
	ft_strlcpy(res + ft_strlen(dir) + 1, file, ft_strlen(file) + 1);
	return (res);
}

static char *build_key_value(t_env *env)
{
	char *joined;

	joined = malloc(ft_strlen(env->key) + ft_strlen(env->value) + 2);
	if (!joined)
		return (NULL);
	ft_strlcpy(joined, env->key, ft_strlen(env->key) + 1);
	joined[ft_strlen(env->key)] = '=';
	ft_strlcpy(joined + ft_strlen(env->key) + 1, env->value, ft_strlen(env->value) + 1);
	return (joined);
}

char **env_to_array(t_list *env)
{
	char **arr;
	int i;
	t_list *tmp;
	char *joined;

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

void free_2d(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

static void set_path(char **paths, char *file, char **argv, char **envp)
{
	char *full_path;
	int i;

	i = -1;
	while (paths[++i])
	{
		full_path = join_path(paths[i], file);
		if (full_path && is_executable(full_path))
		{
			execve(full_path, argv, envp);
			return (free(full_path));
		}
		free(full_path);
	}
}

int ft_execvpe(char *file, char **argv, t_list **env)
{
	char *path_env;
	char **paths;
	char **envp;

	envp = env_to_array(*env);
	if (!envp)
		return (-1);
	path_env = env_get(*env, "PATH");
	if (!path_env || ft_strchr(file, '/'))
	{
		execve(file, argv, envp);
		return (free_2d(envp), -1);
	}
	paths = ft_split(path_env, ":");
	if (!paths)
		return (free_2d(envp), -1);
	set_path(paths, file, argv, envp);
	return (free_2d(paths), free_2d(envp), -1);
}
