/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 08:49:40 by iel-mach          #+#    #+#             */
/*   Updated: 2022/07/05 16:21:35 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_splitit(t_cub *cub)
{
	t_color	color;
	char	**splt;
	int		i;

	splt = ft_split(cub->f, ',');
	color.a = ft_atoi(splt[0]);
	color.b = ft_atoi(splt[1]);
	color.c = ft_atoi(splt[2]);
	if (color.a > 255 || color.b > 255 || color.c > 255)
		return (0);
	i = -1;
	while (splt[++i])
		free(splt[i]);
	free(splt);
	splt = ft_split(cub->c, ',');
	color.i = ft_atoi(splt[0]);
	color.j = ft_atoi(splt[1]);
	color.k = ft_atoi(splt[2]);
	if (color.i > 255 || color.j > 255 || color.k > 255)
		return (0);
	i = -1;
	while (splt[++i])
		free(splt[i]);
	free(splt);
	return (1);
}

int	ft_checkcomma(char *s)
{
	int	i;
	int	comma;

	i = 0;
	comma = 1;
	while (s[i])
	{
		if (s[i] == ',')
			comma++;
		if (s[i] != ',' && !ft_isdigit(s[i]))
			return (0);
		if (s[0] == ',')
			return (0);
		if (s[i] == ',' && (!ft_isdigit(s[i - 1]) || !ft_isdigit(s[i + 1])))
			return (0);
		i++;
	}
	if (comma != 3)
		return (0);
	return (1);
}

void	ft_checkvar(t_cub *cub)
{
	t_color	color;
	int		i;

	i = 0;
	if (!cub->n || !cub->s || !cub->w || !cub->e || !cub->f || !cub->c)
	{
		printf("Error: check your variable\n");
		exit(1);
	}
	color.fdn = open(cub->n, O_RDONLY);
	color.fds = open(cub->s, O_RDONLY);
	color.fdw = open(cub->w, O_RDONLY);
	color.fde = open(cub->e, O_RDONLY);
	if (color.fdn < 0 || color.fds < 0 || color.fdw < 0 || color.fde < 0)
	{
		printf("Check the image file\n");
		exit(1);
	}
	if (!ft_checkcomma(cub->c) || !ft_checkcomma(cub->f))
	{
		printf("check color\n");
		exit (1);
	}
}

int	ft_checkzero(int i, char *str, char *str1)
{
	int	a;
	int	b;

	a = ft_strlen(str);
	b = ft_strlen(str1);
	if (i > a || i > b)
		return (0);
	return (1);
}

t_cub	*ft_parse(char **map)
{
	t_cub	*cub;
	int		i;
	int		j;
	int		a;

	i = -1;
	cub = malloc (sizeof(t_cub));
	if (!cub)
		return (NULL);
	while (map[++i])
	{
		j = 0;
		if (map[i][j] == ' ')
		{
			while (map[i][j] == ' ')
				j++;
			if (map[i][j] == '\0')
				i++;
			else
				break ;
		}
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
		else if (!ft_strncmp(map[i], "1", 1))
			break ;
	}
	j = 0;
	while (map[j])
		j++;
	a = j - i;
	cub->map = malloc(sizeof(char *) * (a + 1));
	j = 0;
	while (map[i])
		cub->map[j++] = ft_strdup(map[i++]);
	cub->map[j] = NULL;
	i = -1;
	while (map[++i])
		free(map[i]);
	free(map);
	return (cub);
}
