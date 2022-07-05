/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_skip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 01:54:03 by iel-mach          #+#    #+#             */
/*   Updated: 2022/06/24 02:39:15 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// char    *ft_skipn(char *str)
// {
//     int i;
//     char    *n;

//     i = 2;
//     while(str[i] == ' ')
//         i++;
//     while(n)
//     return (n);
// }

char	*ft_skip(char *s1)
{
	char	*ptr;
	int		len;
	int		i;
	int		x;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	ptr = malloc (len + 1 * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 2;
    while(s1[i] == ' ' || s1[i] == '\t')
        i++;
	x = 0;
	while (i < len )
	{
		ptr[x] = s1[i];
		i++;
        x++;
	}
	ptr[x] = '\0';
	s1 = ptr;
	return (s1);
}
