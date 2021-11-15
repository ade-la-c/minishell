/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:26:22 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/15 15:03:55 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define PIPE		10
# define MORE		11
# define LESS		12
# define DMORE		13
# define DLESS		14
# define SPACE		15
# define WORD		16
# define DQUOTE_STR	17
# define SQUOTE_STR	18

enum e_symbols
{
	CHR_SPACE	= ' ',
	CHR_PIPE	= '|',
	CHR_SQUOTE	= '\'',
	CHR_DQUOTE	= '\"',
	CHR_LESS	= '<',
	CHR_MORE	= '>'
};

#endif
