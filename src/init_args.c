/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 11:52:40 by mel-hada          #+#    #+#             */
/*   Updated: 2022/09/20 17:29:47 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void init_objects()
{
    int i;

    srand(time(NULL));
    i = 0;
    while (++i < 7)
        data.mouse.on_clk[i] = 0,
        data.mouse.on_hov[i] = 0;
    data.objects.w = 0;
    data.objects.t1 = rand() % 10;
    data.objects.t2 = rand() % 10;
    data.objects.t3 = rand() % 10;
    data.objects.t4 = rand() % 10;
    data.objects.health = 100;
    data.objects.breath = 100;
    i = 0;
    while (++i < 17)
        data.intro.on_hov[i] = 0,
        data.intro.on_clk[i] = 0;
}

void    init_keys()
{
    data.intro.g_k[0] = 1;
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

void    init_guns_objects()
{
    data.gun[2].f_shoot = 4;
    data.gun[2].f_reload = 32;
    data.gun[2].frame = 0;
    data.gun[2].case_bullet = 10;
    data.gun[2].bullet = 32;

    data.gun[4].f_shoot = 6;
    data.gun[4].f_reload = 32;
    data.gun[4].frame = 0;
    data.gun[4].case_bullet = 24;
    data.gun[4].bullet = 12;
    
    data.gun[5].f_shoot = 8;
    data.gun[5].f_reload = 25;
    data.gun[5].frame = 0;
    data.gun[5].case_bullet = 13;
    data.gun[5].bullet = 9;
    
    data.gun[19].f_shoot = 6;
    data.gun[19].f_reload = 48;
    data.gun[19].frame = 0;
    data.gun[19].case_bullet = 32;
    data.gun[19].bullet = 6;

    data.gun[13].f_shoot = 7;
    data.gun[13].f_reload = 25;
    data.gun[13].frame = 0;
    data.gun[13].case_bullet = 12;
    data.gun[13].bullet = 28;

    data.gun[15].f_shoot = 16;
    data.gun[15].f_reload = 16;
    data.gun[15].frame = 0;
    data.gun[15].case_bullet = 0;
    data.gun[15].bullet = 6;
    
    data.gun[17].f_shoot = 15;
    data.gun[17].f_reload = 52;
    data.gun[17].frame = 0;
    data.gun[17].case_bullet = 14;
    data.gun[17].bullet = 6;

    data.gun[20].f_shoot = 23;
    data.gun[20].f_reload = 23;
    data.gun[20].frame = 0;
    data.gun[20].case_bullet = 0;
    data.gun[20].bullet = 80;
    
    data.gun[9].f_shoot = 13;
    data.gun[9].frame = 0;

    data.use_gun = 0;
    data.aim = 0;
    
}

void init_motions_enemies()
{
    int i;

    i = -1;
    while (++i < 7)
        data.enemy[i].health = 1000,
        data.enemy[i].hit = 0,
        data.motion[i].frame = 0,
        data.enemy[i].old_motion = 0,
        data.enemy[i].motion = 0;
}

void init_args(t_map **map)
{
    data.death = 0;
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
    data.mouse.sett2 = 0;
    data.intro.fov = 0;
    data.intro.up = 0;
    data.door.op = 15;
    data.door.is_op = 0;
    data.mode = INTRO;
    data.light = 0;
    data.bld = 0;
    data.sound.hover = 0;
    data.sound.click = 0;
    data.intro.vol_click = 0;
    data.sound.scroll = 0;
	data.sound.hit = 0;
    data.sound.breath = 0;
    init_guns_objects();
    data.mv = 0;
    data.g_mv = 0;
    data.zoom = 0;
    data.mv_x = 0;
    data.mv_y = 0;
    data.map_zoom = 0;
    data.map_rotation = 0;
    data.c_x = 0;
    data.c_y = 0;
    data.enemy[0].frm = 0;
    init_motions_enemies();
    init_keys();
    *map = NULL;
}
