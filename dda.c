/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:43:16 by iel-mach          #+#    #+#             */
/*   Updated: 2022/07/06 13:54:44 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw(t_img *img, t_ddi *ddi)
{
	int		dakshi;
	float	d;
	float	ca;
	int		j;

	d = sqrt(pow((ddi->y - ddi->y0), 2) + pow((ddi->x - ddi->x0), 2));
	ca = ((img->r * M_PI) / 180) - (((img->r + img->a) * M_PI) / 180);
	if (ca < 0)
		ca += 2 * M_PI;
	if (ca > 2 * M_PI)
		ca -= 2 * M_PI;
	d = d * cos(ca);
	dakshi = (40 * 1080) / d;
	j = -1;
	while (++j < 1080 && img->y < 1920)
	{
		if (j < (int)(1080 - dakshi) / 2)
			my_mlx_pixel_put(&img->data, img->y, j, 42239);
		else if (j <= (int)((1080 - dakshi) / 2) + dakshi)
			my_mlx_pixel_put(&img->data, img->y, j, 13762560);
		else
			my_mlx_pixel_put(&img->data, img->y, j, 13794560);
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
