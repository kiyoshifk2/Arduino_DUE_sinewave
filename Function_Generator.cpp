//
//	Function Generator
//
#include <Arduino.h>
#include <stdarg.h>
#include "lcd.h"
#include "tch.h"
#include "menu.h"

void func_gene_out(unsigned long freq);
void set_freq(unsigned long freq);

/********************************************************************************/
/*		func_gene_main															*/
/********************************************************************************/
struct menu func_gene_main_menu[]={
	{15, 60, 3, 100, "KH"},
	{15,100, 3, 101, "Hz"},
	{15,140, 3, 102, "C"},
	{15,180, 3, 103, "AC"},
	
	{63, 60, 3, '7', "7"},
	{63,100, 3, '4', "4"},
	{63,140, 3, '1', "1"},
	{63,180, 3, '0', "0"},
	
	{111, 60, 3, '8', "8"},
	{111,100, 3, '5', "5"},
	{111,140, 3, '2', "2"},
//	{111,180, 3, '.', "."},
	
	{159, 60, 3, '9', "9"},
	{159,100, 3, '6', "6"},
	{159,140, 3, '3', "3"},
//	{159,180, 3, '=', "="},
	
	{0,0,0,0,0},
};


void func_gene_main()
{
	int cmd, len, freq;
  char func_str[50];
	
	lcd_clear(BLACK);
	for(;;){
		/*** 周波数表示 ***/
		lcd_clearA(0,0,319,40,BLACK);
		lcd_disp_str_x2(0,0,func_str);
		
		btn_back_color = YELLOW;
		cmd = menu_select(func_gene_main_menu);
		switch(cmd){
			case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
				len = strlen(func_str);
				func_str[len] = cmd;
				func_str[len+1] = 0;
				break;
      case 103:           // AC
        func_str[0] = '\0';
        break;
      case 102:           // C
        len = strlen(func_str);
        if(len){
          func_str[len-1] = '\0';
        }
        break;
      case 100:           // KHz
        freq = atoi(func_str) * 1000;
        strcat(func_str, "KHz");
        /*** 周波数表示 ***/
        lcd_clearA(0,0,319,40,BLACK);
        lcd_disp_str_x2(0,0,func_str);

        func_gene_out(freq);
        break;
      case 101:           // Hz
        freq = atoi(func_str);
        strcat(func_str, "Hz");
        /*** 周波数表示 ***/
        lcd_clearA(0,0,319,40,BLACK);
        lcd_disp_str_x2(0,0,func_str);

        func_gene_out(freq);
        break;
		}
	}
}

const unsigned char sine_tbl[]={
    128,
    130,
    132,
    134,
    136,
    138,
    141,
    143,
    145,
    147,
    149,
    151,
    154,
    156,
    158,
    160,
    162,
    164,
    166,
    168,
    170,
    172,
    174,
    175,
    177,
    179,
    181,
    183,
    184,
    186,
    188,
    189,
    191,
    192,
    194,
    195,
    197,
    198,
    199,
    201,
    202,
    203,
    204,
    205,
    207,
    208,
    208,
    209,
    210,
    211,
    212,
    213,
    213,
    214,
    214,
    215,
    215,
    216,
    216,
    216,
    217,
    217,
    217,
    217,
    217,
    217,
    217,
    217,
    217,
    216,
    216,
    216,
    215,
    215,
    214,
    214,
    213,
    213,
    212,
    211,
    210,
    209,
    208,
    208,
    207,
    205,
    204,
    203,
    202,
    201,
    199,
    198,
    197,
    195,
    194,
    192,
    191,
    189,
    188,
    186,
    184,
    183,
    181,
    179,
    177,
    175,
    174,
    172,
    170,
    168,
    166,
    164,
    162,
    160,
    158,
    156,
    154,
    151,
    149,
    147,
    145,
    143,
    141,
    138,
    136,
    134,
    132,
    130,
    128,
    125,
    123,
    121,
    119,
    117,
    114,
    112,
    110,
    108,
    106,
    104,
    101,
    99,
    97,
    95,
    93,
    91,
    89,
    87,
    85,
    83,
    81,
    80,
    78,
    76,
    74,
    72,
    71,
    69,
    67,
    66,
    64,
    63,
    61,
    60,
    58,
    57,
    56,
    54,
    53,
    52,
    51,
    50,
    48,
    47,
    47,
    46,
    45,
    44,
    43,
    42,
    42,
    41,
    41,
    40,
    40,
    39,
    39,
    39,
    38,
    38,
    38,
    38,
    38,
    38,
    38,
    38,
    38,
    39,
    39,
    39,
    40,
    40,
    41,
    41,
    42,
    42,
    43,
    44,
    45,
    46,
    47,
    47,
    48,
    50,
    51,
    52,
    53,
    54,
    56,
    57,
    58,
    60,
    61,
    63,
    64,
    66,
    67,
    69,
    71,
    72,
    74,
    76,
    78,
    80,
    81,
    83,
    85,
    87,
    89,
    91,
    93,
    95,
    97,
    99,
    101,
    104,
    106,
    108,
    110,
    112,
    114,
    117,
    119,
    121,
    123,
    125,
};

/************************************************/
/*      DAC に正弦波データを出力する            */
/************************************************/
//typedef union{
//    ulong l;
//    struct{
//        uchar c0;
//        uchar c1;
//        uchar c2;
//        uchar c3; 
//    };
//} freq_data;
//
//freq_data phase;
unsigned short inc, phase;

void func_gene_out(unsigned long freq)
{
	unsigned long time1, time2;
	
	set_freq(freq);
	time1 = micros();
	for(;;){
		time2 = micros();
		while(time2-time1 < 10)
			time2 = micros();
		time1 += 10;
		phase += inc;
		analogWrite(66, sine_tbl[phase>>8]);
	}
}



//void __interrupt() isr()
//{
//    PIR1bits.TMR2IF = 0;   // 割り込みフラグクリア
//    phase.l += inc;
//}
/************************************************/
/*      set_freq                                */
/*      周波数を設定する                        */
/************************************************/
void set_freq(unsigned long freq)
{
    inc = (65536UL*freq+50000)/100000;
}
