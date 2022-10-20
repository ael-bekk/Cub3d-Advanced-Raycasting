# Walk Through:

### ``Raycasting`` :
 ~First I implimented a normal `raycast` from player position (x, y) :
  ```
        x += decrease * cos(angl * M_PI / 180);
        y += decrease * sin(angl * M_PI / 180);
  ```
 ~Until i reach the wall and calculate the `distance` between start_pos(x0, y0) and end_pos(x1, y1) :
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
 
  ~Until now all was easy, and for more details about this part [Check This Documentation](https://github.com/Toufa7/Cub3D/blob/main/Readme.md?param1=value1?target=_blank).


### ``Advanced Raycasting`` :
  ~The challenge started when I came to this part, because I had already added some features that would take this part to another level of difficulty, especially these two (player jumping and crouching).
  
  ~First I have to take a position from the window and try to project it on the actual map, to do so:
  
  step 1- Get the angle of the point I are looking at by taking the cosine of the the player angle - the current ray angle
 
  step 2- Then I take another angle for the distance on the y direction, I do that by dividing the size of your ground tile times the y position - half the screen height  and diving that again by the calculated angle in step 1. Then I multiply the result by half the screen size
 
  step 3- After that I calculate the texture x position, by taking the cosine of the ray angle, multiplying it by the rseult of step 2 and adding the real player x position on the map to it (real means not the minimap value)
 
  step 4- Then I do the same for the texture y value, by taking the sine of the ray angle, multiplying it by step 2 and adding the real player y position
 
  step 5- Lastly I get the color for the current pixel from the texture, by taking step 4 % texture size and adding texture size * step 3 % texture size, basically what you should do with walls already
 
  step 6- I's the additional part and it was the hard part because i had to make the seen stable whenever the player jump or crouch then i moddified
the step 2
to be like this way : 

I changed `the half of the screen height` to be `the half of the screen height + the screen height * (wher the player eyes on the screen from (0->1) the diffolt is 0.5 the middle of the screen)`

### ``Textures or Aseets`` :
  ~First I used the flood fill algorithm to separate each room from another.
  
  ~I creat a 7 diffrent desine of rooms by taking the offset of differant parts and all was toking from one image :
  ![texture](https://github.com/ael-bekk/cube3d_advanced_raycasting/blob/main/img_srces/AnyConv.com__textures.png)
  
  exemple `Room A`:
  
  Floor===>`Start from x = 96px and y = 40 there 7 textures horizontaly and for each collomn ther are one texture`
  
  Wall====>`Start from x = 456 and y = 40 there 7 textures horizontaly and for each collomn ther are 2 textures`
  
  cillen===>`Start from x = 1392px and y = 40 there 4 textures horizontaly and for each collomn ther are 4 textures`
  
  ```
  //--------------------------- :::  room {A}  ::: ---------------------------//
     # define FLOOR2_START__X 96
     # define FLOOR2_START__Y 40
     # define FLOOR2_SIZE_Y 7
     # define FLOOR2_SIZE_X 1

     # define CART1_START__X 456
     # define CART1_START__Y 40
     # define CART1_SIZE_Y 7
     # define CART1_SIZE_X 2

     # define SUPPORT_START__X 1392
     # define SUPPORT_START__Y 40
     # define SUPPORT_SIZE_X 4
     # define SUPPORT_SIZE_Y 4
  ```
### ``Extra Features`` :

 .`LOOK UP-DOWN`:
 
 .`JUMP` :
 
 .`CROUCH` :
 
 .`ZOOM` :
 
 
