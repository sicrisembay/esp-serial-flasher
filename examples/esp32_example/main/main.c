/* Flash multiple partitions example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <sys/param.h>
#include <string.h>
#include "esp_err.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "serial_io.h"
#include "esp_loader.h"
#include "example_common.h"

#define HIGHER_BAUDRATE 230400

void app_main(void)
{
    example_binaries_t bin;

    const loader_serial_config_t config = {
        .baud_rate = 115200,
        .uart_port = UART_NUM_1,
        .uart_rx_pin = GPIO_NUM_5,
        .uart_tx_pin = GPIO_NUM_4,
        .reset_trigger_pin = GPIO_NUM_25,
        .gpio0_trigger_pin = GPIO_NUM_26,
    };

    if ( loader_port_serial_init(&config) != ESP_LOADER_SUCCESS) {
        ESP_LOGE("example", "serial initialization failed.");
        return;
    }

    if (connect_to_target(HIGHER_BAUDRATE) == ESP_LOADER_SUCCESS) {

        get_example_binaries(esp_loader_get_target(), &bin);

        flash_binary(bin.boot.data, bin.boot.size, bin.boot.addr);
        flash_binary(bin.part.data, bin.part.size, bin.part.addr);
        flash_binary(bin.app.data,  bin.app.size,  bin.app.addr);
    }
}