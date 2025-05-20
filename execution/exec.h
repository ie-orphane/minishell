/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:02:35 by mbentale          #+#    #+#             */
/*   Updated: 2025/05/19 19:45:00 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../libft/libft.h"
# include <limits.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>

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
char	*get_env_value(t_env *env, const char *key, size_t len); // delete later
int	update_oldpwd(t_env *env);                                // delete later

// Helper functions
void				*ft_malloc(int size);

#endif // EXEC_H
