/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:08:28 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/08/17 16:05:11 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int paths(t_map *map)
{
    char **path;

    replace_tab(map->content);
    path = ft_split(map->content, ' ');
    if ((!ft_strncmp("NO", path[0], 3) || !ft_strncmp("SO", path[0], 3)
        || !ft_strncmp("WE", path[0], 3) || !ft_strncmp("EA", path[0], 3)
        || !ft_strncmp("TF", path[0], 3) || !ft_strncmp("TC", path[0], 3)))
    {
        if (!ft_strncmp("NO", path[0], 3))
            data.no = ft_str_trim(ft_strnstr(map->content, "NO ", 3) + 2, " ");
        if (!ft_strncmp("SO", path[0], 3))
            data.so = ft_str_trim(ft_strnstr(map->content, "SO ", 3) + 2, " ");
        if (!ft_strncmp("WE", path[0], 3))
            data.we = ft_str_trim(ft_strnstr(map->content, "WE ", 3) + 2, " ");
        if (!ft_strncmp("EA", path[0], 3))
            data.ea = ft_str_trim(ft_strnstr(map->content, "EA ", 3) + 2, " ");
        if (!ft_strncmp("TF", path[0], 3))
            data.tf = ft_str_trim(ft_strnstr(map->content, "TF ", 3) + 2, " ");
        if (!ft_strncmp("TC", path[0], 3))
            data.tc = ft_str_trim(ft_strnstr(map->content, "TC ", 3) + 2, " ");
        return (1);
    }
    return (0);
}

int init_rgb(t_rgb *p, char *s)
{
    char **rgb;

    rgb = ft_split(s, ',');
    if (ft_strlen2(rgb) != 3
        || !ft_str_isdigit(rgb[0]) || !ft_str_isdigit(rgb[1]) || !ft_str_isdigit(rgb[2]))
        return (0);
    
    p->r = ft_atoi(rgb[0]);
    p->g = ft_atoi(rgb[1]);
    p->b = ft_atoi(rgb[2]);
    return (1);
}

int rgb(t_map *map)
{
    char **path;

    replace_tab(map->content);
    path = ft_split(map->content, ' ');
    if (!ft_strncmp("F", path[0], 2) && ft_strlen2(path) == 2)
        return (init_rgb(&data.floor, path[1]));
    if (!ft_strncmp("C", path[0], 2) && ft_strlen2(path) == 2)
        return (init_rgb(&data.ceil, path[1]));
    return (0);
}

void    parse_map(t_map *it)
{
    int i;

    i = 0;
    data.map = (char **)malloc(sizeof(char *) * (ft_lst_size(it) + 1));
    while (it)
    {
        if (it->content[0])
            data.map[i++] = ft_substr(it->content, 0, ft_strlen(it->content));
        else
            error("Error:\ninvalid map\n",1);
        it = it->next;
    }
    data.map[i] = NULL;
}

void    parsing(t_map *map)
{
    t_map *it;
    
    it = map;
    while (it)
    {
        if (!it->content[0])
        {
            
            it = it->next;
            continue;
        }
        if (!paths(it) && !rgb(it))
            break;
        it = it->next;
    }
    check_elements();
    parse_map(it);
    check_file();
}
