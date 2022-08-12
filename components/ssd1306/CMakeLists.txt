set(srcs "src/ssd1306.cpp")

idf_component_register(SRCS "${srcs}"
                    INCLUDE_DIRS "src" "hal"
                    REQUIRES "driver" "esp_system")
