/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:43:16 by iel-mach          #+#    #+#             */
/*   Updated: 2022/07/04 14:26:27 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void ft_dda(t_img *img, int X0, int Y0, int X1, int Y1)
{
	int dx = X1 - X0;
	int dy = Y1 - Y0;
	int steps;

	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
 
	float Xinc = dx / (float) steps;
	float Yinc = dy / (float) steps;
	float X = X0;
	float Y = Y0;
	while (1)
	{
		if (img->map[(int)(Y / 40)][(int)(X / 40)] == '1' || img->map[(int)(Y / 40)][(int)(X / 40)] == ' ')
			break;
		X += Xinc;
		Y += Yinc;
	}
	float D = sqrt(pow((Y - Y0), 2) + pow((X - X0), 2));
	float CA = ((img->r * M_PI) / 180) - (((img->r + img->a) * M_PI) / 180);
    if (CA < 0)
        CA += 2 * M_PI;
    if (CA > 2 * M_PI)
        CA -= 2 * M_PI;
    D = D * cos(CA);
	int Dakshi = (40 * 1080) / D;
	int j = -1;
	while (++j < 1080 && img->y < 1920)
	{
		if (j < (int)(1080 - Dakshi) / 2)
			my_mlx_pixel_put(&img->data, img->y, j, 42239);
		else if (j <= (int)((1080 - Dakshi) / 2) + Dakshi)
			my_mlx_pixel_put(&img->data, img->y, j, 13762560);
		else
			my_mlx_pixel_put(&img->data, img->y, j, 13794560);
	}
}