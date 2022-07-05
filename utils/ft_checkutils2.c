/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkutils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 08:53:54 by iel-mach          #+#    #+#             */
/*   Updated: 2022/07/05 07:25:49 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void ft_checkex(char *str)
{
    char *ex;
    
    if (!str)
        exit(1);
    ex = ft_strrchr(str, '.');
    if (!ex)
    {
        printf("map extension invalide !\n");
        exit(1);
    }
    if (ft_strncmp(ex, ".cub", 4) || ft_strlen(ex) != 4)
    {
        printf("map extension must be end with .cub !\n");
        exit(1);
    }
}

char    *ft_getmap(char *str)
{
    int fd;
    char *get;
    char    *join;
    // char **map;

    fd = open(str, O_RDONLY);
    if (fd == -1)
    {
        printf("Error: cannot open map\n");
        exit(1);
    }
    get = get_next_line(fd);
    join = ft_strdup("");
    while(get)
    {
        join = ft_strjoin(join, get);
        free(get);
        get = get_next_line(fd);
    }
    // map = ft_split(join, '\n');
    // free(join);
    return (join);
}

int ft_checkspace(char *str)
{
    int i;

    i = 0;
    while (str[i] == ' ')
		i++;
    if (str[i] == '1')
        return(1);
    if (str[i] == '\0')
        return (1);
    return (0);
}

void    ft_checkfile(char **map)
{
    int     i;
    t_check check;

    i = 0;
    check.n = 0;
    check.s = 0;
    check.w = 0;
    check.e = 0;
    check.f = 0;
    check.c = 0;
    while (map[i])
    {
        if (!ft_strncmp(map[i], "NO ", 3))
        {
            i++;
           check.n++;
        }
        else if (!ft_strncmp(map[i], "SO ", 3))
        {
            i++;
            check.s++;
        }
        else if (!ft_strncmp(map[i], "WE ", 3))
        {
            i++;
            check.w++;
        }
        else if (!ft_strncmp(map[i], "EA ", 3))
        {
            i++;
            check.e++;
        }
        else if (!ft_strncmp(map[i], "F ", 2))
        {
            i++;
            check.f++;
        }
        else if (!ft_strncmp(map[i], "C ", 2))
        {
            i++;
            check.c++;
        }
        else if (!ft_strncmp(map[i], "1", 1))
            i++;
        else if (ft_checkspace(map[i]))
            i++;
        else
        {
            printf("Error: check file!\n");
            exit(1);
        }
    }
    if (check.n != 1 || check.s != 1 || check.w != 1 || check.e != 1 || check.f != 1 || check.c != 1)
    {
        printf("Error: check file!\n");
        exit(1);
    }
}

int ft_skipspace(char *str)
{
    int i;

    i = 0;
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
    if (str[i] == '\0')
        return (1);
    return (0);
}
