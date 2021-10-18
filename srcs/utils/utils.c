/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:22:06 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/18 13:34:43 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_toklst	*toklstnew(void *content, int type)
{
	t_toklst	*ptr;

	ptr = (t_toklst *)malloc(sizeof(t_toklst));
	if (!ptr)
		exit_error("malloc failed");
	ptr->content = content;
	ptr->type = type;
	ptr->next = NULL;
	return (ptr);
}

void	toklstadd_back(t_toklst **toklst, t_toklst *new)
{
	if (!toklst || !new)
		return ;
	if (!(*toklst))
		*toklst = new;
	else
	{
		while ((*toklst)->next)
			*toklst = (*toklst)->next;
		(*toklst)->next = new;
	}
}

void	exit_error(char *error)
{
	ft_putstr(error);
	ft_putchar('\n');
	exit(0);
}

// provisoire

void	print_toklst(t_toklst *toklst)
{
	while (toklst->next)
	{
		printf("%s\n", toklst->content);
		toklst = toklst->next;
	}
}
