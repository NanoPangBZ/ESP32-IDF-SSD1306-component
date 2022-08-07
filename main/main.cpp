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
    OLED12864_Draw_Line(0,0,64,32);
    OLED12864_Draw_Line(128,0,64,32);
    OLED12864_Draw_Rect(0,0,127,63);
    OLED12864_Show_String(5,32,(uint8_t*)"HelloWorld",1);
    while(1){
        int x = rand()%128;
        int y = rand()%64;
        OLED12864_Draw_Point(x,y,rand()%2-1);
        vTaskDelay(5/portTICK_RATE_MS);
    }
}
