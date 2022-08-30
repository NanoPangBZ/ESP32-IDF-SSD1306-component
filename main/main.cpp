#include <stdio.h>

#include "lvgl.h"
#include "demos/lv_demos.h"

extern "C" void app_main(void){
    lv_disp_drv_t* disp_driver = NULL;
    disp_driver = new lv_disp_drv_t;

    lv_init();
    lv_disp_drv_init(disp_driver);
    lv_disp_drv_register(disp_driver);

    lv_demo_widgets();

    while(1){
        lv_tick_inc(1);
        lv_timer_handler();
    }
}

