/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:52:40 by mel-hada          #+#    #+#             */
/*   Updated: 2022/08/17 20:09:50 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void init_objects()
{
    int i;

    srand(time(NULL));
    i = 0;
    while (++i < 7)
        data.objects.ammo[i] = 0,
        data.mouse.on_clk[i] = 0,
        data.mouse.on_hov[i] = 0;
    data.objects.w = 0;
    data.objects.t1 = rand() % 10;
    data.objects.t2 = rand() % 10;
    data.objects.t3 = rand() % 10;
    data.objects.t4 = rand() % 10;
    data.objects.health = 100;
    i = 0;
    while (++i < 17)
        data.intro.on_hov[i] = 0,
        data.intro.on_clk[i] = 0;
}
void    init_keys()
{
    data.intro.g_k[0] = 0;
    data.intro.g_k[1] = KEY_W;
    data.intro.g_k[2] = KEY_S;
    data.intro.g_k[3] = KEY_A;
    data.intro.g_k[4] = KEY_D;
    data.intro.g_k[5] = ENTER;
    data.intro.g_k[6] = CONTROL;
    data.intro.g_k[7] = M_LEFT_CLICK;
    data.intro.g_k[8] = M_RIGHT_CLICK;
    data.intro.g_k[9] = SPACE;
    data.intro.g_k[10] = SHIFT;
    data.intro.g_k[11] = TAB;
    data.intro.volume = 100;
    data.intro.light = 200;
}

void init_args(t_map **map)
{
    data.no = NULL;
    data.so = NULL;
    data.we = NULL;
    data.ea = NULL;
    data.tf = NULL;
    data.tc = NULL;
    data.c = 0;
    data.dir.ph = 0.5;
    data.floor.r = -1;
    data.floor.g = -1;
    data.floor.b = -1;
    data.ceil.r = -1;
    data.ceil.g = -1;
    data.ceil.b = -1;
    data.speed = 0;
    init_objects();
    data.mouse.show = 1;
    data.fov.jumping = 0;
    data.fov.crouching = 0;
    data.mouse.on = 1;
    data.mouse.x = 10000;
    data.mouse.y = 10000;
    data.mouse.hover = 0;
    data.mouse.clicked = 0;
    data.intro.fov = 0;
    data.intro.up = 0;
    data.mode = SETTING;
    data.sound.hover = 0;
    data.sound.click = 0;
    data.intro.vol_click = 0;
    init_keys();
    *map = NULL;
}