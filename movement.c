/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 09:35:10 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/01/05 12:44:04 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_pixel     *forward(t_pixel *ptr, int map[MAPWIDTH][MAPHEIGHT])
{
	double mspeed;

	mspeed = 5.0 / 20;
	if(map[(int)(ptr->rander->pos_x + ptr->rander->dir_x *
				mspeed)][(int)(ptr->rander->pos_y)] == 0)
		ptr->rander->pos_x += ptr->rander->dir_x * mspeed;
	if(map[(int)(ptr->rander->pos_x)][(int)(ptr->rander->pos_y +
				ptr->rander->dir_y * mspeed)] == 0)
		ptr->rander->pos_y += ptr->rander->dir_y * mspeed;
	return (ptr);
}

t_pixel     *backward(t_pixel *ptr, int map[MAPWIDTH][MAPHEIGHT])
{
	double mspeed;

	mspeed = 5.0 / 20;
	if(map[(int)(ptr->rander->pos_x - ptr->rander->dir_x *
				mspeed)][(int)(ptr->rander->pos_y)] == 0)
		ptr->rander->pos_x -= ptr->rander->dir_x * mspeed;
	if(map[(int)(ptr->rander->pos_x)][(int)(ptr->rander->pos_y -
				ptr->rander->dir_y * mspeed)] == 0)
		ptr->rander->pos_y -= ptr->rander->dir_y * mspeed;
	return (ptr);
}

t_pixel     *right(t_pixel *ptr)
{
	double rspeed;
	
	rspeed = 3.0/ 100;
	double oldDirX = ptr->rander->dir_x;
	ptr->rander->dir_x = ptr->rander->dir_x * cos(-rspeed) -
		ptr->rander->dir_y * sin(-rspeed);
	ptr->rander->dir_y = oldDirX * sin(-rspeed) + ptr->rander->dir_y *
		cos(-rspeed);
	double oldPlaneX = ptr->rander->plane_x;
	ptr->rander->plane_x = ptr->rander->plane_x *
		cos(-rspeed) - ptr->rander->plane_y * sin(-rspeed);
	ptr->rander->plane_y = oldPlaneX * sin(-rspeed) +
		ptr->rander->plane_y * cos(-rspeed);
	return (ptr);
}

t_pixel     *left(t_pixel *ptr)
{
	double rspeed;

	rspeed = 3.0/ 100;
	double oldDirX = ptr->rander->dir_x;
	ptr->rander->dir_x = ptr->rander->dir_x *
		cos(rspeed) - ptr->rander->dir_y * sin(rspeed);
	ptr->rander->dir_y = oldDirX * sin(rspeed) +
		ptr->rander->dir_y * cos(rspeed);
	double oldPlaneX = ptr->rander->plane_x;
	ptr->rander->plane_x = ptr->rander->plane_x *
		cos(rspeed) - ptr->rander->plane_y * sin(rspeed);
	ptr->rander->plane_y = oldPlaneX * sin(rspeed) +
		ptr->rander->plane_y * cos(rspeed);
	return (ptr);
}
