/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:06:14 by mbentale          #+#    #+#             */
/*   Updated: 2025/05/09 10:14:32 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "exec.h"
# include "parsing.h"

typedef struct _s_env
{
	char	*key;
	char	*value;
}			_t_env;

void		_env_free(void *content);
_t_env		*_env_new(char *key, char *value);
t_list		*_env_init(char **__env);
void		_env_show(void *content);
char		*_env_get(t_list *env, char *key);
void		_env_set(t_list **env, char *key, char *value);

int			ft_export(char **args, t_list **env);

#endif // MAIN_H
