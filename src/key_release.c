/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:38:21 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/08/29 16:07:56 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int key_release(int key, void *d)
{
    d = NULL;

    if (data.mode == INTRO)
    {
        if (!data.mouse.clicked)
            data.mouse.clicked = 1;
        data.mouse.on_click = 0;
    }
    if (data.mode == SETTING && key == ENTER && data.mouse.on_clk[0])
        data.mouse.on_clk[0] = 0,
        data.mode = GAME;
    if ((data.mode == SETTING || data.mode == SETTING2) && key == ENTER && data.mouse.on_clk[1])
        data.mouse.on_clk[1] = 0,
        data.mode = S_CONTROL;
    if ((data.mode == SETTING || data.mode == SETTING2) && key == ENTER && data.mouse.on_clk[2])
        data.mouse.on_clk[2] = 0,
        mlx_clear_window(data.mlx.mlx_ptr, data.mlx.win_ptr),
        exit (0);
    
    if (data.mode == SETTING2 && key == ENTER && data.mouse.on_clk[3])
        data.mouse.on_clk[3] = 0,
        data.mode = GAME;
    // if (data.mode == SETTING2 && key == ENTER && data.mouse.on_clk[4])
    //     data.mouse.on_clk[4] = 0,
    //     data.mode = GAME;
    data.keys[key] = 0;
    return (0);
}
