/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:40:53 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/09/11 15:23:55 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    mouse_press_intro(int key)
{
    if (key == LEFT_CLICK)
        data.mouse.on_click = 1;
}

void    mouse_press_setting(int key, int x, int y)
{
    if (key == LEFT_CLICK)
    {
        if (data.mode == SETTING)
        {
            if (x >= (RES_X - data.intro.start.x) / 2 && y >= (RES_Y - data.intro.start.y) / 2 - RES_Y / 6 && x < (RES_X + data.intro.start.x) / 2 && y < (RES_Y + data.intro.start.y) / 2 - RES_Y / 6)
                data.mouse.on_clk[0] = 1;
            if (x >= (RES_X - data.intro.sett.x) / 2 && y >= (RES_Y - data.intro.sett.y) / 2 - RES_Y / 12 && x < (RES_X + data.intro.sett.x) / 2 && y < (RES_Y + data.intro.sett.y) / 2 - RES_Y / 12)
                data.mouse.on_clk[1] = 1;
            if (x >= (RES_X - data.intro.exit.x) / 2 && y >= (RES_Y - data.intro.exit.y) / 2 && x < (RES_X + data.intro.exit.x) / 2 && y < (RES_Y + data.intro.exit.y) / 2)
                data.mouse.on_clk[2] = 1;
        }
        if (data.mode == SETTING2)
        {
            if (x >= (RES_X - data.intro.cont.x) / 2 && y >= (RES_Y - data.intro.cont.y) / 2 - RES_Y / 6 && x < (RES_X + data.intro.cont.x) / 2 && y < (RES_Y + data.intro.cont.y) / 2 - RES_Y / 6)
                data.mouse.on_clk[3] = 1;
            if (x >= (RES_X - data.intro.restart.x) / 2 && y >= (RES_Y - data.intro.restart.y) / 2 - RES_Y / 12 && x < (RES_X + data.intro.restart.x) / 2 && y < (RES_Y + data.intro.restart.y) / 2 - RES_Y / 12)
                data.mouse.on_clk[4] = 1;
            if (x >= (RES_X - data.intro.sett.x) / 2 && y >= (RES_Y - data.intro.sett.y) / 2 && x < (RES_X + data.intro.sett.x) / 2 && y < (RES_Y + data.intro.sett.y) / 2)
                data.mouse.on_clk[1] = 1;
            if (x >= (RES_X - data.intro.exit.x) / 2 && y >= (RES_Y - data.intro.exit.y) / 2 + RES_Y / 12 && x < (RES_X + data.intro.exit.x) / 2 && y < (RES_Y + data.intro.exit.y) / 2 + RES_Y / 12)
                data.mouse.on_clk[2] = 1;
        }
        if (data.mode == S_CONTROL)
        {
            if (x >= RES_X / 2 - 225 && y >= RES_Y - 100 && x < RES_X / 2 - 75 && y < RES_Y - 40)
                data.mouse.on_clk[5] = 1;
            if (x >= RES_X / 2 + 75 && y >= RES_Y - 100 && x < RES_X / 2 + 225 && y < RES_Y - 40)
                data.mouse.on_clk[6] = 1;
        }
    }
}


