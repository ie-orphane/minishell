/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 07:57:11 by mbentale          #+#    #+#             */
/*   Updated: 2025/06/27 10:56:49 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static bool	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (false);
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
}

void	ft_exit(t_list **lst)
{
	int		status;
	t_data	*data;

	data = (*lst)->content;
	if (!data->args[1])
	{
		ft_putendl_fd("exit", 1);
		__exit(0);
	}
	if (!is_numeric(data->args[1]))
	{
		print_exit_error(data->args);
		__exit(255);
	}
	if (data->args[2])
	{
		print_exit_error(data->args);
		return ;
	}
	status = (unsigned char)ft_atoi(data->args[1]);
	ft_putendl_fd("exit", 1);
	__exit(status);
}
