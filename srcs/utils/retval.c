/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retval.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 22:03:18 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/22 22:38:45 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

static int	*get_retval(void)
{
	static int	retval = 0;

	return (&retval);
}

void	msh_parser_set_retval(int retval)
{
	*get_retval() = retval;
}

int	msh_parser_get_retval(void)
{
	return (*get_retval());
}
