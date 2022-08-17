/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_to_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:09:00 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/08/17 18:33:20 by ael-bekk         ###   ########.fr       */
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

int get_color(int x, int y)
{
    y = (int)round((double)y * (64.0 / 500.0)) % 64;
    if (!data.color[x][0])
        return (*(int *)(data.n.addr + (y * data.n.line_len + data.color[x][1] * (data.n.bpp / 8))));
    if (data.color[x][0] == 1)
        return (*(int *)(data.w.addr + (y * data.w.line_len + data.color[x][1] * (data.w.bpp / 8))));
    if (data.color[x][0] == 2)
        return (*(int *)(data.s.addr + (y * data.s.line_len + data.color[x][1] * (data.s.bpp / 8))));
    if (data.color[x][0] == 3)
        return (*(int *)(data.e.addr + (y * data.e.line_len + data.color[x][1] * (data.e.bpp / 8))));
    return (0);
}

int get_weapon_color(int x, int y)
{
    return (*(int *)(data.objects.weapon[data.objects.w].addr + (y * data.objects.weapon[data.objects.w].line_len + x * (data.objects.weapon[data.objects.w].bpp / 8))));
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

    c = cos((data.dir.angle + 90) * M_PI / 180);
    s = sin((data.dir.angle + 90) * M_PI / 180);
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
    if (x <= 0 || y <= 0 || y / 50 >= ft_strlen2(data.map) || x / 50 >= ft_strlen(data.map[y / 50]))
        return (0);
    if (data.map[y / 50][x / 50] == '1')
        return (*(int *)(data.mlx.wall.addr + ((y % 50) * data.mlx.wall.line_len + (x % 50) * (data.mlx.wall.bpp / 8))));
    return (0);
}

int get_color_22(double dy, int side)
{
	double  angle;
	double	dy_angle;
	double	tx;
	double	ty;

	angle = cos((data.g) * M_PI / 180);
	dy_angle = (540 + 1080 * (0.5 - data.dir.ph) * side) * (((60) / dy) / angle);
    // if (side == -1)
    //     dy_angle = (540 + 1080 * (0.5 - data.dir.ph) * side + 1000) * (((60) / dy) / angle);
	tx = (double)data.dir.x + 17 + cos((data.dir.angle + data.g) * M_PI / 180) * dy_angle;
	ty = (double)data.dir.y + 17 + sin((data.dir.angle + data.g) * M_PI / 180) * dy_angle;

    if (side != -1)
        return (*(int *)(data.img_f.addr + (((int)(ty * 10.0 * (64.0 / 500.0)) % 64)  * data.img_f.line_len + ((int)(tx * 10.0 * (64.0 / 500.0)) % 64) * (data.img_f.bpp / 8))));
	else
        return (*(int *)(data.img_c.addr + (((int)(ty * 10.0 * (64.0 / 500.0)) % 64) * data.img_c.line_len + ((int)(tx * 10.0 * (64.0 / 500.0)) % 64) * (data.img_c.bpp / 8))));
}

