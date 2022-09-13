/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:32:22 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/09/13 21:20:10 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int cnt;
int c;
int ac;
int a;
int i;
int f;

void path_name(char *path, char *p, int i, int len)
{
	int j;

	ft_memcpy(path, p, len);
	j = len;
	if (i / 100)
		path[j++] = '0' + (i / 100);
	if (i / 10)
		path[j++] = '0' + (i % 100) / 10;
	path[j++] = '0' + (i % 10);
	path[j++] = '.';
	path[j++] = 'x';
	path[j++] = 'p';
	path[j++] = 'm';
	path[j++] = 0;
}

int get_img_color(t_img *img, int x, int y)
{
	return (*(int *)(img->addr + (y * img->line_len + x * (img->bpp / 8))));
}

void    render_intro()
{
	char path[100];
	t_img img;
	int x;
	int y;

	path_name(path, "img/intro/", i, 10);
	img.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, path, &x, &y);

	mlx_clear_window(data.mlx.mlx_ptr, data.mlx.win_ptr);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, img.mlx_img, (RES_X - 498) / 2, (RES_Y - 280) / 2);
	mlx_destroy_image(data.mlx.mlx_ptr, img.mlx_img);

	img.mlx_img = mlx_new_image(data.mlx.mlx_ptr, 498, 280);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
	y = -1;
	while (++y < 280)
	{
		x = -1;
		while (++x < 498)
		{
			if (x < 125)
				img_pix_put(&img, x, y, ((x * 2) << 24));
			else if (x > 498 - 125)
				img_pix_put(&img, x, y, (((-x + 498 - 125) * 2) << 24));
			else if (y < 10)
				img_pix_put(&img, x, y, ((y * 20) << 24));
			else if (y > 280 - 10)
				img_pix_put(&img, x, y, (((-y + 280 - 10) * 20) << 24));
			else
				img_pix_put(&img, x, y, (255 << 24));
		}
	}
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, img.mlx_img, (RES_X - 498) / 2, (RES_Y - 280) / 2);
	mlx_destroy_image(data.mlx.mlx_ptr, img.mlx_img);

	i++;
	if (i == 182)
		f = 1;
	i = i * (i < 182);
	if (f)
	{
		img.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/press_to_continue.xpm", &x, &y);
		img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
		y = -1;
		while (++y < 53)
		{
			x = -1;
			while (++x < 439)
				if (data.mouse.on_click && (unsigned int)get_img_color(&img, x, y) != 0xff000000)
					img_pix_put(&img, x, y, 0xffffff);
				else if (!data.mouse.hover && (unsigned int)get_img_color(&img, x, y) != 0xff000000)
					img_pix_put(&img, x, y, get_img_color(&img, x, y) + ((i * 2) << 24));
				else if ((unsigned int)get_img_color(&img, x, y) == 0x000000)
					img_pix_put(&img, x, y, get_img_color(&img, x, y) + 0xac51e38);
		}
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, img.mlx_img, (RES_X - 498) / 2 + 35, (RES_Y + 280) / 2 + 70);
		mlx_destroy_image(data.mlx.mlx_ptr, img.mlx_img);
	}
	if (data.mouse.clicked)
	{
		img.mlx_img = mlx_new_image(data.mlx.mlx_ptr, RES_X, RES_Y);
		img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
		y = -1;
		while (++y < RES_Y)
		{
			x = -1;
			while (++x < RES_X)
					img_pix_put(&img, x, y, 0x000000 + ((255 - data.mouse.clicked * 2) << 24));
		}
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, img.mlx_img, 0, 0);
		mlx_destroy_image(data.mlx.mlx_ptr, img.mlx_img);
		data.mouse.clicked++;
	}
}

int mm;

void    render_intro1()
{
	char    path[100];
	void    *img;
	int     y;
	int     x;

	path_name(path, "img/intro1/", mm++, 11);
	mlx_clear_window(data.mlx.mlx_ptr, data.mlx.win_ptr);
	img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, path, &x, &y);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, img, 0, 0);
	mlx_destroy_image(data.mlx.mlx_ptr, img);
	// usleep(12000);
	// mm++;
	if (mm >= 175)
		data.mode = INTRO2;
}

