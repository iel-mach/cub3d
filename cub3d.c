/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:35 by iel-mach          #+#    #+#             */
/*   Updated: 2022/07/04 20:46:43 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(void)
{
	exit(0);
	return (0);
}

void	ft_init(t_img *img)
{
	if (img->map[img->i][img->j] == 'N' || img->map[img->i][img->j] == 'S' || \
		img->map[img->i][img->j] == 'W' || img->map[img->i][img->j] == 'E')
	{
		if (img->map[img->i][img->j] == 'N')
			img->r = 270;
		else if (img->map[img->i][img->j] == 'S')
			img->r = 90;
		else if (img->map[img->i][img->j] == 'W')
			img->r = 180;
		else if (img->map[img->i][img->j] == 'E')
			img->r = 0;
		img->t = img->j * 40;
		img->f = img->i * 40;
	}
}

void	ft_drawmap(t_cub *cub)
{
	t_img	img;

	img.i = -1;
	img.map = cub->map;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 1920, 1080, "cub3d");
	img.data.img = mlx_new_image(img.mlx, 1920, 1080);
	img.data.addr = mlx_get_data_addr(img.data.img, &img.data.bits_per_pixel, \
		&img.data.line_length, &img.data.endian);
	while (img.map[++img.i])
	{
		img.j = -1;
		while (img.map[img.i][++img.j])
			ft_init(&img);
	}
	ft_rays(&img);
	ft_hooks(img);
}

char	**ft_split_file(char *str)
{
	char	**map;
	int		i;

	i = 0;
	// while (str[i])
	// {
	// 	if (str[i] == '1' && str[i + 1] == '\n' && str[i + 2] == '\n')
	// 	{
	// 		printf("Error: check map!\n");
	// 		exit(1);
	// 	}
	// 	i++;
	// }
	map = ft_split(str, '\n');
	free(str);
	return (map);
}

int	main(int ac, char **av)
{
	t_cub	*cub;
	char	**map;
	char	*str;

	if (ac != 2)
	{
		printf("Error: Bad Arg\n");
		return (1);
	}
	else
	{
		ft_checkex(av[1]);
		str = ft_getmap(av[1]);
		map = ft_split_file(str);
		if (!map[0])
		{
			printf("Error: empty file!\n");
			return (1);
		}
		ft_checkfile(map);
		cub = ft_parse(map);
		ft_checkmap(cub->map);
		if (!ft_checkvar(cub))
		{
			printf("Error: check\n");
			return (1);
		}
		if (!ft_splitit(cub))
		{
			printf("Error: check C or F\n");
			return (1);
		}
		ft_drawmap(cub);
	}
}