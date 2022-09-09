/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_to_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:09:00 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/09/09 15:56:15 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void    before()
{
    int i;
    int j;
    t_img img;

    img.mlx_img = mlx_new_image(data.mlx.mlx_ptr, 300, 300);
    img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
    i = RES_X - 300;
    while (++i < RES_X)
    {
        j = RES_Y - 300;
        while (++j < RES_Y)
            if (pow(X - i + 45, 2) + pow(Y - j + 40, 2) - 120 * 120 <= 0)
                img_pix_put(&img, i - RES_X + 300, j - RES_Y + 300, 0xff000000);
    }
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, img.mlx_img, RES_X - 300, RES_Y - 300);
}

int get_weapon_color(int x, int y)
{
    return (*(int *)(data.guns.addr + (((int)(round((double)(y) * (256.0 / 200.0))) + 256 * (data.objects.w / 9)) * data.guns.line_len + ((int)round((double)(x) * (256.0 / 200.0)) + 256 * (data.objects.w % 9)) * (data.guns.bpp / 8))));
}

int get_gun_color(int x, int y)
{
    int color;

    if (data.objects.w == 9 || data.objects.w == 4  || data.objects.w == 5 || data.objects.w == 2 || data.objects.w == 17 || data.objects.w == 19 || data.objects.w == 13 || data.objects.w == 15 || data.objects.w == 20)
    {
        color = (*(int *)(data.gun[data.objects.w].gun[data.gun[data.objects.w].frame].addr + (y * data.gun[data.objects.w].gun[data.gun[data.objects.w].frame].line_len + x * (data.gun[data.objects.w].gun[data.gun[data.objects.w].frame].bpp / 8))));
        if (color == 0x00ffff || ((color >> 8) % 256 >= 150 && data.objects.w == 17))
            return (0xff000000);
        return (color);
    }
    return (0xff000000);
}

void    points_put(int x, int y)
{
    int i;
    int j;

    i = -1;
    while (++i < 10)
    {
        j = -1;
        while (++j < 10)
        {
            if (i && i < 9 && j && j < 9)
                img_pix_put(&data.img, i + x, j + y, 0x000000);
            else
                img_pix_put(&data.img, i + x, j + y, 0xadb5bd);
        }
    }
}

int get_minimap_color(int x, int y)
{
    double c;
    double s;

    c = data.angles.pl_cos_plus_90;
    s = data.angles.pl_sin_plus_90;
    x -= 1345;
    y -= 935;
    
    double xnew = x * c - y * s + 1345;
    double ynew = x * s + y * c + 935;
    
    
    if (xnew < MX)
        x = (double)data.dir.x - fabs(MX - xnew) * 2 - 16.5;
    else
        x = (double)data.dir.x + fabs(MX - xnew) * 2 - 16.5;
    if (ynew < MY)
        y = (double)data.dir.y - fabs(MY - ynew) * 2 - 16.5;
    else
        y = (double)data.dir.y + fabs(MY - ynew) * 2 - 16.5;
    if (x <= 0 || y <= 0 || y / 50 >= data.h_map || x / 50 >= data.w_map[y / 50])
        return (0xff000000);
    switch (data.door.map[y / 50][x / 50])
    {
        case '1':
            return (*(int *)(data.assets.addr + (((int)(y * 64.0 / 50.0) % 64 + FLOOR2_START__Y) * data.assets.line_len + ((int)(x * 64.0 / 50.0) % 64 + FLOOR2_START__X) * (data.assets.bpp / 8))));
        case 'A':
            return (0x36454F);
        case 'B':
            return (0x231A1A);
        case 'C':
            return (0x645F5F);
        case 'D':
            return (0x393801);
        case 'E':
            if (data.map[(int)y / 50][(int)x / 50] == '0' && (data.map[(int)y / 50 - 1][(int)x / 50] != data.map[(int)y / 50 + 1][(int)x / 50] || data.map[(int)y / 50][(int)x / 50 - 1] != data.map[(int)y / 50][(int)x / 50 + 1]))
                return (*(int *)(data.assets.addr + (((int)(y * 64.0 / 50.0 + data.light) % 64 + 576) * data.assets.line_len + ((int)(x * 64.0 / 50.0 + data.light) % 64 + 1680) * (data.assets.bpp / 8))));
            else
                return (*(int *)(data.assets.addr + (((int)(y * 64.0 / 50.0 + data.light) % 64 + 648) * data.assets.line_len + ((int)(x * 64.0 / 50.0 + data.light) % 64 + 1680) * (data.assets.bpp / 8))));
        case 'F':
            return (0xB2BEB5);
        case 'G':
            return (0xE5E4E2);
        default:
            return (0xff000000);
    }
}
int light;

