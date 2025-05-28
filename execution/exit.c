/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:01:09 by mbentale          #+#    #+#             */
/*   Updated: 2025/05/28 12:01:25 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void cleanup_sh(t_list **env, t_list **lst, char **line)
{
	if (env)
		ft_lstclear(env, env_free);
	if (lst)
		ft_lstclear(lst, ft_strsclear);
	if (line && *line)
		free(*line);
}

bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	print_exit_error(char **args)
{
	ft_putstr_fd("larrysh: exit: ", STDERR);
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (args[2])
		ft_putendl_fd("too many arguments", STDERR);
	else
		ft_putendl_fd(strerror(errno), STDERR);
}

int	ft_exit(char **args, t_list **env)
{
	int status;

	if (!args[1])
	{
		ft_lstclear(env, env_free);
		// cleanup_sh(env, lst, line);
		exit(0);
	}
	if (!is_numeric(args[1]))
	{
		print_exit_error(args);
		// cleanup_sh(env, lst, line);
		ft_lstclear(env, env_free);
		exit(255);
	}
	if (args[2])
	{
		print_exit_error(args);
		// ft_lstclear(env, env_free);
		return (1);
	}
	status = ft_atoi(args[1]);
	// cleanup_sh(env, lst, line);
	ft_lstclear(env, env_free);
	exit(status);
}
