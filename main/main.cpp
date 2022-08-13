#if 1
#include "ssd1306.h"

extern Ssd1306_hal_handle_t oled_spi4_fun_t;

extern "C" void app_main(void){
    auto oled = new Ssd1306(&oled_spi4_fun_t);
    for(uint8_t x=0;x<128;x++){
        for(uint8_t y=0;y<64;y++){
            oled->drawPoint(x,y,1);
        }
    }   
    oled->refresh();
}
#endif

#if 0
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "oled12864.h"
#include "driver\gpio.h"
#include "freertos\FreeRTOS.h"
#include "freertos\task.h"

extern "C" void app_main(void)
{
    srand((unsigned int)time(0));
    OLED12864_Init();
    OLED12864_Auto_Refresh(200);
    //OLED12864_Draw_Line(0,0,64,32);
    //OLED12864_Draw_Line(128,0,64,32);
    //OLED12864_Draw_Rect(0,0,127,63);
    //OLED12864_Show_String(5,32,(uint8_t*)"HelloWorld",1);
    OLED12864_Show_String(12,35,(uint8_t*)"HelloWorld!",2);
    while(1){
        int x = rand()%128;
        int y = rand()%64;
        OLED12864_Draw_Point(x,y,rand()%2-1);
        
        vTaskDelay(100/portTICK_RATE_MS);
    }
}
#endif
