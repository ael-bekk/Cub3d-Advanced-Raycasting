/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:48:48 by mel-hada          #+#    #+#             */
/*   Updated: 2022/08/08 12:31:15 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_strlen(const char *str)
{
	int	len;

	if(!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_strlen2(char **str)
{
	int	len;

	if(!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}
