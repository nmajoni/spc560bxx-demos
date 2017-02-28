This test application demonstrates how to Init, start and manage a 
continuos ADC conversion.  

in this example, LED1  toggle frequency depends on value resistor W1. 
converted value is managed in the conversion callback function.

if any error during conversion, an error callback function is called.

Please note that jumper J40 must be closed and PJ5 pin1 and PJ5 pin 9 
should be connected
