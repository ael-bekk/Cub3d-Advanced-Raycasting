/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:24:38 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/09/20 17:46:21 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    mouse_move_intro(int x, int y)
{

    if (x >= (RES_X - 498) / 2 + 35 && y >= (RES_Y + 280) / 2 + 70 && x < (RES_X + 498) / 2 + 35 && y < (RES_Y + 280) / 2 + 70 + 50)
        data.mouse.hover = 1;
    else
        data.mouse.hover = 0;
}

void    mouse_move_setting(int x, int y)
{
    int p;
    int i;

    p = -1;
    if (data.mode == SETTING)
    {
        if (!data.mouse.on_hov[0] && x >= (RES_X - data.intro.start.x) / 2 && y >= (RES_Y - data.intro.start.y) / 2 - RES_Y / 6 && x < (RES_X + data.intro.start.x) / 2 && y < (RES_Y + data.intro.start.y) / 2 - RES_Y / 6)
            data.sound.hover = 1,
            p = 0;
        if (!data.mouse.on_hov[1] && x >= (RES_X - data.intro.sett.x) / 2 && y >= (RES_Y - data.intro.sett.y) / 2 - RES_Y / 12 && x < (RES_X + data.intro.sett.x) / 2 && y < (RES_Y + data.intro.sett.y) / 2 - RES_Y / 12)
            data.sound.hover = 1,
            p = 1;
        if (!data.mouse.on_hov[2] && x >= (RES_X - data.intro.exit.x) / 2 && y >= (RES_Y - data.intro.exit.y) / 2 && x < (RES_X + data.intro.exit.x) / 2 && y < (RES_Y + data.intro.exit.y) / 2)
            data.sound.hover = 1,
            p = 2;
    }
    if (data.mode == SETTING2)
    {
        if (!data.mouse.on_hov[3] && x >= (RES_X - data.intro.cont.x) / 2 && y >= (RES_Y - data.intro.cont.y) / 2 - RES_Y / 6 && x < (RES_X + data.intro.cont.x) / 2 && y < (RES_Y + data.intro.cont.y) / 2 - RES_Y / 6)
            data.sound.hover = 1,
            p = 3;
        if (!data.mouse.on_hov[4] && x >= (RES_X - data.intro.restart.x) / 2 && y >= (RES_Y - data.intro.restart.y) / 2 - RES_Y / 12 && x < (RES_X + data.intro.restart.x) / 2 && y < (RES_Y + data.intro.restart.y) / 2 - RES_Y / 12)
            data.sound.hover = 1,
            p = 4;
        if (!data.mouse.on_hov[1] && x >= (RES_X - data.intro.sett.x) / 2 && y >= (RES_Y - data.intro.sett.y) / 2 && x < (RES_X + data.intro.sett.x) / 2 && y < (RES_Y + data.intro.sett.y) / 2)
            data.sound.hover = 1,
            p = 1;
        if (!data.mouse.on_hov[2] && x >= (RES_X - data.intro.exit.x) / 2 && y >= (RES_Y - data.intro.exit.y) / 2 + RES_Y / 12 && x < (RES_X + data.intro.exit.x) / 2 && y < (RES_Y + data.intro.exit.y) / 2 + RES_Y / 12)
            data.sound.hover = 1,
            p = 2;
    }
    if (data.mode == S_CONTROL)
    {
        if (x >= RES_X / 2 - 225 && y >= RES_Y - 100 && x < RES_X / 2 - 75 && y < RES_Y - 40)
            data.sound.hover = !data.mouse.on_hov[5],
            p = 5;
        else if (x >= RES_X / 2 + 75 && y >= RES_Y - 100 && x < RES_X / 2 + 225 && y < RES_Y - 40)
            data.sound.hover = !data.mouse.on_hov[6],
            p = 6;
        else
            p = 0;
    }
    if (p != -1)
    {
        data.mouse.on_hov[p] = 1;
        i = 0;
        while (++i < 7)
            data.mouse.on_hov[(p + i) % 7] = 0;
    }
    data.mouse.x = x;
    data.mouse.y = y;
}

void    mouse_move_control(int x, int y)
{
    int i;
    int inc_y;
    int pos;

    i = 5;
    inc_y = 280;
    pos = 3 * (x > 390 && x < 436 && y > 120 && y < 160)
            + 4 * (x > 564 && x < 610 && y > 120 && y < 160);
    while (i < 16)
    {
        pos += i++ * (x - 100 > 0 && x - 100 < 500 && y - inc_y > -25 && y - inc_y < 65);
        if (i < 16)
            pos += i++ * (x - 800 > 0 && x - 800 < 500 && y - inc_y > -25 && y - inc_y < 65);
        inc_y += 120;
    }
    if (pos && !data.intro.on_hov[pos])
        data.sound.hover = 1,
        data.intro.on_hov[pos] = 1;
    i = 1;
    while (++i < 15)
        data.intro.on_hov[(pos + i) % 16] = 0;
    if (data.intro.vol_click)
    {
        data.intro.volume = x - 1100 + 12;
        if (data.intro.volume > 200)
            data.intro.volume = 200;
        if (data.intro.volume < 0)
            data.intro.volume = 0;
        paint_color(&data.intro.vol[0], 0xB2BEB5, 200, 10);
        paint_color(&data.intro.vol[0], 0xff0000, data.intro.volume, 10);
    }
    if (data.intro.lgt_click)
    {
        data.intro.light = x - 1100 + 12;
        if (data.intro.light > 200)
            data.intro.light = 200;
        if (data.intro.light < 0)
            data.intro.light = 0;
        paint_color(&data.intro.lgt[0], 0xB2BEB5, 200, 10);
        paint_color(&data.intro.lgt[0], 0xff0000, data.intro.light, 10);
    }
    mouse_move_setting(x, y);
}

