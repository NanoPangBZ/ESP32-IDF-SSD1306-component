set(srcs    "src/ssd1306.cpp" 
            "hal/spi_4wire_hal/ssd1306_spi4_hal.c"
            )

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS "src" "hal" "."
                    REQUIRES "driver" "esp_system")
