#include <stdio.h>
#include <stdlib.h>
// Need errno to check if errors occur with conversion.
#include <errno.h>


struct temp_data {
    float temperature;
    int temp_scale;
    int conversion_temp;
};


struct temp_data get_user_input();
float fahrenheit_to_celsius(float temp_in_f);
float celsius_to_fahrenheit (float temp_in_c);
float celsius_to_kelvin (float temp_in_k);
float kelvin_to_celsius (float temp_in_k);
void categorize_temp(float celsius);


int main() {
    // Obtain user input about temperature, units, and conversion
    // Create the required variables we will need.
    // Call our user input function once
    struct temp_data data = get_user_input();
    // If the function got invalid data, it will return
    // temp_scale as 0. If so, we can keep calling it while printing out
    // a helpful error message.
    while (data.temp_scale == 0) {
        printf(" please try again.\n");
        data = get_user_input();
    }
    printf("Temp: %f\n", data.temperature);
    printf("Scale: %i\n", data.temp_scale);
    printf("Convert to: %i", data.conversion_temp);

}

struct temp_data get_user_input() {
    struct temp_data data;
    char input_buffer[128];
    char *end;
    printf("Enter the temperature: ");
    // strtof and strtol will set the end to input_buffer if conversion cannot be done.
    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
        data.temperature = strtof(input_buffer, &end);
        if (end == input_buffer) {
            printf("\nInvalid temperature input,");
            data.temp_scale = 0;
            return data;
        }
    }
    printf("Choose the temperature scale (1: Celsius, 2: Fahrenheit, 3: Kelvin): ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
        data.temp_scale = strtol(input_buffer, &end, 10);
        // Ensure temp scale is within range.
        if (end == input_buffer || (data.temp_scale < 1 || data.temp_scale > 3)) {
            printf("\nInvalid temperature scale input,");
            data.temp_scale = 0;
            return data;
        }
    }
    printf("Convert to (1: Celsius, 2: Fahrenheit, 3: Kelvin): ");
    if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
        data.conversion_temp = strtol(input_buffer, &end, 10);
        // Ensure temp scale is within range.
        // As well , check if the end
        if (end == input_buffer || (data.conversion_temp < 1 || data.conversion_temp > 3)) {
            printf("\nInvalid temperature conversion input,");
            data.temp_scale = 0;
            return data;
        }
    }
    if (errno == ERANGE) {
        printf("Range error occurred. A value was either too small or too large.\n");
        data.temp_scale = 0;
    }
    return data;
}

float fahrenheit_to_celsius (float temp_in_f) {
    return (temp_in_f-32.0)*(5.0/9);
}

float celsius_to_fahrenheit (float temp_in_c) {
    return (temp_in_c+32.0)*(9.0/5);
}

float celsius_to_kelvin (float temp_in_c) {
    return temp_in_c+273.15;
}
float kelvin_to_celsius (float temp_in_k) {
    return temp_in_k-273.15;
}

void categorize_temp(float celsius) {
    /* need to write statements:
     * <0, freezing
     * > 0 && <= 10, cold
     * > 10 && <= 25, comfortable
     * > 25 && <= 35, hot
     * > 35, extreme heat
     */
    if (celsius < 0) {
        printf("Temperature Category: Freezing");
        printf("Advisory: Limit time spent outside and ensure you are insulated from the cold.");
    } else if (celsius > 0 && celsius <= 10) {
        printf("Temperature Category: Cold");
        printf("Advisory: Make sure to wear a jacket while outside.");
    } else if (celsius > 10 && celsius <= 25) {
        printf("Temperature Category: Comfortable");
        printf("Advisory: It should be comfortable outdoors, enjoy it!");
    } else if (celsius > 25 && celsius <= 35) {
        printf("Temperature Category: Extreme Heat");
        printf("Advisory: Stay indoors. If you must go outside, limit time as much as possible.");
    }
}
