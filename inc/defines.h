/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:53:23 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/09/11 19:01:05 by ael-bekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_CODE_H
# define KEY_CODE_H

/*************************************************************/
/*========               keyboard code               ========*/
/*************************************************************/
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

# define M_LEFT_CLICK 600
# define M_RIGHT_CLICK 601
# define M_UP 500
# define M_DOWN 501
# define M_LEFT 502
# define M_RIGHT 503
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_T 17
# define KEY_Y 16
# define KEY_U 32
# define KEY_I 34
# define KEY_O 31
# define KEY_P 35
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_Z 6
# define KEY_X 7
# define KEY_C 8
# define KEY_V 9
# define KEY_B 11
# define KEY_N 45
# define KEY_M 46
# define TAB 48
# define CAPS 272
# define SHIFT 257
# define ESC 53
# define SPACE 49
# define ENTER 36
# define F1 122
# define CONTROL 269

/*************************************************************/
/*========                mouse code                 ========*/
/*************************************************************/
# define LEFT_CLICK 1
# define RIGHT_CLICK 2
# define MIDDLE_CLICK 3
# define SCROLL_UP 4
# define SCROLL_DOWN 5

/*************************************************************/
/*========                 game mode                 ========*/
/*************************************************************/
# define INTRO 1
# define INTRO1 2
# define INTRO2 3
# define SETTING 4
# define S_CONTROL 5
# define GAME 6
# define G_EXIT 7
# define G_MAP 8
# define SETTING2 9
# define ANIMATE_SETT2_IN 10
# define ANIMATE_SETT2_OUT 11

/*************************************************************/
/*========          some const for the game          ========*/
/*************************************************************/
# define RES_X 1500 
# define RES_Y 1080
# define X 1500 - 191
# define Y 1080 - 181
# define MX 1500 - 186 + 16.5
# define MY 1080 - 176 + 16.5
# define MAP_CHAR "01NSWEH "
# define ANGLE 2
# define ANGLES 4

/*************************************************************/
/*========                 env assets                ========*/
/*************************************************************/
//--------------------------- :::  room {A}  ::: ---------------------------//
# define FLOOR2_START__X 96
# define FLOOR2_START__Y 40
# define FLOOR2_SIZE_Y 7
# define FLOOR2_SIZE_X 1

# define CART1_START__X 456
# define CART1_START__Y 40
# define CART1_SIZE_Y 7
# define CART1_SIZE_X 2

# define SUPPORT_START__X 1392
# define SUPPORT_START__Y 40
# define SUPPORT_SIZE_X 4
# define SUPPORT_SIZE_Y 4

//--------------------------- :::  room {B}  ::: ---------------------------//
# define CART2_START__X 600
# define CART2_START__Y 40
# define CART2_SIZE_Y 7
# define CART2_SIZE_X 2

# define CONCRETE_START__X 240
# define CONCRETE_START__Y 576
# define CONCRETE_SIZE_Y 2
# define CONCRETE_SIZE_X 3

# define LIGHT_START__X 744
# define LIGHT_START__Y 40
# define LIGHT_SIZE_X 2
# define LIGHT_SIZE_Y 3

//--------------------------- :::  room {C}  ::: ---------------------------//
# define TECH1_2_START__X 888
# define TECH1_2_START__Y 40
# define TECH1_2_SIZE_Y 9
# define TECH1_2_SIZE_X 2

# define STEEL_START__X 168
# define STEEL_START__Y 40
# define STEEL_SIZE_Y 3
# define STEEL_SIZE_X 4

# define SUPPORT_P_START__X 1392
# define SUPPORT_P_START__Y 40
# define SUPPORT_P_SIZE_X 1
# define SUPPORT_P_SIZE_Y 4

# define GREED_START__X 168
# define GREED_START__Y 256
# define GREED_SIZE_Y 3
# define GREED_SIZE_X 1

//--------------------------- :::  room {D}  ::: ---------------------------//
# define FLOOR3_START__X 600
# define FLOOR3_START__Y 576
# define FLOOR3_SIZE_Y 4
# define FLOOR3_SIZE_X 1

# define LAB_START__X 888
# define LAB_START__Y 576
# define LAB_SIZE_Y 3
# define LAB_SIZE_X 5

# define SUPPORT_G_START__X 1248
# define SUPPORT_G_START__Y 576
# define SUPPORT_G_SIZE_X 3
# define SUPPORT_G_SIZE_Y 4

//--------------------------- :::  room {E}  ::: ---------------------------//
# define SLIME_START__X 1680
# define SLIME_START__Y 576
# define SLIME_SIZE_Y 2
# define SLIME_SIZE_X 1

# define LAB_B_START__X 888
# define LAB_B_START__Y 576
# define LAB_B_SIZE_Y 3
# define LAB_B_SIZE_X 3

# define SUPPORT_F_START__X 672
# define SUPPORT_F_START__Y 576
# define SUPPORT_F_SIZE_X 3
# define SUPPORT_F_SIZE_Y 2

# define PIPES_START__X 1464
# define PIPES_START__Y 576
# define PIPES_SIZE_X 1
# define PIPES_SIZE_Y 1

//--------------------------- :::  room {F}  ::: ---------------------------//
# define TECH3_START__X 1104
# define TECH3_START__Y 40
# define TECH3_SIZE_Y 6
# define TECH3_SIZE_X 5

# define FLOOR1_START__X 24
# define FLOOR1_START__Y 40
# define FLOOR1_SIZE_Y 5
# define FLOOR1_SIZE_X 1

# define SUPPORT_PP_START__X 1680
# define SUPPORT_PP_START__Y 256
# define SUPPORT_PP_SIZE_X 1
# define SUPPORT_PP_SIZE_Y 2

# define GREED_START__X 168
# define GREED_START__Y 256
# define GREED_SIZE_Y 3
# define GREED_SIZE_X 1

//--------------------------- :::  room {G}  ::: ---------------------------//
# define SZ_START__X 456 + 72
# define SZ_START__Y 40 + 72 * 4
# define SZ_SIZE_Y 1
# define SZ_SIZE_X 1

# define TILE_START__X 24
# define TILE_START__Y 576
# define TILE_SIZE_Y 6
# define TILE_SIZE_X 3

# define SUPPORT_PP_START__X 1680
# define SUPPORT_PP_START__Y 256
# define SUPPORT_PP_SIZE_X 1
# define SUPPORT_PP_SIZE_Y 2

# define GREED_START__X 168
# define GREED_START__Y 256
# define GREED_SIZE_Y 3
# define GREED_SIZE_X 1

//--------------------------- :::  door  ::: ---------------------------//
# define DOOR_START__X 744
# define DOOR_START__Y 40

#endif