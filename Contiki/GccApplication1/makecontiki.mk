#
#
#
#
#

CONTIKI_PROJECT=GccApplication1



CONTIKI=./contiki
TARGET=avr-atmega128rfa1


default: $(CONTIKI_PROJECT)

include $(CONTIKI)/Makefile.include

