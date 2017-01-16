#include "GPIO.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/*
*	hcyinux
*/

GPIO::GPIO()
{
        m_led_fd = -1;
}

GPIO::~GPIO()
{
        Close();
}

int GPIO::Open()
{
        Export(GREEN_LED_1);
        Export(RED_LED_1);
}


void GPIO::Close()
{
        if ( m_led_fd >= 0 )
        {
                Set_GREEN_LED(0);
                Set_RED_LED(0);
                close(m_led_fd);
                m_led_fd = -1;
        }
        Unexport(GREEN_LED_1);
        Unexport(RED_LED_1);
}
//making gpio(num) directory and set direction
void GPIO::Export(int id)
{
        char buf[MAX_BUF];

        m_led_fd = open(GPIO_LED_DEV "/export", O_WRONLY);
        if(m_led_fd < 0)
        {
                perror("GPIO Export error");
        }
        sprintf(buf,"%d",id);
        write(m_led_fd,buf,strlen(buf));
        close(m_led_fd);

        sprintf(buf, GPIO_LED_DEV "/gpio%d/direction", id);
        m_led_fd = open(buf, O_WRONLY);
        if(m_led_fd < 0)
        {
                perror("GPIO Direction error");
        }
        write(m_led_fd, "out", 3);
        close(m_led_fd);
}

void GPIO::Unexport(int id)
{
        char buf[MAX_BUF];

        m_led_fd = open(GPIO_LED_DEV "/unexport", O_WRONLY);
        if(m_led_fd < 0)
        {
                perror("GPIO unexport error");
        }
        sprintf(buf,"%d",id);
        write(m_led_fd,buf,strlen(buf));
        close(m_led_fd);

}

void GPIO::Set_GREEN_LED(int onoff)
{
        char buf[MAX_BUF];

        sprintf(buf, GPIO_LED_DEV "/gpio%d/value", GREEN_LED_1);
        m_led_fd = open(buf, O_WRONLY);
        if ( m_led_fd >= 0 )
        {
                if(onoff == 1) {
                        write(m_led_fd,"1",1);
                }
                else{
                        write(m_led_fd,"0",1);
                }
        }
        close(m_led_fd);
}

void GPIO::Set_RED_LED(int onoff)
{
        char buf[MAX_BUF];

        sprintf(buf, GPIO_LED_DEV "/gpio%d/value", RED_LED_1);
        m_led_fd = open(buf, O_WRONLY);
        if ( m_led_fd >= 0 )
        {
                if(onoff == 1) {
                        write(m_led_fd,"1",1);
                }
                else{
                        write(m_led_fd,"0",1);
                }
        }
        close(m_led_fd);
}