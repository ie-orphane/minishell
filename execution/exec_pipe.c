/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mb11junior <mb11junior@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:24:24 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/21 16:51:47 by mb11junior       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	child_exec(t_data *data, t_list **env, int in_fd, int out_fd)
{
	if (handle_redirections(data->redirs) < 0)
	{
		perror("redirection error");
		exit(EXIT_FAILURE);
	}
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	if (is_builtin_cmd(data->args))
	{
		exec_builtin(data->args, env);
		exit(EXIT_SUCCESS);
	}
	ft_execvpe(data->args[0], data->args, env);
	perror("larrysh");
	exit(EXIT_FAILURE);
}

static void	first_child(t_list *lst, int fd[2], pid_t *pid, t_list **env)
{
	t_data *data;
	
	data = lst->content;
	*pid = fork();
	if (*pid == 0)
		child_exec(data, env, STDIN_FILENO, fd[1]);
}

static void	second_child(t_list *lst, int fd[2], pid_t *pid, t_list **env)
{
	t_data *data;
	
	data = lst->content;
	*pid = fork();
	if (*pid == 0)
	{
		if (lst->next)
			exec_pipe(lst->next, env);
		else
			child_exec(data, env, fd[0], STDOUT_FILENO);
		exit(EXIT_SUCCESS);
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

