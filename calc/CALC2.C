#include <bios.h>
#include <dos.h>
#include <dosvideo.h>


#define ZLIWA	21

#define COLORFON_BACK   LIGHTCYAN
#define COLORFON_TEXT   DARKGRAY
#define COLORCNOP_BACK   LIGHTBLUE
#define COLORCNOP_TEXT   WHITE


char knop[][3][3]={
	{"7","8","6"},
	{"8","14","6"},
	{"9","20","6"},
	{"*","26","6"},
	{"4","8","10"},
	{"5","14","10"},
	{"6","20","10"},
	{"/","26","10"},
	{"1","8","14"},
	{"2","14","14"},
	{"3","20","14"},
	{"+","26","14"},
	{"D","8","18"},
	{"0","14","18"},
	{"-","20","18"},
	{"=","26","18"}
};

void main() {
	char key,kb[30],color,first[30],two[30],sum[60];
	struct colorrec col;
	struct colorrec colfon;
	struct colorrec colcnop; 
	struct recXY koord;
	int koef,kn,i,j,numb,znak,kilk;
	float f1,f2;
	float result;

	colcnop.coltext = COLORCNOP_TEXT;
	colcnop.colback = COLORCNOP_BACK;
	colfon.coltext = COLORFON_TEXT;
	colfon.colback = COLORFON_BACK;
	koef = 0;
	numb = 0;
	clear();
	_setcursortype(0);
	koord.x1 = ZLIWA + 0;
	koord.y1 = 0;
	koord.x2 = ZLIWA + 36;
	koord.y2 = 22;
	col.coltext = COLORFON_TEXT;
	col.colback = COLORFON_BACK;
	rectan(koord, col, '2', '1', '0');
	col.coltext = COLORCNOP_TEXT;
	col.colback = COLORCNOP_BACK;
	color = setColor(col);
	for( i=0; i<16; i++ )
		knopka((char)(ZLIWA+atoi(knop[i][1])-1), (char)(atoi(knop[i][2])-1), col, knop[i][0], '1', color);
	space(ZLIWA+3,2,color,30);

	while (key!=0X1b) {
		key=bioskey(0);
		switch (key) {
		case 0x30:
			numb=13;
			kb[koef]='0';
			koef++;
			kn=1;
			kb[koef]=0x0;
			break;
		case 0x31:
			numb=8;
			kb[koef]='1';
			koef++;
			kn=1;
			kb[koef]=0x0;
			break;
		case 0x32:
			numb=9;
			kb[koef]='2';
			koef++;
			kn=1;
			kb[koef]=0x0;
			break;
		case 0x33:
			numb=10;
			kb[koef]='3';
			koef++;
			kn=1;
			kb[koef]=0x0;
			break;
		case 0x34:
			numb=4;
			kb[koef]='4';
			koef++;
			kn=1;
			kb[koef]=0x0;
			break;
		case 0x35:
			numb=5;
			kb[koef]='5';
			koef++;
			kn=1;
			kb[koef]=0x0;
			break;
		case 0x36:
			numb=6;
			kb[koef]='6';
			koef++;
			kn=1;
			kb[koef]=0x0;
			break;
		case 0x37:
			numb=0;
			kb[koef]='7';
			koef++;
			kn=1;
			kb[koef]=0x0;
			break;
		case 0x38:
			numb=1;
			kb[koef]='8';
			koef++;
			kn=1;
			kb[koef]=0x0;
			break;
		case 0x39:
			numb=2;
			kb[koef]='9';
			koef++;
			kn=1;
			kb[koef]=0x0;
			break;
		case 0x2a:
			numb=3;
			kb[koef]='*';
			kilk=koef;
			znak=1;
			kn=1;
			koef++;
			kb[koef]=0x0;
			break;
		case 0x2f:
			numb=7;
			kb[koef]='/';
			kilk=koef;
			znak=2;
			kn=1;
			koef++;
			kb[koef]=0x0;
			break;
		case 0x2b:
			numb=11;
			kb[koef]='+';
			kilk=koef;
			znak=3;
			kn=1;
			koef++;
			kb[koef]=0x0;
			break;
		case 0x2d:
			numb=14;
			kb[koef]='-';
			kilk=koef;
			kn=1;
			znak=4;
			koef++;
			kb[koef]=0x0;
			break;
		case 0x00:
			numb=12;
			if (koef==0)
				koef++;
			koef--;
			kb[koef]=0x0;
			kn=1;
			break;
		case 0x3d:
			numb=15;;
			kb[koef]='=';
			koef=0;
			for (i=0;i<kilk;i++) {
				first[i]=kb[i];
				first[i+1]=0x0;
			}
			for(i=kilk;kb[i]!='=';i++) {
				two[i-kilk-1]=kb[i];
				two[i-kilk]=0x0;
			}
			f1=atoi(first);
			f2=atoi(two);
			if (znak==1)
				result=(f1*f2);
			if (znak==2)
				result=(f1/f2);
			if (znak==3)
				result=(f1+f2);
			if (znak==4)
				result=(f1-f2);
			space(ZLIWA+3,2,color,30);
			sprintf(sum,"%f",result);
			string(ZLIWA+3,2,color,sum);
			if ((kb[0]=='*')||(kb[0]=='/')||(kb[0]=='-')||(kb[0]=='+')||(kb[kilk+1]=='=')||(kb[0]=='=')||(kb[kilk]!='*')&&(kb[kilk]!='/')&&(kb[kilk]!='-')&&(kb[kilk]!='+')) {
				for (i=0;sum[i]!=0x0;i++)
					sum[i]=0x0;
				sprintf(sum,"%s","error");
				space(ZLIWA+3,2,color,30);
				string(ZLIWA+3,2,color,sum);
			}
			for (i=0;sum[i]!=0x0;i++) sum[i]=0x0;
				kilk=0;
			for (i=0;kb[i]!=0x0;i++)
				kb[i]=0x0;
			knopka((char)(ZLIWA+atoi(knop[numb][1])-1), (char)(atoi(knop[numb][2])-1), colfon, 0x0, '0', color);
			knopka((char)(ZLIWA+atoi(knop[numb][1])), (char)(atoi(knop[numb][2])), colcnop, knop[numb][0], '0', color);
			delay(150);
			knopka((char)(ZLIWA+atoi(knop[numb][1])), (char)(atoi(knop[numb][2])), colfon, 0x0, '0', color);
			knopka((char)(ZLIWA+atoi(knop[numb][1])-1), (char)(atoi(knop[numb][2])-1), colcnop, knop[numb][0], '1', color);
			break;
		}
		string(ZLIWA+3,2,color,kb);
		if (kn==1) {
			space(ZLIWA+3, 2, color, 30);
			string(ZLIWA+3,2,color, kb);
			knopka((char)(ZLIWA+atoi(knop[numb][1])-1), (char)(atoi(knop[numb][2])-1), colfon, 0x0, '0', color);
			knopka((char)(ZLIWA+atoi(knop[numb][1])), (char)(atoi(knop[numb][2])), colcnop, knop[numb][0], '0', color);
			delay(150);
			knopka((char)(ZLIWA+atoi(knop[numb][1])), (char)(atoi(knop[numb][2])), colfon, 0x0, '0', color);
			knopka((char)(ZLIWA+atoi(knop[numb][1])-1), (char)(atoi(knop[numb][2])-1), colcnop, knop[numb][0], '1', color);
		}
		kn=0;
	}
}
