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
   void notepad:: draw()

    {
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"");
	int margin,top,bottom,right,left;
	restrictmouseptr(45,30,410,405);
	callmouse();
	margin=50;
        left=margin;
        top=margin;
	bottom=400;
        right=400;
        setfillstyle(SOLID_FILL,field);
        bar(left,top,right,bottom);
        rectangle(left,top,right,bottom);
        setcolor(BLACK);
        setfillstyle(SOLID_FILL,outline);
	//top bar
        bar(45,30,410,50);
        rectangle(45,30,410,50);
        //left bar
        bar(45,50,55,405);
	rectangle(45,50,55,405);
        //right bar
        bar(400,49,410,405);
        rectangle(400,49,410,405);
        //bottom bar
        bar(45,400,410,405);
        rectangle(45,400,410,420);
	setcolor(BLACK);
        setfillstyle(SOLID_FILL,menu);
        bar(45,47,410,60);
        rectangle(45,47,410,60);
        outtextxy(47,50,"File");
	outtextxy(85,50,"Edit");
	outtextxy(125,50,"Help");
	outtextxy(165,50,"Mods");
	outtextxy(52,35,"NOTEPAD++ ");
	outtextxy(135,35,"Beta Mode");
	outtextxy(395,35,"X");
    }


void restrictmouseptr(int x1,int y1,int x2,int y2)

{
    i.x.ax=7;
    i.x.cx=x1;
    i.x.dx=x2;
    int86(51,&i,&o);
    i.x.ax=8;
    i.x.cx=y1;
    i.x.dx=y2;
    int86(51,&i,&o);
}
int callmouse()

{ i.x.ax=1;
    int86(51,&i,&o);
    return 1;
}
void getmousepos(int &xpos,int &ypos,int &cl)

{ i.x.ax=3;
    int86(51,&i,&o);
    cl=o.x.bx;
    xpos=o.x.cx;
    ypos=o.x.dx;
}

void count_words( char name[20])

{ 
    fstream f;
    int count_word=1,letters=0,lines=0;
    file s;
    f.open(name,ios::binary|ios::in);
    while( f.read((char*)&s,sizeof(s)));
    // s.read();
    for(int i=0;s.notes[i]!=' ';++i)
    
    {
        if(s.notes[i]==' ')
        ++count_word;
        else if(s.notes[i]!=' '&&s.notes[i]!='.')
        ++letters;
        else if(s.notes[i]=='.')
        ++lines;
    }
    f.close();
    outtextxy(72,102,"Words :");
    gotoxy(18,7);
    cout<<count_word;
    outtextxy(72,117,"Letters:");
    gotoxy(18,8);
    cout<<letters;
    outtextxy(72,132,"Lines :");
    gotoxy(18,9);
    cout<<lines;
    
}
void intro()
{
    int gd=DETECT,gm;
    int margin,top,bottom,right,left;
    initgraph(&gd,&gm,"");
    char str[300];
    int i,j,location,n;
    char ch;
    strcpy(str,"          NOTEPAD++          ");
    outtextxy(350,300,"PRESS ANY KEY");
    for(i=0;i<10;i++)
    {
	setfillstyle(SOLID_FILL,BLACK);
        bar(50,50,600,90);
        settextstyle(3,HORIZ_DIR,4);
        outtextxy(50,50,str);
        setcolor(i);
        delay(100);
	ch = str[0];
        n=strlen(str);
        location=0;
        for(j=location;j<n;j++)
        {
            str[j] = str[j+1];
        }
    }
    str[n-1]=ch;
    str[n]=NULL;
    bar(230,150,350,268);
    rectangle(230,150,380,268);
    setcolor(CYAN);
    circle(362,140,25);
    settextstyle(2,HORIZ_DIR,4);
    outtextxy(244,160,"C++ NOTEPAD");
    delay(400);
    outtextxy(244,172,"Developed by VIBHOOTHI ");
    delay(400);
    outtextxy(244,238,"LOADING");
    int inx=294;
    for( i=0;i<8;++i)
    {
        outtextxy(inx,238,".");
        inx+=6;
        delay(300);
    }
    outtextxy(244,250 ,"DONE");
    getch();
}

void main()

