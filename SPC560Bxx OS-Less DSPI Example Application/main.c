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

#include "hal_spi_lld_cfg.h"

/*
 * SPI TX and RX buffers.
 */
static uint8_t txbuf[512];
static uint8_t rxbuf[512];

/*
 * Application entry point.
 */
int main(void) {
  unsigned i;

  /* Initialization of all the imported components in the order specified in
     the application wizard. The function is generated automatically.*/
  componentsInit();

  /* Prepare transmit pattern.*/
  for (i = 0; i < sizeof(txbuf); i++)
    txbuf[i] = (uint8_t)i;

  /* Starting driver for test.*/
  spiStart(&SPID1, &spi_config_low_speed);

  /* Testing sending and receiving at the same time.*/
  spiExchange(&SPID1, 4, txbuf, rxbuf);
  spiExchange(&SPID1, 32, txbuf, rxbuf);
  spiExchange(&SPID1, 512, txbuf, rxbuf);

  /* Testing clock pulses without data buffering.*/
  spiIgnore(&SPID1, 4);
  spiIgnore(&SPID1, 32);

  /* Testing sending data ignoring incoming data.*/
  spiSend(&SPID1, 4, txbuf);
  spiSend(&SPID1, 32, txbuf);

  /* Testing receiving data while sending idle bits (high level).*/
  spiReceive(&SPID1, 4, rxbuf);
  spiReceive(&SPID1, 32, rxbuf);

  /* Testing stop procedure.*/
  spiStop(&SPID1);

  /* Testing 16bits wide frames.*/
  spiStart(&SPID1, &spi_config_low_speed_16);
  spiExchange(&SPID1, 4, txbuf, rxbuf);
  spiExchange(&SPID1, 32, txbuf, rxbuf);
  spiExchange(&SPID1, 256, txbuf, rxbuf);
  spiStop(&SPID1);

  /* Application main loop, two SPI configuration are used alternating them.*/
  while (1) {
    palClearPad(PORT_E, PE_LED1);               /* LED ON.                  */
    spiStart(&SPID1, &spi_config_high_speed);   /* Setup parameters.        */
    spiExchange(&SPID1, 512, txbuf, rxbuf);

    palSetPad(PORT_E, PE_LED1);                 /* LED OFF.                */
    spiStart(&SPID1, &spi_config_low_speed);    /* Setup parameters.       */
    spiExchange(&SPID1, 512, txbuf, rxbuf);
  }
}