void    mouse_press_control(int key, int x, int y)
{
    int i;
    int inc_y;
    int pos;

    pos = -1;
    i = -1;
        while (++i < 12)
            if (data.intro.on_clk[i + 4])
                pos = i;
    if (key == LEFT_CLICK && pos == -1)
    {
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
        if (pos && !data.intro.on_clk[pos])
        {
            if (pos == 3 || pos == 4)
                data.intro.g_k[0] = !data.intro.g_k[0];
            else    
                data.intro.on_clk[pos] = 3;
            data.sound.click = 1;
        }
        i = 0;
        while (++i < 15)
            data.intro.on_clk[(pos + i) % 16] = 0;
    }
    else if (key == LEFT_CLICK && key_not_in_use(M_LEFT_CLICK))
        data.intro.on_clk[pos + 4] = 0,
        data.intro.g_k[pos] = M_LEFT_CLICK;
    else if (key == RIGHT_CLICK && key_not_in_use(M_RIGHT_CLICK))
        data.intro.on_clk[pos + 4] = 0,
        data.intro.g_k[pos] = M_RIGHT_CLICK;
    else
        data.intro.on_clk[pos + 4] = 0;
    if (key == LEFT_CLICK && x >= 1100 - 25 && y >= 75 && x <= 1300 && y <= 115)
    {
        data.intro.volume = x - 1100 + 12;
        if (data.intro.volume > 200)
            data.intro.volume = 200;
        if (data.intro.volume < 0)
            data.intro.volume = 0;
        paint_color(&data.intro.vol[1], 0xff3333, 25, 40);
        paint_color(&data.intro.vol[0], 0xB2BEB5, 200, 10);
        paint_color(&data.intro.vol[0], 0xff0000, data.intro.volume, 10);
        data.intro.vol_click = 1;
    }
    if (key == LEFT_CLICK && x >= 1025 && y >= 70 && x <= 1075 && y <= 120)
    {
        data.sound.click = 1;
        data.intro.vol_click = 1;
        data.intro.volume = !data.intro.volume * 100;
        paint_color(&data.intro.vol[0], 0xB2BEB5, 200, 10);
        paint_color(&data.intro.vol[0], 0xff0000, data.intro.volume, 10);
    }
    
    if (key == LEFT_CLICK && x >= 1100 - 25 && y >= 170 && x <= 1300 && y <= 210)
    {
        data.intro.light = x - 1100 + 12;
        if (data.intro.light > 200)
            data.intro.light = 200;
        if (data.intro.light < 0)
            data.intro.light = 0;
        paint_color(&data.intro.lgt[1], 0xff3333, 25, 40);
        paint_color(&data.intro.lgt[0], 0xB2BEB5, 200, 10);
        paint_color(&data.intro.lgt[0], 0xff0000, data.intro.light, 10);
        data.intro.lgt_click = 1;
    }
    if (key == LEFT_CLICK && x >= 1025 && y >= 165 && x <= 1075 && y <= 215)
    {
        data.sound.click = 1;
        data.intro.lgt_click = 1;
        data.intro.light = !data.intro.light * 200;
        paint_color(&data.intro.lgt[0], 0xB2BEB5, 200, 10);
        paint_color(&data.intro.lgt[0], 0xff0000, data.intro.light, 10);
    }
    mouse_press_setting(key, x, y);
}


void    mouse_press_game(int key)
{
    if (key == SCROLL_UP && !data.keys[data.intro.g_k[8]])
        data.objects.w++,
        data.sound.scroll = 1,
        data.keys[1000 - SCROLL_UP - 1] = 1;
    else if (key == SCROLL_UP && data.zoom > 0)
        data.zoom--;
    
    if (!data.keys[data.intro.g_k[8]] && key == SCROLL_DOWN && !data.keys[data.intro.g_k[8]])
        data.objects.w--,
        data.sound.scroll = 1,
        data.keys[1000 - SCROLL_DOWN - 1] = 1;
    else if (key == SCROLL_DOWN && data.zoom < 20)
        data.zoom++;
    
    if (data.objects.w < 0)
        data.objects.w = 26;
    if (data.objects.w > 26)
        data.objects.w = 0;

    if (data.intro.g_k[7] == M_LEFT_CLICK && key == LEFT_CLICK)
        data.keys[data.intro.g_k[7]] = 1;
    if (data.intro.g_k[8] == M_RIGHT_CLICK && key == RIGHT_CLICK)
        data.keys[data.intro.g_k[8]] = 1;
    if (data.intro.g_k[7] == M_LEFT_CLICK && key == LEFT_CLICK && data.use_gun > 100)
        data.use_gun = 0,
        data.gun[data.objects.w].frame = 0;
}

void    mouse_press_map(int key)
{
    if (data.intro.g_k[7] == M_LEFT_CLICK && key == LEFT_CLICK)
        data.keys[data.intro.g_k[7]] = 1;
    if (data.intro.g_k[8] == M_RIGHT_CLICK && key == RIGHT_CLICK)
        data.keys[data.intro.g_k[8]] = 1;

    if (key == SCROLL_UP && data.map_zoom > -1.9)
        data.map_zoom -= 0.1;
    if (key == SCROLL_DOWN && data.map_zoom < 1.9)
        data.map_zoom += 0.1;
}

int mouse_press(int key, int x, int y, void *w)
{
    w = NULL;
    if (data.mode == INTRO)
        mouse_press_intro(key);
    else if (data.mode == SETTING || data.mode == SETTING2)
        mouse_press_setting(key, x, y);
    else if (data.mode == S_CONTROL)
        mouse_press_control(key, x, y);
    else if (data.mode == G_MAP)
        mouse_press_map(key);
    else if (data.mode == GAME)
        mouse_press_game(key);
    return (0);
}
