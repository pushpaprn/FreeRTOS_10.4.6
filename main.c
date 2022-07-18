

/**
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>

#include "driverlib/sysctl.h"
#include "driverlib/debug.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"

#include "drivers/pinout.h"
#include "utils/uartstdio.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "stdbool.h"
#include "semphr.h"
#include "stream_buffer.h"
#include "FreeRTOSConfig.h"


#define SYSTEM_CLOCK                                120000000   //!< System clock in Hz


void vLEDTask( void * pvParameters )
{
    while(1)
    {
        // Turn on LED 1
        LEDWrite(0x0F, 0x01);
        vTaskDelay(1000);

        // Turn on LED 2
        LEDWrite(0x0F, 0x02);
        vTaskDelay(1000);

        // Turn on LED 3
        LEDWrite(0x0F, 0x04);
        vTaskDelay(1000);

        // Turn on LED 4
        LEDWrite(0x0F, 0x08);
        vTaskDelay(1000);
    }
}

void vConsoleTask( void * pvParameters )
{
    UARTStdioConfig(0, 115200, SYSTEM_CLOCK);
    while(1)
    {
        UARTprintf("Hello, world from FreeRTOS 10.4.6!\r\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}


int main(void)
{
    MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), SYSTEM_CLOCK);

    PinoutSet(false, false);

//#if (configUSE_TRACE_FACILITY)
//    vTraceEnable(TRC_START);            //Initialize and start tracing
//#endif

    xTaskCreate(vLEDTask, "task1", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vConsoleTask, "task2", configMINIMAL_STACK_SIZE, NULL, 3, NULL);

    vTaskStartScheduler();

    while(1)
    {
    }
}
