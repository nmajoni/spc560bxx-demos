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
#include "hal_adc_lld_cfg.h"

/*
 * Buffers used for the ADC conversions, note, the constants are defined
 * in adc_lld_cfg.h and are generated automatically.
 */
static adcsample_t samples[ADC1_GROUP_CFG0_NUM_CHANNELS *
                            ADC1_GROUP_CFG0_BUF_DEPTH];

/*
 * ADC streaming callback, the name is defined in the ADC graphic
 * configuration.
 */
static uint16_t		mswaittime;
void adc_conversion_callback(ADCDriver *adcp, adcsample_t *buffer, size_t n) {
	(void)adcp;
	(void)n;
	mswaittime = buffer[0] / 8 ;

}

/*
 * ADC error callback, the name is defined in the ADC graphic
 * configuration.
 */
void adc_error_callback(ADCDriver *adcp, adcerror_t err) {
  (void)adcp;
  (void)err;
  palSetPad(PORT_E, PE_LED2);
  osalSysHalt("ADC failure");

}

/*
 * Application entry point.
 */
int main(void) {

  /* Initialization of all the imported components in the order specified in
     the application wizard. The function is generated automatically.*/
  componentsInit();

  /* Starts the ADCD2 drivers.*/
  adcStart(&ADCD2, NULL);

  /* Starts an ADC continuous conversion.*/
  adcStartConversion(&ADCD2, &adc1_group_cfg0,
                     samples, ADC1_GROUP_CFG0_BUF_DEPTH);

  /* Normal main() thread activity, LED1 toggle frequency
     depends on value resistor W1. converted value is managed
     in the conversion callback function. */
  while (TRUE) {

	  osalThreadSleepMilliseconds(mswaittime + 100);
	  palTogglePad(PORT_E, PE_LED1);
  }
}
