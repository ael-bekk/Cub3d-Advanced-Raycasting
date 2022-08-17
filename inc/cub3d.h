/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 12:41:47 by mel-hada          #+#    #+#             */
/*   Updated: 2022/08/16 15:03:15 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include <pthread.h>
# include "../lib/mlx.h"
# include <math.h>
# include "defines.h"
# include "structs.h"
#include <x86intrin.h>

t_data data;

/* utils */
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_strlen(const char *str);
int     ft_strlen2(char **str);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_substr(char const *s, int start, int len);
char	*ft_strchr(const char *str, int c);
char    *get_next_line(int fd);
int	    ft_isdigit(int c);
int	    ft_atoi(const char *str);
void    init_args(t_map **map);
void	error(char *str,int m);
int		ft_close(void);

t_map	*ft_lst_last(t_map *lst);
void	ft_lst_del_one(t_map *lst, void (*del)(void*));
void	ft_lst_clear(t_map **lst, void (*del)(void*));
void	ft_lst_add_back(t_map **lst, t_map *new);
void	ft_lst_add_front(t_map **lst, t_map *new);
t_map	*ft_lst_new(void *content);

void    parsing( t_map *map);
int     ft_str_isdigit(char *s);
int     ft_lst_size(t_map *lst);
char	*ft_str_trim(char const *s1, char const *set);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void    check_elements();
void    replace_tab(char *s);
void    check_file();
int     check_all_spaces(char *s);
void    set_minimap();
void    set_char_to_win();

void    up();
void    down();
void    left_angle();
void    right_angle();
void    left();
void    right();

int		key_press(int key, void *d);
void    set_rays();
void    cast_to_3d(int i, double *cord);
void	img_pix_put(t_img *img, int x, int y, int color);
void    before();
int		key_release(int key, void *data);
int		rendering(void *data);
int		mouse_press(int key, int x, int y, void *w);
int		mouse_move(int x, int y, void *w);
int		mouse_release(int key, int x, int y, void *w);
void    *time_count(void *d);
int		get_img_color(t_img *img, int x, int y);
void    *check_sound(void *d);
int     key_not_in_use(int key);
void    paint_color(t_img *img, int color, int x_s, int y_s);
void    set_volume();
void    init_keys();
void    map_appending();
int get_color(int x, int y);

#endif