/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:22:06 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/19 20:50:20 by ade-la-c         ###   ########.fr       */
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
		{printf(".");
			(*toklst) = (*toklst)->next;
		}printf("\n");
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

void	print_toklst(t_toklst *toklst, char *str)
{
	printf("{%s}", str);
	while (toklst->next)
	{
		printf("[%s]\n", toklst->content);
		toklst = toklst->next;
	}
	printf("\n");
}
