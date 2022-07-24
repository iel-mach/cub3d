/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:43:16 by iel-mach          #+#    #+#             */
/*   Updated: 2022/07/08 17:39:06 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_wall(t_img *img, t_ddi *ddi)
{
	if (img->map[(int)(ddi->y / 40)][(int)((ddi->x - ddi->xinc)/ 40)] != '1')
	{
		if (ddi->xinc > 0)
			ddi->dwall = 1;
		else
			ddi->dwall = 2;
	}
	else if (img->map[(int)((ddi->y - ddi->yinc) / 40)][(int)(ddi->x / 40)] != '1')
	{
		if (ddi->yinc > 0)
			ddi->dwall = 3;
		else
			ddi->dwall = 4;
	}
}


int	ft_getcolor(t_ddi *ddi)
{
	if (ddi->dwall == 1)
		return (13762560);
	else if (ddi->dwall == 2)
		return (3124639);
	else if (ddi->dwall == 3)
		return (3124480);
	else if (ddi->dwall == 4)
		return (15922176);
	return (0);
}
void	ft_sheftcolor(t_img *img, t_cub *cub)
{
	img->floor = (cub->redf << 16) + (cub->greenf << 8) + cub->bluef;
	img->ceilling = (cub->redc << 16) + (cub->greenc << 8) + cub->bluec;
}
void	ft_draw(t_img *img, t_ddi *ddi)
{
	int		dakshi;
	float	d;
	float	ca;
	int		j;

	ft_wall(img, ddi);
	d = sqrt(pow((ddi->y - ddi->y0), 2) + pow((ddi->x - ddi->x0), 2));
	ca = ((img->r * M_PI) / 180) - (((img->r + img->a) * M_PI) / 180);
	if (ca < 0)
		ca += 2 * M_PI;
	if (ca > 2 * M_PI)
		ca -= 2 * M_PI;
	d = d * cos(ca);
	dakshi = (40 * WIN_HEIGHT) / d;
	j = -1;
	while (++j < WIN_HEIGHT && img->y < WIN_WIDTH)
	{
		if (j < (int)(WIN_HEIGHT - dakshi) / 2)
			my_mlx_pixel_put(&img->data, img->y, j, img->ceilling);
		else if (j <= (int)((WIN_HEIGHT - dakshi) / 2) + dakshi)
		{
			if (ddi->dwall == 1 || ddi->dwall == 2)
				ddi->c = fmod(img->y, 1);
			else
				ddi->c = fmod(j, 1);
			my_mlx_pixel_put(&img->data, img->y, j, ft_getcolor(ddi));
		}
		else
			my_mlx_pixel_put(&img->data, img->y, j, img->floor);
	}
}

void	ft_dda(t_img *img, t_ddi *ddi)
{
	ddi->dx = ddi->x1 - ddi->x0;
	ddi->dy = ddi->y1 - ddi->y0;
	if (abs(ddi->dx) > abs(ddi->dy))
		ddi->steps = abs(ddi->dx);
	else
		ddi->steps = abs(ddi->dy);
	ddi->xinc = ddi->dx / (float) ddi->steps;
	ddi->yinc = ddi->dy / (float) ddi->steps;
	ddi->x = ddi->x0;
	ddi->y = ddi->y0;
	while (1)
	{
		if (img->map[(int)(ddi->y / 40)][(int)(ddi->x / 40)] == '1' \
			|| img->map[(int)(ddi->y / 40)][(int)(ddi->x / 40)] == ' ' \
			|| !img->map[(int)(ddi->y / 40)][(int)(ddi->x / 40)])
			break ;
		ddi->x += ddi->xinc;
		ddi->y += ddi->yinc;
	}
	ft_draw(img, ddi);
}
