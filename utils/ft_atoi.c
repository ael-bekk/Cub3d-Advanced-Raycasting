/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 09:34:16 by mel-hada          #+#    #+#             */
/*   Updated: 2022/08/26 18:42:12 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	num = 0;
	i = 0;
	sign = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	num = num * sign;
	return (num);
}

void	*ft_memset(void *b, int c, size_t len)
{
	while (len--)
		((unsigned char *)b)[len] = (unsigned char)c;
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}

static int	ft_size_nb(int n)
{
	int	i;

	i = 1 + !(n) + (n < 0);
	while (n && i++)
		n /= 10;
	return (i);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				i;
	unsigned int	u;

	i = ft_size_nb(n);
	res = (char *)ft_calloc(i, 1);
	if (!res)
		return (NULL);
	res[0] = '-';
	res[--i] = '\0';
	u = -n * (n < 0) + n * !(n < 0);
	if (!u)
		res[i - 1] = '0';
	while (u)
	{
		res[--i] = (u % 10) + '0';
		u /= 10;
	}
	return (res);
}