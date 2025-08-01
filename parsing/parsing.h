/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:32:25 by ielyatim          #+#    #+#             */
/*   Updated: 2025/08/01 16:27:43 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

# define BUFFER_SIZE 1024
# define MAX_FD 1024

typedef enum e_type
{
	T_PIPE,
	T_HER_DOC,
	T_APPEND,
	T_INPUT,
	T_OUTPUT,
	T_ARG,
	T_EMPTY,
	T_STRING,
	T_NONE,
	T_NULL,
}			t_type;

typedef struct s_cmd
{
	t_type	type;
	char	*value;
}			t_cmd;

int			ft_cmdcmp_type(t_cmd *ref, t_cmd *cmd);
t_cmd		*ft_cmdnew(char *value);
bool		ft_cmdis_redir(t_cmd *cmd);
void		ft_cmditer(t_list **lst, void (*f)(t_cmd *prev, t_cmd *cmd));

bool		ft_ispipe(const char *str);
bool		ft_issredir(const char *str);
bool		ft_isdredir(const char *str);
bool		ft_isquote(const char *str);
bool		ft_isredir(const char *str);

char		*env_key(char *str);
char		*env_value(char *key);

void		ft_err(char *err);

// -----------------------------------
// Parsing functions
//
// ft_parse_utils.c
// ft_parse.c
// -----------------------------------
char		*expand(char *str);
t_list		*ft_lstsplit(t_list *lst);
t_list		*ft_fill(t_list *__lst);
t_list		*ft_spell(const char *str);

t_list		*ft_parse(char *line);

#endif // PARSING_H
