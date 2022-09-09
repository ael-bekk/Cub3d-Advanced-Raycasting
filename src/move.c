/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:02:02 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/08/26 12:16:37 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define ABS(X) ((X > 0)? X : -X) 

void    up()
{
    int x;
    int y;

    x = round(data.dir.x + (7 + data.speed) * data.angles.pl_cos);
    y = round(data.dir.y + (7 + data.speed) * data.angles.pl_sin);
        
    if (data.map[(y + 17) / 50][(x + 17) / 50] != '1'
        && data.map[(y + 17) / 50][(data.dir.x + 17) / 50] != '1'
        && data.map[(data.dir.y + 17) / 50][(x + 17) / 50] != '1'
        && data.map[(y + 15) / 50][(x + 15) / 50] != '1'
        && data.map[(y + 15) / 50][(data.dir.x + 15) / 50] != '1'
        && data.map[(data.dir.y + 15) / 50][(x + 15) / 50] != '1')
    {
        data.dir.x = x;
        data.dir.y = y;
    }
    else if (data.map[(data.dir.y + 17) / 50][(x + 17) / 50] != '1'
            && data.map[(data.dir.y + 15) / 50][(x + 15) / 50] != '1')
        data.dir.x = x;
    else if (data.map[(y + 17) / 50][(data.dir.x + 17) / 50] != '1'
            && data.map[(y + 15) / 50][(data.dir.x + 15) / 50] != '1')
        data.dir.y = y;
}

void    down()
{
    int x;
    int y;

    x = round(data.dir.x - 7 * data.angles.pl_cos);
    y = round(data.dir.y - 7 * data.angles.pl_sin);
        
    if (data.map[(y + 17) / 50][(x + 17) / 50] != '1'
        && data.map[(y + 17) / 50][(data.dir.x + 17) / 50] != '1'
        && data.map[(data.dir.y + 17) / 50][(x + 17) / 50] != '1'
        && data.map[(y + 15) / 50][(x + 15) / 50] != '1'
        && data.map[(y + 15) / 50][(data.dir.x + 15) / 50] != '1'
        && data.map[(data.dir.y + 15) / 50][(x + 15) / 50] != '1')
    {
        data.dir.x = x;
        data.dir.y = y;
    }
    else if (data.map[(data.dir.y + 17) / 50][(x + 17) / 50] != '1'
            && data.map[(data.dir.y + 15) / 50][(x + 15) / 50] != '1')
        data.dir.x = x;
    else if (data.map[(y + 17) / 50][(data.dir.x + 17) / 50] != '1'
            && data.map[(y + 15) / 50][(data.dir.x + 15) / 50] != '1')
        data.dir.y = y;
}

void    right_angle()
{
    data.dir.s--;
    if (data.dir.s < 0)
        data.dir.s = 16 * ANGLES - 1;

    data.dir.angle += ANGLE * data.mouse.on;
    if (data.dir.angle >= 360)
        data.dir.angle -= (double)360;
    init_angles();
}

void    left_angle()
{
    data.dir.s++;
    data.dir.s %= 16 * ANGLES;
    
    data.dir.angle -= ANGLE * data.mouse.on;
    if (data.dir.angle < 0)
        data.dir.angle += (double)360;
    init_angles();
}

void    right()
{
    int x;
    int y;

    x = round(data.dir.x + 7 * data.angles.pl_cos_plus_90);
    y = round(data.dir.y + 7 * data.angles.pl_sin_plus_90);
        
    if (data.map[(y + 17) / 50][(x + 17) / 50] != '1'
        && data.map[(y + 17) / 50][(data.dir.x + 17) / 50] != '1'
        && data.map[(data.dir.y + 17) / 50][(x + 17) / 50] != '1'
        && data.map[(y + 15) / 50][(x + 15) / 50] != '1'
        && data.map[(y + 15) / 50][(data.dir.x + 15) / 50] != '1'
        && data.map[(data.dir.y + 15) / 50][(x + 15) / 50] != '1')
    {
        data.dir.x = x;
        data.dir.y = y;
    }
    else if (data.map[(data.dir.y + 17) / 50][(x + 17) / 50] != '1'
            && data.map[(data.dir.y + 15) / 50][(x + 15) / 50] != '1')
        data.dir.x = x;
    else if (data.map[(y + 17) / 50][(data.dir.x + 17) / 50] != '1'
            && data.map[(y + 15) / 50][(data.dir.x + 15) / 50] != '1')
        data.dir.y = y;
}

void   left()
{
    int x;
    int y;

    x = round(data.dir.x - 7 * data.angles.pl_cos_plus_90);
    y = round(data.dir.y - 7 * data.angles.pl_sin_plus_90);
        
    if (data.map[(y + 17) / 50][(x + 17) / 50] != '1'
        && data.map[(y + 17) / 50][(data.dir.x + 17) / 50] != '1'
        && data.map[(data.dir.y + 17) / 50][(x + 17) / 50] != '1'
        && data.map[(y + 15) / 50][(x + 15) / 50] != '1'
        && data.map[(y + 15) / 50][(data.dir.x + 15) / 50] != '1'
        && data.map[(data.dir.y + 15) / 50][(x + 15) / 50] != '1')
    {
        data.dir.x = x;
        data.dir.y = y;
    }
    else if (data.map[(data.dir.y + 17) / 50][(x + 17) / 50] != '1'
            && data.map[(data.dir.y + 15) / 50][(x + 15) / 50] != '1')
        data.dir.x = x;
    else if (data.map[(y + 17) / 50][(data.dir.x + 17) / 50] != '1'
            && data.map[(y + 15) / 50][(data.dir.x + 15) / 50] != '1')
        data.dir.y = y;
}