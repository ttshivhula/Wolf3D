/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 09:35:10 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/01/05 09:35:23 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_pixel     *forward(t_pixel *ptr, int map[MAPWIDTH][MAPHEIGHT])
{
    double moveSpeed;
    double rotSpeed;
    
    moveSpeed = 5.0 / 50;
    rotSpeed = 3.0/ 50;
    if(map[(int)(ptr->rander->pos_x + ptr->rander->dir_x * moveSpeed)][(int)(ptr->rander->pos_y)] == 0)
        ptr->rander->pos_x += ptr->rander->dir_x * moveSpeed;
    if(map[(int)(ptr->rander->pos_x)][(int)(ptr->rander->pos_y + ptr->rander->dir_y * moveSpeed)] == 0)
        ptr->rander->pos_y += ptr->rander->dir_y * moveSpeed;
    return (ptr);
}

t_pixel     *backward(t_pixel *ptr, int map[MAPWIDTH][MAPHEIGHT])
{
    double moveSpeed;
    double rotSpeed;
    
    moveSpeed = 5.0 / 50;
    rotSpeed = 3.0/ 50;
    if(map[(int)(ptr->rander->pos_x - ptr->rander->dir_x * moveSpeed)][(int)(ptr->rander->pos_y)] == 0)
        ptr->rander->pos_x -= ptr->rander->dir_x * moveSpeed;
    if(map[(int)(ptr->rander->pos_x)][(int)(ptr->rander->pos_y - ptr->rander->dir_y * moveSpeed)] == 0)
        ptr->rander->pos_y -= ptr->rander->dir_y * moveSpeed;
    return (ptr);
}

t_pixel     *right(t_pixel *ptr)
{
    double moveSpeed;
    double rotSpeed;
    
    moveSpeed = 5.0 / 50;
    rotSpeed = 3.0/ 50;
    double oldDirX = ptr->rander->dir_x;
    ptr->rander->dir_x = ptr->rander->dir_x * cos(-rotSpeed) - ptr->rander->dir_y * sin(-rotSpeed);
    ptr->rander->dir_y = oldDirX * sin(-rotSpeed) + ptr->rander->dir_y * cos(-rotSpeed);
    double oldPlaneX = ptr->rander->plane_x;
    ptr->rander->plane_x = ptr->rander->plane_x * cos(-rotSpeed) - ptr->rander->plane_y * sin(-rotSpeed);
    ptr->rander->plane_y = oldPlaneX * sin(-rotSpeed) + ptr->rander->plane_y * cos(-rotSpeed);
    return (ptr);
}

t_pixel     *left(t_pixel *ptr)
{
    double moveSpeed;
    double rotSpeed;
    
    moveSpeed = 5.0 / 50;
    rotSpeed = 3.0/ 50;
    double oldDirX = ptr->rander->dir_x;
        ptr->rander->dir_x = ptr->rander->dir_x * cos(rotSpeed) - ptr->rander->dir_y * sin(rotSpeed);
        ptr->rander->dir_y = oldDirX * sin(rotSpeed) + ptr->rander->dir_y * cos(rotSpeed);
        double oldPlaneX = ptr->rander->plane_x;
        ptr->rander->plane_x = ptr->rander->plane_x * cos(rotSpeed) - ptr->rander->plane_y * sin(rotSpeed);
        ptr->rander->plane_y = oldPlaneX * sin(rotSpeed) + ptr->rander->plane_y * cos(rotSpeed);
    return (ptr);
}
