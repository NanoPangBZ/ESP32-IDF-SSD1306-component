#if 1
#include "ssd1306.h"
#include "freertos\FreeRTOS.h"
#include "freertos\task.h"

extern Ssd1306_hal_handle_t oled_spi4_fun_t;

extern "C" void app_main(void){
    auto oled = new Ssd1306(&oled_spi4_fun_t);
    oled->displayString(1,1,"HelloWorld!",1);
    oled->displayString(12,17,"11111",2);
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
