/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:19:46 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/24 18:53:50 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_tokel(void *content)
{
	t_token	*token;
	t_list	el;

	if (content == NULL)
		return ;
	el.content = (t_list *)content;
	token = (t_token *)el.content;
	free(token->content);
	free(el.content);
}

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
	free(prog);
}

void	free_envel(void *content)
{
	char	**strs;
	t_list	el;

	el.content = (t_list *)content;
	strs = (char **)el.content;
	free(strs[0]);
	free(strs[1]);
	free(strs);
}

void	ft_free(t_data *data)
{
	ft_lstclear(&(data->toklst), free_tokel);
	ft_lstclear(&(data->proglst), free_prog);
	ft_lstclear(&(data->envlst), free_envel);
	free(data->progs);
}

void	env_free(t_list *envlst)
{
	ft_lstclear(&(envlst), free_envel);
	free(envlst);
	printf("exit\n");
	exit(0);
}

void	free_toks(t_data *data, t_token *toks)
{
	int		i;

	i = -1;
	while (++i < data->toklen)
		free(toks[i].content);
	free(toks);
}