void    render_intr(t_img *img)
{
	t_img	img2;
	int		x;
	int		y;

	mlx_clear_window(data.mlx.mlx_ptr, data.mlx.win_ptr);
	img2.mlx_img = mlx_new_image(data.mlx.mlx_ptr, RES_X, RES_Y);
	img2.addr = mlx_get_data_addr(img2.mlx_img, &img2.bpp, &img2.line_len, &img2.endian);
	y = -1;
	while (++y < RES_Y)
	{
		x = -1;
		while (++x < RES_X)
				img_pix_put(&img2, x, y, get_img_color(img, x, y) + (((255 - i * 4) * !f + ((i * 4) % 256) * f) << 24));
	}
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, img2.mlx_img, 0, 0);
	mlx_destroy_image(data.mlx.mlx_ptr, img2.mlx_img);
}

void    render_intro2()
{
	if (i < 64 * 2)
		render_intr(&data.intro.int1);
	else
		render_intr(&data.intro.int2);
	i++;
	if (i == 64)
		f = 1;
	if (i == 64 * 2)
		f = 0;
	if (i == 64 * 3)
		data.mode = SETTING;
}

void    setting_render(t_img *img, int x, int y, int type)
{
	int i;
	int j;
	t_img img2;

	img2.mlx_img = mlx_new_image(data.mlx.mlx_ptr, img->x, img->y);
	img2.addr = mlx_get_data_addr(img2.mlx_img, &img2.bpp, &img2.line_len, &img2.endian);
	i = -1;
	while (++i < img->x)
	{
		j = -1;
		while (++j < img->y)
			img_pix_put(&img2, i, j, get_img_color(img, i, j) + 0xffffff * ((unsigned int)get_img_color(img, i, j) != 0xff000000 && data.mouse.on_clk[type]) + 0xff0000 * ((unsigned int)get_img_color(img, i, j) != 0xff000000 && data.mouse.on_hov[type] && !data.mouse.on_clk[type]));
	}
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, img2.mlx_img, x, y);
	mlx_destroy_image(data.mlx.mlx_ptr, img2.mlx_img);
}

void    animate_sett_in()
{
	int a;

	a = data.intro.animate_sett--;
	mlx_clear_window(data.mlx.mlx_ptr, data.mlx.win_ptr);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.img.mlx_img, 0, 0);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t4].mlx_img, RES_X - 142, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t3].mlx_img, RES_X - 142 + 30, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t2].mlx_img, RES_X - 132 + 60, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t1].mlx_img, RES_X - 132 + 90, 30);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.tr2.mlx_img, 0, 0);

	setting_render(&data.intro.cont, (RES_X - data.intro.cont.x) / 2 - a * (a > 0), (RES_Y - data.intro.cont.y) / 2 - RES_Y / 6, 3);
	setting_render(&data.intro.restart, (RES_X - data.intro.restart.x) / 2 + (a + 400) * (a + 400 > 0), (RES_Y - data.intro.restart.y) / 2 - RES_Y / 12, 4);
	setting_render(&data.intro.sett, (RES_X - data.intro.sett.x) / 2 - (a + 800) * (a + 800 > 0), (RES_Y - data.intro.sett.y) / 2, 1);
	setting_render(&data.intro.exit, (RES_X - data.intro.exit.x) / 2 + (a + 1200) * (a + 1200 > 0), (RES_Y - data.intro.exit.y) / 2 + RES_Y / 12, 2);
	data.intro.animate_sett -= 60;
	if (data.intro.animate_sett < -1200)
		data.mode = SETTING2;
}

