/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mb11junior <mb11junior@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:24:24 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/28 19:18:20 by mb11junior       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	perror_and_exit(const char *msg)
{
	perror(msg);
	__exit(EXIT_FAILURE);
}

static void	exec_and_exit(t_list *lst, t_list **env)
{
	t_data	**data;

	data = (t_data **)&lst->content;
	if (is_builtin_cmd((*data)->args))
	{
		exec_builtin(&lst, env);
		__exit(EXIT_SUCCESS);
	}
	ft_execvpe((*data)->args[0], (*data)->args, env);
	perror("larrysh");
	__exit(EXIT_FAILURE);
}

static void	first_child(t_list *lst, int fd[2], pid_t *pid)
{
	t_data	*data;

	data = lst->content;
	*pid = fork();
	if (*pid == 0)
	{
		if (!is_valid_command(data->args[0], g_global.env)
			&& !is_builtin_cmd(data->args))
		{
			print_error(data->args[0], "command not found");
			__exit(127);
		}
		if (handle_redirections(data->redirs) < 0)
			perror_and_exit("larrysh: redirection error");
		close(fd[0]);
		if (!has_output_redirection(data->redirs))
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_and_exit(lst, &g_global.env);
	}
}

static void	second_child(t_list *lst, int fd[2], pid_t *pid)
{
	t_data	*data;

	data = lst->content;
	*pid = fork();
	if (*pid != 0)
		return ;
	if (!is_valid_command(data->args[0], g_global.env)
		&& !is_builtin_cmd(data->args))
	{
		print_error(data->args[0], "command not found");
		__exit(127);
	}
	if (handle_redirections(data->redirs) < 0)
		perror_and_exit("larrysh: redirection error");
	close(fd[1]);
	if (!has_input_redirection(data->redirs))
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	if (lst->next)
	{
		exec_pipe(lst);
		__exit(EXIT_SUCCESS);
	}
	else
		exec_and_exit(lst, &g_global.env);
}

void	exec_pipe(t_list *lst)
{
	int		status;
	int		pipe_fd[2];
	pid_t	pids[2];

	pipe(pipe_fd);
	first_child(lst, pipe_fd, &pids[0]);
	second_child(lst->next, pipe_fd, &pids[1]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pids[0], &status, 0);
	update_exit_status(status);
	waitpid(pids[1], &status, 0);
	update_exit_status(status);
}
