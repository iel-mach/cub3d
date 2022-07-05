/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:39:27 by iel-mach          #+#    #+#             */
/*   Updated: 2022/07/04 14:55:25 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_hooks(t_img img)
{
    mlx_hook(img.mlx_win, 02, 1L<<0, ft_keyhook, &img);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.data.img, 0, 0);
	mlx_hook(img.mlx_win, 17, 0, ft_exit, NULL);
	mlx_loop(img.mlx);
}


void	ft_rays(t_img *img)
{
	img->y = -1;
	img->a = -32;
	while (++img->y < 1920)
	{
		ft_dda(img, img->t + 20, img->f + 20, img->t  +  (1000 * cos((img->r + img->a) * M_PI / 180)), \
			img->f + (1000 * sin((img->r + img->a) * M_PI / 180)));
		img->a += (float)1 / (1920 / 64);
	}
}

int ft_keyhook(int key, t_img *img)
{
	if (key == 13)
	{
			img->t += cos(img->r  * M_PI / 180) * 10;
			img->f += sin(img->r * M_PI / 180) * 10;
	}
	else if (key == 0)
	{
		img->r -= 90;
		img->t += cos(img->r  * M_PI / 180) * 10;
		img->f += sin(img->r * M_PI / 180) * 10;
		img->r += 90;
	}
	else if (key == 1)
	{
		img->t -= cos(img->r  * M_PI / 180) * 10;
		img->f -= sin(img->r * M_PI / 180) * 10;
	}
	else if (key == 2)
	{
		img->r += 90;
		img->t += cos(img->r  * M_PI / 180) * 10;
		img->f += sin(img->r * M_PI / 180) * 10;
		img->r -= 90;
	}
	else if (key == 124)
		img->r += 5;
	else if (key == 123)
		img->r -= 5;
	else if (key == 53)
		ft_exit();
	if (img->r > 360)
		img->r = 0;
	if (img->r < 0)
		img->r = 360;
	ft_rays(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->data.img, 0, 0);
	return(0);
}