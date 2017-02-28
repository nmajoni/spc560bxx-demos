This application uses the channel 0 of the PWM driver 1 (eMIOS0 CH9) and the
ICU driver 1 (eMIOS0 CH0). The port pin PA[9] (pin 12 on the external connector
X4) is the output of the channel 0 of the PWM driver 1, the port pin PA[0] (pin
19 on the external connector X1) is the input of the ICU driver 1. The LED7 is
driven by the PWM output, the LED8 is driven by the ICU input. So if the two
pins X1[19] and X4[12] are externally connected together, the LED7 and LED8
will blink synchronously.