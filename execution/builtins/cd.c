/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:14:33 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/28 16:50:08 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	print_cd_error(char *path)
{
	ft_putstr_fd("larrysh: cd: ", STDERR);
	ft_putstr_fd(path, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(strerror(errno), STDERR);
}

static char	*update_path(t_list *env, char *key)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	env_set(&env, ft_strdup(key), cwd);
	return (((t_env *)env->content)->value);
}

int ft_strslen(char **s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_cd(char **args, t_list *env)
{
	int		cd_ret;
	char	*path_value;

	if (ft_strslen(args) > 2)
	{
		ft_putendl_fd("larrysh: cd: too many arguments", STDERR);
		return (EXIT_FAILURE);
	}
	if (!args[1])
	{
		path_value = env_get(env, "HOME");
		if (!path_value)
		{
			ft_putstr_fd("larrysh: cd: HOME not set", STDERR);
			return (EXIT_FAILURE);
		}
	}
	else
		path_value = args[1];
	update_path(env, "OLDPWD");
	cd_ret = chdir(path_value);
	if (cd_ret == -1)
		print_cd_error(path_value);
	update_path(env, "PWD");
	return (cd_ret);
}
