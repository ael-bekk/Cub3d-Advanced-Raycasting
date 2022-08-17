/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:38:21 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/08/14 16:20:19 by ael-bekk         ###   ########.fr       */
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
        data.mode = GAME;
    if (data.mode == SETTING && key == ENTER && data.mouse.on_clk[1])
        data.mode = S_CONTROL;
    if (data.mode == SETTING && key == ENTER && data.mouse.on_clk[2])
        exit (0);
    
    data.keys[key] = 0;
    return (0);
}
