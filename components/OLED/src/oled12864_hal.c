#include "oled12864_hal.h"
#include "freertos\FreeRTOS.h"
#include "freertos\task.h"
#include "driver\gpio.h"
#include "driver\spi_master.h"
#include "oled12864.h"
#include "esp_timer.h"
#include "stdlib.h"
#include "string.h"

static spi_device_handle_t  spi_handle;     //spi操作句柄


void OLED12864_GPIO_Init(void)
{
    gpio_set_direction((gpio_num_t)OLED_DC,GPIO_MODE_OUTPUT);
    gpio_set_direction((gpio_num_t)OLED_RES,GPIO_MODE_OUTPUT);
    OLED12864_Reset_Bit(OLED_DC);
    OLED12864_Set_Bit(OLED_RES);
}

void IRAM_ATTR OLED12864_SPI_Finnish_CallBack(spi_transaction_t *para){
    free((void*)para);
}

void IRAM_ATTR OLED12864_SPI_Start_CallBack(spi_transaction_t *para){
    if( (int)para->user == OLED_CMD){
        gpio_set_level((gpio_num_t)OLED_DC,0);
    }else{
        gpio_set_level((gpio_num_t)OLED_DC,1);
    }
}

void OLED12864_SPI_Init(void) //内部函数
{
    spi_bus_config_t buscfg={
        .miso_io_num = -1,
        .mosi_io_num = OLED_MOSI,
        .sclk_io_num = OLED_SCL,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4092,
    };
    spi_device_interface_config_t device_interface ={
        .clock_speed_hz = SPI_MASTER_FREQ_20M,
        .queue_size = 3,
        .mode = 3,
        .spics_io_num = OLED_CS,
        .post_cb = OLED12864_SPI_Finnish_CallBack,
        .pre_cb = OLED12864_SPI_Start_CallBack,
    };
    spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
    spi_bus_add_device(SPI2_HOST,&device_interface,&spi_handle);

}

void OLED12864_Set_Bit(int pin_Num){
    gpio_set_level((gpio_num_t)pin_Num,1);
}

void OLED12864_Reset_Bit(int pin_Num){
    gpio_set_level((gpio_num_t)pin_Num,0);
}

void OLED12864_Send_NumByte(const uint8_t*dat,uint16_t len,uint8_t cmd)
{
    spi_transaction_t *tran = (spi_transaction_t*)malloc(sizeof(spi_transaction_t));
    tran->tx_buffer = dat;
    tran->length = len*8;
    tran->rxlength = tran->length;
    tran->flags = SPI_TRANS_MODE_OCT;
    //数据在oled12864.c中是一个静态的局部变量
    //命令随机生成,得另外开辟内存用于存储命令 -> 在完成回调函数中释放
    if(cmd==OLED_CMD){
        tran->user = (void*)OLED_CMD;
    }else{
        tran->user = (void*)OLED_DATA;
    }
    spi_device_queue_trans(spi_handle,tran, 20 / portTICK_PERIOD_MS );
}

void OLED12864_delay_ms(uint16_t ms){
    vTaskDelay(ms/portTICK_PERIOD_MS);
}

static esp_timer_handle_t timer;
static esp_timer_create_args_t para;

void OLED12864_Auto_Callback(void*args){
    OLED12864_Refresh();
    //esp_timer_start_once(timer, *(int*)args);
}

void OLED12864_Auto_Refresh(float hz){
    para.callback = OLED12864_Auto_Callback;
    para.dispatch_method = ESP_TIMER_TASK;
    esp_timer_init();
    esp_timer_create(&para,&timer);
    esp_timer_start_once(timer, 1000/hz);
}
