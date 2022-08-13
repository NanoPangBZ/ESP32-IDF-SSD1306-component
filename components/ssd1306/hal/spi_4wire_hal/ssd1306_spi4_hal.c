#include "ssd1306_hal.h"

#include "freertos\FreeRTOS.h"
#include "freertos\task.h"
#include "driver\gpio.h"
#include "driver\spi_master.h"
#include "esp_log.h"

#define x_MAX           128
#define y_MAX           64
#define page_MAX        8
//引脚编号
#define SSD1306_D1  25
#define SSD1306_D0  33
#define OLED_MOSI   SSD1306_D1
#define OLED_SCL    SSD1306_D0
#define OLED_CS     14
#define OLED_RES    26
#define OLED_DC     27

#define OLED_CMD    0
#define OLED_DATA   1

#define TAG "ssd1306_spi4_hal"

Ssd1306_hal_handle_t oled_spi4_fun_t = {
    .buf = NULL,
    .ctx = NULL,
    .deinit = Deint,
    .init = Init,
    .sendCmd = sendCmd,
    .sendDat = sendDat,
};

static spi_device_handle_t  spi_handle;     //spi操作句柄

void OLED12864_Set_Bit(int pin_Num){
    gpio_set_level((gpio_num_t)pin_Num,1);
}

void OLED12864_Reset_Bit(int pin_Num){
    gpio_set_level((gpio_num_t)pin_Num,0);
}

void OLED12864_GPIO_Init(void)
{
    gpio_set_direction((gpio_num_t)OLED_DC,GPIO_MODE_OUTPUT);
    gpio_set_direction((gpio_num_t)OLED_RES,GPIO_MODE_OUTPUT);
    OLED12864_Reset_Bit(OLED_DC);
    OLED12864_Set_Bit(OLED_RES);
}

void IRAM_ATTR OLED12864_SPI_Start_CallBack(spi_transaction_t *para){
    if( (int)para->user == OLED_CMD){
        gpio_set_level((gpio_num_t)OLED_DC,0);
    }else{
        gpio_set_level((gpio_num_t)OLED_DC,1);
    }
}

void OLED12864_SPI_Init(void)
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
        .pre_cb = OLED12864_SPI_Start_CallBack,
        .flags = SPI_DEVICE_HALFDUPLEX,
    };
    spi_bus_initialize(SPI2_HOST, &buscfg, SPI_DMA_CH_AUTO);
    spi_bus_add_device(SPI2_HOST,&device_interface,&spi_handle);

}

void OLED12864_Send_NumByte(const uint8_t*dat,uint16_t len,uint8_t cmd)
{
    static spi_transaction_t tran;
    tran.tx_buffer = dat;
    tran.length = len*8;
    //tran.rxlength = tran.length;
    tran.flags = SPI_TRANS_MODE_OCT;
    if(cmd==OLED_CMD){
        tran.user = (void*)OLED_CMD;
    }else{
        tran.user = (void*)OLED_DATA;
    }
    spi_device_queue_trans(spi_handle,&tran, portMAX_DELAY );
}

void OLED12864_delay_ms(uint16_t ms){
    vTaskDelay(ms/portTICK_PERIOD_MS);
}

void Init(void*ctx){
    OLED12864_GPIO_Init();
    OLED12864_SPI_Init();
    OLED12864_Reset_Bit(OLED_RES);
    OLED12864_delay_ms(300);
    OLED12864_Set_Bit(OLED_RES);
    //ESP_LOGW(TAG,"Init");
}

void Deint(void*ctx){

}

void sendCmd(uint8_t* cmd,uint8_t len,void* ctx){
    OLED12864_Send_NumByte(cmd,len,OLED_CMD);
    //ESP_LOGW(TAG,"CmdSend");
}

void sendDat(uint8_t* dat,uint16_t len,void* ctx){
    OLED12864_Send_NumByte(dat,len,OLED_DATA);
    //ESP_LOGW(TAG,"DatSend");
}

