/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_minimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:16:54 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/09/09 18:54:10 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    variant_calculate_d(double *cord, double decrease, int angl)
{
    int v;

    v = 0;
    while (data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl])/50][(int)cord[0]/50] == '0'
        && data.map[(int)cord[1] /50][(int)(cord[0] + decrease * data.angles.r_cos[angl])/50] == '0'
        && data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl])/50][(int)(cord[0] + decrease * data.angles.r_cos[angl])/50] == '0')
    {
        cord[0] += decrease * data.angles.r_cos[angl];
        cord[1] += decrease * data.angles.r_sin[angl];
        v = 1;
    }
    if (v)
    {
        cord[0] -= decrease * data.angles.r_cos[angl];
        cord[1] -= decrease * data.angles.r_sin[angl];
    }
}

void    variant_calculate(double *cord, double decrease, int angl)
{
    int v;

    v = 0;
    while (data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl])/50][(int)cord[0]/50] != '1'
        && data.map[(int)cord[1] /50][(int)(cord[0] + decrease * data.angles.r_cos[angl])/50] != '1'
        && data.map[(int)(cord[1] + decrease * data.angles.r_sin[angl])/50][(int)(cord[0] + decrease * data.angles.r_cos[angl])/50] != '1')
    {
        cord[0] += decrease * data.angles.r_cos[angl];
        cord[1] += decrease * data.angles.r_sin[angl];
        v = 1;
    }
    if (v)
    {
        cord[0] -= decrease * data.angles.r_cos[angl];
        cord[1] -= decrease * data.angles.r_sin[angl];
    }
}

void    init_angles()
{
    double  r;
    double  angl;
    int     i;

    i = -1;
    r = -30;
    while (++i < RES_X)
    {
        angl = data.dir.angle + r;
        data.angles.r_cos[i] = cos(angl * M_PI / 180);
        data.angles.r_sin[i] = sin(angl * M_PI / 180);
        data.angles.r_res_cos[i] = cos(r * M_PI / 180);
        r += 0.04;
    }
    data.angles.pl_cos = cos(data.dir.angle * M_PI / 180);
    data.angles.pl_sin = sin(data.dir.angle * M_PI / 180);
    data.angles.pl_cos_plus_90 = cos((data.dir.angle + 90) * M_PI / 180);
    data.angles.pl_sin_plus_90 = sin((data.dir.angle + 90) * M_PI / 180);
    data.angles.cte_tan = tan(30 * M_PI / 180);
}

void    set_rays()
{
    int i;
    double cord[2];

    i = 0;
    while (i < RES_X)
    {
        data.color[i][0] = 0;
        cord[0] = data.dir.x + 17;
        cord[1] = data.dir.y + 17;
        data.indx = i;
        variant_calculate_d(cord, 45, i);
        variant_calculate_d(cord, 20, i);
        variant_calculate_d(cord, 10, i);
        variant_calculate_d(cord, 1, i);
        variant_calculate_d(cord, 0.1, i);
        data.door.hit_wall = 0;
        if (data.map[(int)(cord[1] + data.angles.r_sin[i])/50][(int)cord[0]/50] == 'H' || data.map[(int)cord[1]/50][(int)(cord[0] + data.angles.r_cos[i])/50] == 'H')
        {
            data.door.cord[0] = (int)cord[0];
            data.door.cord[1] = (int)cord[1];
            data.color[i][0] = 1;
            data.door.is_op = !(fabs(cord[0] - data.dir.x - 17) < 90 && fabs(cord[1] - data.dir.y - 17) < 90);
            if (data.map[(int)cord[1]/50][(int)(cord[0] + data.angles.r_cos[i])/50] == 'H' && cord[0] + data.angles.r_cos[i] > cord[0])
                data.door.color[i][1] = (int)cord[1];
            else if (data.map[(int)cord[1]/50][(int)(cord[0] + data.angles.r_cos[i])/50] == 'H' && cord[0] + data.angles.r_cos[i] < cord[0])
                data.door.color[i][1] = (int)cord[1];
            else if (data.map[(int)(cord[1] + data.angles.r_sin[i])/50][(int)cord[0]/50] == 'H' && cord[1] + data.angles.r_sin[i] > cord[1])
                data.door.color[i][1] = (int)cord[0];
            else if (data.map[(int)(cord[1] + data.angles.r_sin[i])/50][(int)cord[0]/50] == 'H' && cord[1] + data.angles.r_sin[i] < cord[1])
                data.door.color[i][1] = (int)cord[0];
            data.door.rays[i] = sqrt((cord[0] - (double)data.dir.x - 17)*(cord[0] - (double)data.dir.x - 17) + (cord[1] - (double)data.dir.y - 17)*(cord[1] - (double)data.dir.y - 17)) * data.angles.r_res_cos[i];
            variant_calculate(cord, 45, i);
            variant_calculate(cord, 20, i);
            variant_calculate(cord, 10, i);
            variant_calculate(cord, 1, i);
            variant_calculate(cord, 0.1, i);
            data.door.hit_wall = data.map[(int)(cord[1])/50][(int)(cord[0])/50] == 'H';
        }
        if (data.map[(int)cord[1]/50][(int)(cord[0] + data.angles.r_cos[i])/50] == '1' && cord[0] + data.angles.r_cos[i] > cord[0])
            data.color[i][1] = (int)cord[1];
        else if (data.map[(int)cord[1]/50][(int)(cord[0] + data.angles.r_cos[i])/50] == '1' && cord[0] + data.angles.r_cos[i] < cord[0])
            data.color[i][1] = (int)cord[1];
        else if (data.map[(int)(cord[1] + data.angles.r_sin[i])/50][(int)cord[0]/50] == '1' && cord[1] + data.angles.r_sin[i] > cord[1])
            data.color[i][1] = (int)cord[0];
        else if (data.map[(int)(cord[1] + data.angles.r_sin[i])/50][(int)cord[0]/50] == '1' && cord[1] + data.angles.r_sin[i] < cord[1])
            data.color[i][1] = (int)cord[0];

        data.rays[i] = sqrt((cord[0] - (double)data.dir.x - 17)*(cord[0] - (double)data.dir.x - 17) + (cord[1] - (double)data.dir.y - 17)*(cord[1] - (double)data.dir.y - 17)) * data.angles.r_res_cos[i];
        i++;
        data.cord = cord;
        data.design = data.door.map[(int)(cord[1] - data.angles.r_sin[i])/50][(int)(cord[0] - data.angles.r_cos[i])/50];
        if (i <= RES_X)
            cast_to_3d(i - 1);
    }
    data.light++;
    if (data.light >= 600)
        data.light = 0;
}

