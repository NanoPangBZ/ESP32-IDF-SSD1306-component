#include "oled.h"

Oled* Oled::_oled = NULL;

Oled* Oled::getInstance(){
    if(!_oled){
        _oled = new Oled(&oled_spi4_handle);
    }
    return _oled;
}

void Oled::destroy(){
    if(_oled){
        delete _oled;
        _oled = NULL;
    }
}

void _timerCallback(void*args){
    Oled *oled = (Oled*)args;
    oled->refresh();
}

void Oled::autoRefresh(int fre){
    _args.arg = (void*)this;
    _args.callback = _timerCallback;
    _args.dispatch_method = ESP_TIMER_TASK;
    esp_timer_init();
    esp_timer_create(&_args,&_timer);
    esp_timer_start_periodic(_timer, (int)1000000/fre);
}


