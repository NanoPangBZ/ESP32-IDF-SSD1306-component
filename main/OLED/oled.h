#ifndef _Oled_h
#define _Oled_h

#include "ssd1306.h"
#include "esp_timer.h"

class Oled : public Ssd1306{
public:
    static Oled* getInstance();
    static void destroy();
    void autoRefresh(int fre);
private:
    Oled(Ssd1306_hal_handle_t *handle) : Ssd1306(handle){};
    virtual ~Oled(){};
    static Oled *_oled;
    esp_timer_handle_t      _timer;
    esp_timer_create_args_t _args;
};

#endif


