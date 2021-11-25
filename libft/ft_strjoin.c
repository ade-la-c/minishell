/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzerates <tzerates@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:37:12 by ade-la-c          #+#    #+#             */
/*   Updated: 2021/11/25 13:53:24 by tzerates         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (s2 == NULL)
		return (ft_strdup(s1));
	str = (malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (!s1 || !s2 || !str)
		return (NULL);
	*str = '\0';
	return (ft_strcat(ft_strcpy(str, s1), s2));
}
