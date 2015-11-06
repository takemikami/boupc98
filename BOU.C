/*
  —‰º–_ Version 2.00  for PC-98/EPSON PC
			§ì ‚P‚X‚X‚S ‚b‚b‚b ‚r‚n‚e‚s
*/

#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <pc98.h>
#include <dos.h>


void b_start(); /* —‰º–_‚Ì‰æ–Ê */
void menu(); /* —‰º–_@‚l‚d‚m‚t‘I‘ğ */
void game(); /* —‰º–_‚Ì’†g */
void okms(char om[20],int aa); /* ƒƒbƒZ[ƒW•\¦ */
int pckey(); /* ƒL|”½‰ */
void sen(); /* L‚Ñ‚éü */
void sp_check(); /* ƒXƒy[ƒXƒL[‚Ìƒ`ƒFƒbƒN */
void casol(int iti); /* ƒJ[ƒ\ƒ‹ˆÊ’u */
void bcas(); /* ƒJ[ƒ\ƒ‹ˆÊ’u */
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
	  printf("\033[22;6HƒXƒy[ƒXƒL[‚Å");
	  printf("\033[23;6H ƒQ[ƒ€‚ğn‚ß‚Ü‚·");
	  menu();
	  printf("\033[22;0H\033[2M\033[31m");
	  printf("\033[22;8HƒQ[ƒ€‚ğ");
	  printf("\033[23;9HŠJn‚µ‚Ü‚µ‚½\033[37m");
	  game();
	  }
	return;
	}
void b_start() /* —‰º–_‚Ì‰æ–Ê */
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

	bigzi_w(9,12,4,1,4,"—‰º–_",-2,-2);
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

	printf("\033[2;60Ht §ìŠÖŒWÒ s");
	printf("\033[4;61HŒ´ˆÄ");
	printf("\033[5;65HOã  ˆĞ");
	printf("\033[7;61H§ì");
	printf("\033[8;65HOã  ˆĞ");
	printf("\033[10;61HƒeƒXƒg");
	printf("\033[11;65H‰F–ì Œ’ˆê");
	printf("\033[12;65H“íŒ³ ‘¾˜N");
	printf("\033[13;65HËã  ò");
	printf("\033[16;60Ht g—pƒ\ƒtƒg s");
	printf("\033[18;61H‚s‚t‚q‚a‚n ‚b{{");

	printf("\033[9;4H‚l‚d‚m‚t");
	printf("\033[41m\033[11;5H  ƒQ[ƒ€ƒXƒ^[ƒg  \033[37m");
	printf("\033[13;5H   –_‚Ì’·‚³’²ß   ");
	printf("\033[15;5H   —‰º‘¬“x’²ß   ");
	bigzi_s(23,256,1,15,"’á‘¬ •’Ê ‚‘¬ Œƒ‘¬");
	printf("\033[31m\033[17;4H’á‘¬");
	printf("\033[19;5H     ‚d‚w‚h‚s     \033[37m");
	}
void menu() /* —‰º–_@‚l‚d‚m‚t‘I‘ğ */
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
	    case 0x3a00: /* ã */
	    case 0x4338: /* ã */
	      if(a2!=0)
	        a2=a2-1;
	      else
	        a2=3;
	      casol(a2);
	      break;
	    case 0x3d00: /* ‰º */
	    case 0x4b32: /* ‰º */
	      if(a2!=3)
	        a2=a2+1;
	      else
	        a2=0;
	      casol(a2);
	      break;
	    case 0x3b00: /* ¶ */
	    case 0x4634: /* ¶ */
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
	    case 0x3c00: /* ‰E */
	    case 0x4836: /* ‰E */
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
	    case 0x3420: /* ƒXƒy[ƒX */
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
void game() /* —‰º–_‚Ì’†g */
	{
	int lin; /* –_‚Ì’ê•Ó */
	int b1=0,b2,b3;
	randomize();  /* —”‚Ì”­¶ */
	while(b1==0)
	  {
	  if(random(5000)==2558)
	    b1=1;
	  if(pckey()==' ')
	    b1=2;
	  }
	for(lin=150;lin<400;lin=lin+2) /* –_‚ğ—‚Æ‚· */
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
	  okms("š™ ‚n‚j ™š",0);
	else
	  okms("~ ‚l‚h‚r‚r ~",1);
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
void okms(char om[20],int aa) /* ƒƒbƒZ[ƒW•\¦ */
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
	      printf("\033[23;5H‚±‚ê‚®‚ç‚¢˜‚ÌŒû‚³");
	      break;
	    case 80:
	    case 60:
	    case 40:
	      printf("\033[23;10Hƒ€ƒ€ƒbI");
	      break;
	    case 20:
	      printf("\033[23;6H‚±‚è‚á‚Ü‚¢‚Á‚½I");
	      break;
	    }
	  }
	}
