/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mb11junior <mb11junior@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:02:35 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/28 19:15:50 by mb11junior       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "libft.h"
# include "parsing.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define STDERR 2

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

// Execution functions
int			is_builtin_cmd(char **args);
void		exec_builtin(t_list **lst, t_list **env);
void		exec_pipe(t_list *lst, t_list **env);
int			ft_execvpe(char *file, char **argv, t_list **env);
void		ft_exec(t_list **lst, t_list **env);
void		update_exit_status(int status);
int			handle_redirections(char **args);
bool		is_valid_command(char *cmd, t_list *env);
char		*join_path(const char *dir, const char *file);
void		perror_and_exit(const char *msg);
void		print_error(char *cmd, char *msg);
bool		has_output_redirection(char **redirs);
bool		has_input_redirection(char **redirs);

// Built-ins
int			ft_echo(char **args);
int			ft_pwd(void);
int			ft_env(t_list *env);
int			ft_cd(char **args, t_list *env);
int			ft_export(char **args, t_list **env);
int			ft_unset(char **args, t_list **env);
int			ft_exit(t_list **lst, t_list **env);

// env helper functions
t_env		*env_new(char *key, char *value);
t_list		*env_init(char **__env);
void		env_free(void *content);
char		*env_get(t_list *env, char *key);
void		env_set(t_list **env, char *key, char *value);
char		**env_to_array(t_list *env);
void		free_2d(char **arr);

#endif
