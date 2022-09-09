/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_release.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 21:37:37 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/09/02 14:20:54 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    mouse_release_intro(int key)
{
    if (key == LEFT_CLICK && !data.mouse.clicked)
        data.mouse.clicked = 1;
    if (key == LEFT_CLICK)
        data.mouse.on_click = 0;
        // data.mode = SETTING;
}

void    set_vol_lgt_as_def(t_img *img2, int *v, int val)
{
    *v = val;
    if (*v > 200)
        *v = 200;
    if (*v < 0)
        *v = 0;
    paint_color(img2, 0xB2BEB5, 200, 10);
    paint_color(img2, 0xff0000, *v, 10);
    set_volume();
    paint_color(&data.intro.lt, ((55 + data.intro.light) << 24), RES_X, RES_Y);
}

void    mouse_release_setting(int key, int x, int y)
{
    if (key == LEFT_CLICK)
    {
        if (data.mode == SETTING)
        {
            if (data.mouse.on_clk[0] && x >= (RES_X - data.intro.start.x) / 2 && y >= (RES_Y - data.intro.start.y) / 2 - RES_Y / 6 && x < (RES_X + data.intro.start.x) / 2 && y < (RES_Y + data.intro.start.y) / 2 - RES_Y / 6)
                data.sound.click = 1,
                data.mode = GAME;
            if (data.mouse.on_clk[1] && x >= (RES_X - data.intro.sett.x) / 2 && y >= (RES_Y - data.intro.sett.y) / 2 - RES_Y / 12 && x < (RES_X + data.intro.sett.x) / 2 && y < (RES_Y + data.intro.sett.y) / 2 - RES_Y / 12)
                data.sound.click = 1,
                data.mode = S_CONTROL;
            if (data.mouse.on_clk[2] && x >= (RES_X - data.intro.exit.x) / 2 && y >= (RES_Y - data.intro.exit.y) / 2 && x < (RES_X + data.intro.exit.x) / 2 && y < (RES_Y + data.intro.exit.y) / 2)
                data.sound.click = 1,
                exit (0);
        }
        if (data.mode == SETTING2)
        {
            if (data.mouse.on_clk[3] && x >= (RES_X - data.intro.cont.x) / 2 && y >= (RES_Y - data.intro.cont.y) / 2 - RES_Y / 6 && x < (RES_X + data.intro.cont.x) / 2 && y < (RES_Y + data.intro.cont.y) / 2 - RES_Y / 6)
                data.sound.click = 1,
                data.mode = GAME;
            if (data.mouse.on_clk[4] && x >= (RES_X - data.intro.restart.x) / 2 && y >= (RES_Y - data.intro.restart.y) / 2 - RES_Y / 12 && x < (RES_X + data.intro.restart.x) / 2 && y < (RES_Y + data.intro.restart.y) / 2 - RES_Y / 12)
                data.sound.click = 1,
                data.mode = GAME;
            if (data.mouse.on_clk[1] && x >= (RES_X - data.intro.sett.x) / 2 && y >= (RES_Y - data.intro.sett.y) / 2 && x < (RES_X + data.intro.sett.x) / 2 && y < (RES_Y + data.intro.sett.y) / 2)
                data.sound.click = 1,
                data.mode = S_CONTROL;
            if (data.mouse.on_clk[2] && x >= (RES_X - data.intro.exit.x) / 2 && y >= (RES_Y - data.intro.exit.y) / 2 + RES_Y / 12 && x < (RES_X + data.intro.exit.x) / 2 && y < (RES_Y + data.intro.exit.y) / 2 + RES_Y / 12)
                data.sound.click = 1,
                exit (0);
        }
        if (data.mode == S_CONTROL)
        {
            if (data.mouse.on_clk[5] && x >= RES_X / 2 - 225 && y >= RES_Y - 100 && x < RES_X / 2 - 75 && y < RES_Y - 40)
            {
                data.sound.click = 1;
                data.mode = SETTING * !data.mouse.sett2 + SETTING2 * data.mouse.sett2;
            }
            if (data.mouse.on_clk[6] && x >= RES_X / 2 + 75 && y >= RES_Y - 100 && x < RES_X / 2 + 225 && y < RES_Y - 40)
            {
                data.sound.click = 1;
                init_keys();
                set_vol_lgt_as_def(&data.intro.vol[0], &data.intro.volume, 100);
                set_vol_lgt_as_def(&data.intro.lgt[0], &data.intro.light, 200);
            }
        }
        data.mouse.on_clk[0] = 0;
        data.mouse.on_clk[1] = 0;
        data.mouse.on_clk[2] = 0;
        data.mouse.on_clk[3] = 0;
        data.mouse.on_clk[4] = 0;
        data.mouse.on_clk[5] = 0;
        data.mouse.on_clk[6] = 0;
    }
}

void    mouse_release_control(int key, int x, int y)
{
    if (key == LEFT_CLICK)
    {
        paint_color(&data.intro.vol[1], 0xffffff, 25, 40);
        paint_color(&data.intro.lgt[1], 0xffffff, 25, 40);
        data.intro.vol_click = 0;
        data.intro.lgt_click = 0;
    }
    mouse_release_setting(key, x, y);
}

void    mouse_release_game(int key)
{
    
    if (data.intro.g_k[7] == M_LEFT_CLICK && key == LEFT_CLICK)
        data.keys[data.intro.g_k[7]] = 0;
    if (data.intro.g_k[8] == M_RIGHT_CLICK && key == RIGHT_CLICK)
        data.keys[data.intro.g_k[8]] = 0;
}

int mouse_release(int key, int x, int y, void *w)
{

    w = NULL;
    if (data.mode == INTRO)
        mouse_release_intro(key);
    if (data.mode == SETTING || data.mode == SETTING2)
        mouse_release_setting(key, x, y);
    if (data.mode == S_CONTROL)
        mouse_release_control(key, x, y);
    if (data.mode == GAME)
        mouse_release_game(key);
    return (0);
}
