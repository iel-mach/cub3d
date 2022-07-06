/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:39:27 by iel-mach          #+#    #+#             */
/*   Updated: 2022/07/06 11:00:44 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hooks(t_img img)
{
	mlx_hook(img.mlx_win, 02, 1L << 0, ft_keyhook, &img);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.data.img, 0, 0);
	mlx_hook(img.mlx_win, 17, 0, ft_exit, NULL);
	mlx_loop(img.mlx);
}

void	ft_rays(t_img *img)
{
	t_ddi	ddi;

	img->y = -1;
	img->a = -32;
	while (++img->y < 1920)
	{
		ddi.x0 = img->t + 20;
		ddi.y0 = img->f + 20;
		ddi.x1 = img->t + (1000 * cos((img->r + img->a) * M_PI / 180));
		ddi.y1 = img->f + (1000 * sin((img->r + img->a) * M_PI / 180));
		ft_dda(img, &ddi);
		img->a += (float)1 / (1920 / 64);
	}
}

int	ft_keyhook(int key, t_img *img)
{
	if (key == 13)
	{
		img->y0 = (img->f + (sin(img->r * M_PI / 180) * 10)) / 40;
		img->x0 = (img->t + (cos(img->r * M_PI / 180) * 10)) / 40;
		if (img->map[(int)img->y0][(int)img->x0] != '0')
			return (0);
		img->f += sin(img->r * M_PI / 180) * 10;
		img->t += cos(img->r * M_PI / 180) * 10;
	}
	else if (key == 0)
	{
		img->y0 = (img->f - sin(((img->r + 90) % 360) * M_PI / 180) * 10) / 40;
		img->x0 = (img->t - cos(((img->r + 90) % 360) * M_PI / 180) * 10) / 40;
		if (img->map[(int)img->y0][(int)img->x0] != '0')
			return (0);
		img->t = img->x0 * 40;
		img->f = img->y0 * 40;
	}
	else if (key == 1)
	{
		img->y0 = (img->f - (sin(img->r * M_PI / 180) * 10)) / 40;
		img->x0 = (img->t - (cos(img->r * M_PI / 180) * 10)) / 40;
		if (img->map[(int)img->y0][(int)img->x0] != '0')
			return (0);
		img->t -= cos(img->r * M_PI / 180) * 10;
		img->f -= sin(img->r * M_PI / 180) * 10;
	}
	else if (key == 2)
	{
		img->y0 = (img->f + sin((img->r + 90) * M_PI / 180) * 10) / 40;
		img->x0 = (img->t + cos((img->r + 90) * M_PI / 180) * 10) / 40;
		if (img->map[(int)img->y0][(int)img->x0] != '0')
			return (0);
		img->t = (img->t + (cos(((img->r + 90) % 360) * M_PI / 180) * 10));
		img->f = (img->f + (sin(((img->r + 90) % 360) * M_PI / 180) * 10));
	}
	else if (key == 124)
		img->r = (img->r + 2) % 360;
	else if (key == 123)
		img->r = (img->r + 358) % 360;
	else if (key == 53)
		ft_exit();
	if (img->r > 360)
		img->r = 0;
	if (img->r < 0)
		img->r = 360;
	ft_rays(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->data.img, 0, 0);
	return (0);
}
