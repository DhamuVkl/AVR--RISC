default:
		avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o tim.o tim.c
		avr-gcc -o tim.bin tim.o
		avr-objcopy -O ihex -R .eeprom tim.bin tim.hex
		sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:tim.hex
		