/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:32:02 by mel-hada          #+#    #+#             */
/*   Updated: 2022/08/08 12:31:29 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
char *get_next_line(int fd)
{
    //int 	rd = 0;
    char	*c;
    char 	*buffer = malloc(10000);
	
	c = buffer;
    while (read(fd, c, 1) > 0 && *c++ != '\n');
    if (c > buffer)
	{
        *c = 0;
        return (buffer);
    }
	else
	{
		free(buffer);
		return (NULL);
	}
}