void    mouse_move_game(int x, int y)
{
    if (data.mouse.x == 10000)
    {
        data.mouse.x = x,
        data.mouse.y = y;
        return ;
    }
    
    if (data.intro.g_k[0])
    {
        int i = 0;
        if (data.mouse.x - x > 1)
            while (data.mouse.x - x - i++ > 1)
                left_angle(),
                i += 10;
        else if (x - data.mouse.x > 1)
            while (x - data.mouse.x - i++ > 1)
                right_angle(),
                i += 10;
        if (x >= 0 && x <= RES_X)
            data.keys[RIGHT] = 0,
            data.keys[LEFT] = 0;
        if (data.mouse.y - y > 1)
            data.c -= 25 * (data.mouse.y - y) / 5 * (-data.c + 25 * (data.mouse.y - y) / 5 < RES_Y - 200);
        else if (y - data.mouse.y > 1)
            data.c += 25 * (y - data.mouse.y) / 5 * (data.c + 25 * (y - data.mouse.y) / 5 < RES_Y - 200);
        
        if (y >= 0 && y <= RES_Y)
            data.keys[UP] = 0,
            data.keys[DOWN] = 0;
    }
    if (x >= RES_X || x <= 0 || y >= RES_Y || y <= 0)
    {
        mlx_mouse_move(data.mlx.win_ptr, 900, 1000);
        data.mouse.x = 900;
        data.mouse.y = 1000;
        return ;
    }
    else
        data.mouse.x = x,
        data.mouse.y = y;
}

void    inc_get_minimap_color2(int x, int y, int angle)
{
    double  c;
    double  s;
    double  c1;
    double  s1;

    c = cos((data.dir.angle + angle + 90 + 7.2 * (double)data.intro.map * (data.intro.map < 51)) * M_PI / 180);
    s = sin((data.dir.angle + angle + 90 + 7.2 * (double)data.intro.map * (data.intro.map < 51)) * M_PI / 180);
    c1 = cos((data.dir.angle + 90 + 7.2 * (double)data.intro.map * (data.intro.map < 51)) * M_PI / 180);
    s1 = sin((data.dir.angle + 90 + 7.2 * (double)data.intro.map * (data.intro.map < 51)) * M_PI / 180);

    x -= 1345;
    y -= 935;
    
    double xnew = x * c - y * s + 1345;
    double ynew = x * s + y * c + 935;
    
    double old_x = x * c1 - y * s1 + 1345;
    double old_y = x * s1 + y * c1 + 935;
    
    if (xnew < MX)
        x = (double)data.dir.x - fabs(MX - xnew) * (2 - data.map_zoom) - 16.5;
    else
        x = (double)data.dir.x + fabs(MX - xnew) * (2 - data.map_zoom) - 16.5;
    if (ynew < MY)
        y = (double)data.dir.y - fabs(MY - ynew) * (2 - data.map_zoom) - 16.5;
    else
        y = (double)data.dir.y + fabs(MY - ynew) * (2 - data.map_zoom) - 16.5;

    if (old_x < MX)
        old_x = (double)data.dir.x - fabs(MX - xnew) * (2 - data.map_zoom) - 16.5;
    else
        old_x = (double)data.dir.x + fabs(MX - xnew) * (2 - data.map_zoom) - 16.5;
    if (old_y < MY)
        old_y = (double)data.dir.y - fabs(MY - ynew) * (2 - data.map_zoom) - 16.5;
    else
        old_y = (double)data.dir.y + fabs(MY - ynew) * (2 - data.map_zoom) - 16.5;

    data.mv_x -= (old_x - x) * 7 * cos((data.dir.angle - angle + 90 + 7.2 * (double)data.intro.map * (data.intro.map < 51)) * M_PI / 180);
    data.mv_y -= (old_y - y) * 7 * sin((data.dir.angle - angle + 90 + 7.2 * (double)data.intro.map * (data.intro.map < 51)) * M_PI / 180);
}


void    mouse_move_map(int x, int y)
{
    if (data.keys[data.intro.g_k[7]])
        data.mv_x += (x - data.mouse.x) * 3,
        data.mv_y += (y - data.mouse.y) * 3;
    if (data.keys[data.intro.g_k[8]])
    {
        inc_get_minimap_color2(1345, 935, x - data.mouse.x);
        data.map_rotation += x - data.mouse.x;
    }
}

int mouse_move(int x, int y, void *w)
{
    w = NULL;
        
    if (data.mode == INTRO)
        mouse_move_intro(x, y);
    else if (data.mode == SETTING || data.mode == SETTING2)
        mouse_move_setting(x, y);
    else if (data.mode == S_CONTROL)
        mouse_move_control(x, y);
    else if (data.mode == G_MAP)
        mouse_move_map(x, y);
    if (data.mode == GAME && data.objects.health > 0)
        mouse_move_game(x, y);
    else
        data.mouse.x = x,
        data.mouse.y = y;
    return (0);
}