/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:32:25 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/19 18:33:26 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

int		ft_strcmp(const char *s1, const char *s2);

bool	ft_ispipe(const char *str);
bool	ft_issredir(const char *str);
bool	ft_isdredir(const char *str);
bool	ft_isquote(const char *str);
bool	ft_isredir(const char *str);

char	*env_key(char *str);
char	*env_value(char *key);

void	ft_error(char *type, char *err);

t_list	*ft_fill(t_list *__lst);
t_list	*ft_spell(const char *str);
t_list	*ft_parse(char *line);

#endif // PARSING_H
