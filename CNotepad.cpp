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
class file

{ public: char notes[150];
    void write();
    void read();
};
void file::write()

{ outtextxy(80,85,"|");
    gotoxy(12,6);
    gets(notes);
}
void file::read()

{ char array[2];
    for(int i=0;notes[i]!=' ';i++)

    {
	array[0]=notes[i];
	array[1]='\0';
	outtextxy(ox,oy,array);
	ox+=8;
	if(ox>=380)

	{
	    ox=71;
	    oy+=8;
	}
    }
}

class notepad

{
    public:
    int field;
    int menu;
    int outline;
    int popup;
    void draw();
    notepad()

    { field=15;
	menu=4;
	outline=3;
	popup=6;
    }
};