int get_color_22(double dy, int side)
{
	double  angle;
	double	dy_angle;
	double	tx;
	double	ty;

	angle = data.angles.r_res_cos[data.indx];
	dy_angle = (540 + 1080 * (0.5 - data.dir.ph) * side) * (((60) / dy) / angle);
	tx = (double)data.dir.x + 17 + data.angles.r_cos[data.indx] * dy_angle;
	ty = (double)data.dir.y + 17 + data.angles.r_sin[data.indx] * dy_angle;

    if (data.map[(int)ty / 50][(int)tx / 50] != 'H' && data.door.map[(int)ty / 50][(int)tx / 50] == 'G' && side == -1)
    {
        dy_angle = (6540 + 1080 * (0.5 - data.dir.ph) * side) * (((60) / dy) / angle);
        tx = (double)data.dir.x + 17 + data.angles.r_cos[data.indx] * dy_angle;
        ty = (double)data.dir.y + 17 + data.angles.r_sin[data.indx] * dy_angle;
        data.door.c = 0;
        return (set_design(side, tx, ty, 'G'));
    }
    else
        data.door.c = 1;
    return (set_design(side, tx, ty, data.door.map[(int)ty / 50][(int)tx / 50]));
}

void    cast_to_3d_for_door(int i)
{
    int j;
    int forward;
    int forward2;
    unsigned int color;

    if (!data.door.rays[i])
        data.door.rays[i] = 1;
    data.door.rays[i] = round((50 * (RES_X / 2) / tan(30 * M_PI / 180)) / data.door.rays[i]);
    forward = (RES_Y / 2 - data.door.rays[i] * data.dir.ph)  - data.c;
    forward2 = forward;
    if (forward < 0)
        forward = 0;
    if (forward > RES_Y)
        forward = RES_Y;
    j = 0;
    j = forward;
    while ((int)(64 / data.door.rays[i] * (j - forward2)) < 64 && j < RES_Y)
    {
        if (data.mode == GAME && j > 5 && j < 195 && i > RES_X - 340 && i < RES_X - 144 && (unsigned int)get_weapon_color(i - RES_X + 341, j - 6) != 0xff000000)
            img_pix_put(&data.img, i, j , get_weapon_color(i - RES_X + 341, j - 6));
        else if (data.mode == GAME && j > 205 && j <= 215 && i > RES_X - 330 && i <= RES_X - 30)
            img_pix_put(&data.img, i, j , 0xaa0000 * (i - RES_X + 330 <= 3 * data.objects.health) + 0x700000 * !(i - RES_X + 330 <= 3 * data.objects.health));
        else if (data.mode == GAME && j > 200 && j <= 220 && i > RES_X - 335 && i <= RES_X - 25)
            img_pix_put(&data.img, i, j , 0x000);
        
        else if (data.mode == GAME && data.objects.breath != 100 && j > 235 && j <= 245 && i > RES_X - 330 && i <= RES_X - 30)
            img_pix_put(&data.img, i, j , 0xaaaaaa * (i - RES_X + 330 <= 3 * data.objects.breath) + 0x444444 * !(i - RES_X + 330 <= 3 * data.objects.breath));
        else if (data.mode == GAME && data.objects.breath != 100 && j > 230 && j <= 250 && i > RES_X - 335 && i <= RES_X - 25)
            img_pix_put(&data.img, i, j , 0x000);

        else if (data.mode == GAME && (X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 115 * 115 <= 0)
            img_pix_put(&data.img, i, j, get_minimap_color(i, j));
        else if (data.mode == GAME && (X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 120 * 120 <= 0)
            img_pix_put(&data.img, i, j, 0xffffff);
        else if (data.mode == GAME && j > data.g_mv && i < 1500 - data.aim * 4 && (unsigned int)get_gun_color(i + data.aim * 4, j - data.g_mv) != 0xff000000 && (unsigned int)get_gun_color(i + data.aim * 4, j - data.g_mv) != 0x00ffff)
            img_pix_put(&data.img, i, j , get_gun_color(i + data.aim * 4, j - data.g_mv));
        else
        {
            color = set_design(3, i, (int)(64 / data.door.rays[i] * (j - forward2)) % 64, data.design);
            if (color < 0xff000000)
                img_pix_put(&data.img, i, j, color);
        }
        j++;
    }
}

void    cast_to_3d(int i)
{
    int j;
    int forward;
    int forward2;

    if (!data.rays[i])
        data.rays[i] = 1;
    data.rays[i] = round((50 * (RES_X / 2) / tan(30 * M_PI / 180)) / data.rays[i]);
    forward = (RES_Y / 2 - data.rays[i] * data.dir.ph)  - data.c;
    forward2 = forward;
    if (forward < 0)
        forward = 0;
    if (forward > RES_Y)
        forward = RES_Y;
    j = 0;
    data.door.dor = 0;
    while (j < forward)
    {
        if (data.mode == GAME && j > 5 && j < 195 && i > RES_X - 340 && i < RES_X - 144 && (unsigned int)get_weapon_color(i - RES_X + 341, j - 6) != 0xff000000)
            img_pix_put(&data.img, i, j , get_weapon_color(i - RES_X + 341, j - 6));
        else if (data.mode == GAME && j > 205 && j <= 215 && i > RES_X - 330 && i <= RES_X - 30)
            img_pix_put(&data.img, i, j , 0xaa0000 * (i - RES_X + 330 <= 3 * data.objects.health) + 0x700000 * !(i - RES_X + 330 <= 3 * data.objects.health));
        else if (data.mode == GAME && j > 200 && j <= 220 && i > RES_X - 335 && i <= RES_X - 25)
            img_pix_put(&data.img, i, j , 0x000);
            
        else if (data.mode == GAME && data.objects.breath != 100 && j > 235 && j <= 245 && i > RES_X - 330 && i <= RES_X - 30)
            img_pix_put(&data.img, i, j , 0xaaaaaa * (i - RES_X + 330 <= 3 * data.objects.breath) + 0x444444 * !(i - RES_X + 330 <= 3 * data.objects.breath));
        else if (data.mode == GAME && data.objects.breath != 100 && j > 230 && j <= 250 && i > RES_X - 335 && i <= RES_X - 25)
            img_pix_put(&data.img, i, j , 0x000);

        else if (data.mode == GAME && (X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 115 * 115 <= 0)
            img_pix_put(&data.img, i, j, get_minimap_color(i, j));
        else if (data.mode == GAME && (X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 120 * 120 <= 0)
            img_pix_put(&data.img, i, j, 0xffffff);
        else if (data.mode == GAME && j > data.g_mv && i < 1500 - data.aim * 4 && (unsigned int)get_gun_color(i + data.aim * 4, j - data.g_mv) != 0xff000000 && (unsigned int)get_gun_color(i + data.aim * 4, j - data.g_mv) != 0x00ffff)
            img_pix_put(&data.img, i, j , get_gun_color(i + data.aim * 4, j - data.g_mv));
        else
            img_pix_put(&data.img, i, j, get_color_22(RES_Y / 2 - j - data.c, -1));
        j++;
    }

    while ((int)(64 / data.rays[i] * (j - forward2)) < 64 && j < RES_Y)
    {
        if (data.mode == GAME && j > 5 && j < 195 && i > RES_X - 340 && i < RES_X - 144 && (unsigned int)get_weapon_color(i - RES_X + 341, j - 6) != 0xff000000)
            img_pix_put(&data.img, i, j , get_weapon_color(i - RES_X + 341, j - 6));
        else if (data.mode == GAME && j > 205 && j <= 215 && i > RES_X - 330 && i <= RES_X - 30)
            img_pix_put(&data.img, i, j , 0xaa0000 * (i - RES_X + 330 <= 3 * data.objects.health) + 0x700000 * !(i - RES_X + 330 <= 3 * data.objects.health));
        else if (data.mode == GAME && j > 200 && j <= 220 && i > RES_X - 335 && i <= RES_X - 25)
            img_pix_put(&data.img, i, j , 0x000);
        
        else if (data.mode == GAME && data.objects.breath != 100 && j > 235 && j <= 245 && i > RES_X - 330 && i <= RES_X - 30)
            img_pix_put(&data.img, i, j , 0xaaaaaa * (i - RES_X + 330 <= 3 * data.objects.breath) + 0x444444 * !(i - RES_X + 330 <= 3 * data.objects.breath));
        else if (data.mode == GAME && data.objects.breath != 100 && j > 230 && j <= 250 && i > RES_X - 335 && i <= RES_X - 25)
            img_pix_put(&data.img, i, j , 0x000);

        else if (data.mode == GAME && (X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 115 * 115 <= 0)
            img_pix_put(&data.img, i, j, get_minimap_color(i, j));
        else if (data.mode == GAME && (X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 120 * 120 <= 0)
            img_pix_put(&data.img, i, j, 0xffffff);
        else if (data.mode == GAME && j > data.g_mv && i < 1500 - data.aim * 4 && (unsigned int)get_gun_color(i + data.aim * 4, j - data.g_mv) != 0xff000000 && (unsigned int)get_gun_color(i + data.aim * 4, j - data.g_mv) != 0x00ffff)
            img_pix_put(&data.img, i, j , get_gun_color(i + data.aim * 4, j - data.g_mv));
        else
            img_pix_put(&data.img, i, j, set_design(3, i, (int)(64 / data.rays[i] * (j - forward2)) % 64, data.design));
        j++;
    }
    
    while (j < RES_Y)
    {
        if (data.mode == GAME && j > 5 && j < 195 && i > RES_X - 340 && i < RES_X - 144 && (unsigned int)get_weapon_color(i - RES_X + 341, j - 6) != 0xff000000)
            img_pix_put(&data.img, i, j , get_weapon_color(i - RES_X + 341, j - 6));
        else if (data.mode == GAME && j > 205 && j <= 215 && i > RES_X - 330 && i <= RES_X - 30)
            img_pix_put(&data.img, i, j , 0xaa0000 * (i - RES_X + 330 <= 3 * data.objects.health) + 0x700000 * !(i - RES_X + 330 <= 3 * data.objects.health));
        else if (data.mode == GAME && j > 200 && j <= 220 && i > RES_X - 335 && i <= RES_X - 25)
            img_pix_put(&data.img, i, j , 0x000);
            
        else if (data.mode == GAME && data.objects.breath != 100 && j > 235 && j <= 245 && i > RES_X - 330 && i <= RES_X - 30)
            img_pix_put(&data.img, i, j , 0xaaaaaa * (i - RES_X + 330 <= 3 * data.objects.breath) + 0x444444 * !(i - RES_X + 330 <= 3 * data.objects.breath));
        else if (data.mode == GAME && data.objects.breath != 100 && j > 230 && j <= 250 && i > RES_X - 335 && i <= RES_X - 25)
            img_pix_put(&data.img, i, j , 0x000);
            
        else if (data.mode == GAME && (X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 115 * 115 <= 0)
            img_pix_put(&data.img, i, j , get_minimap_color(i, j));
        else if (data.mode == GAME && (X - i + 45)*(X - i + 45) + (Y - j  + 40)*(Y - j + 40) - 120 * 120 <= 0)
            img_pix_put(&data.img, i, j , 0xffffff);
        else if (data.mode == GAME && j > data.g_mv && i < 1500 - data.aim * 4 && (unsigned int)get_gun_color(i + data.aim * 4, j - data.g_mv) != 0xff000000 && (unsigned int)get_gun_color(i + data.aim * 4, j - data.g_mv) != 0x00ffff)
            img_pix_put(&data.img, i, j , get_gun_color(i + data.aim * 4, j - data.g_mv));
        else
            img_pix_put(&data.img, i, j, get_color_22(j - RES_Y / 2 + data.c, 1));
        j++;
    }
    data.door.dor = 1;
    if (data.color[data.indx][0])
        cast_to_3d_for_door(i);
    points_put(RES_X - 142 + 60, 55);
    points_put(RES_X - 142 + 60, 65);
}