
all: gpioCtrl

gpioCtrl: gpioCtrl.c
	gcc -o gpioCtrl -lwiringPi -I/home/broussel/Legato/team/raspi/wiringPi gpioCtrl.c

