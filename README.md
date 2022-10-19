# Cub3D 👾

The goal of ``cub3d`` is to make *something* using raycasting (like [Wolfenstein 3D](https://fr.wikipedia.org/wiki/Wolfenstein_3D)).

### First of all:
  The more time I spend on the project, the much more I like it.

This project is written in ``c`` using ``mini-libx`` Library, 
This old library has a little builtin-funcs that's can make my project show on the graphics

# Preview
![Logo](https://github.com/ael-bekk/cube3d_advanced_raycasting/blob/main/img_srces/Blank%208%20Grids%20Collage.png)

# Walk Through:

### ``Raycasting`` :
 -First I implimented a normal `raycast` from player position (x, y) :
  ```
        x += decrease * cos(angl * M_PI / 180);
        y += decrease * sin(angl * M_PI / 180);
  ```
 -Until i reatch the wall and calculate the `distance` between start_pos(x0, y0) and end_pos(x1, y1) :
  ```
    dist = sqrt((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1));
  ```
 -Fixed the `fisheye` :
  ```
    dist *= cos(angl * M_PI / 180);
  ```
 
 -I use every distance to draw a line vertically using the `projection formula` :
 ```
  distance_between_player_and_projection_plan : (WIDTH_OF_THE_WIN / 2) / tan(30 * M_PI / 180).
  distance_between_player_and_wall (that we calculate using raycasting) : dist. 
  wall_hight = round((ACTUAL_WALL_HIGHT * (WIDTH_OF_THE_WIN / 2) / tan(30 * M_PI / 180)) / dist);
 ```

-After adding many things, I know that I have to optimize my code, Then I used a lock-up tables, for not calling the `cos-sin-tan` built-in funcs many times :
  ```
     void    change_angle()
    {
        double  r;
        double  angl;
        int     i;

        i = -1;
        r = -30; // r = - (FOV / 2) : in my case -(60 / 2)
        while (++i < WIDTH_OF_THE_WIN)
        {
            angl = data.player.angle + r;
            data.angles.r_cos[i] = cos(angl * M_PI / 180);
            data.angles.r_sin[i] = sin(angl * M_PI / 180);
            data.angles.r_res_cos[i] = cos(r * M_PI / 180);
            r += 0.04; // r += FOV / WIDTH_OF_THE_WIN : in my case (60 / 1500)
        }
        data.angles.pl_cos = cos(data.player.angle * M_PI / 180);
        data.angles.pl_sin = sin(data.player.angle * M_PI / 180);
        data.angles.pl_cos_plus_90 = cos((data.player.angle + 90) * M_PI / 180);
        data.angles.pl_sin_plus_90 = sin((data.player.angle + 90) * M_PI / 180);
        data.angles.cte_tan = tan(30 * M_PI / 180);
    }
  ```
  After that, I call the `cos-sin-tan` just in case the player's direction has changed to the left or right.

### ``Advanced Raycasting`` :


### ``Textures or Aseets`` :

### ``Extra Features`` :