{
    int flag=0;
    notepad n;
    fstream f,f1;
    intro();
    n.draw();
    int x,y,cl=0;
    file s;
    while(1)

    {
	fstream f;
	getmousepos(x,y,cl);
	gotoxy(5,8); //  cout<<"ntMouse Position is: X: "<<x<<" Y: "<<y; // cout<<"CLICK:"<<cl;
	if((x>=45 && x<=78)&&(y>=49&&y<=56)&&(cl==1))

	{ //pop up
	    flag=1;
	    cleardevice();  // system("CLS");
	    n. draw();
	    setfillstyle(SOLID_FILL,n.popup);
	    delay(500);
	    bar(45,60,110,99);
	    rectangle(45,60,110,99);
	    outtextxy(46,65,"NEW");
	    outtextxy(46,76,"OPEN");
	    outtextxy(46,86,"ADD");
	}
	if((x>=45&&x<=69)&&(y>=66&&y<=71)&&(cl==1)&&(flag==1))

	{
	    cleardevice(); // system("CLS");
	    n.draw();
	    char save;
	    outtextxy(71,68,"Enter name of file: ");
	    gotoxy(29 ,5);
	    gets(name);
	    strcat(name,".dat");
	    f.open(name,ios::binary|ios::out);
	    s.write();
	    outtextxy(71,355,"Do you wish to save your file(Y/y)");
	    gotoxy(45,23);
	    cin>>save;
	    if(save=='y'||save=='Y')

	    {
		f.write((char*)&s,sizeof(s));
		outtextxy(71,375,"Your file has been saved");
	    }
	    f.close();
	}
	if((x>=45&&x<=76)&&(y>=76&&y<=83)&&(cl==1)&&(flag==1))

	{
	    closegraph();
	    n. draw();
	    outtextxy(71,68,"Enter name of file: ");
	    gotoxy(28,5);
	    gets(name);
	    strcat(name,".dat");
	    f.open(name,ios::binary|ios::in);
	    ox=71;
	    while(f.read((char*)&s,sizeof(s)))
	    s.read();
	}
	if((x>=45&&x<=68)&&(y>=87&&y<=92)&&(cl==1)&&(flag==1))

	{
	    closegraph();
	    n.draw();
	    outtextxy(71,68,"Enter name of file: ");
	    gotoxy(28,5);
	    gets(name);
	    strcat(name,".dat");
	    f.open(name,ios::binary|ios::app);
	    s.write() ;
	    f.write((char*)&s,sizeof(s));
	    f.close();
	    outtextxy(71,375,"Done(0.08s)");
	}
	if((x>=85&&x<=114)&&(y>=50&&y<=58)&&(cl==1))

	{
	    flag=2;
	    closegraph();
	    system("CLS");
	    n. draw();
	    setfillstyle(SOLID_FILL,n.popup);
	    bar(81,60,139,72);
	    rectangle(81,60,139,72);
	    outtextxy(82,62,"Details");
	}
	if((x>=83&&x<=135)&&(y>=63&&y<=69)&&(cl==1)&&(flag==2))

	{
	    closegraph();
	    n.draw();
	    outtextxy(71,68,"Enter name of file: ");
	    gotoxy(28,5);
	    gets(name);
	    strcat(name,".dat");
	    count_words(name);
	}
	if((x>=121&&x<=155)&&(y>=51&&y<=57)&&(cl==1))

	{
	    flag=3;
	    closegraph();
	    system("CLS");
	    n.draw();
	    setfillstyle(SOLID_FILL,n.popup);
	    bar(121,60,200,90);
	    rectangle(121,60,200,90);
	    outtextxy(121,63,"Developers");
	    outtextxy(121,72,"About");
	    outtextxy(121,81,"Bugs");
	}
	if((x>=121&&x<=199)&&(y>=63&&y<=68)&&(cl==1)&&(flag==3))

	{
	    closegraph();
	    n.draw();
	    outtextxy(63,140,"1. VIBHOOTHI");
	}
	if((x>=121&&x<=157)&&(y>=72&&y<=79)&&(cl==1)&&(flag==3))

	{
	    closegraph();
	    n.draw();
	    outtextxy(100,100,"NOTEPAD++");
	}
	if((x>=121&&x<=149)&&(y>=81&&y<=87)&&(cl==1)&&(flag==3))

	{
	    closegraph();
	    n.draw();
	    outtextxy(60,81,"The bugs include:");
	    outtextxy(60,90,"1. The user can enter entire range but");
	    outtextxy(60,99,"  cannot restrict to the defined region. ");
	    outtextxy(60,108,"2. The input is in text mode and may cause");
	    outtextxy(60,117,"  problems.");
	    outtextxy(60,126,"3. The output file is suppose at 65 and");
	    outtextxy(60,135,"  ends at 85 then again opened output ");
	    outtextxy(60,144,"  then it would start from 85.");
	    outtextxy(60,153,"4. The output of text is not intelligent");
	    outtextxy(60,162,"  to detect words.");
	    outtextxy(60,171,"5. The no of words lines letters output");
	    outtextxy(60,180,"  is in text mode.");
	    outtextxy(60,189,"6. The output screen will have some black");
	    outtextxy(60,198,"  spots or the graphics part may be like ");
	    outtextxy(60,207,"  erased if mouse cursor is dragged from ");
	    outtextxy(60,216,"  one place to  another so creating a");
	    outtextxy(60,225,"  ugly look.");

	}

  }

}