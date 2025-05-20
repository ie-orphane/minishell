/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:52:59 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/16 15:53:15 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Inserts a new node after the given node in the linked list.
 *
 * @param lst A pointer to the node after which the new node will be inserted.
 * @param __new The new node to be inserted.
 */
void	ft_lstinsert(t_list **lst, t_list *__new)
{
	if (!lst || !*lst || !__new)
		return ;
	__new->next = (*lst)->next;
	(*lst)->next = __new;
}
