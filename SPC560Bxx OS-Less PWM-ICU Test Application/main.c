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

#include "hal_pwm_lld_cfg.h"
#include "hal_icu_lld_cfg.h"

void pwmpcb(PWMDriver *pwmp) {

  (void)pwmp;
  palClearPad(PORT_E, PE_LED1);

}

void pwmc1cb(PWMDriver *pwmp) {

  (void)pwmp;
  palSetPad(PORT_E, PE_LED1);
}

icucnt_t last_width, last_period;

void icuwidthcb(ICUDriver *icup) {

  palSetPad(PORT_E, PE_LED2);
  last_width = icuGetWidth(icup);
}

void icuperiodcb(ICUDriver *icup) {

  palClearPad(PORT_E, PE_LED2);
  last_period = icuGetPeriod(icup);
}

/*
 * Application entry point.
 */
int main(void) {

  /* Initialization of all the imported components in the order specified in
     the application wizard. The function is generated automatically.*/
  componentsInit();

  palClearPad(PORT_E, PE_LED4);

  /*
   * Initializes the PWM driver 1 and ICU driver 1.
   */
  icuStart(&ICUD1, &icu_config_cfg0);
  icuEnable(&ICUD1);
  pwmStart(&PWMD1, &pwm_config_cfg0);

  osalThreadSleepMilliseconds(2000);

  /*
   * Starts the PWM channel 0 using 75% duty cycle.
   */
  pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 7500));
  osalThreadSleepMilliseconds(5000);

  /*
   * Changes the PWM channel 0 to 50% duty cycle.
   */
  pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 5000));
  osalThreadSleepMilliseconds(5000);

  /*
   * Changes the PWM channel 0 to 25% duty cycle.
   */
  pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 2500));
  osalThreadSleepMilliseconds(5000);

  /*
   * Changes PWM period and the PWM channel 0 to 50% duty cycle.
   */
  pwmChangePeriod(&PWMD1, 30000);
  pwmEnableChannel(&PWMD1, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD1, 5000));
  osalThreadSleepMilliseconds(5000);

  /*
   * Disables channel 0 and stops the drivers.
   */
  pwmDisableChannel(&PWMD1, 0);
  pwmStop(&PWMD1);
  icuDisable(&ICUD1);
  icuStop(&ICUD1);

  palClearPad(PORT_E, PE_LED3);
  palClearPad(PORT_E, PE_LED4);

  /*
   * Normal main() thread activity, in this demo it does nothing.
   */
  while (TRUE) {
    osalThreadSleepMilliseconds(500);
  }
  return 0;
}
