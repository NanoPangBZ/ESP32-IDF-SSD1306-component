idf_component_register(SRCS "main.cpp"
                            "OLED/oled.cpp"
                    INCLUDE_DIRS "." "OLED"
                    REQUIRES  "ssd1306")