void    set_char_to_win()
{
    mlx_clear_window(data.mlx.mlx_ptr, data.mlx.win_ptr);
    set_rays();
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.img.mlx_img, 0, 0);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.mlx.player, MX, MY);


    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t4].mlx_img, RES_X - 142, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t3].mlx_img, RES_X - 142 + 30, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t2].mlx_img, RES_X - 132 + 60, 30);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.objects.time[data.objects.t1].mlx_img, RES_X - 132 + 90, 30);

    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.nums[data.gun[data.objects.w].case_bullet / 10].mlx_img, RES_X - (242 + 17 * 2), 175);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.nums[data.gun[data.objects.w].case_bullet % 10].mlx_img, RES_X - (242 + 17), 175);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.sl, RES_X - 242, 175);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.nums[data.gun[data.objects.w].bullet / 10].mlx_img, RES_X - (242 - 17), 175);
    mlx_put_image_to_window(data.mlx.mlx_ptr, data.mlx.win_ptr, data.nums[data.gun[data.objects.w].bullet % 10].mlx_img, RES_X - (242 - 17 * 2), 175);
}

void    paint_img(t_img *img, char *path, int res_x, int res_y)
{
    t_img img2;
    int x;
    int y;

    img2.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, path, &img2.x, &img2.y);
    img2.addr = mlx_get_data_addr(img2.mlx_img, &img2.bpp, &img2.line_len, &img2.endian);
    y = -1;
    while (++y < res_y)
    {
        x = -1;
        while (++x < res_x)
                img_pix_put(img, x, y, get_img_color(&img2, (img2.x * x) / res_x, (img2.y * y) / res_y));
    }
    mlx_destroy_image(data.mlx.mlx_ptr, img2.mlx_img);
}

void    paint_color(t_img *img, int color, int x_s, int y_s)
{
    int x;
    int y;

    y = -1;
    while (++y < y_s)
    {
        x = -1;
        while (++x < x_s)
                img_pix_put(img, x, y, color);
    }
}

