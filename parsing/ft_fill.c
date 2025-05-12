/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:52:07 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/12 18:58:55 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*ft_spell(const char *str)
{
	int		c[4];
	t_list	*lst;

	ft_bzero(c, sizeof(c));
	lst = NULL;
	while (str[c[0]] != '\0')
	{
		if (str[c[0]] != ' ')
		{
			c[1] = 0;
			while (str[c[0]] != '\0' && (str[c[0]] != ' ' || c[2]))
			{
				if (!c[2] && ft_isquote(str + c[0]))
					c[3] = str[c[0]];
				c[2] = (c[2] + (str[c[0]] == c[3])) % 2;
				c[3] *= c[2];
				c[0]++;
				c[1]++;
			}
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, c[0] - c[1], c[1])));
		}
		if (str[c[0]] != '\0')
			c[0]++;
	}
	return (lst);
}

t_list	*ft_fill(t_list *__lst)
{
	char	**arr;
	t_list	*lst;
	t_list	*node;
	char	*content;
	char	*tmp;

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
