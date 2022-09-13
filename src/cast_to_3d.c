/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_to_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:09:00 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/09/13 17:54:09 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
} 

int get_weapon_color(int x, int y)
{
    t_img *p;

    p = &(data.guns);
    return (*(int *)(p->addr + (((int)(round((double)(y) * (256.0 / 200.0))) + 256 * (data.objects.w / 9)) * p->line_len + ((int)round((double)(x) * (256.0 / 200.0)) + 256 * (data.objects.w % 9)) * (p->bpp / 8))));
}

int get_gun_color(int x, int y)
{
    int w;
    int color;
    t_img *p;

    x = (double)x * (double)(500.0 / RES_X);
    y = (double)y * (double)(400.0 / RES_Y);
    w = data.objects.w;
    if (w == 9 || w == 4  || w == 5 || w == 2 || w == 17 || w == 19 || w == 13 || w == 15 || w == 20)
    {
        p = &(data.gun[w].gun[data.gun[w].frame]);
        color = (*(int *)(p->addr + (y * p->line_len + x * (p->bpp / 8))));
        if (color == 0x00ffff || (w == 17 && (color / 256) % 256 >= 150))
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
                img_pix_put(&data.img3, i + x, j + y, 0x000000);
            else
                img_pix_put(&data.img3, i + x, j + y, 0xadb5bd);
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
    t_img   *p;

    p = &(data.assets);
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
            return (*(int *)(p->addr + (((int)(y * 64.0 / 50.0) % 64 + FLOOR2_START__Y) * p->line_len + ((int)(x * 64.0 / 50.0) % 64 + FLOOR2_START__X) * (p->bpp / 8))));
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
                return (*(int *)(p->addr + (((int)(y * 64.0 / 50.0 + data.light) % 64 + 576) * p->line_len + ((int)(x * 64.0 / 50.0 + data.light) % 64 + 1680) * (p->bpp / 8))));
            else
                return (*(int *)(p->addr + (((int)(y * 64.0 / 50.0 + data.light) % 64 + 648) * p->line_len + ((int)(x * 64.0 / 50.0 + data.light) % 64 + 1680) * (p->bpp / 8))));
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

void     put_clob_tex_object(int j, int i) // global textures object
{
    int x1;

    x1 = X - 1500 + 500;
    if (j > 5 && j < 195 && i > (RES_X / 3) - 340   && i < (RES_X / 3) - 144   && (unsigned int)get_weapon_color(i - (RES_X / 3) + 341 , j - 6) != 0xff000000)
        img_pix_put(&data.img3, i, j , get_weapon_color(i - (RES_X / 3) + 341 , j - 6));
    else if (j > 205 && j <= 215 && i > (RES_X / 3) - 330 && i <= (RES_X / 3) - 30)
        img_pix_put(&data.img3, i, j , 0xaa0000 * (i - (RES_X / 3) + 330 <= 3 * data.objects.health) + 0x700000 * !(i - (RES_X / 3) + 330 <= 3 * data.objects.health));
    else if (j > 200 && j <= 220 && i > (RES_X / 3) - 335 && i <= (RES_X / 3) - 25)
        img_pix_put(&data.img3, i, j , 0x000);
    
    else if (data.objects.breath != 100 && j > 235 && j <= 245 && i > (RES_X / 3) - 330 && i <= (RES_X / 3) - 30)
        img_pix_put(&data.img3, i, j , 0xaaaaaa * (i - (RES_X / 3) + 330 <= 3 * data.objects.breath) + 0x444444 * !(i - (RES_X / 3) + 330 <= 3 * data.objects.breath));
    else if (data.objects.breath != 100 && j > 230 && j <= 250 && i > (RES_X / 3) - 335 && i <= (RES_X / 3) - 25)
        img_pix_put(&data.img3, i, j , 0x000);

    else if ((x1 - i  + 45)*(x1 - i  + 45) + (Y - j  + 40)*(Y - j  + 40) - 115 * 115 <= 0)
        img_pix_put(&data.img3, i, j, get_minimap_color(i + (RES_X / 3) * 2, j));
    else if ((x1 - i  + 45)*(x1 - i  + 45) + (Y - j  + 40)*(Y - j  + 40) - 120 * 120 <= 0)
        img_pix_put(&data.img3, i, j, 0xffffff);
    else
        img_pix_put(&data.img3, i, j , 0xff000000);
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
    j = forward;
    while ((int)(64 / data.door.rays[i] * (j - forward2)) < 64 && j < RES_Y)
    {
        if (i >= (RES_X / 3) * 2)
            put_clob_tex_object(j, i - (RES_X / 3) * 2);
        color = (unsigned int)get_gun_color(i + data.aim * 4, j - data.g_mv);
        if (j > data.g_mv && i < 1500  && color != 0xff000000 && color != 0x00ffff)
            img_pix_put(&data.img, i, j , color);
        else
        {
            color = set_design(3, i, (int)(64 / data.door.rays[i] * ((j - forward2))) % 64, data.design);
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
    unsigned int color;

    if (!data.rays[i])
        data.rays[i] = 1;
    data.rays[i] = round((50 * (RES_X / 2) / tan(30 * M_PI / 180)) / data.rays[i]);
    forward = (RES_Y / 2 - data.rays[i] * data.dir.ph) - data.c;
    forward2 = forward;
    if (forward < 0)
        forward = 0;
    if (forward > RES_Y)
        forward = RES_Y;
    j = 0;
    data.door.dor = 0;
    while (j < forward)
    {
        if (i >= (RES_X / 3) * 2)
            put_clob_tex_object(j, i - (RES_X / 3) * 2);
        color = (unsigned int)get_gun_color(i + data.aim * 4, j - data.g_mv);
        if (j > data.g_mv && i < 1500  && color != 0xff000000 && color != 0x00ffff)
            img_pix_put(&data.img, i, j, color);
        else
            img_pix_put(&data.img, i, j, get_color_22((RES_Y / 2 - j - data.c), -1));
        j++;
    }

    while ((int)(64 / data.rays[i] * (j - forward2)) < 64 && j < RES_Y)
    {
        if (i >= (RES_X / 3) * 2)
            put_clob_tex_object(j, i - (RES_X / 3) * 2);
        color = (unsigned int)get_gun_color(i + data.aim * 4, j - data.g_mv);
        if (j > data.g_mv && i < 1500  && color != 0xff000000 && color != 0x00ffff)
            img_pix_put(&data.img, i, j, color);
        else
            img_pix_put(&data.img, i, j, set_design(3, i, (int)(64 / data.rays[i] * (j - forward2)) % 64, data.design));
        j++;
    }
    
    while (j < RES_Y)
    {
        if (i >= (RES_X / 3) * 2)
            put_clob_tex_object(j, i - (RES_X / 3) * 2);
        color = (unsigned int)get_gun_color(i + data.aim * 4, j - data.g_mv);
        if (j > data.g_mv && i < 1500  && color != 0xff000000 && color != 0x00ffff)
            img_pix_put(&data.img, i, j, color);
        else
            img_pix_put(&data.img, i, j, get_color_22(((j - RES_Y / 2 + data.c)), 1));
        j++;
    }
    data.door.dor = 1;
    if (data.color[0])
        cast_to_3d_for_door(i);
    points_put(RES_X - 142 + 60, 55);
    points_put(RES_X - 142 + 60, 65);
}