void    init_img_control()
{
    int i;
    int arr[26];
    char    path[50];
    int tmp;

    ft_memcpy(path, "img/keys/?.xpm", 15);
    arr[0] = KEY_A;
    arr[1] = KEY_B;
    arr[2] = KEY_C;
    arr[3] = KEY_D;
    arr[4] = KEY_E;
    arr[5] = KEY_F;
    arr[6] = KEY_G;
    arr[7] = KEY_H;
    arr[8] = KEY_I;
    arr[9] = KEY_J;
    arr[10] = KEY_K;
    arr[11] = KEY_L;
    arr[12] = KEY_N;
    arr[13] = KEY_M;
    arr[14] = KEY_O;
    arr[15] = KEY_P;
    arr[16] = KEY_Q;
    arr[17] = KEY_R;
    arr[18] = KEY_S;
    arr[19] = KEY_T;
    arr[20] = KEY_U;
    arr[21] = KEY_V;
    arr[22] = KEY_W;
    arr[23] = KEY_X;
    arr[24] = KEY_Y;
    arr[25] = KEY_Z;
    i = -1;
    while (++i < 26)
    {
        path[9] = 'A' + i;
        data.intro.keys[arr[i]] = mlx_xpm_file_to_image(data.mlx.mlx_ptr, path, &tmp, &tmp);
    }

    data.intro.keys[UP] = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/keys/up.xpm", &tmp, &tmp);
    data.intro.keys[DOWN] = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/keys/down.xpm", &tmp, &tmp);
    data.intro.keys[LEFT] = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/keys/left.xpm", &tmp, &tmp);
    data.intro.keys[RIGHT] = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/keys/right.xpm", &tmp, &tmp);
    data.intro.keys[TAB] = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/keys/tab.xpm", &tmp, &tmp);
    data.intro.keys[SHIFT] = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/keys/shift.xpm", &tmp, &tmp);
    data.intro.keys[CAPS] = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/keys/caps.xpm", &tmp, &tmp);
    data.intro.keys[SPACE] = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/keys/space.xpm", &tmp, &tmp);
    data.intro.keys[ENTER] = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/keys/enter.xpm", &tmp, &tmp);
    data.intro.keys[CONTROL] = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/keys/ctrl.xpm", &tmp, &tmp);
    data.intro.keys[M_LEFT_CLICK] = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/keys/l_click.xpm", &tmp, &tmp);
    data.intro.keys[M_RIGHT_CLICK] = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/keys/r_click.xpm", &tmp, &tmp);
    ///////////
    data.intro.guide[0].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/fov.xpm", &data.intro.guide[0].x, &data.intro.guide[0].y);
    data.intro.guide[0].addr = mlx_get_data_addr(data.intro.guide[0].mlx_img, &data.intro.guide[0].bpp, &data.intro.guide[0].line_len, &data.intro.guide[0].endian);
    data.intro.guide[1].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/arrows.xpm", &data.intro.guide[1].x, &data.intro.guide[1].y);
    data.intro.guide[1].addr = mlx_get_data_addr(data.intro.guide[1].mlx_img, &data.intro.guide[1].bpp, &data.intro.guide[1].line_len, &data.intro.guide[1].endian);
    data.intro.guide[2].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/mouse.xpm", &data.intro.guide[2].x, &data.intro.guide[2].y);
    data.intro.guide[2].addr = mlx_get_data_addr(data.intro.guide[2].mlx_img, &data.intro.guide[2].bpp, &data.intro.guide[2].line_len, &data.intro.guide[2].endian);
    data.intro.guide[3].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/l_ch1.xpm", &data.intro.guide[3].x, &data.intro.guide[3].y);
    data.intro.guide[3].addr = mlx_get_data_addr(data.intro.guide[3].mlx_img, &data.intro.guide[3].bpp, &data.intro.guide[3].line_len, &data.intro.guide[3].endian);
    data.intro.guide[4].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/r_ch1.xpm", &data.intro.guide[4].x, &data.intro.guide[4].y);
    data.intro.guide[4].addr = mlx_get_data_addr(data.intro.guide[4].mlx_img, &data.intro.guide[4].bpp, &data.intro.guide[4].line_len, &data.intro.guide[4].endian);
    data.intro.guide[5].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/up.xpm", &data.intro.guide[5].x, &data.intro.guide[5].y);
    data.intro.guide[5].addr = mlx_get_data_addr(data.intro.guide[5].mlx_img, &data.intro.guide[5].bpp, &data.intro.guide[5].line_len, &data.intro.guide[5].endian);
    data.intro.guide[6].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/down.xpm", &data.intro.guide[6].x, &data.intro.guide[6].y);
    data.intro.guide[6].addr = mlx_get_data_addr(data.intro.guide[6].mlx_img, &data.intro.guide[6].bpp, &data.intro.guide[6].line_len, &data.intro.guide[6].endian);
    data.intro.guide[7].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/left.xpm", &data.intro.guide[7].x, &data.intro.guide[7].y);
    data.intro.guide[7].addr = mlx_get_data_addr(data.intro.guide[7].mlx_img, &data.intro.guide[7].bpp, &data.intro.guide[7].line_len, &data.intro.guide[7].endian);
    data.intro.guide[8].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/right.xpm", &data.intro.guide[8].x, &data.intro.guide[8].y);
    data.intro.guide[8].addr = mlx_get_data_addr(data.intro.guide[8].mlx_img, &data.intro.guide[8].bpp, &data.intro.guide[8].line_len, &data.intro.guide[8].endian);
    data.intro.guide[9].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/jump.xpm", &data.intro.guide[9].x, &data.intro.guide[9].y);
    data.intro.guide[9].addr = mlx_get_data_addr(data.intro.guide[9].mlx_img, &data.intro.guide[9].bpp, &data.intro.guide[9].line_len, &data.intro.guide[9].endian);
    data.intro.guide[10].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/crouch.xpm", &data.intro.guide[10].x, &data.intro.guide[10].y);
    data.intro.guide[10].addr = mlx_get_data_addr(data.intro.guide[10].mlx_img, &data.intro.guide[10].bpp, &data.intro.guide[10].line_len, &data.intro.guide[10].endian);
    data.intro.guide[11].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/attack.xpm", &data.intro.guide[11].x, &data.intro.guide[11].y);
    data.intro.guide[11].addr = mlx_get_data_addr(data.intro.guide[11].mlx_img, &data.intro.guide[11].bpp, &data.intro.guide[11].line_len, &data.intro.guide[11].endian);
    data.intro.guide[12].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/aim.xpm", &data.intro.guide[12].x, &data.intro.guide[12].y);
    data.intro.guide[12].addr = mlx_get_data_addr(data.intro.guide[12].mlx_img, &data.intro.guide[12].bpp, &data.intro.guide[12].line_len, &data.intro.guide[12].endian);
    data.intro.guide[13].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/run.xpm", &data.intro.guide[13].x, &data.intro.guide[13].y);
    data.intro.guide[13].addr = mlx_get_data_addr(data.intro.guide[13].mlx_img, &data.intro.guide[13].bpp, &data.intro.guide[13].line_len, &data.intro.guide[13].endian);
    data.intro.guide[14].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/setting.xpm", &data.intro.guide[14].x, &data.intro.guide[14].y);
    data.intro.guide[14].addr = mlx_get_data_addr(data.intro.guide[14].mlx_img, &data.intro.guide[14].bpp, &data.intro.guide[14].line_len, &data.intro.guide[14].endian);
    data.intro.guide[15].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/str/map.xpm", &data.intro.guide[15].x, &data.intro.guide[15].y);
    data.intro.guide[15].addr = mlx_get_data_addr(data.intro.guide[15].mlx_img, &data.intro.guide[15].bpp, &data.intro.guide[15].line_len, &data.intro.guide[15].endian);
}

