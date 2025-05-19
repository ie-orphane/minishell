/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:14:33 by mbentale          #+#    #+#             */
/*   Updated: 2025/05/19 20:02:27 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_error(char **args)
{
	ft_putstr_fd("cd: ", STDERR);
	if (args[2])
		ft_putstr_fd("too many arguments: ", STDERR);
	else
	{
		ft_putstr_fd(strerror(errno), STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putendl_fd(args[1], STDERR);
}

char	*get_env_value(t_env *env, const char *key, size_t len)
{
	// char	*path_value;
	// int		size;
	// int		i;
	// int		j;

	while (env)
	{
		if (ft_strncmp(env->value, key, len) == 0 && env->value[len] == '=')
		{
			// size = ft_strlen(env->value) - len;
			// if (!(path_value = malloc(sizeof(char) * size + 1)))
			//     return (NULL);
			// i = len;
			// j = 0;
			// while (env->value[i++])
			//     path_value[j++] = env->value[i];
			return (ft_strdup(env->value + len + 1));
			// path_value[j] = '\0';
			// return (path_value);
		}
		env = env->next;
	}
	return (NULL);
}

int	update_oldpwd(t_env *env)
{
	char	*cwd;
	char	*new_value;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (EXIT_FAILURE);
    // check if oldpwd exists, if not add it using env_add()
    
    // if (!is_in_env(env, "OLDPWD="))
	//     env_add(&env, "OLDPWD=");
	while (env)
	{
		if (ft_strncmp(env->value, "OLDPWD=", 7) == 0)
		{
			if (!(new_value = ft_strjoin("OLDPWD=", cwd)))
			{
				free(cwd);
				return (EXIT_FAILURE);
			}
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
	while (env)
	{
		if (ft_strncmp(env->value, "PWD=", 4) == 0)
		{
			if (!(new_value = ft_strjoin("PWD=", cwd)))
			{
				free(cwd);
				return (EXIT_FAILURE);
			}
			free(env->value);
			env->value = new_value;
			break ;
		}
		env = env->next;
	}
	free(cwd);
	return (EXIT_SUCCESS);
}

char *get_path(t_env *env, const char *key, int option, size_t len)
{
    char *path;

    path = get_env_value(env, key, len);
    if (!path)
    {
        ft_putstr_fd("larrysh : cd: ", STDERR);
        if (option == 0)
            ft_putendl_fd("HOME not set", STDERR);
        else if (option == 1)
            ft_putendl_fd("OLDPWD not set", STDERR);
        return NULL;
    }
    return path;
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

int	key_match(t_env *env, const char *key, int len)
{
	return (ft_strncmp(env->value, key, len) == 0 && env->value[len] == '=');
}

int	is_in_env(t_env *env, char *value)
{
	char	*key;
	int		len;

	if (!value)
		return (0);
	len = 0;
	while (value[len] && value[len] != '=')
		len++;
	key = ft_substr(value, 0, len);
	if (!key)
		return (0);
	while (env)
	{
		if (key_match(env, key, len))
		{
			free(key);
			return (1);
		}
		env = env->next;
	}
	free(key);
	return (0);
}

int	env_add(t_env **env, char *value)
{
	t_env	*new;
    t_env   *tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (0);
	}
	new->next = NULL;
	if (!*env)
	{
		*env = new;
		return (1);
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

int	ft_cd(char **args, t_env *env)
{
	int	cd_ret;

	if (!args[1])
		return (go_to_path(0, env));
	else if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, env);
	else
	{
		update_oldpwd(env);
		cd_ret = chdir(args[1]);
		if (cd_ret == -1)
			print_error(args);
	}
    if (cd_ret != -1)
        update_pwd(env);
    return cd_ret;
}