void    cast_to_3d(int i, double *cord)
{
    int j;
    int forward;
    int forward1;
    int forward2;

    (void) cord[0];
    if (!data.rays[i])
        data.rays[i] = 1;
    data.rays[i] = round((60 * RES_Y) / data.rays[i]);
    forward = (RES_Y / 2 - data.rays[i] * data.dir.ph)  - data.c;
    forward1 = (RES_Y / 2 - data.rays[i] * (1.0 - data.dir.ph)) - data.c;
    int g = (RES_Y - data.rays[i]) / 2;
    int m = (RES_Y - data.rays[i]) / 2 + data.c;
    forward2 = forward;
    if (forward < 0)
        forward = 0;
    if (forward > RES_Y)
        forward = RES_Y;
    g *= (g >= 0);
    m *= (m >= 0);
    j = 0;
    while (j < forward)
    {
        if (j > 5 && j < 195 && i > RES_X - 340 && i < RES_X - 144 && (unsigned int)get_weapon_color(i - RES_X + 341, j - 6) != 0xff000000)
            img_pix_put(&data.img, i, j , get_weapon_color(i - RES_X + 341, j - 6));
        else if (j > 205 && j <= 215 && i > RES_X - 330 && i <= RES_X - 30)
            img_pix_put(&data.img, i, j , 0xaa0000 * (i - RES_X + 330 <= 3 * data.objects.health) + 0x700000 * !(i - RES_X + 330 <= 3 * data.objects.health));
        else if (j > 200 && j <= 220 && i > RES_X - 335 && i <= RES_X - 25)
            img_pix_put(&data.img, i, j , 0x000);
        else if (data.mode == GAME && (X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 115 * 115 <= 0)
            img_pix_put(&data.img, i, j, get_minimap_color(i, j));
        else if (data.mode == GAME && (X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 120 * 120 <= 0)
            img_pix_put(&data.img, i, j, 0xffffff);
        else
            img_pix_put(&data.img, i, j, get_color_22(RES_Y / 2 - j - data.c, -1) + ((j / 5)  << 24));
        j++;
    }

    while ((int)(500 / data.rays[i] * (j - forward2)) < 500 && j < RES_Y)
    {
        if (j > 5 && j < 195 && i > RES_X - 340 && i < RES_X - 144 && (unsigned int)get_weapon_color(i - RES_X + 341, j - 6) != 0xff000000)
            img_pix_put(&data.img, i, j , get_weapon_color(i - RES_X + 341, j - 6));
        else if (j > 205 && j <= 215 && i > RES_X - 330 && i <= RES_X - 30)
            img_pix_put(&data.img, i, j , 0xaa0000 * (i - RES_X + 330 <= 3 * data.objects.health) + 0x700000 * !(i - RES_X + 330 <= 3 * data.objects.health));
        else if (j > 200 && j <= 220 && i > RES_X - 335 && i <= RES_X - 25)
            img_pix_put(&data.img, i, j , 0x000);
        else if (data.mode == GAME && (X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 115 * 115 <= 0)
            img_pix_put(&data.img, i, j, get_minimap_color(i, j));
        else if (data.mode == GAME && (X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 120 * 120 <= 0)
            img_pix_put(&data.img, i, j, 0xffffff);
        else
            img_pix_put(&data.img, i, j, get_color(i, (int)(500 / data.rays[i] * (j - forward2)) % 500) + ((g / 4) << 24));
        j++;
    }
    while (j < RES_Y)
    {
        if (j > 5 && j < 195 && i > RES_X - 340 && i < RES_X - 144 && (unsigned int)get_weapon_color(i - RES_X + 341, j - 6) != 0xff000000)
            img_pix_put(&data.img, i, j , get_weapon_color(i - RES_X + 341, j - 6));
        else if (j > 205 && j <= 215 && i > RES_X - 330 && i <= RES_X - 30)
            img_pix_put(&data.img, i, j , 0xaa0000 * (i - RES_X + 330 <= 3 * data.objects.health) + 0x700000 * !(i - RES_X + 330 <= 3 * data.objects.health));
        else if (j > 200 && j <= 220 && i > RES_X - 335 && i <= RES_X - 25)
            img_pix_put(&data.img, i, j , 0x000);
        else if (data.mode == GAME && (X - i + 45)*(X - i + 45) + (Y - j + 40)*(Y - j + 40) - 115 * 115 <= 0)
            img_pix_put(&data.img, i, j , get_minimap_color(i, j));
        else if (data.mode == GAME && (X - i + 45)*(X - i + 45) + (Y - j  + 40)*(Y - j + 40) - 120 * 120 <= 0)
            img_pix_put(&data.img, i, j , 0xffffff);
        else
            img_pix_put(&data.img, i, j, get_color_22(j - RES_Y / 2 + data.c, 1));
        j++;
    }
    points_put(RES_X - 142 + 60, 55);
    points_put(RES_X - 142 + 60, 65);
}