void    put_color(int i, int j, char p)
{
    if (data.door.map[i][j] != '0')
        return ;
    data.door.map[i][j] = p;
    put_color(i + 1, j, p);
    put_color(i - 1, j, p);
    put_color(i, j + 1, p);
    put_color(i, j - 1, p);
}

void    init_virtual_map()
{
    int i;
    int j;
    int p;

    p = 'A';
    i = -1;
    while (data.door.map[++i])
    {
        j = -1;
        while (data.door.map[i][++j])
            if (data.door.map[i][j] == '0')
                put_color(i, j, p++);
        if (p == 'H')
            p = 'A';
    }
}

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

void    init_guns()
{
    int     i;
    int     g;
    char    path[100];

    i = 0;
	ft_memcpy(path, "img/guns/g1/", 12);
    while (++i < 53)
    {
        path_name2(path, i, 12);
        data.gun[4].gun[i - 1].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, path, &g, &g);
        data.gun[4].gun[i - 1].addr = mlx_get_data_addr(data.gun[4].gun[i - 1].mlx_img, &data.gun[4].gun[i - 1].bpp, &data.gun[4].gun[i - 1].line_len, &data.gun[4].gun[i - 1].endian);
    }
    i = 0;
	ft_memcpy(path, "img/guns/g2/", 12);
    while (++i < 15)
    {
        path_name2(path, i, 12);
        data.gun[9].gun[i - 1].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, path, &g, &g);
        data.gun[9].gun[i - 1].addr = mlx_get_data_addr(data.gun[9].gun[i - 1].mlx_img, &data.gun[9].gun[i - 1].bpp, &data.gun[9].gun[i - 1].line_len, &data.gun[9].gun[i - 1].endian);
    }
    i = 0;
	ft_memcpy(path, "img/guns/g3/", 12);
    while (++i < 34)
    {
        path_name2(path, i, 12);
        data.gun[2].gun[i - 1].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, path, &g, &g);
        data.gun[2].gun[i - 1].addr = mlx_get_data_addr(data.gun[2].gun[i - 1].mlx_img, &data.gun[2].gun[i - 1].bpp, &data.gun[2].gun[i - 1].line_len, &data.gun[2].gun[i - 1].endian);
    }
    i = 0;
	ft_memcpy(path, "img/guns/g4/", 12);
    while (++i < 50)
    {
        path_name2(path, i, 12);
        data.gun[19].gun[i - 1].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, path, &g, &g);
        data.gun[19].gun[i - 1].addr = mlx_get_data_addr(data.gun[19].gun[i - 1].mlx_img, &data.gun[19].gun[i - 1].bpp, &data.gun[19].gun[i - 1].line_len, &data.gun[19].gun[i - 1].endian);
    }
    i = 0;
	ft_memcpy(path, "img/guns/g5/", 12);
    while (++i < 27)
    {
        path_name2(path, i, 12);
        data.gun[13].gun[i - 1].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, path, &g, &g);
        data.gun[13].gun[i - 1].addr = mlx_get_data_addr(data.gun[13].gun[i - 1].mlx_img, &data.gun[13].gun[i - 1].bpp, &data.gun[13].gun[i - 1].line_len, &data.gun[13].gun[i - 1].endian);
    }
    i = 0;
	ft_memcpy(path, "img/guns/g6/", 12);
    while (++i < 18)
    {
        path_name2(path, i, 12);
        data.gun[15].gun[i - 1].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, path, &g, &g);
        data.gun[15].gun[i - 1].addr = mlx_get_data_addr(data.gun[15].gun[i - 1].mlx_img, &data.gun[15].gun[i - 1].bpp, &data.gun[15].gun[i - 1].line_len, &data.gun[15].gun[i - 1].endian);
    }
    i = 0;
	ft_memcpy(path, "img/guns/g9/", 12);
    while (++i < 82)
    {
        path_name2(path, i, 12);
        data.gun[17].gun[i - 1].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, path, &g, &g);
        data.gun[17].gun[i - 1].addr = mlx_get_data_addr(data.gun[17].gun[i - 1].mlx_img, &data.gun[17].gun[i - 1].bpp, &data.gun[17].gun[i - 1].line_len, &data.gun[17].gun[i - 1].endian);
    }
    i = 0;
	ft_memcpy(path, "img/guns/g7/", 12);
    while (++i < 25)
    {
        path_name2(path, i, 12);
        data.gun[20].gun[i - 1].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, path, &g, &g);
        data.gun[20].gun[i - 1].addr = mlx_get_data_addr(data.gun[20].gun[i - 1].mlx_img, &data.gun[20].gun[i - 1].bpp, &data.gun[20].gun[i - 1].line_len, &data.gun[20].gun[i - 1].endian);
    }
    i = 0;
	ft_memcpy(path, "img/guns/g8/", 12);
    while (++i < 27)
    {
        path_name2(path, i, 12);
        data.gun[5].gun[i - 1].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, path, &g, &g);
        data.gun[5].gun[i - 1].addr = mlx_get_data_addr(data.gun[5].gun[i - 1].mlx_img, &data.gun[5].gun[i - 1].bpp, &data.gun[5].gun[i - 1].line_len, &data.gun[5].gun[i - 1].endian);
    }
}

