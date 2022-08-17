/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:38:15 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/08/08 12:38:15 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:28:49 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/08/08 12:31:22 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	ft_search(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}

char	*ft_str_trim(char const *s1, char const *set)
{
	int		sl;
	char	*s;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	s = (char *)s1;
	while (*s && ft_search((char *)set, *s))
		s++;
	sl = ft_strlen(s);
	while (sl && ft_search((char *)set, s[sl - 1]))
		sl--;
	res = ft_substr(s, 0, sl);
	if (!res)
		return (NULL);
	return (res);
}