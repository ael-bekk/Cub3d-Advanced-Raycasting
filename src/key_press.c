/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:20:15 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/09/11 14:44:52 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    key_press_intro(int key)
{
    key = 0;
    data.mouse.on_click = 1;
}

void    key_press_setting(int key)
{
    int o;

    o = data.mouse.on_hov[0] + 2 * data.mouse.on_hov[1] + 3 * data.mouse.on_hov[2];
    if (key == UP && !o)
        data.mouse.on_hov[2] = 1;
    else if (key == UP)
    {
        data.mouse.on_hov[o - 1] = 0;
        data.mouse.on_hov[o % 3] = 0;
        data.mouse.on_hov[(o + 1) % 3] = 1;
    }
    if (key == DOWN && !o)
            data.mouse.on_hov[0] = 1;
    else if (key == DOWN)
    {
        data.mouse.on_hov[o - 1] = 0;
        data.mouse.on_hov[o % 3] = 1;
        data.mouse.on_hov[(o + 1) % 3] = 0;
    }
    if (key == ENTER && o)
        data.mouse.on_clk[o - 1] = 1;
}

void    key_press_setting2(int key)
{
    int o;

    o = 2 * data.mouse.on_hov[1] + 3 * data.mouse.on_hov[2] + 4 * data.mouse.on_hov[3] + 5 * data.mouse.on_hov[4];
    if (key == UP && !o)
        data.mouse.on_hov[2] = 1;
    else if (key == UP)
    {
        data.mouse.on_hov[o - 1] = 0;
        data.mouse.on_hov[o % 5 + (o > 4)] = 0;
        data.mouse.on_hov[(o + 1) % 5 + ((o + 1) > 4)] = 0;
        data.mouse.on_hov[(o + 2) % 5 + ((o + 2) > 4)] = 1;
    }
    if (key == DOWN && !o)
            data.mouse.on_hov[3] = 1;
    else if (key == DOWN)
    {
        data.mouse.on_hov[o - 1] = 0;
        data.mouse.on_hov[o % 5 + (o > 4)] = 1;
        data.mouse.on_hov[(o + 1) % 5 + ((o + 1) > 4)] = 0;
        data.mouse.on_hov[(o + 2) % 5 + ((o + 2) > 4)] = 0;
    }
    if (key == ENTER && o)
        data.mouse.on_clk[o - 1] = 1;
    if (key == ESC)
        data.mode = ANIMATE_SETT2_OUT;
}

int key_not_in_use(int key)
{
    int i;

    i = -1;
    while (++i < 12)
        if (key == data.intro.g_k[i] && !data.intro.on_clk[i + 4])
            return (0);
    return (1);
}

void    key_press_control(int key)
{
    int i;
    int pos;

    pos = -1;
    if (key == ESC)
        data.mode = SETTING * !data.mouse.sett2 + SETTING2 * data.mouse.sett2;
    if (key_not_in_use(key))
    {
        i = -1;
        while (++i < 12)
            if (data.intro.on_clk[i + 4])
                pos = i;
        if (data.intro.keys[key] && pos != -1)
            data.intro.g_k[pos] = key;
    }
    i = -1;
    while (++i < 16)
        data.intro.on_clk[i] = 0;
}

void    key_press_map(int key)
{
    if (key == data.intro.g_k[10])
        data.intro.up = !data.intro.up,
        data.mv_x = 0,
        data.mv_y = 0,
        data.keys[data.intro.g_k[7]] = 0;
}

void    key_press_game(int key)
{
    if (key == F1 && data.mouse.show)
        mlx_mouse_hide(),
        data.mouse.show = 0;
    else if (key == F1)
        mlx_mouse_show(),
        data.mouse.show = 1;
    if (key == data.intro.g_k[10])
        data.mode = G_MAP,
        data.intro.up = !data.intro.up;
    if (key == data.intro.g_k[6])
        data.fov.crouching = !data.fov.crouching,
        data.fov.jumping = 0;
    if (key == data.intro.g_k[5] && ((!data.fov.jumping && data.dir.ph == 0.5) || data.fov.crouching))
        data.fov.jumping = !data.fov.jumping,
        data.fov.crouching = 0;

    data.keys[key] = 1;
    if (key == data.intro.g_k[7] && data.use_gun > 100)
        data.use_gun = 0;
    if (key == SPACE)
        data.fov.crouching = 0;
    if (key == ESC)
        data.mode = ANIMATE_SETT2_IN,
        set_char_to_win(),
        data.intro.animate_sett = 700;
}

void    key_press_animate_sett_in(key)
{
    if (key == ESC)
        data.mode = ANIMATE_SETT2_OUT;
}

void    key_press_animate_sett_out(key)
{
    if (key == ESC)
        data.mode = ANIMATE_SETT2_IN;
}

int key_press(int key, void *d)
{
    d = NULL;
    if (data.mode == INTRO)
        key_press_intro(key);
    else if (data.mode == SETTING)
        key_press_setting(key);
    else if (data.mode == SETTING2)
        key_press_setting2(key);
    else if (data.mode == ANIMATE_SETT2_IN)
        key_press_animate_sett_in(key);
    else if (data.mode == ANIMATE_SETT2_OUT)
        key_press_animate_sett_out(key);
    else if (data.mode == S_CONTROL)
        key_press_control(key);
    else if (data.mode == G_MAP)
        key_press_map(key);
    else if (data.mode == GAME)
        key_press_game(key);
    return (0);
}