void    set_minimap()
{
    int w;
    int h;
    pthread_t t;
    pthread_t t2;

    w = 50;
    h = 50;

    data.mlx.mlx_ptr = mlx_init();
    data.mlx.win_ptr = mlx_new_window(data.mlx.mlx_ptr, RES_X, RES_Y, "map");

    data.img.mlx_img = mlx_new_image(data.mlx.mlx_ptr, RES_X, RES_Y);
    data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);

    data.img_c.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/ceill.xpm", &w, &h);
    data.assets.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/textures.xpm", &w, &h);
    data.guns.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/weapons.xpm", &w, &h);
    data.blood_hit.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/blood_hit.xpm", &w, &h);
    data.blood_hit2.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/blood_hit.xpm", &w, &h);
    
    data.img_c.addr = mlx_get_data_addr(data.img_c.mlx_img, &data.img_c.bpp, &data.img_c.line_len, &data.img_c.endian);
    data.assets.addr = mlx_get_data_addr(data.assets.mlx_img, &data.assets.bpp, &data.assets.line_len, &data.assets.endian);
    data.guns.addr = mlx_get_data_addr(data.guns.mlx_img, &data.guns.bpp, &data.guns.line_len, &data.guns.endian);
    data.blood_hit.addr = mlx_get_data_addr(data.blood_hit.mlx_img, &data.blood_hit.bpp, &data.blood_hit.line_len, &data.blood_hit.endian);
    data.blood_hit2.addr = mlx_get_data_addr(data.blood_hit2.mlx_img, &data.blood_hit2.bpp, &data.blood_hit2.line_len, &data.blood_hit2.endian);


    data.mlx.player = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/cursor/4.xpm", &w, &h);
    
    data.objects.time[0].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/num/0.xpm", &w, &h);
    data.objects.time[1].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/num/1.xpm", &w, &h);
    data.objects.time[2].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/num/2.xpm", &w, &h);
    data.objects.time[3].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/num/3.xpm", &w, &h);
    data.objects.time[4].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/num/4.xpm", &w, &h);
    data.objects.time[5].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/num/5.xpm", &w, &h);
    data.objects.time[6].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/num/6.xpm", &w, &h);
    data.objects.time[7].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/num/7.xpm", &w, &h);
    data.objects.time[8].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/num/8.xpm", &w, &h);
    data.objects.time[9].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/num/9.xpm", &w, &h);

    data.objects.time[0].addr = mlx_get_data_addr(data.objects.time[0].mlx_img, &data.objects.time[0].bpp, &data.objects.time[0].line_len, &data.objects.time[0].endian);
    data.objects.time[1].addr = mlx_get_data_addr(data.objects.time[1].mlx_img, &data.objects.time[1].bpp, &data.objects.time[1].line_len, &data.objects.time[1].endian);
    data.objects.time[2].addr = mlx_get_data_addr(data.objects.time[2].mlx_img, &data.objects.time[2].bpp, &data.objects.time[2].line_len, &data.objects.time[2].endian);
    data.objects.time[3].addr = mlx_get_data_addr(data.objects.time[3].mlx_img, &data.objects.time[3].bpp, &data.objects.time[3].line_len, &data.objects.time[3].endian);
    data.objects.time[4].addr = mlx_get_data_addr(data.objects.time[4].mlx_img, &data.objects.time[4].bpp, &data.objects.time[4].line_len, &data.objects.time[4].endian);
    data.objects.time[5].addr = mlx_get_data_addr(data.objects.time[5].mlx_img, &data.objects.time[5].bpp, &data.objects.time[5].line_len, &data.objects.time[5].endian);
    data.objects.time[6].addr = mlx_get_data_addr(data.objects.time[6].mlx_img, &data.objects.time[6].bpp, &data.objects.time[6].line_len, &data.objects.time[6].endian);
    data.objects.time[7].addr = mlx_get_data_addr(data.objects.time[7].mlx_img, &data.objects.time[7].bpp, &data.objects.time[7].line_len, &data.objects.time[7].endian);
    data.objects.time[8].addr = mlx_get_data_addr(data.objects.time[8].mlx_img, &data.objects.time[8].bpp, &data.objects.time[8].line_len, &data.objects.time[8].endian);
    data.objects.time[9].addr = mlx_get_data_addr(data.objects.time[9].mlx_img, &data.objects.time[9].bpp, &data.objects.time[9].line_len, &data.objects.time[9].endian);
    
    
    data.nums[0].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 15, 23);
    data.nums[1].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 15, 23);
    data.nums[2].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 15, 23);
    data.nums[3].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 15, 23);
    data.nums[4].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 15, 23);
    data.nums[5].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 15, 23);
    data.nums[6].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 15, 23);
    data.nums[7].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 15, 23);
    data.nums[8].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 15, 23);
    data.nums[9].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 15, 23);
    data.nums[0].addr = mlx_get_data_addr(data.nums[0].mlx_img, &data.nums[0].bpp, &data.nums[0].line_len, &data.nums[0].endian);
    data.nums[1].addr = mlx_get_data_addr(data.nums[1].mlx_img, &data.nums[1].bpp, &data.nums[1].line_len, &data.nums[1].endian);
    data.nums[2].addr = mlx_get_data_addr(data.nums[2].mlx_img, &data.nums[2].bpp, &data.nums[2].line_len, &data.nums[2].endian);
    data.nums[3].addr = mlx_get_data_addr(data.nums[3].mlx_img, &data.nums[3].bpp, &data.nums[3].line_len, &data.nums[3].endian);
    data.nums[4].addr = mlx_get_data_addr(data.nums[4].mlx_img, &data.nums[4].bpp, &data.nums[4].line_len, &data.nums[4].endian);
    data.nums[5].addr = mlx_get_data_addr(data.nums[5].mlx_img, &data.nums[5].bpp, &data.nums[5].line_len, &data.nums[5].endian);
    data.nums[6].addr = mlx_get_data_addr(data.nums[6].mlx_img, &data.nums[6].bpp, &data.nums[6].line_len, &data.nums[6].endian);
    data.nums[7].addr = mlx_get_data_addr(data.nums[7].mlx_img, &data.nums[7].bpp, &data.nums[7].line_len, &data.nums[7].endian);
    data.nums[8].addr = mlx_get_data_addr(data.nums[8].mlx_img, &data.nums[8].bpp, &data.nums[8].line_len, &data.nums[8].endian);
    data.nums[9].addr = mlx_get_data_addr(data.nums[9].mlx_img, &data.nums[9].bpp, &data.nums[9].line_len, &data.nums[9].endian);
    paint_img(&data.nums[0], "img/num/0.xpm", 15, 23);
    paint_img(&data.nums[1], "img/num/1.xpm", 15, 23);
    paint_img(&data.nums[2], "img/num/2.xpm", 15, 23);
    paint_img(&data.nums[3], "img/num/3.xpm", 15, 23);
    paint_img(&data.nums[4], "img/num/4.xpm", 15, 23);
    paint_img(&data.nums[5], "img/num/5.xpm", 15, 23);
    paint_img(&data.nums[6], "img/num/6.xpm", 15, 23);
    paint_img(&data.nums[7], "img/num/7.xpm", 15, 23);
    paint_img(&data.nums[8], "img/num/8.xpm", 15, 23);
    paint_img(&data.nums[9], "img/num/9.xpm", 15, 23);
    data.sl = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/num/sl.xpm", &w, &h);

    data.mouse.img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/cursor.xpm", &w, &h);
    

    // data.mlx.wall = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/wall.xpm", &w, &h);
    data.mlx.none = mlx_new_image(data.mlx.mlx_ptr, RES_X, RES_Y);
    // data.mlx.cadre1 = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/2_1.xpm", &w, &h);
    // data.mlx.cadre2 = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/2_2.xpm", &w, &h);
    data.mlx.floor.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/f.xpm", &w, &h);
    data.mlx.floor.addr = mlx_get_data_addr(data.mlx.floor.mlx_img, &data.mlx.floor.bpp, &data.mlx.floor.line_len, &data.mlx.floor.endian);
    
    // data.mlx.wall.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/wall.xpm", &w, &h);
    // data.mlx.wall.addr = mlx_get_data_addr(data.mlx.wall.mlx_img, &data.mlx.wall.bpp, &data.mlx.wall.line_len, &data.mlx.wall.endian);
    
    data.mlx.space.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/sp.xpm", &w, &h);
    data.mlx.space.addr = mlx_get_data_addr(data.mlx.space.mlx_img, &data.mlx.space.bpp, &data.mlx.space.line_len, &data.mlx.space.endian);

    data.intro.int1.mlx_img = mlx_new_image(data.mlx.mlx_ptr, RES_X, RES_Y);
    data.intro.int1.addr = mlx_get_data_addr(data.intro.int1.mlx_img, &data.intro.int1.bpp, &data.intro.int1.line_len, &data.intro.int1.endian);
    paint_img(&data.intro.int1, "img/int_1.xpm", RES_X, RES_Y);
    
    data.intro.int2.mlx_img = mlx_new_image(data.mlx.mlx_ptr, RES_X, RES_Y);
    data.intro.int2.addr = mlx_get_data_addr(data.intro.int2.mlx_img, &data.intro.int2.bpp, &data.intro.int2.line_len, &data.intro.int2.endian);
    paint_img(&data.intro.int2, "img/int_2.xpm", RES_X, RES_Y);

    data.intro.tr.mlx_img = mlx_new_image(data.mlx.mlx_ptr, RES_X, RES_Y);
    data.intro.tr.addr = mlx_get_data_addr(data.intro.tr.mlx_img, &data.intro.tr.bpp, &data.intro.tr.line_len, &data.intro.tr.endian);
    paint_color(&data.intro.tr, ((int)(255 * 0.15) << 24), RES_X, RES_Y);
    
    data.intro.tr2.mlx_img = mlx_new_image(data.mlx.mlx_ptr, RES_X, RES_Y);
    data.intro.tr2.addr = mlx_get_data_addr(data.intro.tr2.mlx_img, &data.intro.tr2.bpp, &data.intro.tr2.line_len, &data.intro.tr2.endian);
    paint_color(&data.intro.tr2, ((int)(255 * 0.5) << 24), RES_X, RES_Y);
    
    data.intro.up_logo.mlx_img = mlx_new_image(data.mlx.mlx_ptr, RES_X / 3, RES_Y / 6);
    data.intro.up_logo.addr = mlx_get_data_addr(data.intro.up_logo.mlx_img, &data.intro.up_logo.bpp, &data.intro.up_logo.line_len, &data.intro.up_logo.endian);
    paint_img(&data.intro.up_logo, "img/logo.xpm", RES_X / 3, RES_Y / 6);
    
    /////////////////
    data.intro.start.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/sett/start.xpm", &data.intro.start.x, &data.intro.start.y);
    data.intro.start.addr = mlx_get_data_addr(data.intro.start.mlx_img, &data.intro.start.bpp, &data.intro.start.line_len, &data.intro.start.endian);
    
    data.intro.sett.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/sett/setting.xpm", &data.intro.sett.x, &data.intro.sett.y);
    data.intro.sett.addr = mlx_get_data_addr(data.intro.sett.mlx_img, &data.intro.sett.bpp, &data.intro.sett.line_len, &data.intro.sett.endian);
    
    data.intro.exit.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/sett/exit.xpm", &data.intro.exit.x, &data.intro.exit.y);
    data.intro.exit.addr = mlx_get_data_addr(data.intro.exit.mlx_img, &data.intro.exit.bpp, &data.intro.exit.line_len, &data.intro.exit.endian);
    
    data.intro.cont.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/sett/cont.xpm", &data.intro.cont.x, &data.intro.cont.y);
    data.intro.cont.addr = mlx_get_data_addr(data.intro.cont.mlx_img, &data.intro.cont.bpp, &data.intro.cont.line_len, &data.intro.cont.endian);
    
    data.intro.restart.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/sett/restart.xpm", &data.intro.restart.x, &data.intro.restart.y);
    data.intro.restart.addr = mlx_get_data_addr(data.intro.restart.mlx_img, &data.intro.restart.bpp, &data.intro.restart.line_len, &data.intro.restart.endian);
    
    data.intro.reset.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/sett/reset.xpm", &data.intro.reset.x, &data.intro.reset.y);
    data.intro.reset.addr = mlx_get_data_addr(data.intro.reset.mlx_img, &data.intro.reset.bpp, &data.intro.reset.line_len, &data.intro.reset.endian);
    
    data.intro.back.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/sett/back.xpm", &data.intro.back.x, &data.intro.back.y);
    data.intro.back.addr = mlx_get_data_addr(data.intro.back.mlx_img, &data.intro.back.bpp, &data.intro.back.line_len, &data.intro.back.endian);
    ////////////////
    
    data.intro.gun.mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/gun.xpm", &data.intro.gun.x, &data.intro.gun.y);
    data.intro.gun.addr = mlx_get_data_addr(data.intro.gun.mlx_img, &data.intro.gun.bpp, &data.intro.gun.line_len, &data.intro.gun.endian);

    data.intro.vol_icon[0].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 50, 50);
    data.intro.vol_icon[0].addr = mlx_get_data_addr(data.intro.vol_icon[0].mlx_img, &data.intro.vol_icon[0].bpp, &data.intro.vol_icon[0].line_len, &data.intro.vol_icon[0].endian);
    paint_img(&data.intro.vol_icon[0], "img/mute.xpm", 50, 50);
    data.intro.vol_icon[1].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 50, 50);
    data.intro.vol_icon[1].addr = mlx_get_data_addr(data.intro.vol_icon[1].mlx_img, &data.intro.vol_icon[1].bpp, &data.intro.vol_icon[1].line_len, &data.intro.vol_icon[1].endian);
    paint_img(&data.intro.vol_icon[1], "img/half_volume.xpm", 50, 50);
    data.intro.vol_icon[2].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 50, 50);
    data.intro.vol_icon[2].addr = mlx_get_data_addr(data.intro.vol_icon[2].mlx_img, &data.intro.vol_icon[2].bpp, &data.intro.vol_icon[2].line_len, &data.intro.vol_icon[2].endian);
    paint_img(&data.intro.vol_icon[2], "img/volume.xpm", 50, 50);

    data.intro.vol[0].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 200, 10);
    data.intro.vol[0].addr = mlx_get_data_addr(data.intro.vol[0].mlx_img, &data.intro.vol[0].bpp, &data.intro.vol[0].line_len, &data.intro.vol[0].endian);
    paint_color(&data.intro.vol[0], 0xB2BEB5, 200, 10);
    paint_color(&data.intro.vol[0], 0xff0000, data.intro.volume, 10);

    data.intro.vol[1].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 25, 40);
    data.intro.vol[1].addr = mlx_get_data_addr(data.intro.vol[1].mlx_img, &data.intro.vol[1].bpp, &data.intro.vol[1].line_len, &data.intro.vol[1].endian);
    paint_color(&data.intro.vol[1], 0xffffff, 25, 40);
    
    
    data.intro.light_icon[1].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/light.xpm", &data.intro.light_icon[1].x, &data.intro.light_icon[1].y);
    
    data.intro.lt.mlx_img = mlx_new_image(data.mlx.mlx_ptr, RES_X, RES_Y);
    data.intro.lt.addr = mlx_get_data_addr(data.intro.lt.mlx_img, &data.intro.lt.bpp, &data.intro.lt.line_len, &data.intro.lt.endian);
    paint_color(&data.intro.lt, (255 << 24), RES_X, RES_Y);
    
    data.intro.lgt[0].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 200, 10);
    data.intro.lgt[0].addr = mlx_get_data_addr(data.intro.lgt[0].mlx_img, &data.intro.lgt[0].bpp, &data.intro.lgt[0].line_len, &data.intro.lgt[0].endian);
    paint_color(&data.intro.lgt[0], 0xB2BEB5, 200, 10);
    paint_color(&data.intro.lgt[0], 0xff0000, data.intro.light, 10);

    data.intro.lgt[1].mlx_img = mlx_new_image(data.mlx.mlx_ptr, 25, 40);
    data.intro.lgt[1].addr = mlx_get_data_addr(data.intro.lgt[1].mlx_img, &data.intro.lgt[1].bpp, &data.intro.lgt[1].line_len, &data.intro.lgt[1].endian);
    paint_color(&data.intro.lgt[1], 0xffffff, 25, 40);
    init_guns();
    
    data.door.door[0][0].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/dor1_0.xpm", &w, &h);
    data.door.door[0][0].addr = mlx_get_data_addr(data.door.door[0][0].mlx_img, &data.door.door[0][0].bpp, &data.door.door[0][0].line_len, &data.door.door[0][0].endian);
    data.door.door[0][1].mlx_img = mlx_xpm_file_to_image(data.mlx.mlx_ptr, "img/dor1_1.xpm", &w, &h);
    data.door.door[0][1].addr = mlx_get_data_addr(data.door.door[0][1].mlx_img, &data.door.door[0][1].bpp, &data.door.door[0][1].line_len, &data.door.door[0][1].endian);


    int i;
    i = -1;
    while (++i < 1000)
        data.keys[i] = 0,
        data.intro.keys[i] = NULL;
    init_virtual_map();
    init_img_control();
    init_angles();
    mlx_mouse_hide();
    pthread_create(&t, NULL, &time_count, NULL);
    pthread_create(&t2, NULL, &check_sound, NULL);
    mlx_hook(data.mlx.win_ptr, 2, 1L<<0, key_press, NULL);
    mlx_hook(data.mlx.win_ptr, 3, 1L<<1, key_release, NULL);
    
    mlx_loop_hook(data.mlx.mlx_ptr, rendering, NULL);
    mlx_hook(data.mlx.win_ptr, 17, 1, ft_close, NULL); 
    mlx_loop(data.mlx.mlx_ptr);
}
