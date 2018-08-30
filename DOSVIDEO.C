#include <dosvideo.h>

char far *scrn=	(char far*) 0xB8000000;

/*clearing screen*/
void clear()
{       int i;
	for (i=0;i<80*25*2;i+=2)
	{
		scrn[i]=0;
		scrn[i+1]=0;
	}
}


/*Vuvid Sumvolu*/
void symb(char x, char y, char color, char sym)
{
	scrn [(x+y*80)*2]=sym;
	scrn [(x+y*80)*2+1]=color;
}
/*vuvid probilu*/
void space(unsigned char x, unsigned char y, unsigned char color,char len)

{   int i,j=0;
	char sym=32;
	for (i=0;i<len;i++)
	{
		scrn [(x+y*80)*2+j]=sym;
		scrn [(x+y*80)*2+1+j]=color;
		j+=2;
	}
}

/*Vuvid stroku*/
void string(unsigned char x,unsigned char y,unsigned char color, char *st)
{
	int i,j=0;
	for (i=0;st[i]!=0x0;i++)
	{
		scrn [(x+y*80)*2+j]=st[i];
		scrn [(x+y*80)*2+1+j]=color;
		j+=2;
	}
}

unsigned char setColor( struct colorrec toset ) {
	return ( (toset.colback<<4) | toset.coltext ) ^ (1<<7); //only light colors
}

/*maluje ramku    variab  '1'- probilu, '2'- odunarna ramka, '3'- podvijna ramka*/
/* font - zaluvae kolorom ramky ---  '1' - z zaluvkoj   '2' - bez zaluvku*/

void rectan(struct recXY koord,struct colorrec col,char variab,char font,char shad) {

	unsigned int i=0,j=0;
	char k1=0, k2=0, k3=0, k4=0, l1=0, l2=0, color, color_background,colortext;

	color = setColor(col);
	if (variab=='1')  /*malue probilu*/
			{
			l2=' ';
			l1=32;
			k1=32;
			k2=32;
			k3=32;
			k4=32;
			}
	if (variab=='2')     /*malue odunarny ramky*/
			{
			l2=179;
			l1=196;
			k2=191;
			k3=217;
			k4=192;
			k1=218;
			}
	if (variab=='3')      /*maluje podvijny ramku*/
			{
			l2=186;
			l1=205;
			k2=187;
			k3=188;
			k4=200;
			k1=201;
			}
	for (i=koord.x1;i<koord.x2+1;i++)
	{
		symb(i,koord.y1,color,l1);
		symb(i,koord.y2,color,l1);
	}
	for (i=koord.y1;i<koord.y2+1;i++)
	{
		symb(koord.x1,i,color,l2);
		symb(koord.x2,i,color,l2);
	}
	symb(koord.x1,koord.y1,color,k1);
	symb(koord.x2,koord.y1,color,k2);
	symb(koord.x2,koord.y2,color,k3);
	symb(koord.x1,koord.y2,color,k4);
	if (font=='1')
	{
		l1=255;
		for (j=koord.y1+1;j<koord.y2;j++)
		{
			for (i=koord.x1+1;i<koord.x2;i++)
			{
				symb(i,j,color,l1);
			}
		}
	}
	if (shad=='1') {
		colortext=((scrn[(koord.x1+1+(koord.y2+1)*80)*2+1])>>4)<<4|BLACK;
		for (i=koord.x1+1;i<koord.x2+1;i++)
			symb(i,koord.y2+1,colortext,223);
		for (i=koord.y1+1;i<koord.y2+1;i++)
			symb(koord.x2+1	,i,colortext,0xdb);
		symb(koord.x2+1	,i,colortext,0xdf);
	}
}

//maluje knopku
//shadow -'1' - maluje tin '2' bez tini
void knopka(char x, char y,struct colorrec col, char *sym,char shadow, char color){
	struct recXY koord;
	int i=1;
	while (sym[i]!=0x0)
		i++;
	koord.x1 = x ;
	koord.y1 = y ;
	koord.x2 = x + i + 1 ;
	koord.y2 = y + 2;
	rectan(koord, col, '1', '1', shadow);
	if (sym[0] != 0x0)
		string(koord.x1+1, koord.y1+1, color, sym);
}