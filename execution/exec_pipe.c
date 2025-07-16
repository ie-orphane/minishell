/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:24:24 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/16 10:14:55 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	first_child(t_list *lst, int fd[2], pid_t *pid, t_list **env)
{
	char	**args;

	args = lst->content;
	*pid = fork();
	if (*pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		if (is_builtin_cmd(args))
		{
			exec_builtin(args, env);
			exit(EXIT_SUCCESS);
		}
		ft_execvpe(args[0], args, env);
		perror("larrysh");
		exit(EXIT_FAILURE);
	}
}

void	second_child(t_list *lst, int fd[2], pid_t *pid, t_list **env)
{
	char	**args;

	args = lst->content;
	*pid = fork();
	if (*pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		if (lst->next)
		{
			exec_pipe(lst, env);
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (is_builtin_cmd(args))
			{
				exec_builtin(args, env);
				exit(EXIT_SUCCESS);
			}
			ft_execvpe(args[0], args, env);
			perror("larrysh");
			exit(EXIT_FAILURE);
		}
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

void	execute_cmd(char **args, t_list **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		ft_execvpe(args[0], args, env);
		perror("larrysh");
		exit(127);
	}
	waitpid(pid, &status, 0);
	update_exit_status(status);
}
