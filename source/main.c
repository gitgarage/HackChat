#include <stdio.h>
#include <string.h>
#include <math.h>
#include <3ds.h>
#include </home/omikey/Desktop/libsf2d/include/sf2d.h>
#include </home/omikey/Desktop/libsftd/include/sftd.h>
#include <stdlib.h>
#include <strings.h>
#include "/home/omikey/Desktop/sample/build/arial_ttf.h"
#include "structures.h"


int main()
{
    global.sent = 0;
    global.t = 0;
        char lines[20][200];
        int i = 0;
        global.message = "";
        global.first = 0;
        strcpy(lines[0], "Please enter a username.");
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
       	sf2d_texture *tex2 = sf2d_create_texture_mem_RGBA8(type_1.pixel_data, type_1.width, type_1.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	sf2d_set_vblank_wait(0);

	// Font loading
	sftd_init();
	sftd_font *font = sftd_load_font_mem(arial_ttf, arial_ttf_size);

	int textWidth = 0;
	int textHeight = 0;
        touchPosition touch;
       	u16 touch_x = 0;
	u16 touch_y = 0;
        u32 held;
        u8 letGo = 1;
//        u8 index = 10;
        int n = 0;
        int j;
        char buf[200];
        u8 even = 0;
        int count = 0;
        //char buf[200];
        char str[100];
        char new_string[100];
        char c[1];
        int len = 0;
                        int y;
                        int x;
        
        int counter = 0;
            int end = 1; //read(fd, buf, 200);
            // buf[end] = '\0';
        
            //printf("read: %d - %s\n", counter, buf);  
            char name[30];
//            int count;
            int index;
            char* bang;
            int bangIndex;
            char* ping;
            char* r1;
            char* r2;
            char* r3;
            char* r4;
            int cbob = 0;
            
            global.last = "";
            
            
	while (aptMainLoop()) {                
            if (global.sent == 2)
            {
                strcpy(lines[0], "You have entered #3dshacks");
            }
            while (cbob > 8)
            {
                for (y = 0; y < 9; y++)
                {
                    if (y > 0)
                    {
                        strcpy(lines[y-1], lines[y]);
                    }
                }
                cbob -= 1;                
            }

            if (global.sent == 1)
            {
                global.sent = 0;
                strcpy(lines[cbob], global.ourMessage);
                global.ourMessage = "";
                cbob++;                
            }
                global.sent == 0;
                global.ourMessage = "";
            if (global.t > 0)                
            {
                end = 1;
                while (end > 0)
                {
                    bzero(buf, 200);
                    count = 0;
                    //end = sgetline(fd, buf);
                    while (end > 0 && count < 200)
                    {
                        end = read(global.t, c, 1);
                        
                        if (c[0] == '\n')
                        {
                            count++;
                            buf[count] = '\0';
                            break;                            
                        }
                        
                        if (count == 0)
                        {
                            strcpy(buf, c);
                        }
                        else
                        {
                            strcat(buf, c);                            
                        }
                        //buf = concatinate(buf, c);
                        count++;
                        buf[count] = '\0';
                    }
                    //buf[end] = '\0';
                    counter++;

                    ping = strstr(buf, "PING");
                    if (ping != NULL)
                    {
                        send(global.t, "PONG :irc.rizon.io", 18, 0);
                        //printf("PONG :irc.rizon.io\r\n");
                    }

                    char* map = strstr(buf, "PRIVMSG #3dshacks :");
                    char* laster = strstr(buf, global.last);
                    
                    if (map != NULL && laster != NULL)
                    {
                        bzero(name, 30);
                        index = map - buf;
                        bang = strstr(buf, "!");
                        bangIndex = bang - buf;
                        strncpy(name, buf + 1, bangIndex);
                        name[bangIndex - 1] = '\0';
                        if (name[bangIndex - 2] == '\r')
                        {
                            name[bangIndex - 2] = '\0';
                        }
                        
                        r1 = concatinate("<", name);
                        r2 = concatinate(r1, "> ");
                        r3 = concatinate(r2, buf + index + 19);
                        r3[strlen(r3)-1] = '\0';
//                        printf("<%s> %s\n", name, buf + index + 19);                        
                        strcpy(lines[cbob], r3);
                        cbob++;
                    }
                }
            }

            
       		hidScanInput();
                held = hidKeysHeld();

		if (held & KEY_START) {
			break;
		} else if (held & KEY_TOUCH) {
			hidTouchRead(&touch);
			touch_x = touch.px;
			touch_y = touch.py;
                        if (letGo == 1)
                        {
                            letGo = 0;
                            getText(touch_x, touch_y, index);
                            //index--;
                        }
		}
                
                if (!held)
                {
                    letGo = 1;
                }
            
		hidScanInput();
		if (hidKeysDown() & KEY_START) break;

		sf2d_start_frame(GFX_TOP, GFX_LEFT);

			sf2d_draw_rectangle(10, 40, textWidth, textHeight, RGBA8(0, 100, 0, 255));
                        
                        for (y = 0; y < 8; y++)
                        {
                            sftd_draw_text_wrap(font, 5, 5 + (y * 30),  RGBA8(0, 255, 0, 255), 12, 300, lines[y]);                                                                                
                        }
//                        sftd_draw_text_wrap(font, 5, 19,  RGBA8(0, 255, 0, 255), 12, 300, a02);                                                        
//                        sftd_draw_text_wrap(font, 5, 33,  RGBA8(0, 255, 0, 255), 12, 300, a03);                                                        
//                        sftd_draw_text_wrap(font, 5, 47,  RGBA8(0, 255, 0, 255), 12, 300, a04);                                                        
//                        sftd_draw_text_wrap(font, 5, 61,  RGBA8(0, 255, 0, 255), 12, 300, a05);                                                        
//                        sftd_draw_text_wrap(font, 5, 75,  RGBA8(0, 255, 0, 255), 12, 300, a06);                                                        
//                        sftd_draw_text_wrap(font, 5, 89,  RGBA8(0, 255, 0, 255), 12, 300, a07);                                                        
//                        sftd_draw_text_wrap(font, 5, 103,  RGBA8(0, 255, 0, 255), 12, 300, a08);                                                        
//                        sftd_draw_text_wrap(font, 5, 117,  RGBA8(0, 255, 0, 255), 12, 300, a09);                                                        
//                        sftd_draw_text_wrap(font, 5, 131,  RGBA8(0, 255, 0, 255), 12, 300, a10);                                                        
//                        sftd_draw_text_wrap(font, 5, 145,  RGBA8(0, 255, 0, 255), 12, 300, a11);                                                        
//                        sftd_draw_text_wrap(font, 5, 159,  RGBA8(0, 255, 0, 255), 12, 300, a12);                                                        
//                        sftd_draw_text_wrap(font, 5, 173,  RGBA8(0, 255, 0, 255), 12, 300, a13);                                                        
//                        sftd_draw_text_wrap(font, 5, 187,  RGBA8(0, 255, 0, 255), 12, 300, a14);                                                        
//                        sftd_draw_text_wrap(font, 5, 201,  RGBA8(0, 255, 0, 255), 12, 300, a15);                                                        
//                        sftd_draw_text_wrap(font, 5, 215,  RGBA8(0, 255, 0, 255), 12, 300, a16);                                                        
//                        sftd_draw_text_wrap(font, 5, 229,  RGBA8(0, 255, 0, 255), 12, 300, a17);                                                        
//                        sftd_draw_text_wrap(font, 5, 243,  RGBA8(0, 255, 0, 255), 12, 300, a18);                                                        
//                        sftd_draw_text_wrap(font, 5, 257,  RGBA8(0, 255, 0, 255), 12, 300, a19);                                                        
//                        sftd_draw_text_wrap(font, 5, 271,  RGBA8(0, 255, 0, 255), 12, 300, a20);                                                        

                sf2d_end_frame();

		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
                
                        sf2d_draw_texture(tex2, 0, 0);
                        if (strlen(global.message) % 8 == 0)
                        {
                            char* new_string = malloc(strlen(global.message) + 2);
                            strcpy(new_string, global.message);
                            strcat(new_string, " ");
                            sftd_draw_text_wrap(font, 5, 5,  RGBA8(0, 255, 0, 255), 24, 275, new_string);                            
                        } else
                        {
                            sftd_draw_text_wrap(font, 5, 5,  RGBA8(0, 255, 0, 255), 24, 275, global.message);                            
                        }

		sf2d_end_frame();
		sf2d_swapbuffers();
               
	}

	sftd_free_font(font);
	sftd_fini();
	sf2d_fini();
	return 0;
}
