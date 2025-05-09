/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:32:25 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/09 09:58:46 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

int		ft_strcmp(const char *s1, const char *s2);

bool	ft_isredir(char *str);
bool	ft_ispipe(char *str);
void	ft_error(char *type, char *err);

t_list	*ft_fill(t_list *__lst);
t_list	*ft_parse(char *line);

#endif // PARSING_H
