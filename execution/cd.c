/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:14:33 by mbentale          #+#    #+#             */
/*   Updated: 2025/05/20 15:04:21 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_cd(char **args, t_env *env)
{
	int	cd_ret;

	if (args[2])
	{
		print_error(args);
		return (EXIT_FAILURE);
	}
	if (!args[1])
		cd_ret = go_to_path(0, env);
	else if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, env);
	else
	{
		update_oldpwd(env);
		cd_ret = chdir(args[1]);
		if (cd_ret == -1)
			print_error(args);
	}
	if (cd_ret != -1)
		update_pwd(env);
	return (cd_ret);
}
