#ifndef _oled12864_hal_h
#define _oled12864_hal_h

#include "esp_system.h"
#include "ssd1306.h"

#define x_MAX           128
#define y_MAX           64
#define page_MAX        8
//引脚编号
#define SSD1306_D1  25
#define SSD1306_D0  33
#define OLED_MOSI   SSD1306_D1
#define OLED_SCL    SSD1306_D0
#define OLED_CS     14
#define OLED_RES    26
#define OLED_DC     27

#define OLED_CMD    0
#define OLED_DATA   1

void Init(void*);
void Deint(void*);
void sendCmd(uint8_t*cmd,uint8_t len,void*);
void sendDat(uint8_t*dat,uint8_t len,void*);

#endif  //_oled12864_hel_h


