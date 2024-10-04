#include <stdio.h>
float fahrenheit_to_celsius(float temp_in_f);
float celsius_to_fahrenheit (float temp_in_c);
float celsius_to_kelvin (float temp_in_k);
float kelvin_to_celsius (float temp_in_k);
void categorize_temp(float celsius);
int main() {
    // Obtain user input about temperature, units, and conversion

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
}
