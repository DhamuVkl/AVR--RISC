default:
		avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o timer.o timer.c
		avr-gcc -o timer.bin timer.o
		avr-objcopy -O ihex -R .eeprom timer.bin timer.hex
		sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:timer.hex
		