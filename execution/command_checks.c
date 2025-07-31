/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mb11junior <mb11junior@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 08:37:15 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/31 15:15:22 by mb11junior       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin_cmd(char **args)
{
	if (!args || !args[0])
		return (0);
	return (ft_strcmp(args[0], "echo") == 0 || ft_strcmp(args[0], "pwd") == 0
		|| ft_strcmp(args[0], "cd") == 0 || ft_strcmp(args[0], "export") == 0
		|| ft_strcmp(args[0], "unset") == 0 || ft_strcmp(args[0], "env") == 0
		|| ft_strcmp(args[0], "exit") == 0);
}

static bool	check_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		full_path = join_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (true);
	}
	return (false);
}

bool	is_valid_command(char *cmd, t_list *env)
{
	char	*path_env;
	char	**paths;

	if (!cmd || cmd[0] == '\0')
		return (false);
	if (ft_strchr(cmd, '/'))
		return (access(cmd, X_OK) == 0);
	if (is_builtin_cmd((char *[]){cmd, NULL}))
		return (true);
	path_env = env_get(env, "PATH");
	if (!path_env)
		return (false);
	paths = ft_split(path_env, ":");
	if (!paths)
		return (false);
	return (check_paths(paths, cmd));
}
