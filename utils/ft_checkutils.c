/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 08:49:40 by iel-mach          #+#    #+#             */
/*   Updated: 2022/07/04 17:20:48 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int ft_splitit(t_cub *cub)
{
    t_f f;
    char **splt;
    int i;

    splt = ft_split(cub->c, ',');
    f.a = ft_atoi(splt[0]);
    f.b = ft_atoi(splt[1]);
    f.c = ft_atoi(splt[2]);
    if (f.a > 255 || f.b > 255 || f.c > 255)
        return (0);
    i = -1;
    while(splt[++i])
        free(splt[i]);
    free(splt);
    splt = ft_split(cub->c, ',');
    f.i = ft_atoi(splt[0]);
    f.j = ft_atoi(splt[1]);
    f.k = ft_atoi(splt[2]);
    if (f.i > 255 || f.j > 255 || f.k > 255)
        return (0);
    i = -1;
     while(splt[++i])
        free(splt[i]);
    free(splt);
    return(1);
}

int ft_checkvar(t_cub *cub)
{
    int fdn;
    int fds;
    int fdw;
    int fde;
    int i;
    
    i = 0;
    if (!cub->n || !cub->s || !cub->w || !cub->e)
        return (0);
    fdn = open(cub->n, O_RDONLY);
    fds = open(cub->s, O_RDONLY);
    fdw = open(cub->w, O_RDONLY);
    fde = open(cub->e, O_RDONLY);
    if (fdn < 0 || fds < 0 || fdw < 0 || fde < 0)
        return (0);
    while(cub->c[i])
    {
        if (cub->c[i] != ',' && !ft_isdigit(cub->c[i]))
            return (0);
        if (cub->c[0] == ',')
            return (0);
        if(cub->c[i] == ',' && (!ft_isdigit(cub->c[i - 1])  || !ft_isdigit(cub->c[i + 1])))
            return (0);
        i++;
    }
    i = 0;
    while(cub->f[i])
    {
        if (cub->f[i] != ',' && !ft_isdigit(cub->f[i]))
            return (0);
        if (cub->f[0] == ',')
            return (0);
        if(cub->f[i] == ',' && (!ft_isdigit(cub->f[i - 1])  || !ft_isdigit(cub->f[i + 1])))
            return (0);
        i++;
    }
    return (1);
}


int ft_checkzero(int i, char *str, char *str1)
{
    int a;
    int b;

    a = ft_strlen(str);
    b = ft_strlen(str1);
    // i++;
    if (i > a || i > b )
        return (0);
    return (1);
}

t_cub   *ft_parse(char  **map)
{
    t_cub   *cub;
    int     i;
    int     j;
    int     a;

    i = 0;
    j = 0;
    cub = malloc (sizeof(t_cub));
    if (!cub)
        return (NULL);
    while (map[i])
    {
        
        if (ft_skipspace(map[i]))
            i++;
        if (!ft_strncmp(map[i], "NO ", 3))
            cub->n = ft_skip(map[i]);
        else if (!ft_strncmp(map[i], "SO ", 3))
            cub->s = ft_skip(map[i]);
        else if (!ft_strncmp(map[i], "WE ", 3))
            cub->w = ft_skip(map[i]);
        else if (!ft_strncmp(map[i], "EA ", 3))
            cub->e = ft_skip(map[i]);
        else if (!ft_strncmp(map[i], "F ", 2))
            cub->f = ft_skip(map[i]);
        else if (!ft_strncmp(map[i], "C ", 2))
            cub->c = ft_skip(map[i]);
        else
            break;
        i++;
    }
    while (map[j])
        j++;
    a = j - i;
    cub->map = malloc(sizeof(char *) * (a + 1));
    j = 0;
    while (map[i])
        cub->map[j++] = ft_strdup(map[i++]);
    cub->map[j] = NULL;
    i = -1;
    while(map[++i])
        free(map[i]);
    free(map);
    return (cub);
}