void    animate_sett_out()
{
	int a;

	a = data.intro.animate_sett++;
	mlx_clear_window(data.mlx.mlx_ptr, data.mlx.win_ptr);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.img.mlx_img, 0, 0);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t4].mlx_img, RES_X - 142, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t3].mlx_img, RES_X - 142 + 30, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t2].mlx_img, RES_X - 132 + 60, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t1].mlx_img, RES_X - 132 + 90, 30);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.tr2.mlx_img, 0, 0);

	setting_render(&data.intro.cont, (RES_X - data.intro.cont.x) / 2 - a * (a > 0), (RES_Y - data.intro.cont.y) / 2 - RES_Y / 6, 3);
	setting_render(&data.intro.restart, (RES_X - data.intro.restart.x) / 2 + (a + 400) * (a + 400 > 0), (RES_Y - data.intro.restart.y) / 2 - RES_Y / 12, 4);
	setting_render(&data.intro.sett, (RES_X - data.intro.sett.x) / 2 - (a + 800) * (a + 800 > 0), (RES_Y - data.intro.sett.y) / 2, 1);
	setting_render(&data.intro.exit, (RES_X - data.intro.exit.x) / 2 + (a + 1200) * (a + 1200 > 0), (RES_Y - data.intro.exit.y) / 2 + RES_Y / 12, 2);
	data.intro.animate_sett += 60;
	if (data.intro.animate_sett > 700)
		data.mode = GAME;
}

void    render_setting2()
{
	mlx_clear_window(data.mlx.mlx_ptr, data.mlx.win_ptr);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.img.mlx_img, 0, 0);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t4].mlx_img, RES_X - 142, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t3].mlx_img, RES_X - 142 + 30, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t2].mlx_img, RES_X - 132 + 60, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t1].mlx_img, RES_X - 132 + 90, 30);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.tr2.mlx_img, 0, 0);

	setting_render(&data.intro.cont, (RES_X - data.intro.cont.x) / 2, (RES_Y - data.intro.cont.y) / 2 - RES_Y / 6, 3);
	setting_render(&data.intro.restart, (RES_X - data.intro.restart.x) / 2, (RES_Y - data.intro.restart.y) / 2 - RES_Y / 12, 4);
	setting_render(&data.intro.sett, (RES_X - data.intro.sett.x) / 2, (RES_Y - data.intro.sett.y) / 2, 1);
	setting_render(&data.intro.exit, (RES_X - data.intro.exit.x) / 2, (RES_Y - data.intro.exit.y) / 2 + RES_Y / 12, 2);
	if (data.mouse.on_clk[3])
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.gun.mlx_img, (RES_X - data.intro.cont.x) / 2 - 40, (RES_Y - data.intro.cont.y) / 2 - RES_Y / 6 + 40);
	else if (data.mouse.on_clk[4])
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.gun.mlx_img, (RES_X - data.intro.restart.x) / 2 - 40, (RES_Y - data.intro.restart.y) / 2 - RES_Y / 12 + 40);
	else if (data.mouse.on_clk[1])
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.gun.mlx_img, (RES_X - data.intro.start.x) / 2 - 70, (RES_Y - data.intro.sett.y) / 2 + 40);
	else if (data.mouse.on_clk[2])
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.gun.mlx_img, (RES_X - data.intro.start.x) / 2 - 40, (RES_Y - data.intro.exit.y) / 2 + RES_Y / 12 + 40);
	else if (data.mouse.on_hov[3])
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.gun.mlx_img, (RES_X - data.intro.cont.x) / 2 - 40, (RES_Y - data.intro.cont.y) / 2 - RES_Y / 6 + 40);
	else if (data.mouse.on_hov[4])
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.gun.mlx_img, (RES_X - data.intro.restart.x) / 2 - 40, (RES_Y - data.intro.restart.y) / 2 - RES_Y / 12 + 40);
	else if (data.mouse.on_hov[1])
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.gun.mlx_img, (RES_X - data.intro.start.x) / 2 - 70, (RES_Y - data.intro.sett.y) / 2 + 40);
	else if (data.mouse.on_hov[2])
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.gun.mlx_img, (RES_X - data.intro.start.x) / 2 - 40, (RES_Y - data.intro.exit.y) / 2 + RES_Y / 12 + 40);
}

