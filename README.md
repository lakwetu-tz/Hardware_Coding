# esp32_repo
 ESP32 is that it has a lot more GPIOs than the ESP8266. 
 
 ##   ESP32 Peripherals and I/O
 
Although the ESP32 has 48 GPIO pins in total, only 25 of them are broken out to the pin headers on both sides of the development board. 
These pins can be assigned a variety of peripheral duties, including:
        15 ADC channels	    15 channels of 12-bit SAR ADC with selectable ranges
                            of 0-1V, 0-1.4V, 0-2V, or 0-4V
                            
        2 UART interfaces	2 UART interfaces with flow control and IrDA support
        
        25 PWM outputs	    25 PWM pins to control things like motor speed or LED brightness

        2 DAC channels	    Two 8-bit DACs to generate true analog voltages
        
        SPI, I2C and I2S    Three SPI and one I2C interfaces for connecting various sensors and peripherals, 
        interface           as well as two I2S interfaces for adding sound to your project
        
        9 Touch Pads	    9 GPIOs with capacitive touch sensing


For extensive information about the ESP32, please refer to the datasheet.
https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf
