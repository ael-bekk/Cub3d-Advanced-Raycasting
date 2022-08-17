/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:24:38 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/08/14 18:05:26 by ael-bekk         ###   ########.fr       */
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
    // if (data.mode == SETTING)
    // {
    //     if (!data.mouse.on_hov[0] && x >= RES_X - 500 && y >= (RES_Y - data.intro.start.y) / 2 - RES_Y / 6 && x < (RES_X + data.intro.start.x) / 2 && y < (RES_Y + data.intro.start.y) / 2 - RES_Y / 6)
    //         data.sound.hover = 1,
    //         p = 0;
    //     if (!data.mouse.on_hov[1] && x >= RES_X - 300&& y >= (RES_Y - data.intro.sett.y) / 2 - RES_Y / 12 && x < (RES_X + data.intro.sett.x) / 2 && y < (RES_Y + data.intro.sett.y) / 2 - RES_Y / 12)
    //         data.sound.hover = 1,
    //         p = 1;
    //     if (!data.mouse.on_hov[2] && x >= (RES_X - data.intro.exit.x) / 2 && y >= (RES_Y - data.intro.exit.y) / 2 && x < (RES_X + data.intro.exit.x) / 2 && y < (RES_Y + data.intro.exit.y) / 2)
    //         data.sound.hover = 1,
    //         p = 2;
    // }
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
        if (data.mouse.x - x > 1)
            left_angle();
        else if (x - data.mouse.x > 1)
            right_angle();
        if (x >= 0 && x <= RES_X)
            data.keys[RIGHT] = 0,
            data.keys[LEFT] = 0;
        if (data.mouse.y - y > 1)
            data.c -= 25 * (-data.c + 25 < RES_Y - 200);
        else if (y - data.mouse.y > 1)
            data.c += 25 * (data.c + 25 < RES_Y - 200);
        
        if (y >= 0 && y <= RES_Y)
            data.keys[UP] = 0,
            data.keys[DOWN] = 0;
    }
}

int mouse_move(int x, int y, void *w)
{
    w = NULL;
    if (x > RES_X || y > RES_Y || x < 0 || y < 0)
        mlx_mouse_show();
    else
        mlx_mouse_hide();
    if (data.mode == INTRO)
        mouse_move_intro(x, y);
    if (data.mode == SETTING)
        mouse_move_setting(x, y);
    if (data.mode == S_CONTROL)
        mouse_move_control(x, y);
    if (data.mode == GAME)
        mouse_move_game(x, y);
    
    data.mouse.x = x;
    data.mouse.y = y;
    return (0);
}