void    render_setting()
{
	mlx_clear_window(data.mlx.mlx_ptr, data.mlx.win_ptr);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.int2.mlx_img, 0, 0);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.tr.mlx_img, 0, 0);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.up_logo.mlx_img, RES_X / 3, RES_Y / 12);

	setting_render(&data.intro.start, (RES_X - data.intro.start.x) / 2, (RES_Y - data.intro.start.y) / 2 - RES_Y / 6, 0);
	setting_render(&data.intro.sett, (RES_X - data.intro.sett.x) / 2, (RES_Y - data.intro.sett.y) / 2 - RES_Y / 12, 1);
	setting_render(&data.intro.exit, (RES_X - data.intro.exit.x) / 2, (RES_Y - data.intro.exit.y) / 2, 2);
	if (data.mouse.on_clk[0])
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.gun.mlx_img, (RES_X - data.intro.start.x) / 2 - 40, (RES_Y - data.intro.start.y) / 2 - RES_Y / 6 + 40);
	else if (data.mouse.on_clk[1])
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.gun.mlx_img, (RES_X - data.intro.start.x) / 2 - 70, (RES_Y - data.intro.sett.y) / 2 - RES_Y / 12 + 40);
	else if (data.mouse.on_clk[2])
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.gun.mlx_img, (RES_X - data.intro.start.x) / 2 - 40, (RES_Y - data.intro.exit.y) / 2 + 40);
	else if (data.mouse.on_hov[0])
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.gun.mlx_img, (RES_X - data.intro.start.x) / 2 - 40, (RES_Y - data.intro.start.y) / 2 - RES_Y / 6 + 40);
	else if (data.mouse.on_hov[1])
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.gun.mlx_img, (RES_X - data.intro.start.x) / 2 - 70, (RES_Y - data.intro.sett.y) / 2 - RES_Y / 12 + 40);
	else if (data.mouse.on_hov[2])
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.gun.mlx_img, (RES_X - data.intro.start.x) / 2 - 40, (RES_Y - data.intro.exit.y) / 2 + 40);
}

void    paint_img2(t_img *img, int x_w, int y_w, int color)
{
	t_img img2;
	int x;
	int y;

	img2.mlx_img = mlx_new_image(data.mlx.mlx_ptr, img->x, img->y);
	img2.addr = mlx_get_data_addr(img2.mlx_img, &img2.bpp, &img2.line_len, &img2.endian);
	y = -1;
	while (++y < img->y)
	{
		x = -1;
		while (++x < img->x)
			if ((unsigned int)get_img_color(img, x, y) != 0xff000000 && color >= 2)
				img_pix_put(&img2, x, y, 0xffffff * (mm % 200 < 100) + 0xff0000 * (mm % 200 >= 100));
			else if ((unsigned int)get_img_color(img, x, y) != 0xff000000 && color)
				img_pix_put(&img2, x, y, 0xff0000);
			else
				img_pix_put(&img2, x, y, get_img_color(img, x, y));
	}
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, img2.mlx_img, x_w, y_w);
	mlx_destroy_image(data.mlx.mlx_ptr, img2.mlx_img);
	mm++;
}

