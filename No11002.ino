#include "lcd.h"
#include "tch.h"
#include "menu.h"


void pentomino(int fast);
void func_gene_main();

const struct menu main_menu[]={
  {0,   0, 12, 1, "pentomino 1"},
  {0,  60, 12, 2, "pentomino 2"},
  {0, 120, 12, 3, "Func.Gene."},
  {0, 180, 12, 4, ""},
  
  {157,  0, 12, 5, ""},
  {157, 60, 12, 6, ""},
  {157,120, 12, 7, ""},
  {157,180, 12, 8, ""},
  {0,0,0,0,0},
};


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
	lcd_init();
}

void loop() {
  int cmd;

    btn_back_color = GREEN;
    cmd = menu_select0(main_menu);
    switch(cmd){
      case 1:
        pentomino(1);
        break;
      case 2:
        pentomino(0);
        break;
      case 3:
        func_gene_main();
        break;
            case 4:
//                game_main();
        break;
      case 5:
//        calc_main();
        break;
      case 6:
//        oscillo();
        break;
      case 7:
//        spectrumanalizer();
        break;
      case 8:
//        m_measure();
        break;
    }
}

