// Ethan O'Connor
// ECE 231 Lab 3
// 3/8/25

#include "pin_cfg_lib.h"

// Set up GPIO pin as an input
void configure_gpio_input(int gpio_number, char* pin_number){
    config_pin(pin_number, "gpio_pu");      // Configure the pin in GPIO mode
    char GPIODirection[40];                 // Set GPIO direction as input
    sprintf(GPIODirection, "/sys/class/gpio/gpio%d/direction", gpio_number);
    FILE* fp = fopen(GPIODirection, "w");   // Set GPIO as input
    fwrite("in", sizeof(char), 2, fp);
    fclose(fp);
}

// Sets up a pin to a given mode (in this case, PWM)
void config_pin(char* pin_number, char* mode){
    if(!vfork()){  // Creates an environment to execute shell command
        
        // Execute shell command for pin configuration
        int ret = execl("/usr/bin/config-pin", "config-pin", pin_number, mode, NULL);

        if (ret < 0){
            printf("Failed to configure pin in PWM mode.\n");
            exit(-1);
        }
    }
}