int pckey() /* ƒL|”½‰ */
	{
	if(kbhit()!=0)
	  return(getch());
	return('0');
	}
void sen() /* L‚Ñ‚éü */
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
void sp_check() /* ƒXƒy[ƒXƒL[‚Ìƒ`ƒFƒbƒN */
	{
	while(pckey()==' ');
	}
void casol(int iti) /* ƒJ[ƒ\ƒ‹ˆÊ’u */
	{
	printf("\033[31m\033[11;5H  ƒQ[ƒ€ƒXƒ^[ƒg  \033[37m");
	printf("\033[13;5H   –_‚Ì’·‚³’²ß   ");
	printf("\033[15;5H   —‰º‘¬“x’²ß   ");
	printf("\033[31m\033[19;5H     ‚d‚w‚h‚s     \033[37m");
	setfillstyle(1,8);
	printf("\033[22;0H\033[2M");
	switch(iti)
	  {
	  case 0:
	    printf("\033[41m\033[11;5H  ƒQ[ƒ€ƒXƒ^[ƒg  \033[37m");
	    printf("\033[22;6HƒXƒy[ƒXƒL[‚Å");
	    printf("\033[23;6H ƒQ[ƒ€‚ğn‚ß‚Ü‚·");
	    break;
	  case 1:
	    printf("\033[47m\033[13;5H   –_‚Ì’·‚³’²ß   \033[37m");
	    printf("\033[22;4H–_‚Ì’·‚³‚ğ©‚Å’·‚­");
	    printf("\033[23;4H ¨‚Å’Z‚­’²ß‚µ‚Ü‚·");
	    break;
	  case 2:
	    printf("\033[47m\033[15;5H   —‰º‘¬“x’²ß   \033[37m");
	    printf("\033[22;4H—‰º‘¬“x‚ğ©‚Å’x‚­");
	    printf("\033[23;4H ¨‚Å‘¬‚­’²ß‚µ‚Ü‚·");
	    break;
	  case 3:
	    printf("\033[41m\033[19;5H     ‚d‚w‚h‚s     \033[37m");
	    printf("\033[22;6HƒXƒy[ƒXƒL[‚Å");
	    printf("\033[23;6H ƒQ[ƒ€‚ğI‚è‚Ü‚·");
	    break;
	  }
	}
void bcas() /* ƒJ[ƒ\ƒ‹ˆÊ’u */
	{
	printf("\033[17;0H\033[2K");
	switch(spd)
	  {
	  case 8:
	    printf("\033[31m\033[17;4H’á‘¬");
	    break;
	  case 4:
	    printf("\033[31m\033[17;9H•’Ê");
	    break;
	  case 2:
	    printf("\033[31m\033[17;14H‚‘¬");
	    break;
	  case 1:
	    printf("\033[31m\033[17;19HŒƒ‘¬");
	    break;
	  }
	}
void end()
	{
	closegraph();
	printf("\033[>1l\033[2J\033[37m");
	printf("—‰º–_ Version 2.00\n");
	printf(" Copyright(c)1993 T.Mikami / CCC Soft");
	exit(1);
	}
