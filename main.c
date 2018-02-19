/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 12:23:59 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/02/19 12:38:17 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "wolf_v2.h"

int map[MAPWIDTH][MAPHEIGHT]=
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,4,4,0,4,4,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static t_rander *rander(void)
{
    t_rander *new;

    new = (t_rander *)malloc(sizeof(t_rander));
    bzero(new, sizeof(t_rander));
    new->pos_x = 22;
    new->pos_y = 11;
    new->dir_x = -1;
    new->dir_y = 0;
    new->plane_x = 0;
    new->plane_y = 0.66;
    return (new);
}

/*
** Initializes wolf 3S and allocate needed memory for the wolf ptr
*/

t_pixel     *init_wolf(int width, int height, char *title)
{
    t_pixel *new;

    new = (t_pixel *)malloc(sizeof(t_pixel));
    new->ptr = mlx_init();
    new->w = width;
    new->h = height;
    new->img = mlx_new_image(new->ptr, new->w, new->h);
    new->win = mlx_new_window(new->ptr, new->w, new->h, title);
    new->c_img = mlx_get_data_addr(new->img, &new->bpp, &new->sl, &new->endian);
    new->rander = rander();
    return (new);
}

/*
** Overwrites the address buff with floor and top colors to clear the screen
** in memory space...
*/

void        clear_screen(t_pixel **ptr)
{
    int i;
    int j;

    i = -1;
    (*ptr)->color = 0x00bfff;
    while (++i < (*ptr)->w)
    {
        j = -1;
        while (++j < ((*ptr)->h / 2))
            draw_pixel(ptr, i, j);
    }
    (*ptr)->color = 0x01A611;
    i = -1;
    while (++i < (*ptr)->w)
    {
        j = ((*ptr)->h / 2) - 1;
        while (++j < (*ptr)->h)
            draw_pixel(ptr, i, j);
    }
}

int         get_color(int map[MAPWIDTH][MAPHEIGHT], int x, int y)
{
    int color;
    
    if (map[x][y] == 1)
        color = 0xDC143C;
    else if (map[x][y] == 2)
        color = 0x7FFF00;
    else if (map[x][y] == 3)
        color = 0xBFFF00;
    else if (map[x][y] == 4)
        color = 0xFF00FF;
    else
        color = 0xFFFF00;
    return (color);
}

