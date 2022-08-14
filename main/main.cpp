#if 1
#include "oled.h"
#include "freertos\FreeRTOS.h"
#include "freertos\task.h"

extern Ssd1306_hal_handle_t oled_spi4_fun_t;

extern "C" void app_main(void){
    auto oled = Oled::getInstance();
    oled->autoRefresh(200);
    oled->displayString(0,0,"HelloWorld!",1);
    while(1){
        uint8_t x1,y1,x2,y2;
        x1 = x2 = y1 = y2 = 0;
        for(uint16_t t=0;t<384;t++){
            oled->clear();
            oled->drawLine(x1,y1,x2,y2);
            if(t<64){
                x1 = t;
                y1 = 0;
                x2 = t+64;
                y2 = 0;
            }else if(t<128){
                x1 = t;
                y1 = 0;
                x2 = 128;
                y2 = t - 64;
            }else if(t<192){
                x1 = 127;
                y1 = t - 128;
                x2 = 256 - t;
                y2 = 63;
            }else if(t<320){
                x2 = 128 - (t - 192);
                y1 = 127;
                x1 = x1 - 63;
                y2 = 127;
            }
            vTaskDelay(20/portTICK_RATE_MS);
        }
    }

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
