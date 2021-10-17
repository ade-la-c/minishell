/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:26:22 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/10/17 17:44:59 by ade-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

enum e_symbols
{
	CHR_SPACE = ' ',
	CHR_PIPE = '|',
	CHR_SQUOTE = '\'',
	CHR_DQUOTE = '\"',
	CHR_LESS = '<',
	CHR_MORE = '>'
};

#endif
