/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:18:44 by mbentale          #+#    #+#             */
/*   Updated: 2025/05/08 09:12:19 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *__new)
{
	t_list	*last_node;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = __new;
	else
	{
		last_node = ft_lstlast(*lst);
		last_node->next = __new;
	}
}
