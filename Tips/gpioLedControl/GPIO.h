#ifndef GPIO_H_
#define GPIO_H_

#define MAX_BUF     128
#define GPIO_LED_DEV    "/sys/class/gpio"
#define GREEN_LED_1  169
#define RED_LED_1   170

/*
 * hcyinux
 */

class GPIO
{
	
private:
int m_led_fd;

public:
GPIO();
virtual ~GPIO();

int Open();
void Close();

void Export(int id);
void Unexport(int id);

void Set_GREEN_LED(int onoff = 1);
void Set_RED_LED(int onoff = 1);

};

#endif /* GPIO_H_ */

