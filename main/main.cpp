#include "oled.h"
#include "freertos\FreeRTOS.h"
#include "freertos\task.h"

#include <stdio.h>

extern Ssd1306_hal_handle_t oled_spi4_fun_t;

extern "C" void app_main(void){
    auto oled = Oled::getInstance();
    uint8_t x = 0;
    oled->autoRefresh(200);
    oled->drawLine(127,0,63,31);
    oled->drawLine(0,0,63,31);
    while(1){
        oled->clear();
        oled->drawLine(x,1,63,32);
        oled->drawLine(128 - x,1,63,32);
        x++;
        if(x > 128){
            x = 0;
        }
        vTaskDelay( 20 );
    }

}

