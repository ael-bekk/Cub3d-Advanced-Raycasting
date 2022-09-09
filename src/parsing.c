/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:08:28 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/08/24 14:11:07 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
                if (!i || !j || j + 1 == data.w_map[i] || i + 1 == data.h_map
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
                    data.map[i][j] = '0';
                    data.door.map[i][j] = '0';
                }
            }
        }
    }
}

void    parse_map(t_map *it)
{
    int i;

    i = 0;
    data.h_map = ft_lst_size(it);
    data.map = (char **)malloc(sizeof(char *) * (data.h_map + 1));
    data.door.map = (char **)malloc(sizeof(char *) * (data.h_map + 1));
    data.w_map = (int *)malloc(sizeof(int ) * (data.h_map));
    while (it)
    {
        if (it->content[0])
        {
            data.w_map[i] = ft_strlen(it->content);
            data.door.map[i] = ft_substr(it->content, 0, data.w_map[i]);
            data.map[i] = ft_substr(it->content, 0, data.w_map[i]);
            i++;
        }
        else
            error("Error:\ninvalid map\n",1);
        it = it->next;
    }
    data.map[i] = NULL;
    data.door.map[i] = NULL;
}

void    parsing(t_map *map)
{
    while (map)
    {
        if (map->content[0])
            break;
        map = map->next;
    }
    parse_map(map);
    check_map();
}
