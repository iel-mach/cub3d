/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 23:11:52 by iel-mach          #+#    #+#             */
/*   Updated: 2022/07/04 17:20:56 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

typedef struct cub
{
	char	*n;
	char	*s;
	char	*w;
	char	*e;
	char	*f;
	char	*c;
	char	**map;
}	t_cub;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct img
{
	char	**map;
	void	*mlx;
	void	*mlx_win;
	t_data	data;
	t_cub	cub;
	int		whidth;
	int		height;
	int		i;
	int		j;
	int		x;
	int		y;
	float	a;
	int		r;
	float	t;
	float	f;
}	t_img;
typedef struct f
{
	int	i;
	int	a;
	int	b;
	int	c;
	int	j;
	int	k;
}	t_f;

typedef struct check
{
	int	n;
	int	s;
	int	w;
	int	e;
	int	f;
	int	c;
	int	no;
	int	so;
	int	we;
	int	ea;
	int	g;
}	t_check;

int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strrchr(char *s, int c);
int		ft_strlen(char *str);
void	ft_checkex(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
int		check_line(char *s);
char	*get_next_line(int fd);
char	*ft_strdup(char *s1);
char	**ft_split(char *s, char c);
char	*ft_skip(char *s1);
char	*ft_strjoin1(char *s1, char *s2);
int		ft_atoi(char *s);
int		ft_splitit(t_cub *cub);
int		ft_checkvar(t_cub *cub);
void    ft_checkmap(char **map);
t_cub	*ft_parse(char **map);
int		ft_isdigit(int c);
int		ft_skipspace(char *str);
void	ft_checkfile(char **map);
int		ft_checkspace(char *str);
char	*ft_getmap(char *str);
void	ft_hooks(t_img img);
int		ft_exit(void);
int		ft_keyhook(int key, t_img *img);
void	ft_dda(t_img *img, int X0, int Y0, int X1, int Y1);
void	ft_rays(t_img *img);
int ft_checkzero(int i, char *str, char *str1);

#endif