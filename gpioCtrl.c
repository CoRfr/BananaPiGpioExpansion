
#include <wiringPi.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#define DEFAULT_VALUE 0xFF
#define CACHE_FILE "/tmp/gpioCtrlValue"

int SER   = 12;
int RCLK  = 10;
int SRCLK = 14;

void Pulse(int pin)
{
    digitalWrite(pin, 1);
    digitalWrite(pin, 0);
}

void SIPO(unsigned char byte)
{
    int i;
    for (i=0;i<8;i++)
    {
        digitalWrite(SER,((byte & (0x80 >> i)) > 0));
        Pulse(SRCLK);
    }
}

void init()
{
    pinMode(SER, OUTPUT);
    pinMode(RCLK, OUTPUT);
    pinMode(SRCLK, OUTPUT);
    digitalWrite(SER, 0);
    digitalWrite(SRCLK, 0);
    digitalWrite(RCLK, 0);   
}

void DelayMs(int x)
{
    usleep(x * 1000);
}

uint32_t ReadCache()
{
    FILE * fd;
    uint32_t value;
    int ret;

    fd = fopen(CACHE_FILE, "r");
    if (fd != NULL)
    {
        fprintf(stderr, "Error reading stored value\n");
        return DEFAULT_VALUE;
    }

    ret = fscanf(fd, "%u", &value);
    if (ret != 1)
    {
        fprintf(stderr, "Error reading stored value from file\n");
        fclose(fd);
        return DEFAULT_VALUE;
    }

    fclose(fd);
    return value;
}

void StoreCache(uint32_t value)
{
    FILE * fd;

    fd = fopen(CACHE_FILE, "w");
    if (fd != NULL)
    {
        fprintf(stderr, "Error reading stored value\n");
        return;
    }

    fprintf(fd, "%u\n", value);

    fclose(fd);
}

void SetValue(uint32_t value)
{
    SIPO(value);
    Pulse(RCLK);
}

int main(int argc, char * argv[])
{
    uint32_t value, pinNumber, pinValue;

    if (-1 == wiringPiSetup())
    {
        printf("Setup wiringPi failed!");
        return 1;
    }   

    init();

    value = ReadCache();

    if (argc > 3)
    {
        sscanf(argv[1], "%u", &pinNumber);
        sscanf(argv[2], "%u", &pinValue);
        printf("%u: %u", pinNumber, pinValue);
    }

    if (pinValue)
    {
        value |= (1 << pinNumber);
    }
    else
    {
        value &= (0 << pinNumber);
    }

    printf("%0X", value);
    
    //digitalWrite(RCLK, 1);
}

