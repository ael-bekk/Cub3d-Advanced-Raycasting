/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:13:39 by mel-hada          #+#    #+#             */
/*   Updated: 2022/08/12 11:30:12 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

int     arg_check(int ac, char **av)
{
    char *error;
    
    error = NULL;
    if(ac != 2)
        error = "Error: too many arguments\n";
    else
        if(ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4) != 0)
            error = "Error: invalid file extension\n";
    if (error)
    {
        write(2, error, ft_strlen(error));
        return (0);
    }
    return (1);
}

int main(int ac, char **av)
{
    t_map *map;
    char *buff;
    int fd;

    init_args(&map);
    buff = NULL;
    if (arg_check(ac, av) != 1)
        return (0);
    fd = open(av[1], O_RDONLY);
    buff = get_next_line(fd);
    while(buff)
    {
        if (ft_strlen(buff) > 0 && buff[ft_strlen(buff) - 1] == '\n')
            buff[ft_strlen(buff) - 1] = '\0';
        ft_lst_add_back(&map, ft_lst_new(buff));
        buff = get_next_line(fd);
    }
    parsing(map);
    set_minimap();
}