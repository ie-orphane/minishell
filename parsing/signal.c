/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:53:53 by ielyatim          #+#    #+#             */
/*   Updated: 2025/07/24 10:45:46 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	_sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	__exit(130);
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_global.exit_status = 130;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	printf("\n" GREEN BOLD "larrysh> " RESET);
}
