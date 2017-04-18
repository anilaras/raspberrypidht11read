# raspberrypidht11read
DHT11 sensors read in c

Compile: 

gcc -std=c99 termdht.c -o termdht -lwiringPi  

Using:  

pi@raspberrypi:~ $ ./termdht all  
Humidity = 11.0 % Temperature = 22.0 C (71.6 F)   
Humidity = 11.0 % Temperature = 22.0 C (71.6 F) 

pi@raspberrypi:~ $ ./termdht temp   
Temperature = 23.0 C   
Temperature = 22.0 C  

pi@raspberrypi:~ $ ./termdht humidity   
Humidity = 10.0   
Humidity = 10.0 
