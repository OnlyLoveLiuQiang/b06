#include "stm32f10x.h"
#include "key.h"
#include "exti.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "sd.h"
#include "ff.h"

int main(){
	unsigned int res;
	FATFS fs;
	FIL fil;
	UINT wbw = 0;
	UINT rbw = 0;
	unsigned char config[11] = "config.txt";
	unsigned char wbuff[16] = "5u-clound";
	unsigned char rbuff[16] = "";
	key_init();
	led_init();
//	led_on(1);
	key_on();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	exti0_init();
	uart3_init(115200);
	delay_init();
	while(sd_init());
	//========����������========
	res = f_mount(&fs,"0:",1);
	printf("f_mount:res = %d\n",res);
	//=============================
	//========��/�����ļ�========
	res = f_open(&fil,(const char*)config,FA_OPEN_ALWAYS|FA_READ|FA_WRITE);
	f_sync(&fil);
	printf("f_open config:res = %d\n",res);
	//==============================
	//===========��SD����д����=========
	res = f_write(&fil,(const void*)wbuff,16,&wbw);
	f_sync(&fil);
	printf("f_write config:res = %d wbw = %d\n",res,wbw);
	//===================================
	res = f_lseek(&fil,0);
	//===========��SD���ж�ȡ����========
	res = f_read(&fil,(void *)rbuff,15,&rbw);
	printf("f_read hello.txt: res = %d rbuff = %s\n",res,rbuff);
	//==============================
	//========�رմ򿪵��ļ�========
	res = f_close(&fil);
	printf("f_close config:res = %d\n",res);
	//==============================
	//=========�رվ�����=========
	res = f_mount(0,"0:",1);
	printf("f_mount:res = %d\n",res);
	//==============================
	while(1){
		
	}
}
