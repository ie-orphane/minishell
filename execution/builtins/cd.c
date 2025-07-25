/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:14:33 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/22 16:45:48 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	print_cd_error(char **args)
{
	if (args[2])
		ft_putendl_fd("larrysh: cd: too many arguments", STDERR);
	else
	{
		ft_putstr_fd("larrysh: cd: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putendl_fd(strerror(errno), STDERR);
	}
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

int	ft_cd(char **args, t_list *env)
{
	int		cd_ret;

	if (!args[1])
		return (EXIT_FAILURE);
	if (args[2])
	{
		print_cd_error(args);
		return (EXIT_FAILURE);
	}
	else
	{
		update_path(env, "OLDPWD");
		cd_ret = chdir(args[1]);
		if (cd_ret == -1)
			print_cd_error(args);
	}
	if (cd_ret != -1)
		update_path(env, "PWD");
	return (cd_ret);
}