void    render_control()
{
	mlx_clear_window(data.mlx.mlx_ptr, data.mlx.win_ptr);
	if (!data.mouse.sett2)
	{
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.int2.mlx_img, 0, 0);
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.tr.mlx_img, 0, 0);
	}
	else
	{
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.img.mlx_img, 0, 0);
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t4].mlx_img, RES_X - 142, 30);
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t3].mlx_img, RES_X - 142 + 30, 30);
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t2].mlx_img, RES_X - 132 + 60, 30);
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t1].mlx_img, RES_X - 132 + 90, 30);
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.tr2.mlx_img, 0, 0);
	}
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.guide[0].mlx_img, 100, 120);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.guide[data.intro.g_k[0] + 1].mlx_img, 450, 130);
	paint_img2(&data.intro.guide[3], 400, 120, data.intro.on_hov[3]);
	paint_img2(&data.intro.guide[4], 574, 120, data.intro.on_hov[4]);
	
	// mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.vol_icon[(data.intro.volume > 99) + (data.intro.volume == 200) + !!(data.intro.volume % 100)].mlx_img, 825, 115);
	// mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.vol[0].mlx_img, 900, 135);
	// mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.vol[1].mlx_img, 900 + data.intro.volume - 12, 120);
	
	// mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.light_icon[1].mlx_img, 1200, 115);
	// mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.lgt[0].mlx_img, 1275, 135);
	// mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.lgt[1].mlx_img, 1275 + data.intro.light - 12, 120);
	
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.vol_icon[(data.intro.volume > 99) + (data.intro.volume == 200) + !!(data.intro.volume % 100)].mlx_img, 1025, 70);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.vol[0].mlx_img, 1100, 90);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.vol[1].mlx_img, 1100 + data.intro.volume - 12, 75);
	
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.light_icon[1].mlx_img, 1025, 165);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.lgt[0].mlx_img, 1100, 185);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.lgt[1].mlx_img, 1100 + data.intro.light - 12, 170);
	
	paint_img2(&data.intro.guide[5], 100, 280, data.intro.on_clk[5] + data.intro.on_hov[5]);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.keys[data.intro.g_k[1]], 450, 260 - 20);
	
	paint_img2(&data.intro.guide[6], 800, 280, data.intro.on_clk[6] + data.intro.on_hov[6]);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.keys[data.intro.g_k[2]], 800 + 350, 280 - 20);

	paint_img2(&data.intro.guide[7], 100, 400, data.intro.on_clk[7] + data.intro.on_hov[7]);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.keys[data.intro.g_k[3]], 450, 400 - 20);
	
	paint_img2(&data.intro.guide[8], 800, 400, data.intro.on_clk[8] + data.intro.on_hov[8]);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.keys[data.intro.g_k[4]], 800 + 350, 400 - 20);

	paint_img2(&data.intro.guide[9], 100, 520, data.intro.on_clk[9] + data.intro.on_hov[9]);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.keys[data.intro.g_k[5]], 450, 520 - 25);
	
	paint_img2(&data.intro.guide[10], 800, 520, data.intro.on_clk[10] + data.intro.on_hov[10]);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.keys[data.intro.g_k[6]], 800 + 350, 520 - 25);
	
	paint_img2(&data.intro.guide[11], 100, 640, data.intro.on_clk[11] + data.intro.on_hov[11]);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.keys[data.intro.g_k[7]], 450, 640 - 25);
	
	paint_img2(&data.intro.guide[12], 800, 640, data.intro.on_clk[12] + data.intro.on_hov[12]);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.keys[data.intro.g_k[8]], 800 + 350, 640 - 25);
	
	paint_img2(&data.intro.guide[13], 100, 760, data.intro.on_clk[13] + data.intro.on_hov[13]);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.keys[data.intro.g_k[9]], 450, 760 - 25);
	
	paint_img2(&data.intro.guide[14], 800, 760, data.intro.on_clk[14] + data.intro.on_hov[14]);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.keys[data.intro.g_k[10]], 800 + 350, 760 - 25);
	
	paint_img2(&data.intro.guide[15], 100, 880, data.intro.on_clk[15] + data.intro.on_hov[15]);
	mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.keys[data.intro.g_k[11]], 450, 880 - 25);

	setting_render(&data.intro.back, RES_X / 2 - 300, RES_Y - 100, 5);
	setting_render(&data.intro.reset, RES_X / 2, RES_Y - 100, 6);
}

int get_lava_color(int x, int y)
{
    return (*(int *)(data.blood_hit.addr + (y * data.blood_hit.line_len + x * (data.blood_hit.bpp / 8))));
}
void	paint_hit_blood()
{
	int i;
	int j;

	i = -1;
	while (++i < RES_Y)
	{
		j = -1;
		while (++j < RES_X)
			if ((unsigned int)get_lava_color(j, i) != 0xff000000)
				img_pix_put(&data.blood_hit2, j, i, get_lava_color(j, i) + ((((data.bld * !(((data.bld) / 25) % 2)) % 25 + ((25 - data.bld % 25) * (((data.bld) / 25) % 2)) % 25) * 3 + 175) << 24));
	}
}

