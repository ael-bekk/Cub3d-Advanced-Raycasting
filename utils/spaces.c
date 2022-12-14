/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:38:02 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/08/08 12:31:32 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    replace_tab(char *s)
{
    while (s && *s)
    {
        if (*s == '\t')
            *s = ' ';
        s++;
    }
}

int check_all_spaces(char *s)
{
    if (s && !*s)
        return (0);
    while (s && *s && *s == ' ')
        s++;
    return (!*s);
}