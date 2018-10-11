#include<string.h>
#include<fstream.h>
#include<process.h>
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>

union REGS i,o;
char inputbuf[150];
int input_pos = 0;
char name[20],c;
int ox=71,oy=85;
void draw();
void count_words( char[] );
void intro();
int input(char []);
void restrictmouseptr(int ,int ,int ,int );
int callmouse();
