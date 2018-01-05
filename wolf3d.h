/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 13:16:00 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/01/03 13:19:19 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	WOLF3D_H
# define	WOLF3D_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <string.h>

#define MAPWIDTH 24
#define MAPHEIGHT 24

typedef	struct	s_rander
{
	int			map_x;
	int			map_y;
	double		raypos_x;
	double		raypos_y;
	double		camera_x;
	double		camera_y;
	double		raydir_x;
	double		raydir_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double 		perpwalldist;
	int			hit;
	int			side;
	int			step_x;
	int			step_y;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_rander;

typedef	struct 	s_pixel
{
	void		*ptr;
	void		*win;
	void		*img;
	char		*c_img;
	int			bpp;
	int			sl;
	int			color;
	int			endian;
	int			w;
	int			h;
	t_rander	*rander;
}				t_pixel;

void		vertline(t_pixel *ptr, int x, int start, int end);
void		draw_pixel(t_pixel **ptr, int x, int y);
t_pixel     *forward(t_pixel *ptr, int map[MAPWIDTH][MAPHEIGHT]);
t_pixel     *backward(t_pixel *ptr, int map[MAPWIDTH][MAPHEIGHT]);
t_pixel     *right(t_pixel *ptr);
t_pixel     *left(t_pixel *ptr);

#endif
