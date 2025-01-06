/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoumare <asoumare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:20:32 by asoumare          #+#    #+#             */
/*   Updated: 2023/11/08 12:46:04 by asoumare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = b;
	i = 0;
	while (i < len)
	{
		ptr[i] = c;
		i++;
	}
	return (b);
}
// int main() {
// 	int		myArray[5];
// 	size_t	arraySize = sizeof(myArray) / sizeof(myArray[0]);

// 	ft_memset(myArray, 1, arraySize * sizeof(int));

// 	for (size_t i = 0; i < 10; i++) {
// 		printf("myArray[%zu] = %d\n", i, myArray[i]);
// 	}
// 	return 0;
// }
