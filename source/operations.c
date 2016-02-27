/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   operations.c
 * Author: michael.oriley
 *
 * Created on January 26, 2016, 11:00 AM
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <3ds.h>
#include <stdlib.h>
#include "structures.h"


char * concatinate(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int getText(int x, int y, int index)
{
    char* letter = " ";
    u8 concat = 1;
    
    if (y < 182)
    {
        if (y > 158)
        {
            if (x < 58)
            {
                // capitalize();
                concat = 0; // false
            } else if (x < 113)
            {
                // shift();
                concat = 0; // false
            } else if (x < 213)
            {
                // do nothing();
            } else
            {
                // english();
                concat = 0;
            }
        } else if (y > 136)
        {
            if (x < 40)
            {
                letter = "z";
            } else if (x < 65)
            {
                letter = "x";
            } else if (x < 90)
            {
                letter = "c";
            } else if (x < 115)
            {
                letter = "v";
            } else if (x < 140)
            {
                letter = "b";
            } else if (x < 165)
            {
                letter = "n";
            } else if (x < 190)
            {
                letter = "m";
            } else if (x < 215)
            {
                letter = ",";
            } else if (x < 240)
            {
                letter = ".";
            } else if (x < 265)
            {
                letter = "?";
            } else if (x < 290)
            {
                letter = "!";
            } else
            {
                letter = "@";
            }
        } else if (y > 114)
        {
            if (x < 36)
            {
                letter = "a";
            } else if (x < 60)
            {
                letter = "s";
            } else if (x < 85)
            {
                letter = "d";
            } else if (x < 110)
            {
                letter = "f";
            } else if (x < 135)
            {
                letter = "g";
            } else if (x < 160)
            {
                letter = "h";
            } else if (x < 185)
            {
                letter = "j";
            } else if (x < 210)
            {
                letter = "k";
            } else if (x < 235)
            {
                letter = "l";
            } else if (x < 260)
            {
                letter = "'";
            } else if (x < 285)
            {
                letter = "=";
            } else
            {
                letter = "/";
            }
        } else if (y > 92)
        {
            if (x < 32)
            {
                letter = "q";
            } else if (x < 56)
            {
                letter = "w";
            } else if (x < 81)
            {
                letter = "e";
            } else if (x < 106)
            {
                letter = "r";
            } else if (x < 131)
            {
                letter = "t";
            } else if (x < 156)
            {
                letter = "y";
            } else if (x < 181)
            {
                letter = "u";
            } else if (x < 206)
            {
                letter = "i";
            } else if (x < 231)
            {
                letter = "o";
            } else if (x < 256)
            {
                letter = "p";
            } else
            {
                if (global.first == 0)
                {
                    global.first = 1;
                    global.handle = global.message;
                    global.message = "";
                    return internet_access(global.message);
                }
                else
                {
//                           int offset = 0;
//                           char texts[200];
//                           strcpy(texts, global.message);
//                global.message = "";
//                concat = 0;
                return internet_access(global.message);                    
                }
                //global.chat = "We can be heroes!!!";
                //u8 i;
                //char** args = {"libwebsockets-test-client","https://protected-river-61287.herokuapp.com"};
                //socket_connect(2, args);
            }
        } else if (y > 70)
        {
            if (x < 29)
            {
                letter = "1";
            } else if (x < 52)
            {
                letter = "2";
            } else if (x < 77)
            {
                letter = "3";
            } else if (x < 102)
            {
                letter = "4";
            } else if (x < 127)
            {
                letter = "5";
            } else if (x < 152)
            {
                letter = "6";
            } else if (x < 177)
            {
                letter = "7";
            } else if (x < 202)
            {
                letter = "8";
            } else if (x < 227)
            {
                letter = "9";
            } else if (x < 252)
            {
                letter = "0";
            } else if (x < 277)
            {
                letter = "-";
            } else
            {
                u8 len = strlen(global.message);
                global.message[len - 1] = 0;
                concat = 0;
            }
        }
    }
    
    if (concat == 1)
    {
        char *output = malloc(strlen(global.message) + 2);
        strcpy(output, global.message);
        strcat(output, letter);
        global.message = output;
    }
}
