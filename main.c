#include <math.h>
#include <stdio.h>
#include <mlx.h>

//place the example code below here:

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

void    *ptr;
void    *win;
void    *img;
char    *c_img;
int     bpp;
int     sl;
int     endian;

void			draw_pixel_img(int x, int y, int color)
{
	int i;

	i = ((int)x * 4) + ((int)y * sl);
	c_img[i] = color;
	c_img[++i] = color >> 8;
	c_img[++i] = color >> 16;
}

void    verLine(int x, int drawStart, int drawEnd, int color)
{
    while (drawStart < drawEnd)
    {
        draw_pixel_img(x, drawStart, color);
        drawStart++;
    }
}

double posX = 22, posY = 11;  //x and y start position
    double dirX = -2, dirY = 0; //initial direction vector
    double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
    
    double time = 0; //time of current frame
    double oldTime = 0; //time of previous frame
    
    int h = 512;
    int w = 800;

void    ft_draw(void)
{
    for (int x = 256; x < 512; x++)
    {
        for (int y = 0; y < 800; y++)
            draw_pixel_img(y, x, 0x01A611);
    }
    for (int x = 0; x < 256; x++)
    {
        for (int y = 0; y < 800; y++)
            draw_pixel_img(y, x, 0x87cefa);
    }

        for(int x = 0; x < w; x++)
        {
            //calculate ray position and direction
            double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
            double rayPosX = posX;
            double rayPosY = posY;
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;
            //which box of the map we're in
            int mapX = (int)rayPosX;
            int mapY = (int)rayPosY;
            
            //length of ray from current position to next x or y-side
            double sideDistX;
            double sideDistY;
            
            //length of ray from one x or y-side to next x or y-side
            double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
            double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
            double perpWallDist;
            
            //what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;
            
            int hit = 0; //was there a wall hit?
            int side; //was a NS or a EW wall hit?
            //calculate step and initial sideDist
            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (rayPosX - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
            }
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (rayPosY - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
            }
            //perform DDA
            while (hit == 0)
            {
                //jump to next map square, OR in x-direction, OR in y-direction
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                //Check if ray has hit a wall
                if (worldMap[mapX][mapY] > 0) hit = 1;
            }
            //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
            if (side == 0) perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
            else           perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;
            
            //Calculate height of line to draw on screen
            int lineHeight = (int)(h / perpWallDist);
            
            //calculate lowest and highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2 + h / 2;
            if(drawStart < 0)drawStart = 0;
            int drawEnd = lineHeight / 2 + h / 2;
            if(drawEnd >= h)drawEnd = h - 1;
            //choose wall color
            int  color;
            switch(worldMap[mapX][mapY])
            {
                case 1:  color = 0xDC143C;  break; //red
                case 2:  color = 0x7FFF00;  break; //green
                case 3:  color = 0x00BFFF;   break; //blue
                case 4:  color = 0xFF00FF;  break; //white
                default: color = 0xFFFF00; break; //yellow
            }
            //give x and y sides different brightness
            //if (side == 1) {color = color / 2;}
            
            //draw the pixels of the stripe as a vertical line
            verLine(x, drawStart, drawEnd, color);
        }
        mlx_put_image_to_window(ptr, win, img, 0, 0);
}

int  movement(int key)
{
    printf("key %d\n", key);
    //timing for input and FPS counter
        double frameTime = 0.10; //frameTime is the time this frame has taken, in seconds
        //speed modifiers
        double moveSpeed = frameTime * 2.0; //the constant value is in squares/second
        double rotSpeed = frameTime * 0.5; //the constant value is in radians/second
        //move forward if no wall in front of you
        if (key == 126)
        {
            if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == 0) posX += dirX * moveSpeed;
            if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
        }
        //move backwards if no wall behind you
        if (key == 125)
        {
            if(worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == 0) posX -= dirX * moveSpeed;
            if(worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
        }
        //rotate to the right
        if (key == 124)
        {
            //both camera direction and camera plane must be rotated
            double oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        }
        //rotate to the left
        if (key == 123)
        {
            //both camera direction and camera plane must be rotated
            double oldDirX = dirX;
            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        }
        ft_draw();
        return (0);
}

int main(int argc, char *argv[])
{
    ptr = mlx_init();
    img = mlx_new_image(ptr, w, h);
    win = mlx_new_window(ptr, w, h, "wolf3d by ttshivhu");
    c_img = mlx_get_data_addr(img, &bpp, &sl, &endian);
    ft_draw();
    mlx_key_hook (win, movement, NULL);
    mlx_loop(ptr);
}
