# Walk Through:

### ``Raycasting`` :
 ~First I implimented a normal `raycast` from player position (x, y) :
  ```
        x += decrease * cos(angl * M_PI / 180);
        y += decrease * sin(angl * M_PI / 180);
  ```
 ~Until i reatch the wall and calculate the `distance` between start_pos(x0, y0) and end_pos(x1, y1) :
  ```
    dist = sqrt((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1));
  ```
 ~Fixed the `fisheye` :
  ```
    dist *= cos(angl * M_PI / 180);
  ```
 
 ~I use every distance to draw a new vertical line using the `projection formula` :
 ```
  (WIDTH_OF_THE_WIN / 2) / tan(30 * M_PI / 180)     :: distance between player and projection plan.
  dist     :: distance between player and wall (wich calculated using raycasting).
  wall_hight = round((ACTUAL_WALL_HIGHT * (WIDTH_OF_THE_WIN / 2) / tan(30 * M_PI / 180)) / dist);
 ```

~After adding many things, I know that I have to optimize my code if I want to go further, Then I used a lock-up tables, for not calling the `cos-sin-tan` built-in funcs many times :
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
  Now, I'm calling the `cos-sin-tan` just in case the player's direction has been changed to the left or right.
 
  ~Until now all was easy.

### ``Advanced Raycasting`` :
  ~The challenge started when I came to this part, because I had already added some features that would take this part to another level of difficulty, especially these two (player jumping and crouching).
  
  ~First I have to take a position from the window and try to project it on the actual map, to do so:
  
  ~Get the angle of the point we are looking at by taking the cos of the the player angle - the current ray angle to get the x_dist between the player and the 
 
  

### ``Textures or Aseets`` :

### ``Extra Features`` :
