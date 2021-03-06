/*
  落下棒 Version 2.00  for PC-98/EPSON PC
			制作 １９９４ ＣＣＣ ＳＯＦＴ
*/

#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <pc98.h>
#include <dos.h>


void b_start(); /* 落下棒の画面 */
void menu(); /* 落下棒　ＭＥＮＵ選択 */
void game(); /* 落下棒の中身 */
void okms(char om[20],int aa); /* メッセージ表示 */
int pckey(); /* キ−反応 */
void sen(); /* 伸びる線 */
void sp_check(); /* スペースキーのチェック */
void casol(int iti); /* カーソル位置 */
void bcas(); /* カーソル位置 */
void end();
int main();

int nag=140;
int spd=8;

int main()
	{
	int c1=0,c2,c3,pk;
	printf("\033[>1h");
	pk=peekb(0,0x500);
	pk|=32;
	pokeb(0,0x500,pk);
	g_init();
	info(100,170,8,5,15);
	delay(2100);
	setcolor(0);
	for(c2=0;c2<13;c2++)
	  {
	  for(c3=0;c3<5;c3++)
	    line(100,c3*12+170+c2,564,c3*12+170+c2);
	  delay(10);
	  }
	delay(1000);
	b_start();
	while(c1==0)
	  {
	  printf("\033[22;6Hスペースキーで");
	  printf("\033[23;6H ゲームを始めます");
	  menu();
	  printf("\033[22;0H\033[2M\033[31m");
	  printf("\033[22;8Hゲームを");
	  printf("\033[23;9H開始しました\033[37m");
	  game();
	  }
	return;
	}
void b_start() /* 落下棒の画面 */
	{
	int ly;

	for(ly=0;ly<=399;ly++)
	  {
	  setcolor(1);
	  line(5,ly,634,ly);
	  delay(2);
	  }
	for(ly=5;ly<=205;ly++)
	  {
	  setcolor(2);
	  line(ly,0,ly,400);
	  line(640-ly,0,640-ly,400);
	  delay(2);
	  }

	bigzi_w(9,12,4,1,4,"落下棒",-2,-2);
	info(452,330,3,5,1);
	info(450,328,3,5,4);
	setfillstyle(1,8);
	bar(9,113,200,316);
	bar(9,325,200,380);
	setlinestyle(0,0,3);
	setcolor(15);
	rectangle(9,113,200,316);
	line(350,200,434,200);
	rectangle(9,325,200,380);

	printf("\033[2;60H》 制作関係者 《");
	printf("\033[4;61H原案");
	printf("\033[5;65H三上  威");
	printf("\033[7;61H制作");
	printf("\033[8;65H三上  威");
	printf("\033[10;61Hテスト");
	printf("\033[11;65H宇野 健一");
	printf("\033[12;65H楠元 太朗");
	printf("\033[13;65H才上  浄");
	printf("\033[16;60H》 使用ソフト 《");
	printf("\033[18;61HＴＵＲＢＯ Ｃ＋＋");

	printf("\033[9;4H＝＝＝ＭＥＮＵ＝＝＝");
	printf("\033[41m\033[11;5H  ゲームスタート  \033[37m");
	printf("\033[13;5H   棒の長さ調節   ");
	printf("\033[15;5H   落下速度調節   ");
	bigzi_s(23,256,1,15,"低速 普通 高速 激速");
	printf("\033[31m\033[17;4H低速");
	printf("\033[19;5H     ＥＸＩＴ     \033[37m");
	}
void menu() /* 落下棒　ＭＥＮＵ選択 */
	{
	int a1=0,a2=0;
	union REGS regs;
	setcolor(15);
	line(350,200,434,200);
	setfillstyle(1,11);
	bar(290,150-nag,348,150);
	while(a1==0)
	  {
	  switch(pc98key(0))
	    {
	    case 0x3a00: /* 上 */
	    case 0x4338: /* 上 */
	      if(a2!=0)
	        a2=a2-1;
	      else
	        a2=3;
	      casol(a2);
	      break;
	    case 0x3d00: /* 下 */
	    case 0x4b32: /* 下 */
	      if(a2!=3)
	        a2=a2+1;
	      else
	        a2=0;
	      casol(a2);
	      break;
	    case 0x3b00: /* 左 */
	    case 0x4634: /* 左 */
	      if(a2==1 && nag<140)
	        {
	        nag=nag+20;
	        setfillstyle(1,11);
	        bar(290,150-nag,348,150);
	        }
	      else
	        {
	        if(a2==2 && spd!=8)
	          {
	          spd=spd*2;
	          bcas();
	          }
	        }
	      break;
	    case 0x3c00: /* 右 */
	    case 0x4836: /* 右 */
	      if(a2==1 && nag>20)
	        {
	        nag=nag-20;
	        setfillstyle(1,1);
	        bar(290,0,348,150-nag);
	        }
	      else
	        {
	        if(a2==2 && spd!=1)
	          {
	          spd=spd/2;
	          bcas();
	          }
	        }
	      break;
	    case 0x3420: /* スペース */
	      if(a2==0)
	        {
	        a1=1;
	        setcolor(4);
	        line(350,200,434,200);
	        }
	      else
	       {
	       if(a2==3)
	         end();
	         }
	      break;
	    default:
	      break;
	    }
	  regs.h.ah=4;
	  regs.h.al=0;
	  int86(0x18,&regs,&regs);
	  if((regs.h.ah & 0x1)==1)
	    end();
	  }
	sp_check();
	delay(50);
	return;
	}
