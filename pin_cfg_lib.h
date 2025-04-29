// Ethan O'Connor
// ECE 231 Lab 3
// 3/8/25

#include <stdio.h>  // For input/output
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/epoll.h>
#include <time.h>

// For setting up the GPIO pin as an input
void configure_gpio_input(int gpio_number, char* pin_number);

// Sets up a pin to a mode that is given (for example PWM)
void config_pin(char* pin_number, char* mode);

// Catch CTRL+C from user to turn off PWM pin on user exit
void sigintHandler(int sig_num);

// Sets up the duty cycle for a given PWM pin
void set_pwm_duty_cycle(char* pwmchip, char* channel, char* duty_cycle);

// Set the period for a given PWM pin. Also sets duty_cycle to half
//if the period is less than current duty_cycle
void set_pwm_period(char* pwmchip, char* channel, char* period);

// Disables a given PWM pin (turns the speaker off)
void stop_pwm(char* pin_number, char* pwmchip, char* channel);

// Enables a given PWM pin (turns the speaker on). Also sets
// up period and duty_cycle using corresponding functions
void start_pwm(char* pin_number, char* pwmchip, char* channel, char* period, char* duty_cycle);