void    render_game()
{
	if (cnt == 10)
	{
		// usleep(20000);
		cnt = 0;
		if (data.keys[data.intro.g_k[1]] && !data.keys[data.intro.g_k[9]] && (!data.fov.jumping && data.dir.ph >= 0.5))
			data.c += 3 * (!!((data.mv / 5) % 2) - !((data.mv / 5) % 2)),
			data.g_mv -= 3 * (!!((data.mv / 5) % 2) - !((data.mv++ / 5) % 2)),
			up();
		if (data.keys[data.intro.g_k[2]] && !data.keys[data.intro.g_k[9]])
			data.c += 3 * (!!((data.mv / 5) % 2) - !((data.mv / 5) % 2)),
			data.g_mv -= 3 * (!!((data.mv / 5) % 2) - !((data.mv++ / 5) % 2)),
			down();
		if (data.gun[data.objects.w].bullet && data.keys[data.intro.g_k[8]] && data.aim < 10)
		{
			if (data.objects.w == 17)
				data.gun[data.objects.w].frame = 53 + data.aim;
			data.aim++;
		}
		else if ((!data.keys[data.intro.g_k[8]] || !data.gun[data.objects.w].bullet) && data.aim > 0)
		{
			if (data.objects.w == 17)
				data.gun[data.objects.w].frame = 53 + data.aim;
			if (data.objects.w == 17 && data.aim == 1)
				data.gun[data.objects.w].frame = 15;
			if (data.zoom > 0)
				data.zoom--;
			else
				data.aim--;
		}
		if (data.objects.w == 4 && data.use_gun++ > 100)
		{
			data.gun[data.objects.w].frame++;
			if (data.gun[data.objects.w].frame < data.gun[data.objects.w].f_reload)
				data.gun[data.objects.w].frame = data.gun[data.objects.w].f_reload;
			if (data.gun[data.objects.w].frame == 51)
				data.gun[data.objects.w].frame = 0,
				data.use_gun = 0;
		}
		else if (data.objects.w == 17 && (data.gun[data.objects.w].bullet || data.gun[data.objects.w].case_bullet) && (data.keys[data.intro.g_k[7]] || data.gun[data.objects.w].frame || !data.gun[data.objects.w].bullet))
		{
			if (data.aim && data.objects.w == 17)
			{
				if (data.keys[data.intro.g_k[7]] || data.gun[data.objects.w].frame > 63)
					data.gun[data.objects.w].frame++;
				if (data.gun[data.objects.w].frame > 80 && data.gun[data.objects.w].bullet)
					data.gun[data.objects.w].frame = 63,
					data.gun[data.objects.w].bullet--;
			}
			else
			{
				data.gun[data.objects.w].frame++;
				if (!data.gun[data.objects.w].bullet && data.gun[data.objects.w].frame < data.gun[data.objects.w].f_shoot)
					data.gun[data.objects.w].frame = data.gun[data.objects.w].f_shoot;
				if (data.gun[data.objects.w].frame > data.gun[data.objects.w].f_shoot && data.gun[data.objects.w].bullet)
					data.gun[data.objects.w].frame = 0,
					data.gun[data.objects.w].bullet--;
				if (data.gun[data.objects.w].frame > data.gun[data.objects.w].f_reload && !data.gun[data.objects.w].bullet)
					data.gun[data.objects.w].frame = 0,
					data.gun[data.objects.w].case_bullet--,
					data.gun[data.objects.w].bullet = 12;
				data.use_gun = 0;
				if (data.gun[data.objects.w].frame < 2 && data.objects.w == 13 && data.keys[data.intro.g_k[7]] && (data.gun[data.objects.w].bullet || data.gun[data.objects.w].case_bullet))
					data.gun[data.objects.w].frame = 2;
			}
		}
		else if (data.objects.w != 17 && (data.gun[data.objects.w].bullet || data.gun[data.objects.w].case_bullet) && (data.keys[data.intro.g_k[7]] || data.gun[data.objects.w].frame || !data.gun[data.objects.w].bullet))
		{
			data.gun[data.objects.w].frame++;
			
			if (!data.gun[data.objects.w].bullet && data.gun[data.objects.w].frame < data.gun[data.objects.w].f_shoot)
				data.gun[data.objects.w].frame = data.gun[data.objects.w].f_shoot;
			if (data.gun[data.objects.w].frame > data.gun[data.objects.w].f_shoot && data.gun[data.objects.w].bullet)
				data.gun[data.objects.w].frame = 0,
				data.gun[data.objects.w].bullet--;
			if (data.gun[data.objects.w].frame > data.gun[data.objects.w].f_reload && !data.gun[data.objects.w].bullet)
				data.gun[data.objects.w].frame = 0,
				data.gun[data.objects.w].case_bullet--,
				data.gun[data.objects.w].bullet = 12;
    		data.use_gun = 0;
			if (data.gun[data.objects.w].frame < 2 && data.objects.w == 13 && data.keys[data.intro.g_k[7]] && (data.gun[data.objects.w].bullet || data.gun[data.objects.w].case_bullet))
				data.gun[data.objects.w].frame = 2;
		}
		else if (data.objects.w == 9 && (data.keys[data.intro.g_k[7]] || data.gun[data.objects.w].frame))
		{
			data.gun[data.objects.w].frame++;
			if (data.gun[data.objects.w].frame > data.gun[data.objects.w].f_shoot)
				data.gun[data.objects.w].frame = 0;
		}

		if (!data.intro.g_k[0])
		{
			if (data.keys[UP])
				data.c -= 25 * (-data.c + 25 < RES_Y - 200);
			if (data.keys[DOWN])
				data.c += 25 * (data.c + 25 < RES_Y - 200);
			if (data.keys[LEFT])
				left_angle();
			if (data.keys[RIGHT])
				right_angle();
		}
		if (data.keys[data.intro.g_k[3]])
			data.c += 3 * (!!((data.mv / 5) % 2) - !((data.mv / 5) % 2)),
			data.g_mv -= 3 * (!!((data.mv / 5) % 2) - !((data.mv++ / 5) % 2)),
			left();
		if (data.keys[data.intro.g_k[4]])
			data.c += 3 * (!!((data.mv / 5) % 2) - !((data.mv / 5) % 2)),
			data.g_mv -= 3 * (!!((data.mv / 5) % 2) - !((data.mv++ / 5) % 2)),
			right();
		if (data.fov.jumping && data.dir.ph > 0.2)
			data.speed = -1,
			data.dir.ph -= 0.07,
			up();
		else if (ac >= 2)
			data.fov.jumping = 0;
		else if (data.fov.jumping)
			ac++,
			up();
		if (!data.fov.jumping && data.dir.ph < 0.5)
			ac = 0,
			data.speed = -1,
			data.dir.ph += 0.07,
			up();

		if (!data.sound.breath && !data.keys[data.intro.g_k[2]] && data.keys[data.intro.g_k[9]] && abs(data.c) < 10 && (!data.fov.jumping && data.dir.ph >= 0.5))
			c++,
			data.speed = 3,
			data.c = (ac++ % 4) * (c % 4 - !(c % 4)),
			up();
		else if (!data.sound.breath && !data.keys[data.intro.g_k[2]] && data.keys[data.intro.g_k[9]] && (!data.fov.jumping && data.dir.ph >= 0.5))
			c++,
			data.speed = 3,
			data.c += (15 * (data.c < 0) - 15 * (data.c > 0)) * !!(c % 3) + (3 * (data.c > 0) - 3 * (data.c < 0)) * !(c % 3),
			up();

		if (data.sound.breath && abs(data.c) < 40)
			c++,
			data.c = 3.0 / 20.0 * (ac++ % 20) * (c % 20 - !(c % 20));
		else if (data.sound.breath)
			c++,
			data.c += 3.0 / 18.0 * (15 * (data.c < 0) - 15 * (data.c > 0)) * !!(c % 18) + (18 * (data.c > 0) - 18 * (data.c < 0)) * !(c % 18);

		if (data.fov.crouching && data.dir.ph < 0.8)
			data.dir.ph += 0.05;
		if (!data.fov.crouching && data.dir.ph > 0.5)
			data.dir.ph -= 0.05;
		
		data.door.is_op = 1;
		if (data.keys[data.intro.g_k[6]] || data.keys[999 - SCROLL_UP] || data.keys[999 - SCROLL_DOWN] || data.keys[data.intro.g_k[9]] || data.keys[UP] || data.keys[data.intro.g_k[1]] || data.keys[DOWN] || data.keys[data.intro.g_k[2]] || data.keys[LEFT] || data.keys[RIGHT] || data.keys[data.intro.g_k[3]] || data.keys[data.intro.g_k[4]])
			set_char_to_win(),
			mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.lt.mlx_img, 0, 0);
		data.speed = -3 * data.fov.crouching;
		if (data.door.map[(data.dir.y + 17) / 50][(data.dir.x + 17) / 50] == 'E' && data.objects.health
			&& data.map[(int)data.dir.y / 50][(int)data.dir.x / 50] == '0'
			&& (data.map[(int)data.dir.y / 50 - 1][(int)data.dir.x / 50] != data.map[(int)data.dir.y / 50 + 1][(int)data.dir.x / 50]
			|| data.map[(int)data.dir.y / 50][(int)data.dir.x / 50 - 1] != data.map[(int)data.dir.y / 50][(int)data.dir.x / 50 + 1])
			&& data.dir.ph >= 0.5)
			paint_hit_blood(),
			mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.blood_hit2.mlx_img, 0, 0),
			data.bld += !(data.light % 5),
			data.bld = data.bld * (data.bld != 50),
			data.objects.health -= !(data.light % 5),
			data.sound.hit = !(data.objects.health % 3);

			if ((!data.keys[data.intro.g_k[9]] || (data.keys[data.intro.g_k[9]] && data.sound.breath)) && data.objects.breath < 100)
				data.objects.breath += !(data.light % 5);
		data.enemy[0].frm++;
		if (data.enemy[0].frm >= data.motion[0].frame)
			data.enemy[0].frm = 0;
	}
	cnt++;
	if (data.door.op > 0 && data.door.is_op)
		data.door.op -= cnt / 7;
	if (data.door.op < 45 && !data.door.is_op)
		data.door.op += cnt / 7;
	if (!data.mouse.sett2)
		data.mouse.sett2 = 1;
}

