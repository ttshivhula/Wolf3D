#include "wolf3d.h"

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
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
    new->dir_x = -2;
    new->dir_y = 0;
    new->plane_x = 0;
    new->plane_y = 0.66;
    return (new);
}

t_pixel     *init_wolf(int width, int height)
{
    t_pixel *new;

    new = (t_pixel *)malloc(sizeof(t_pixel));
    new->ptr = mlx_init();
    new->w = width;
    new->h = height;
    new->img = mlx_new_image(new->ptr, new->w, new->h);
    new->win = mlx_new_window(new->ptr, new->w, new->h, "wolf3d");
    new->c_img = mlx_get_data_addr(new->img, &new->bpp, &new->sl, &new->endian);
    new->rander = rander();
    return (new);
}

void    clear_screen(t_pixel **ptr)
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

void    ft_draw(t_pixel *ptr)
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
                if (worldMap[ptr->rander->map_x][ptr->rander->map_y] > 0) ptr->rander->hit = 1;
            }
            //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
            if (ptr->rander->side == 0) ptr->rander->perpwalldist = (ptr->rander->map_x - ptr->rander->raypos_x + (1 - ptr->rander->step_x) / 2) / ptr->rander->raydir_x;
            else           ptr->rander->perpwalldist = (ptr->rander->map_y - ptr->rander->raypos_y + (1 - ptr->rander->step_y) / 2) / ptr->rander->raydir_y;
            
            //Calculate height of line to draw on screen
            int lineHeight = (int)(ptr->h / ptr->rander->perpwalldist);
            
            //calculate lowest and highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2 + ptr->h / 2;
            if(drawStart < 0)drawStart = 0;
            int drawEnd = lineHeight / 2 + ptr->h / 2;
            if(drawEnd >= ptr->h)drawEnd = ptr->h - 1;
            //choose wall color
            switch(worldMap[ptr->rander->map_x][ptr->rander->map_y])
            {
                case 1:  ptr->color = 0xDC143C;  break; //red
                case 2:  ptr->color = 0x7FFF00;  break; //green
                case 3:  ptr->color = 0x00BFFF;   break; //blue
                case 4:  ptr->color = 0xFF00FF;  break; //wptr->rander->hite
                default: ptr->color = 0xFFFF00; break; //yellow
            }
            //give x and y sides different brightness
            if (ptr->rander->side == 1) {ptr->color = ptr->color / 2;}
            vertline(ptr, x, drawStart, drawEnd);
        }
        mlx_put_image_to_window(ptr->ptr, ptr->win, ptr->img, 0, 0);
}

int  movement(int key, void *data)
{
    t_pixel *ptr;

    ptr = (t_pixel *)data;
	if (key == 53)
	{
		exit(1);
	}
    //printf("key %d\n", key);
    //timing for input and FPS counter
        double frameTime = 0.10; //frameTime is the time this frame has taken, in seconds
        //speed modifiers
        double moveSpeed = frameTime * 2.0; //the constant value is in squares/second
        double rotSpeed = frameTime * 0.5; //the constant value is in radians/second
        //move forward if no wall in front of you
        if (key == 126)
        {
            if(worldMap[(int)(ptr->rander->pos_x + ptr->rander->dir_x * moveSpeed)][(int)(ptr->rander->pos_y)] == 0)
                ptr->rander->pos_x += ptr->rander->dir_x * moveSpeed;
            if(worldMap[(int)(ptr->rander->pos_x)][(int)(ptr->rander->pos_y + ptr->rander->dir_y * moveSpeed)] == 0)
                ptr->rander->pos_y += ptr->rander->dir_x * moveSpeed;
        }
        //move backwards if no wall behind you
        if (key == 125)
        {
            if(worldMap[(int)(ptr->rander->pos_x - ptr->rander->dir_x * moveSpeed)][(int)(ptr->rander->pos_y)] == 0)
                ptr->rander->pos_x -= ptr->rander->dir_x * moveSpeed;
            if(worldMap[(int)(ptr->rander->pos_x)][(int)(ptr->rander->pos_y - ptr->rander->dir_y * moveSpeed)] == 0)
                ptr->rander->pos_y -= ptr->rander->dir_y * moveSpeed;
        }
        //rotate to the right
        if (key == 124)
        {
            //both camera direction and camera plane must be rotated
            double oldDirX = ptr->rander->dir_x;
            ptr->rander->dir_x = ptr->rander->dir_x * cos(-rotSpeed) - ptr->rander->dir_y * sin(-rotSpeed);
            ptr->rander->dir_y = oldDirX * sin(-rotSpeed) + ptr->rander->dir_y * cos(-rotSpeed);
            double oldPlaneX = ptr->rander->plane_x;
            ptr->rander->plane_x = ptr->rander->plane_x * cos(-rotSpeed) - ptr->rander->plane_y * sin(-rotSpeed);
            ptr->rander->plane_y = oldPlaneX * sin(-rotSpeed) + ptr->rander->plane_y * cos(-rotSpeed);
        }
        //rotate to the left
        if (key == 123)
        {
            //both camera direction and camera plane must be rotated
            double oldDirX = ptr->rander->dir_x;
            ptr->rander->dir_x = ptr->rander->dir_x * cos(rotSpeed) - ptr->rander->dir_y * sin(rotSpeed);
            ptr->rander->dir_y = oldDirX * sin(rotSpeed) + ptr->rander->dir_y * cos(rotSpeed);
            double oldPlaneX = ptr->rander->plane_x;
            ptr->rander->plane_x = ptr->rander->plane_x * cos(rotSpeed) - ptr->rander->plane_y * sin(rotSpeed);
            ptr->rander->plane_y = oldPlaneX * sin(rotSpeed) + ptr->rander->plane_y * cos(rotSpeed);
        }
        ft_draw(ptr);
        return (0);
}

int main(int argc, char *argv[])
{
    t_pixel *wolf;

    wolf = init_wolf(512, 384);
    ft_draw(wolf);
    mlx_key_hook (wolf->win, movement, wolf);
    mlx_loop(wolf->ptr);
}
