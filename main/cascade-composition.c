#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "fsm-deb.h"

#define GPIO_OUTPUT_IO_0 5
#define GPIO_OUTPUT_IO_1 18
#define GPIO_OUTPUT_IO_2 19
#define GPIO_OUTPUT_IO_3 21

#define GPIO_OUTPUT_PIN_SEL ((1ULL<<GPIO_OUTPUT_IO_0) |(1ULL<<GPIO_OUTPUT_IO_1) |(1ULL<<GPIO_OUTPUT_IO_2) |(1ULL<<GPIO_OUTPUT_IO_3) )

#define GPIO_INPUT_IO_0 32
#define GPIO_INPUT_IO_1 33

#define GPIO_INPUT_PIN_SEL ((1ULL<<GPIO_INPUT_IO_0) | (1ULL<<GPIO_INPUT_IO_1))
int button = 0;
int state_deb = 0;
int led[4] = {1, 0, 0, 0};
int state_led = 0;
int flag = 0;
esp_timer_create_args_t create_args;
esp_timer_handle_t timer_handle;

esp_timer_create_args_t create_args_1;
esp_timer_handle_t timer_handle_1;

void timer_expired_1(void *p){
	flag = 1;
}

void timer_expired(void *p){
	button = ((gpio_get_level(GPIO_INPUT_IO_0))? 0:(-1)) + ((gpio_get_level(GPIO_INPUT_IO_1))? 0:(1));
	fsm_deb(button, &state_deb, &flag, &state_led);
	fsm_led(&state_led, led);
	if(state_deb == COUNT) esp_timer_start_once(timer_handle_1, 500000);
	else esp_timer_stop(timer_handle_1);

	gpio_set_level(GPIO_OUTPUT_IO_0, *(led));
	gpio_set_level(GPIO_OUTPUT_IO_1, *(led+1));
	gpio_set_level(GPIO_OUTPUT_IO_2, *(led+2));
	gpio_set_level(GPIO_OUTPUT_IO_3, *(led+3));
}
void app_main(void){

gpio_config_t io_conf = {};
io_conf.intr_type = GPIO_INTR_DISABLE;
io_conf.mode = GPIO_MODE_OUTPUT;
io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
io_conf.pull_down_en = 0;
io_conf.pull_up_en = 0;
gpio_config(&io_conf);

io_conf.intr_type = GPIO_INTR_DISABLE;
io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
io_conf.mode = GPIO_MODE_INPUT;
io_conf.pull_up_en = 1;
io_conf.pull_down_en = 0;
gpio_config(&io_conf);

create_args.callback = timer_expired;
create_args.dispatch_method = ESP_TIMER_TASK;
create_args.name = "esp_timer";
esp_timer_create(&create_args, &timer_handle);

create_args_1.callback = timer_expired_1;
create_args_1.dispatch_method = ESP_TIMER_TASK;
create_args_1.name = "esp_timer_1";
esp_timer_create(&create_args_1, &timer_handle_1);

esp_timer_start_periodic(timer_handle , 1000);
}
