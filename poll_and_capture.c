// Ethan O'Connor
// ECE 231 Lab 3
// 3/8/25

#include "pin_cfg_lib.h"

void configure_gpio_input(int gpio_num, char* pin_num);
void config_pin(char* pin_number, char* mode);

int main() {
    char gpio_pin_1[32] = "P8_08"; // Set up pin values
    int gpio_num_1 = 67;
    char gpio_pin_2[32] = "P8_09";
    int gpio_num_2 = 69;
    
    // Call function to set up 1st and 2nd input pin
    configure_gpio_input(gpio_num_1, gpio_pin_1);
    configure_gpio_input(gpio_num_2, gpio_pin_2);
    char valuePath[40], valuePath2[40];
    sprintf(valuePath, "/sys/class/gpio/gpio%d/value", gpio_num_1);
    sprintf(valuePath2, "/sys/class/gpio/gpio%d/value", gpio_num_2);
    
    // Sleeping prevents misread inputs
    sleep(1);
    
    // Set up the speaker's pin
    char pin_number[32] = "P9_16";
    char pwmchip[32] = "pwmchip4";
    char channel[32] = "1";
    stop_pwm(pin_number, pwmchip, channel);
    
    // Variables to count pin interrupts
    long count = 0;
    int state;
    long count2 = 0;
    int state2;
    FILE *fp, *fp2;

    // Polling loop
    while(1) {

        // Interrupt for 1st pin
        fp = fopen(valuePath, "r"); 
        fscanf(fp, "%d", &state);  // Scan state
        fclose(fp);
        
        // If state changed, start pwm with given pin number for frequency
        if( state == 0 ) {
            count++;
            printf("Pin Interrupted %lu\n", count);
            start_pwm(pin_number, pwmchip, channel, "10000000", "6000000");
            sleep(5);
            stop_pwm(pin_number, pwmchip, channel);
        }
        
        // Interrupt for 2nd pin, essentially same as above
        fp2 = fopen(valuePath2, "r");
        fscanf(fp2, "%d", &state2); 
        fclose(fp2);
        if( state2 == 0 ) {
            count2++;
            printf("Pin Interrupted2 %lu\n", count2);
            start_pwm(pin_number, pwmchip, channel, "1000000", "700000");
            sleep(5);
            stop_pwm(pin_number, pwmchip, channel);
        }
    }
    return 0;
 }

