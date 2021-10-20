/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toklst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:52:28 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/20 18:55:33 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_toklst	*toklstnew(void *content, int type)
{
	t_toklst	*ptr;

	ptr = (t_toklst *)malloc(sizeof(t_toklst));
	if (!ptr)
		exit_error("malloc failed");
	*ptr = (t_toklst){content, type, NULL};
	return (ptr);
}

void	toklstadd_back(t_toklst **toklst, t_toklst *new)
{
	if (!toklst || !new)
		exit_error("toklstadd_back");
	if (!(*toklst))
		*toklst = new;
	else
	{
		while ((*toklst)->next != NULL)
			toklst = &(*toklst)->next;
		(*toklst)->next = new;
	}
}

void	toklstdelone(t_toklst *toklst, void (*del)(void *))
{
	if (!toklst || !del)
		exit_error("toklstdelone");
	if (toklst->content)
		(*del)(toklst->content);
	free(toklst);
}

void	toklstclear(t_toklst **toklst, void (*del)(void *))
{
	t_toklst	*tmp;

	if (!toklst || !del)
		exit_error("toklstclear");
	while (*toklst)
	{
		tmp = (*toklst)->next;
		toklstdelone(*toklst, del);
		(*toklst) = tmp;
	}
	*toklst = NULL;
}
