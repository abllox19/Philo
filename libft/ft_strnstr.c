/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoumare <asoumare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:37:05 by asoumare          #+#    #+#             */
/*   Updated: 2023/11/08 16:56:11 by asoumare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (str2[0] == '\0')
		return ((char *)(str1));
	if (len == 0)
		return (NULL);
	while (str1[i])
	{
		while (str1[i + j] == str2[j] && i + j < len)
		{
			if (str2[j + 1] == '\0')
				return ((char *)(str1 + i));
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}
