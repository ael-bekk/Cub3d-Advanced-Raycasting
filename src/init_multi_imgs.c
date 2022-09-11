/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_multi_imgs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 11:59:21 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/09/11 13:37:54 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void path_name2(char *path, int i, int len)
{
	int j;

	j = len;
    path[j++] = '0' + i / 10;
	path[j++] = '0' + i % 10;
	path[j++] = '.';
	path[j++] = 'x';
	path[j++] = 'p';
	path[j++] = 'm';
	path[j++] = 0;
}

void    init_gun(int o, int len, char *path)
{
    int i;

    i = 0;
    while (++i < len)
    {
        path_name2(path, i, 12);
        data.gun[o].gun[i - 1].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 500, 400);
        data.gun[o].gun[i - 1].addr = mlx_get_data_addr(data.gun[o].gun[i - 1].mlx_img, &data.gun[o].gun[i - 1].bpp, &data.gun[o].gun[i - 1].line_len, &data.gun[o].gun[i - 1].endian);
        paint_img(data.gun[o].gun + i - 1, path, 500, 400);
    }
}

void    init_guns()
{
	char path[100];

	ft_memcpy(path, "img/guns/g1/", 12);
    init_gun(4, 53, path);
    
	ft_memcpy(path, "img/guns/g2/", 12);
    init_gun(9, 15, path);

	ft_memcpy(path, "img/guns/g3/", 12);
    init_gun(2, 34, path);

	ft_memcpy(path, "img/guns/g4/", 12); 
    init_gun(19, 50, path);

	ft_memcpy(path, "img/guns/g5/", 12);
    init_gun(13, 27, path);

	ft_memcpy(path, "img/guns/g6/", 12);
    init_gun(15, 18, path);

	ft_memcpy(path, "img/guns/g9/", 12);
    init_gun(17, 82, path);

	ft_memcpy(path, "img/guns/g7/", 12);
    init_gun(20, 25, path);
    
	ft_memcpy(path, "img/guns/g8/", 12);
    init_gun(5, 27, path);
}