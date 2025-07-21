/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mb11junior <mb11junior@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:40:06 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/21 16:04:58 by mb11junior       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_exec(t_list *lst, t_list **env)
{
	t_data	*data;
	

	data = lst->content;
	if (!lst->next && is_builtin_cmd(data->args))
	{
		if (data->redirs && data->redirs[0])
		{
			exec_with_redir(data, env, true);
		}
		else
			exec_builtin(data->args, env);
	}
	else if (lst->next)
		exec_pipe(lst, env);
	else
	{
		if (data->redirs && data->redirs[0])
			exec_with_redir(data, env, false);
		else
			execute_cmd(data->args, env);
	}
}
