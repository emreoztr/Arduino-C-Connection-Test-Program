#include "arduino-serial-lib.c"
#include "arduino-serial-lib.h"

int main()
{
	int port = serialport_init("/dev/ttyACM0", 9600); 						//This code opens the communication with arduino//
	int counter=0;
	int choice=-1;
	int exit=0;
	const char* cho1="a";
	const char* cho2="b";
	const char* cho3="c";
	const char* cho4="d";
	const char* cho5="e";
	char square[256];
	char count[256];
	int num_4;
	printf("\n----PLEASE WAIT AROUND 2 SECONDS TO ALLOW ARDUINO STARTS----\n");
	sleep(2);
	while(choice!=0){
		exit=0;
		printf("\n## WELCOME TO GTU ARUINO LAB		##\n## STUDENT NAME: YUNUS EMRE OZTURK	##\n## PLESE SELECT FROM THE FOLLOWING	##\n## MENU :				##\n(1) TURN ON LED ON ARDUINO\n(2) TURN OFF LED ON ARDUINO\n(3) FLASH ARDUINO LED 3 TIMES\n(4) SEND A NUMBER TO ARDUINO TO COMPUTE SQUARE BY ARDUINO\n(5) BUTTON PRESS COUNTER\n(0) EXIT\nPLEASE SELECT:");
		scanf("%d",&choice);
		if(choice==1){
			serialport_write(port, cho1);
		}
		else if(choice==2){
			serialport_write(port, cho2);
		}
		else if(choice==3){
			serialport_write(port, cho3);
		}
		else if(choice==4){
			serialport_write(port, cho4);
			printf("Please write a number: ");
			scanf("%d", &num_4);
			if(num_4<0){
				num_4=num_4*(-1);
			}
			serialport_writebyte(port, num_4);
			serialport_read_until(port, square, '\n', 256, 1000);
			printf("Answer: ");
			printf("%s\n",square);
			
			
			
		}
		else if(choice==5){
			serialport_write(port,cho5);
			while(exit==0){
				serialport_read_until(port, count, '\n', 256, 1000);
				if(count[0]=='x'){    										//It is looking for 'x', if arduino sending 'x' counter increase 1//							
					counter+=1;
					printf("%d\n",counter);

				}
				if(count[0]=='e'){											//If arduino sends 'e' to program, it will exit from the proccess in 5//
					exit=1;
				}
				
			}
			counter=0;
		}
		else if(choice<0 || choice>5){
			printf("PLEASE SELECT NUMBER FROM 0 TO 5\n");
		}
	}	
	serialport_close(port);
	return 0;
}

