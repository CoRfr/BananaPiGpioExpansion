
all: gpioCtrl

#CC=/opt/poky/1.6.1/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi/arm-poky-linux-gnueabi-gcc

WIRINGPI_BASE="${PWD}/wiringPi/wiringPi"

gpioCtrl: gpioCtrl.c
	${CC} -o gpioCtrl -lwiringPi -I${WIRINGPI_BASE} gpioCtrl.c

