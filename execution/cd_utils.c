/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:54:37 by mbentale          #+#    #+#             */
/*   Updated: 2025/05/20 11:00:28 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	update_oldpwd(t_env *env)
{
	char	*cwd;
	char	*new_value;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (EXIT_FAILURE);
	if (!(check_key_exist(&env, "OLDPWD")))
		return (free(cwd), EXIT_FAILURE);
	while (env)
	{
		if (ft_strncmp(env->value, "OLDPWD=", 7) == 0)
		{
			new_value = ft_strjoin("OLDPWD=", cwd);
			if (!new_value)
				return (free(cwd), EXIT_FAILURE);
			free(env->value);
			env->value = new_value;
			break ;
		}
		env = env->next;
	}
	free(cwd);
	return (EXIT_SUCCESS);
}

int	update_pwd(t_env *env)
{
	char	*cwd;
	char	*new_value;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (EXIT_FAILURE);
	if (!(check_key_exist(&env, "PWD")))
		return (free(cwd), EXIT_FAILURE);
	while (env)
	{
		if (ft_strncmp(env->value, "PWD=", 4) == 0)
		{
			new_value = ft_strjoin("PWD=", cwd);
			if (!new_value)
				return (free(cwd), EXIT_FAILURE);
			free(env->value);
			env->value = new_value;
			break ;
		}
		env = env->next;
	}
	free(cwd);
	return (EXIT_SUCCESS);
}

static char	*get_env_value(t_env *env, const char *key, size_t len)
{
	while (env)
	{
		if (ft_strncmp(env->value, key, len) == 0 && env->value[len] == '=')
			return (ft_strdup(env->value + len + 1));
		env = env->next;
	}
	return (NULL);
}

static char	*get_path(t_env *env, const char *key, int option, size_t len)
{
	char	*path;

	path = get_env_value(env, key, len);
	if (!path)
	{
		ft_putstr_fd("larrysh : cd: ", STDERR);
		if (option == 0)
			ft_putendl_fd("HOME not set", STDERR);
		else if (option == 1)
			ft_putendl_fd("OLDPWD not set", STDERR);
		return (NULL);
	}
	return (path);
}

int	go_to_path(int option, t_env *env)
{
	char	*env_path;
	int		ret;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_path(env, "HOME", 0, 4);
	}
	else if (option == 1)
	{
		env_path = get_path(env, "OLDPWD", 1, 6);
		if (env_path)
		{
			update_oldpwd(env);
			ft_putendl_fd(env_path, 1);
		}
	}
	if (!env_path)
		return (EXIT_FAILURE);
	ret = chdir(env_path);
	free(env_path);
	return (ret);
}
