This test application demonstrates how to Init, start and manage a 
continuos ADC conversion.  

in this example, led D7  toggle frequency depends on value resistor R58. 
converted value is managed in the conversion callback function.

if any error during conversion, an error callback function is called.

Please note that jumper  J4 and J7 must be connected on Discovery board 
in ordet to ADC1 to work properly