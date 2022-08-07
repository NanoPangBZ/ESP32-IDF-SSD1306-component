#ifndef _oled12864_hal_h
#define _oled12864_hal_h

#include "esp_system.h"

//硬件相关宏定义,定义物理引脚名字 - 适用stm32f10x
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

void OLED12864_SPI_Init(void);
void OLED12864_GPIO_Init(void);

void OLED12864_Set_Bit(int pin_Num);
void OLED12864_Reset_Bit(int pin_Num);
void OLED12864_Send_NumByte(const uint8_t*dat,uint16_t len,uint8_t cmd);
void OLED12864_delay_ms(uint16_t ms);
void OLED12864_Auto_Refresh(float hz);

#endif  //_oled12864_hel_h