void    render_map()
{
	usleep(1000);
	if (data.intro.up && data.intro.map < 75 && !data.intro.map++)
		set_char_to_win();
	if (!data.intro.up)
		data.intro.map--;
	if (!data.intro.up && !data.intro.map)
		data.mode = GAME;
	mlx_clear_window(data.mlx.mlx_ptr, data.mlx.win_ptr);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.img.mlx_img, 0, 0);

    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t4].mlx_img, RES_X - 142, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t3].mlx_img, RES_X - 142 + 30, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t2].mlx_img, RES_X - 132 + 60, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t1].mlx_img, RES_X - 132 + 90, 30);

	if (data.intro.map > 25)
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.tr2.mlx_img, 0, 0);
	else
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.lt.mlx_img, 0, 0);
	map_appending();
	if (data.intro.map > 25)
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.mouse.img, data.mouse.x, data.mouse.y);
}

int rendering(void *d)
{
	d = NULL;
	if (data.mouse.clicked == 128)
		i = 0,
		f = 0,
		data.mouse.clicked = 0,
		data.mode = INTRO2;
	if (data.mode == INTRO)
		render_intro();
	if (data.mode == INTRO1)
		render_intro1();
	if (data.mode == INTRO2)
		render_intro2();
	if (data.mode == SETTING)
		render_setting();
	if (data.mode == SETTING2)
		render_setting2();
	if (data.mode == ANIMATE_SETT2_IN)
		animate_sett_in();
	if (data.mode == ANIMATE_SETT2_OUT)
		animate_sett_out();
	if (data.mode == S_CONTROL)
		render_control();
	if (data.mode == G_MAP)
		render_map();
	if (data.mode == GAME)
		data.intro.map = 0,
		render_game();
	else if (data.mouse.x != 10000 && data.mode != G_MAP && data.mode != GAME)
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.mouse.img, data.mouse.x, data.mouse.y),
		mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.intro.lt.mlx_img, 0, 0);
	return (0);
}