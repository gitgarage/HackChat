/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   structures.h
 * Author: michael.oriley
 *
 * Created on January 26, 2016, 11:14 AM
 */

#ifndef STRUCTURES_H
#define STRUCTURES_H

#ifdef __cplusplus
extern "C" {
#endif

struct s_data
{
  char* message;
  char* chat[200];
  int t;
  char* handle;
  int first;
  char* ourMessage;
  int sent;
  char* last;
} global;  
    
extern const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel;
  unsigned char	 pixel_data[];
} type_1;

int getText(int x, int y, int index);

#ifdef __cplusplus
}
#endif

#endif /* STRUCTURES_H */

