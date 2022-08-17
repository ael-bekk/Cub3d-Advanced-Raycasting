/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:01:01 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/08/17 20:31:01 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*************************************************************************/
/*========                   needed by parsing                   ========*/
/*************************************************************************/
typedef struct s_map
{
	char			*content;
	struct s_map	*next;
}   t_map;

/*************************************************************************/
/*========                          color                        ========*/
/*************************************************************************/
typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}   t_rgb;

/*************************************************************************/
/*========                        game mode                      ========*/
/*************************************************************************/
typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			x;
	int			y;
	int			bpp; /* bits per pixel */
	int			line_len;
	int			endian;
}	t_img;

/************************************************************************/
/*========              player position / direction             ========*/
/************************************************************************/
typedef struct s_dir
{
	double		ph;
	int			px;
	int			py;
	int			s;
	int			x;
	int			y;
	double		angle;
	void		*pl[16];
}   t_dir;

/*************************************************************************/
/*========   mlx instance && window instance && character imgs   ========*/
/*************************************************************************/
typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		floor;
	t_img		space;
	t_img		wall;
	void		*none;
	void		*player;
	void		*cadre1;
	void		*cadre2;
}   t_mlx;

/*************************************************************************/
/*========        player objects [weapon / time / health]        ========*/
/*************************************************************************/
typedef struct s_p_objects
{
	int			health;
	int			t1;
	int			t2;
	int			t3;
	int			t4;
	int			w;
	int			ammo[7];
	t_img		weapon[7];
	t_img		time[10];
}	t_p_objects;

/*************************************************************************/
/*========                mouse [events/ position]               ========*/
/*************************************************************************/
typedef struct s_mouse
{
	int			hover;
	int			on_click;
	int			clicked;
	int			show;
	int			x;
	int			y;
	double		on;
	void		*img;
	int			on_clk[7];
	int			on_hov[7];
}	t_mouse;

/*************************************************************************/
/*========                      camera vue                       ========*/
/*************************************************************************/
typedef struct s_fov
{
	int			jumping;
	int			crouching;
}	t_fov;

/*************************************************************************/
/*========                      intro imgs                       ========*/
/*************************************************************************/
typedef struct s_intro
{
	int			fov;
	int			map;
	int			up;
	t_img		int1;
	t_img		int2;
	t_img		start;
	t_img		restart;
	t_img		cont;
	t_img		sett;
	t_img		exit;
	t_img		back;
	t_img		reset;
	t_img		gun;
	t_img		tr;
	t_img		tr2;
	// t_img		f_map;
	t_img		up_logo;
	t_img		down_logo;
	t_img		guide[16];
	void		*keys[1000];
	int			g_k[12];
	int			on_hov[17];
	int			on_clk[17];
	int			volume;
	t_img		vol_icon[3];
	t_img		vol[2];
	int			vol_click;

	int			light;
	t_img		light_icon[2];
	t_img		lgt[2];
	t_img		lt;
	int			lgt_click;
}	t_intro;

/*************************************************************************/
/*========                         sound                         ========*/
/*************************************************************************/
typedef struct s_sound
{
	int			click;
	int			hover;
}	t_sound;

/*************************************************************************/
/*========                        textures                       ========*/
/*************************************************************************/
typedef struct s_textures
{
	t_img	floor[]
}	t_textures;

/*************************************************************************/
/*========                     global struct                     ========*/
/*************************************************************************/
typedef struct s_data
{
	int			mode;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*tf;
	char		*tc;
	t_img		n;
	t_img		s;
	t_img		w;
	t_img		e;
	t_img		img_f;
	t_img		img_c;
	int			keys[1000];
	int			height;
	int			width;
	int			c;
	int			speed;
	double		rays[15001];
	int			color[15001][2];
	char		**map;
	t_mlx		mlx;
	t_rgb		floor;
	t_rgb		ceil;
	t_dir		dir;
	t_img		img;
	t_p_objects objects;
	t_mouse		mouse;
	t_fov		fov;
	t_intro		intro;
	t_sound		sound;
	double		g;
}   t_data;

#endif