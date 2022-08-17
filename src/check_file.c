/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:35:33 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/08/17 16:08:49 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    check_elements()
{
    if (!data.no || !data.so || !data.we || !data.ea
        || data.ceil.r == -1 || data.floor.g == -1 || data.floor.b == -1
        || data.ceil.r == -1 || data.ceil.g == -1 || data.ceil.b == -1)
            error("Error:\nmissing elements\n", 1);
}

void    check_textures(char *s, char *o)
{
    int fd;

    fd = open(s,O_RDONLY);
    if (fd == -1)
    {
        error("Error:\ncan't open texture file", 0);
        error(o,1);
    }
    close(fd);
}

void    check_rgb()
{
    if (data.floor.r < 0 || data.floor.r > 255 || data.floor.g < 0
        || data.floor.g > 255 || data.floor.b < 0 || data.floor.b > 255
        || data.ceil.r < 0 || data.ceil.r > 255 || data.ceil.g < 0
        || data.ceil.g > 255 || data.ceil.b < 0 || data.ceil.b > 255)
            error("Error:\ninvalid rgb value\n", 1);
}

void    check_map()
{
    int i;
    int j;

    i = -1;
    while (data.map[++i])
    {
        j = -1;
        while (data.map[i][++j])
        {
            if (!ft_strchr(MAP_CHAR, data.map[i][j]))
                error("Error:\ninvalid map character\n", 1);
            if (data.map[i][j] != ' ' && data.map[i][j] != '1')
            {
                if (!i || !j || j + 1 == ft_strlen(data.map[i]) || i + 1 == ft_strlen2(data.map)
                    || data.map[i][j + 1] == ' ' || data.map[i][j - 1] == ' '
                    || data.map[i + 1][j] == ' ' || data.map[i - 1][j] == ' ')
                    error("Error:\ninvalid map\n", 1);
                if (data.map[i][j] == 'N' || data.map[i][j] == 'W' || data.map[i][j] == 'S' || data.map[i][j] == 'E')
                {
                    data.dir.s = (4 * (data.map[i][j] == 'N') + 8 * (data.map[i][j] == 'W') + 12 * (data.map[i][j] == 'S')) * ANGLES;
                    data.dir.angle = 90 * (data.map[i][j] == 'S') + 180 * (data.map[i][j] == 'W') + 270 * (data.map[i][j] == 'N');
                    data.dir.x = j * 50 + 10;
                    data.dir.y = i * 50 + 10;
                    data.dir.px = data.dir.x;
                    data.dir.py = data.dir.y;
                }
            }
        }
    }
}

void    check_file()
{
    check_textures(data.no, " ------>[NO]\n");
    check_textures(data.so, " ------>[SO]\n");
    check_textures(data.we, " ------>[WE]\n");
    check_textures(data.ea, " ------>[EA]\n");
    check_textures(data.tf, " ------>[EA]\n");
    check_textures(data.tc, " ------>[EA]\n");
    check_rgb();
    check_map();
}