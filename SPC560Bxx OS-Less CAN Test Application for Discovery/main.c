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
#include "hal_can_lld_cfg.h"

CANTxFrame txmsg;
CANRxFrame rxmsg;

static virtual_timer_t tmr;
uint8_t CANtransReq = 0;

/**
 * @brief   Timer callback function.
 *
 * @param[in] p         NULL
 *
 * @notapi
 */
static void tmrfunc(void *p) {
  (void)p;

  osalSysLockFromISR();
  vtSetI(&tmr, OSAL_MS2ST(500), tmrfunc, NULL);
  osalSysUnlockFromISR();

  CANtransReq = 1;
}

/*
 * Application entry point.
 */
int main(void) {
	unsigned int txmailbox =1;

  /* Initialization of all the imported components in the order specified in
     the application wizard. The function is generated automatically.*/
  componentsInit();

  /*
   * Activates the CAN driver 1.
   */
  canStart(&CAND1, &can_config_cfg0);

    /*
     * CAN TX Message structure.
     */
  txmsg.IDE = CAN_IDE_EXT;
  txmsg.RTR = CAN_RTR_DATA;
  txmsg.LENGTH = 8;
  txmsg.data32[0] = 0x55AA55AA;
  txmsg.data32[1] = 0x00FF00FF;

  /*
   * Set Virtual Timer for the CAN periodic transmissions.
   */
    vtSet(&tmr, OSAL_MS2ST(500), tmrfunc, NULL);

  /* Application main loop.*/
  while (1) {
    /*
     * Sends the TX CAN Message.
     */
    if (CANtransReq == 1) {
    	if (txmailbox==1){
    		txmsg.EID = 0x01234567;
    	}
    	else if (txmailbox==2){
    		txmsg.EID = 0x08901234;
    	}
    	if (canTransmit(&CAND1, txmailbox, &txmsg, TIME_IMMEDIATE) != MSG_TIMEOUT) {
    	     CANtransReq = 0;
    	}
    	txmailbox ++;
    	if (txmailbox==3) txmailbox =1;
    }

    /*
     * Receives the RX CAN Message.
     */
     if (canReceive(&CAND1, 1, &rxmsg, TIME_IMMEDIATE) == MSG_OK) {
       /* Process message.*/
       palTogglePad(PORT_C, PC_LED7);
     }

     if (canReceive(&CAND1, 2, &rxmsg, TIME_IMMEDIATE) == MSG_OK) {
       /* Process message.*/
       palTogglePad(PORT_C, PC_LED8);
     }
  }
  return 0;
}
