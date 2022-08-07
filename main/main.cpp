#include <stdio.h>
#include "oled12864.h"
#include "driver\gpio.h"
#include "freertos\FreeRTOS.h"
#include "freertos\task.h"

extern "C" void app_main(void)
{
    OLED12864_Init();
    OLED12864_Draw_Line(0,0,64,32);
    OLED12864_Draw_Line(128,0,64,32);
    OLED12864_Draw_Rect(0,0,127,63);
    OLED12864_Show_String(5,32,(uint8_t*)"HelloWorld",1);
    OLED12864_Refresh();
    printf("HelloWorld!\n");
}