void        ft_draw(t_pixel *ptr)
{
    clear_screen(&ptr);
    for(int x = 0; x < ptr->w; x++)
    {
        //calculate ray position and direction
        ptr->rander->camera_x = 2 * x / (double)(ptr->w) - 1; //x-coordinate in camera space
        ptr->rander->raypos_x = ptr->rander->pos_x;
        ptr->rander->raypos_y = ptr->rander->pos_y;
        ptr->rander->raydir_x = ptr->rander->dir_x + ptr->rander->plane_x * ptr->rander->camera_x;
        ptr->rander->raydir_y = ptr->rander->dir_y + ptr->rander->plane_y * ptr->rander->camera_x;
        //which box of the map we're in
        ptr->rander->map_x = (int)ptr->rander->raypos_x;
        ptr->rander->map_y = (int)ptr->rander->raypos_y;
            
        //length of ray from current position to next x or y-side
        //double ptr->rander->sidedist_x;
        //double ptr->rander->sidedist_y;
            
        //length of ray from one x or y-side to next x or y-side
        ptr->rander->deltadist_x = sqrt(1 + (ptr->rander->raydir_y * ptr->rander->raydir_y) / (ptr->rander->raydir_x * ptr->rander->raydir_x));
        ptr->rander->deltadist_y = sqrt(1 + (ptr->rander->raydir_x * ptr->rander->raydir_x) / (ptr->rander->raydir_y * ptr->rander->raydir_y));
        //what direction to step in x or y-direction (either +1 or -1)
        ptr->rander->hit = 0; //was there a wall ptr->rander->hit?
        //was a NS or a EW wall ptr->rander->hit?
        //calculate step and initial sideDist
        if (ptr->rander->raydir_x < 0)
        {
            ptr->rander->step_x = -1;
            ptr->rander->sidedist_x = (ptr->rander->raypos_x - ptr->rander->map_x) * ptr->rander->deltadist_x;
        }
        else
        {
            ptr->rander->step_x = 1;
            ptr->rander->sidedist_x = (ptr->rander->map_x + 1.0 - ptr->rander->raypos_x) * ptr->rander->deltadist_x;
        }
        if (ptr->rander->raydir_y < 0)
        {
            ptr->rander->step_y = -1;
            ptr->rander->sidedist_y = (ptr->rander->raypos_y - ptr->rander->map_y) * ptr->rander->deltadist_y;
        }
        else
        {
            ptr->rander->step_y = 1;
            ptr->rander->sidedist_y = (ptr->rander->map_y + 1.0 - ptr->rander->raypos_y) * ptr->rander->deltadist_y;
        }
        //perform DDA
        while (ptr->rander->hit == 0)
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if (ptr->rander->sidedist_x < ptr->rander->sidedist_y)
            {
                ptr->rander->sidedist_x += ptr->rander->deltadist_x;
                ptr->rander->map_x += ptr->rander->step_x;
                ptr->rander->side = 0;
            }
            else
            {
                ptr->rander->sidedist_y += ptr->rander->deltadist_y;
                ptr->rander->map_y += ptr->rander->step_y;
                ptr->rander->side = 1;
            }
            //Check if ray has ptr->rander->hit a wall
            if (map[ptr->rander->map_x][ptr->rander->map_y] > 0) ptr->rander->hit = 1;
        }
        //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (ptr->rander->side == 0)
            ptr->rander->perpwalldist = (ptr->rander->map_x - ptr->rander->raypos_x + (1 - ptr->rander->step_x) / 2) / ptr->rander->raydir_x;
        else
        ptr->rander->perpwalldist = (ptr->rander->map_y - ptr->rander->raypos_y + (1 - ptr->rander->step_y) / 2) / ptr->rander->raydir_y;
        //Calculate height of line to draw on screen
        int lineHeight = (int)(ptr->h / ptr->rander->perpwalldist);
            
        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + ptr->h / 2;
        if(drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + ptr->h / 2;
        if(drawEnd >= ptr->h)drawEnd = ptr->h - 1;
        //choose wall color
        ptr->color = get_color(map, ptr->rander->map_x, ptr->rander->map_y);
        vertline(ptr, x, drawStart, drawEnd);
    }
    mlx_put_image_to_window(ptr->ptr, ptr->win, ptr->img, 0, 0);
}

int         exit_hook(void *data)
{
    t_pixel *ptr;

    ptr = (t_pixel *)data;
    mlx_destroy_image(ptr->ptr, ptr->img);
    mlx_destroy_window(ptr->ptr, ptr->win);
    free(ptr->ptr);
    free(ptr->rander);
    free(ptr);
    printf("Exited successfuly.\n");
    exit(0);
}

int  movement(int key, void *data)
{
    t_pixel *ptr;

	//printf("Received key: %d addr buff: %p\n", key, data);
    ptr = (t_pixel *)data;
	if (key == 53)
        exit_hook((void *)ptr);
    if (key == 126)
        ptr = forward(ptr, map);
    if (key == 125)
        ptr = backward(ptr, map);
    if (key == 124)
        ptr = right(ptr);
    if (key == 123)
        ptr = left(ptr);
    ft_draw(ptr);
    return (0);
}

int main(void)
{
    t_pixel *wolf;

    wolf = init_wolf(712, 484, "Wolf3d by ttshivhu");
    ft_draw(wolf);
    mlx_hook(wolf->win, 2, 0, movement, wolf);
    mlx_hook(wolf->win, 17, 0, exit_hook, wolf);
    mlx_loop(wolf->ptr);
}
