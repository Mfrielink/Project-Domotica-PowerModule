PROJECT_SOURCEFILES = adc.c spi.c

CONTIKI=./contiki
TARGET=avr-atmega128rfa1

default: $(CONTIKI_PROJECT) 
include $(CONTIKI)/Makefile.include