/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:24:24 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/21 19:40:04 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	first_child(t_list *lst, int fd[2], pid_t *pid, t_list **env)
{
	t_data	*data;

	data = lst->content;
	*pid = fork();
	if (*pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (is_builtin_cmd(data->args))
		{
			exec_builtin(data->args, env);
			exit(EXIT_SUCCESS);
		}
		ft_execvpe(data->args[0], data->args, env);
		perror("larrysh");
		exit(EXIT_FAILURE);
	}
}

static void	perror_and_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static void	exec_and_exit(t_data **data, t_list **env)
{
	if (is_builtin_cmd((*data)->args))
	{
		exec_builtin((*data)->args, env);
		exit(EXIT_SUCCESS);
	}
	ft_execvpe((*data)->args[0], (*data)->args, env);
	perror_and_exit("larrysh");
}

static void	second_child(t_list *lst, int fd[2], pid_t *pid, t_list **env)
{
	t_data	*data;

	data = lst->content;
	*pid = fork();
	if (*pid == 0)
	{
		if (handle_redirections(data->redirs) < 0)
			perror_and_exit("redirection error");
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (lst->next)
		{
			exec_pipe(lst, env);
			exit(EXIT_SUCCESS);
		}
		else
			exec_and_exit(&data, env);
	}
}

void	exec_pipe(t_list *lst, t_list **env)
{
	int		status;
	int		pipe_fd[2];
	pid_t	pids[2];

	pipe(pipe_fd);
	first_child(lst, pipe_fd, &pids[0], env);
	second_child(lst->next, pipe_fd, &pids[1], env);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pids[0], &status, 0);
	update_exit_status(status);
	waitpid(pids[1], &status, 0);
	update_exit_status(status);
}
