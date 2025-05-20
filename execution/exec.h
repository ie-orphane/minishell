/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:02:35 by mbentale          #+#    #+#             */
/*   Updated: 2025/05/20 11:04:06 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define STDERR 2

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	t_env			*env;
}					t_shell;

// Built-ins
int					ft_echo(char **args);
int					ft_pwd(void);
int					ft_env(t_env *env);
int					ft_cd(char **args, t_env *env);

// Utilities
t_env				*init_env(char **env);
void				ft_putendl(char *s);
void				ft_putendl_fd(char *s, int fd);
void				free_env_list(t_env *env);
void				*ft_malloc(int size);

// Helper functions
int					go_to_path(int option, t_env *env);
int					check_key_exist(t_env **env, char *value);
void				print_error(char **args);
int					update_oldpwd(t_env *env);
int					update_pwd(t_env *env);

#endif // EXEC_H
