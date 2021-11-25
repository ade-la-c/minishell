/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:09:50 by tzerates          #+#    #+#             */
/*   Updated: 2021/11/25 16:12:25 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_25(char *env_list, char *env_names)
{
	int	stop;

	stop = ft_strclen(env_list, '=');
	if (stop != -1)
	{
		env_names = ft_substr(env_list, 0, stop);
		if (!env_names)
			exit_error("substr failed");
	}
	else
	{
		env_names = ft_substr(env_list, 0, ft_strlen(env_list));
		if (!env_names)
			exit_error("substr failed");
	}
	return (env_names);
}

void	ft_print_unset(char *s)
{
	write(2, SHELL_NAME": unset: '", ft_strlen(SHELL_NAME) + 10);
	write(2, s, ft_strlen(s));
	write(2, ": not a valid identifier\n", 26);
	g_glb[1] = 1;
}
