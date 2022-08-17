/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:53:35 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/08/14 15:00:21 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    calculate_time()
{
    if (data.objects.t1 > 9)
        data.objects.t1 = 0,
        data.objects.t2++;
        
    if (data.objects.t2 > 5)
        data.objects.t2 = 0,
        data.objects.t3++;

    if (data.objects.t3 > 3 && data.objects.t4 == 2)
        data.objects.t3 = 0,
        data.objects.t4++;
    
    if (data.objects.t3 > 9 && data.objects.t4 < 2)
        data.objects.t3 = 0,
        data.objects.t4++;
        
    if (data.objects.t4 > 2)
        data.objects.t4 = 0;
}

void    *time_count(void *d)
{
    d = NULL;

    mlx_hook(data.mlx.win_ptr, 6, 1L<<6, mouse_move, NULL);
    mlx_hook(data.mlx.win_ptr, 4, 1L<<2, mouse_press, NULL);
    mlx_hook(data.mlx.win_ptr, 5, 1L<<3, mouse_release, NULL);
    while (1)
    {
        usleep(1000 * 300);
        if (data.mode == GAME)
        {
            data.objects.t1++;
            calculate_time(),
            data.keys[999 - SCROLL_UP] = 1;
        }
    }
}

void    set_volume()
{
    char    str[100];

    ft_memcpy(str, "osascript -e 'set volume output volume 000'", 44);
    str[39] = '0' + (data.intro.volume / 2 == 100);
    str[40] = '0' + ((data.intro.volume / 2) % 100) / 10;
    str[41] = '0' + (data.intro.volume / 2) % 10;
    system(str);
}

void    *check_sound(void *d)
{
    d = NULL;
    
    while (1)
    {
        usleep(1000);
        if (data.intro.vol_click)
            set_volume();
        if (data.intro.lgt_click)
            paint_color(&data.intro.lt, ((55 + data.intro.light) << 24), RES_X, RES_Y);
        if (data.sound.hover == 1)
            data.sound.hover++,
            system("afplay sound/hover.mp3 &");
        if (data.sound.click == 1)
            data.sound.click++,
            system("afplay sound/click.wav &");
        if (data.mode == INTRO1)
            system("afplay sound/gun_intro1.mp3");
        if (data.mode == INTRO2)
            system("afplay sound/mixkit-epic-orchestra-transition-2290.wav");
    }
}