void game() /* 落下棒の中身 */
	{
	int lin; /* 棒の底辺 */
	int b1=0,b2,b3;
	randomize();  /* 乱数の発生 */
	while(b1==0)
	  {
	  if(random(5000)==2558)
	    b1=1;
	  if(pckey()==' ')
	    b1=2;
	  }
	for(lin=150;lin<400;lin=lin+2) /* 棒を落とす */
	  {
	  if(b1!=2)
	    {
	    delay(spd);
	    setfillstyle(1,1);
	    bar(290,lin-nag,348,lin-nag+1);
	    setfillstyle(1,11);
	    bar(290,lin,348,lin+1);
	    if(pckey()==' ')
	      b1=2;
	    }
	  }
	if(b1==2)
	  {
	  b3=getpixel(300,199);
	  sen();
	  sp_check();
	  }
	if(b3==11)
	  okms("★☆ ＯＫ ☆★",0);
	else
	  okms("× ＭＩＳＳ ×",1);
	b1=0;
	while(b1==0)
	  {
	  if(pc98key(0)==0x3420)
	    b1=1;
	  }
	sp_check();
	printf("\033[22;0H\033[2M");
	delay(200);
	setfillstyle(1,1);
	bar(290,0,348,399);
	return;
	}
void okms(char om[20],int aa) /* メッセージ表示 */
	{
	printf("\033[22;0H\033[2M");
	printf("\033[22;7H\033[5;36m%s\033[0;37m",om);
	if(aa==0)
	  {
	  switch(nag)
	    {
	    case 140:
	    case 120:
	    case 100:
	      printf("\033[23;5Hこれぐらい序の口さ");
	      break;
	    case 80:
	    case 60:
	    case 40:
	      printf("\033[23;10Hムムッ！");
	      break;
	    case 20:
	      printf("\033[23;6Hこりゃまいった！");
	      break;
	    }
	  }
	}
int pckey() /* キ−反応 */
	{
	if(kbhit()!=0)
	  return(getch());
	return('0');
	}
void sen() /* 伸びる線 */
	{
	int e1;
	setcolor(4);
	for(e1=350;e1>226;e1--)
	  {
	  putpixel(e1,199,4);
	  putpixel(e1,200,4);
	  putpixel(e1,201,4);
	  delay(1);
	  }
	for(e1=226;e1<350;e1++)
	  {
	  putpixel(e1,199,1);
	  putpixel(e1,200,1);
	  putpixel(e1,201,1);
	  delay(1);
	  }
	}
void sp_check() /* スペースキーのチェック */
	{
	while(pckey()==' ');
	}
void casol(int iti) /* カーソル位置 */
	{
	printf("\033[31m\033[11;5H  ゲームスタート  \033[37m");
	printf("\033[13;5H   棒の長さ調節   ");
	printf("\033[15;5H   落下速度調節   ");
	printf("\033[31m\033[19;5H     ＥＸＩＴ     \033[37m");
	setfillstyle(1,8);
	printf("\033[22;0H\033[2M");
	switch(iti)
	  {
	  case 0:
	    printf("\033[41m\033[11;5H  ゲームスタート  \033[37m");
	    printf("\033[22;6Hスペースキーで");
	    printf("\033[23;6H ゲームを始めます");
	    break;
	  case 1:
	    printf("\033[47m\033[13;5H   棒の長さ調節   \033[37m");
	    printf("\033[22;4H棒の長さを←で長く");
	    printf("\033[23;4H →で短く調節します");
	    break;
	  case 2:
	    printf("\033[47m\033[15;5H   落下速度調節   \033[37m");
	    printf("\033[22;4H落下速度を←で遅く");
	    printf("\033[23;4H →で速く調節します");
	    break;
	  case 3:
	    printf("\033[41m\033[19;5H     ＥＸＩＴ     \033[37m");
	    printf("\033[22;6Hスペースキーで");
	    printf("\033[23;6H ゲームを終ります");
	    break;
	  }
	}
void bcas() /* カーソル位置 */
	{
	printf("\033[17;0H\033[2K");
	switch(spd)
	  {
	  case 8:
	    printf("\033[31m\033[17;4H低速");
	    break;
	  case 4:
	    printf("\033[31m\033[17;9H普通");
	    break;
	  case 2:
	    printf("\033[31m\033[17;14H高速");
	    break;
	  case 1:
	    printf("\033[31m\033[17;19H激速");
	    break;
	  }
	}
void end()
	{
	closegraph();
	printf("\033[>1l\033[2J\033[37m");
	printf("落下棒 Version 2.00\n");
	printf(" Copyright(c)1993 T.Mikami / CCC Soft");
	exit(1);
	}
