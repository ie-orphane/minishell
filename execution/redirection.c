/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:29:40 by mb11junior        #+#    #+#             */
/*   Updated: 2025/07/21 19:15:28 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	handle_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (close(fd), -1);
	close(fd);
	return (0);
}

static int	handle_output(char *file, bool append)
{
	int	flags;
	int	fd;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd < 0)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (close(fd), -1);
	close(fd);
	return (0);
}

int	handle_redirections(char **args)
{
	if (!args)
	{
		return (0);
	}
	while (*args)
	{
		if ((!ft_strcmp(*args, "<") || !ft_strcmp(*args, "<<"))
			&& handle_input(*(args + 1)) < 0)
			return (-1);
		else if (!ft_strcmp(*args, ">") && handle_output(*(args + 1),
				false) < 0)
			return (-1);
		else if (!ft_strcmp(*args, ">>") && handle_output(*(args + 1),
				true) < 0)
			return (-1);
		args++;
	}
	return (0);
}
