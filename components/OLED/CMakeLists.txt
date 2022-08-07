set(srcs "src/oled12864.c"
         "src/oled12864_hal.c")

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS "include"
                    REQUIRES "driver" "esp_system" "esp_timer")
