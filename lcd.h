//
//  15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
// |�E��E�   BRUE   �E��E�|�E��E�    GREEN    �E��E�|�E��E�    RED   �E��E�|
//  R:0�E�`255, G:0�E�`255, B:0�E�`255 ... �E��E��E� 5�E��E��E��E�6bit �E�g�E�p
#define RGB(R,G,B) ((((B) & 0xf8)<<8) | (((G) & 0xfc)<<3) | (((R) & 0xf8)>>3))
#define RGB2R(RGB) (((RGB)<<3) & 0xf8)
#define RGB2G(RGB) (((RGB)>>3) & 0xfc)
#define RGB2B(RGB) (((RGB)>>8) & 0xf8)

#define BLACK RGB(0,0,0)
#define WHITE RGB(255,255,255)
#define GRAY  RGB(192,192,192)
#define RED   RGB(255,0,0)        // �E��E��E��E��E�܂�
#define GREEN RGB(0,255,0)
#define BRUE  RGB(0,0,255)
#define CYAN  RGB(0,255,255)
#define MAGENTA RGB(255,0,255)
#define YELLOW  RGB(255,255,0)

#define LCD_RST   58
#define LCD_CS    57
#define LCD_RS    56
#define LCD_WR    55
#define LCD_RD    54
#define LCD_D0    8
#define LCD_D1    9
#define LCD_D2    2
#define LCD_D3    3
#define LCD_D4    4
#define LCD_D5    5
#define LCD_D6    6
#define LCD_D7    7

#define ColumnAddressSet 0x2a
#define PageAddressSet   0x2b
#define MemoryRead       0x2e
#define MemoryWrite      0x2c

extern int back_color;
extern int text_color;
extern int keisen_color;
extern int graph_color;
extern int lcd_x;                  // 0�E�E�E�`25
extern int lcd_y;                  // 0�E�E�E�`14
extern int lcd_noofline;            // �E�E�E�P�E�E�E��E�E�E�ʂ̍s�E�E�E��E�E�E�
extern char lcd_text_buf[15][26];
extern const short font[256][16];

void lcd_scroll();
void lcd_nl();
int lcd_disp_char_x1(int x, int y, char c);
int lcd_disp_char_x2(int x, int y, char c);
void lcd_disp_str_x1(int x, int y, const char *str);
void lcd_disp_str_x2(int x, int y, const char *str);
void lcd_init();
void lcd_printf(const char *fmt, ...);
void lcd_puts(const char *str);
void lcd_putc(char c);
int lcd_clear(int color);
int lcd_clearA(int x1, int y1, int x2, int y2, int color);
int lcd_area_set(int x1, int y1, int x2, int y2);
void lcd_write_data(int data);
void lcd_write_cmd(int data);
void lcd_write_color(int color);
void lcd_clear1(char color);
void lcd_clear_B();
void lcd_clear_W();
void lcd_read_mem(int x1, int y1, int x2, int y2, short *buf);
void lcd_write_square(int x, int y, int w, int h, const short *pat);
int message(const char *fmt, ...);
void fatal(const char *msg1, const char *msg2, const char *msg3);
