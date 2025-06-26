/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execvpe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:28:06 by mbentale          #+#    #+#             */
/*   Updated: 2025/06/26 19:36:03 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	is_executable(char *path)
{
	struct stat	st;

	if (access(path, X_OK) != 0)
		return (0);
	if (stat(path, &st) != 0)
		return (0);
	return (S_ISREG(st.st_mode));
}

static char	*join_path(const char *dir, const char *file)
{
	char	*res;

	res = malloc(ft_strlen(dir) + ft_strlen(file) + 2);
	if (!res)
		return (NULL);
	ft_strlcpy(res, dir, ft_strlen(dir) + 1);
	res[ft_strlen(dir)] = '/';
	ft_strlcpy(res + ft_strlen(dir) + 1, file, ft_strlen(file) + 1);
	return (res);
}

static char	**env_to_array(t_list *env)
{
	char	**arr;
	int		i;
	t_list	*tmp;

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
		arr[i++] = env->content;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	free_2d(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int	ft_execvpe(char *file, char **argv, t_list *env)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	path_env = env_get(env, "PATH");
	if (!path_env || ft_strchr(file, '/'))
		return (execve(file, argv, (char **)env_to_array(env)));
	paths = ft_split(path_env, ":");
	if (!paths)
		return (-1);
	i = -1;
	while (paths[++i])
	{
		full_path = join_path(paths[i], file);
		if (full_path)
		{
			if (is_executable(full_path))
				execve(full_path, argv, (char **)env_to_array(env));
			free(full_path);
		}
	}
	free_2d(paths);
	return (-1);
}
