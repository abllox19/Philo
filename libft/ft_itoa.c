/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoumare <asoumare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:24:58 by asoumare          #+#    #+#             */
/*   Updated: 2023/11/10 19:04:10 by asoumare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*d;
	char	*new;
	size_t	i;

	i = 0;
	new = ((d = (char *)malloc(sizeof(char) * size + 1)));
	if (!d)
		return (NULL);
	while (i < size)
	{
		new[i] = '\0';
		i++;
	}
	new[i] = '\0';
	return (new);
}

static int	taille_str(long long int n)
{
	long long int	i;

	i = 1;
	if (n < 0)
		n = n * -1;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*rempli_str(char *str, long long int n, int len)
{
	int		debut;

	str[len] = '\0';
	len -= 1;
	if (n < 0)
	{
		n = n * -1;
		debut = 1;
		str[0] = '-';
	}
	else
		debut = 0;
	while (len >= debut)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				len;
	long long int	lli;

	lli = n;
	len = taille_str(lli);
	if (lli < 0)
		len = len + 1;
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	str = rempli_str(str, lli, len);
	return (str);
}
