/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:19:46 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/21 14:24:58 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// /*.
void	free_tokel(void *ptr)
{
	t_token	*token;
	t_list	*el;

	el = (t_list *)ptr;
	token = (t_token *)el->content;
	if (!token)
		return ;
	free(el->content);
	free(ptr);
}

// */

void	free_prog(void *ptr)
{
	int		i;
	t_prog	*prog;

	i = 0;
	if (ptr == NULL)
		return ;
	prog = (t_prog *)ptr;
	while (prog->av[i])
		free(prog->av[i++]);
	free(prog->av);
	free(ptr);
}

void	ft_free(t_data *data)
{
	ft_lstclear(&(data->toklst), free_tokel);
	ft_lstclear(&(data->proglst), free_prog);
	// free(data->toks);
}

void	env_free(t_list *envlst)
{
	char	**strs;

	while (envlst->next)
	{
		strs = (char **)envlst->content;
		free(strs[0]);
		free(strs[1]);
		envlst = envlst->next;
	}
	strs = (char **)envlst->content;
	free(strs[0]);
	free(strs[1]);
	ft_lstclear(&(envlst), free);
	printf("exit\n");
	exit(0);
}
