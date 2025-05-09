/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:52:07 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/09 10:01:04 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*ft_fill(t_list *__lst)
{
	char **arr;
	t_list *lst;
	t_list *node;
	char *content;
	char *tmp;

	node = __lst;
	arr = NULL;
	lst = NULL;
	while (node)
	{
		content = (char *)node->content;
		if (ft_ispipe(content) && !arr)
		{
			ft_error("SyntaxError", "Unexpected token '|'");
			break ;
		}
		if (ft_ispipe(content))
		{
			ft_lstadd_back(&lst, ft_lstnew(arr));
			arr = NULL;
		}
		else if (ft_isredir(content))
		{
			if (!node->next)
			{
				ft_error("SyntaxError", "Unexpected token 'end'");
				break ;
			}
			content = (char *)node->next->content;
			if (ft_ispipe(content) || ft_isredir(content))
			{
				tmp = ft_strreplace("Unexpected token '%s'", "%s", content);
				ft_error("SyntaxError", tmp);
				free(tmp);
				break ;
			}
			node = node->next;
		}
		else
			arr = ft_strsadd(arr, ft_strdup(content));
		node = node->next;
	}
	if (arr)
		ft_lstadd_back(&lst, ft_lstnew(arr));
	return (lst);
}
