/*
    SPC5 HAL - Copyright (C) 2015 STMicroelectronics

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/* Inclusion of the main header files of all the imported components in the
   order specified in the application wizard. The file is generated
   automatically.*/
#include "components.h"

/*
 * Application entry point.
 */
int main(void) {

  /* Initialization of all the imported components in the order specified in
     the application wizard. The function is generated automatically.*/
  componentsInit();

  /*
   * Activates the serial driver 1 using the driver default configuration.
   */
  sdStart(&SD1, NULL);

  /* Application main loop.*/
  while (1) {
    unsigned i;

    chnWriteTimeout(&SD1, (uint8_t *)"Hello World!\r\n", 14, TIME_INFINITE);

    for (i = 0; i < 4; i++) {
      palClearPad(PORT_E, PE_LED1);
      osalThreadSleepMilliseconds(100);
      palClearPad(PORT_E, PE_LED2);
      osalThreadSleepMilliseconds(100);
      palClearPad(PORT_E, PE_LED3);
      osalThreadSleepMilliseconds(100);
      palClearPad(PORT_E, PE_LED4);
      osalThreadSleepMilliseconds(100);
      palSetPad(PORT_E, PE_LED1);
      osalThreadSleepMilliseconds(100);
      palSetPad(PORT_E, PE_LED2);
      osalThreadSleepMilliseconds(100);
      palSetPad(PORT_E, PE_LED3);
      osalThreadSleepMilliseconds(100);
      palSetPad(PORT_E, PE_LED4);
      osalThreadSleepMilliseconds(300);
    }

    for (i = 0; i < 4; i++) {
      palTogglePort(PORT_E, PAL_PORT_BIT(PE_LED1) | PAL_PORT_BIT(PE_LED2) |
                            PAL_PORT_BIT(PE_LED3) | PAL_PORT_BIT(PE_LED4));
      osalThreadSleepMilliseconds(500);
      palTogglePort(PORT_E, PAL_PORT_BIT(PE_LED1) | PAL_PORT_BIT(PE_LED2) |
                            PAL_PORT_BIT(PE_LED3) | PAL_PORT_BIT(PE_LED4));
      osalThreadSleepMilliseconds(500);
    }

    for (i = 0; i < 4; i++) {
      palTogglePad(PORT_E, PE_LED1);
      osalThreadSleepMilliseconds(250);
      palTogglePad(PORT_E, PE_LED1);
      palTogglePad(PORT_E, PE_LED2);
      osalThreadSleepMilliseconds(250);
      palTogglePad(PORT_E, PE_LED2);
      palTogglePad(PORT_E, PE_LED3);
      osalThreadSleepMilliseconds(250);
      palTogglePad(PORT_E, PE_LED3);
      palTogglePad(PORT_E, PE_LED4);
      osalThreadSleepMilliseconds(250);
      palTogglePad(PORT_E, PE_LED4);
    }

    for (i = 0; i < 4; i++) {
      palClearPort(PORT_E, PAL_PORT_BIT(PE_LED1) | PAL_PORT_BIT(PE_LED3));
      palSetPort(PORT_E, PAL_PORT_BIT(PE_LED2) | PAL_PORT_BIT(PE_LED4));
      osalThreadSleepMilliseconds(500);
      palClearPort(PORT_E, PAL_PORT_BIT(PE_LED2) | PAL_PORT_BIT(PE_LED4));
      palSetPort(PORT_E, PAL_PORT_BIT(PE_LED1) | PAL_PORT_BIT(PE_LED3));
      osalThreadSleepMilliseconds(500);
    }

    palSetPort(PORT_E, PAL_PORT_BIT(PE_LED1) | PAL_PORT_BIT(PE_LED2) |
                       PAL_PORT_BIT(PE_LED3) | PAL_PORT_BIT(PE_LED4));
  }
}
