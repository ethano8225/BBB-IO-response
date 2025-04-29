// Ethan O'Connor
// ECE 231 Lab 3
// 3/8/25

#include "pin_cfg_lib.h"

// Set the duty cycle for a given PWM pin
void set_pwm_duty_cycle(char* pwmchip, char* channel, char* duty_cycle){

    // Export file path
    char PWMDutyCycle[60];
    sprintf(PWMDutyCycle, "/sys/class/pwm/%s/pwm-4:%s/duty_cycle", pwmchip, channel);

    // Configure PWM device
    FILE* fp = fopen(PWMDutyCycle, "w");
    fwrite(duty_cycle, sizeof(char), strlen(duty_cycle), fp);
    fclose(fp);
}

// Set the period for a given PWM pin. Also sets duty_cycle to half
//if period is less than current duty_cycle
void set_pwm_period(char* pwmchip, char* channel, char* period){
    long duty_cycle_int, period_int;
    
    // Before setting up the period read old duty cycle (d.c.)
    char PWMDutyCycle[60], duty_cycle_str[20];
    sprintf(PWMDutyCycle, "/sys/class/pwm/%s/pwm-4:%s/duty_cycle", pwmchip, channel);
    FILE* fp = fopen(PWMDutyCycle, "r");
    fscanf(fp, "%ld", &duty_cycle_int);
    fclose(fp);
    period_int = atol(period);

    // If the old d.c. value is greater than the new period, update
    //the dummy_duty_cycle first to avoid errors with setting up the period
    if(duty_cycle_int >= period_int){
        duty_cycle_int = period_int/2;
        
        // Converting long to char data type
        sprintf(duty_cycle_str, "%ld", duty_cycle_int);
        
        // Set the 'dummy' duty cycle
        set_pwm_duty_cycle(pwmchip, channel, duty_cycle_str);
    }
    // Export PWM file path
    char PWMPeriod[60];
    sprintf(PWMPeriod, "/sys/class/pwm/%s/pwm-4:%s/period", pwmchip, channel);
    fp = fopen(PWMPeriod, "w");
    fwrite(period, sizeof(char), strlen(period), fp);
    fclose(fp);
}

// Disables a given PWM pin (turns off the speaker)
void stop_pwm(char* pin_number, char* pwmchip, char* channel){
    char PWMDisable[40];
    sprintf(PWMDisable, "/sys/class/pwm/%s/pwm-4:%s/enable",
    pwmchip, channel);

    // Stop generating PWM
    FILE* fp = fopen(PWMDisable, "w");
    fwrite("0", sizeof(char), 1, fp);
    fclose(fp);
    }

// Enables the given pwm_pin (turns on). Also sets up the period and duty_cycle
void start_pwm(char* pin_number, char* pwmchip, char* channel,
    char* period, char* duty_cycle){
    //Inputs:
    // pin_number: pin_number to generate PWM on
    // pwmchip: the device folder to generate PWM
    // channel: PWM device channel
    // period: PWM period
    // duty_cycle: PWM duty cyle
    
    config_pin(pin_number, "pwm");   // Configure the pin in PWM mode
    FILE* fp;
    set_pwm_period(pwmchip, channel, period);         // Configure PWM Period
    set_pwm_duty_cycle(pwmchip, channel, duty_cycle); // Configure PWM Duty Cycle
    char PWMEnable[40];                               // Enable PWM
    sprintf(PWMEnable, "/sys/class/pwm/%s/pwm-4:%s/enable",
    pwmchip, channel);
    fp = fopen(PWMEnable, "w");      // Configure generating PWM 
    fwrite("1", sizeof(char), 1, fp);
    fclose(fp);
    }
    
   