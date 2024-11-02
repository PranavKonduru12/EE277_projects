volatile unsigned int sw_value;
volatile unsigned int btn_value;
volatile unsigned int led;
int main(){
	while(1){
		sw_value = *(unsigned int*)0x43c00000;
		btn_value = *(unsigned int*)0x43c00004;
		led = sw_value | btn_value;
		*(unsigned int*)0x43c00008 = led;
	}
}
