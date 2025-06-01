/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:01:09 by mbentale          #+#    #+#             */
/*   Updated: 2025/06/01 07:42:34 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	cleanup_sh(t_list **env, t_list **lst, char **line)
{
	if (env)
		ft_lstclear(env, env_free);
	if (lst)
		ft_lstclear(lst, ft_strsclear);
	if (line && *line)
		free(*line);
}

static bool	is_numeric(char *str)
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

static void	print_exit_error(char **args)
{
	ft_putendl_fd("exit", STDERR);
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

int	ft_exit(char **args, t_list **env, t_list **lst, char **line)
{
	int	status;

	if (!args[1])
	{
		cleanup_sh(env, lst, line);
		ft_putendl_fd("exit", STDERR);
		exit(0);
	}
	if (!is_numeric(args[1]))
	{
		print_exit_error(args);
		cleanup_sh(env, lst, line);
		exit(255);
	}
	if (args[2])
	{
		print_exit_error(args);
		cleanup_sh(env, lst, line);
		return (1);
	}
	status = (unsigned char)ft_atoi(args[1]);
	cleanup_sh(env, lst, line);
	ft_putendl_fd("exit", STDERR);
	exit(status);
}
