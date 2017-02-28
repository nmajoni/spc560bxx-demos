This application uses the channel 0 of the PWM driver 1 and the ICU driver 1.
The port pin PA[9] (PJ7[10] on the EVB Motherboard) is the output of the 
channel 0 of the PWM driver 1, the port pin PA[0] (PJ7[1] on the EVB
Motherboard) is the input of the ICU driver 1. The LED1 is driven by the PWM
output, the LED2 is driven by the ICU input. So if the two pins PJ7[10] and
PJ7[1] are externally connected together, the LED1 and LED2 will blink 
synchronously.