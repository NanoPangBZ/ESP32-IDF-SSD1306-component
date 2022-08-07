## 1.基于idf的ESP32 OLED12864的C++组件

### 1.1 ssd1306 class

#### 功能定义

​	抽象ssd1306芯片，使各种通讯模式的oled屏幕能统一使用ssd1306 class完成控制

#### 对外接口

- 由子类实现  -> 多态
	- virtual bool periph_init()             //开启需要用到的esp外设
	- virtual bool periph_deinit()          //关闭需要用到的esp外设
	- virtual bool sendCmd(uint8_t *cmd,int len)
	- virtual bool sendData(uint8_t *dat,int len)
	- 