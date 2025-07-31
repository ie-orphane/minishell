/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:06:14 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/24 10:47:30 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "exec.h"
# include "parsing.h"

typedef struct s_data
{
	char	**args;
	char	**redirs;
}			t_data;

void		ft_dataclear(void *__data);
t_data		*ft_datanew(char **args, char **redirs);
void __exit(int status);
typedef struct s_global
{
	t_list	*env;
	t_list	*lst;
	int		exit_status;
}	t_global;

extern t_global	g_global;

// -----------------------------------
// Signal handlers
//
// signal.c
// -----------------------------------
void		sigint_handler(int sig);
void		_sigint_handler(int sig);

void		ft_dataclear(void *__data);

#endif // MAIN_H
