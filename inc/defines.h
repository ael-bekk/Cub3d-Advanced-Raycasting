/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bekk <ael-bekk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 11:53:23 by ael-bekk          #+#    #+#             */
/*   Updated: 2022/08/14 15:01:16 by ael-bekk         ###   ########.fr       */
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

/*************************************************************/
/*========          some const for the game          ========*/
/*************************************************************/
# define RES_X 1500 
# define RES_Y 1080
# define X 1500 - 191
# define Y 1080 - 181
# define MX 1500 - 186 + 16.5
# define MY 1080 - 176 + 16.5
# define MAP_CHAR "01NSWE "
# define ANGLE 5.625
# define ANGLES 4

#endif