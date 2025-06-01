/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:02:35 by mbentale          #+#    #+#             */
/*   Updated: 2025/06/01 07:57:53 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "libft.h"
# include <errno.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define STDERR 2

typedef struct s_env
{
	char	*key;
	char	*value;
}			t_env;

typedef struct s_shell
{
	t_list	*env;
}			t_shell;

// Built-ins
int			ft_echo(char **args);
int			ft_pwd(void);
int			ft_env(t_list *env);
int			ft_cd(char **args, t_list *env);
int			ft_export(char **args, t_list **env);
int			ft_unset(char **args, t_list **env);
int			ft_exit(char **args, t_list **env, t_list **lst, char **line);
// int			ft_exit(char **args, t_list **env);

// env helper functions
t_env		*env_new(char *key, char *value);
t_list		*env_init(char **__env);
void		env_free(void *content);
char		*env_get(t_list *env, char *key);
void		env_set(t_list **env, char *key, char *value);
void		env_del(t_list **env, char *key);

// Utilities
void		ft_putendl(char *s);
void		ft_putendl_fd(char *s, int fd);
void		*ft_malloc(int size);

// Helper functions

#endif // EXEC_H
