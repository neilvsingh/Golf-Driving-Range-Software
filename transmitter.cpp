#include "pico/stdlib.h"

// Button is connected to GPIO 14
#define BUTTON_PIN 14

// RF transmitter DATA pin is connected to GPIO 15
#define TX_PIN 15

int main() {
    // Initialize standard input/output
    stdio_init_all();

    // Set up button pin as an input
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    // Use internal pull-up resistor
    // Button should connect GPIO 14 to GND when pressed
    gpio_pull_up(BUTTON_PIN);

    // Set up RF transmitter pin as an output
    gpio_init(TX_PIN);
    gpio_set_dir(TX_PIN, GPIO_OUT);

    // Make sure transmitter starts LOW
    gpio_put(TX_PIN, 0);

    while (true) {
        // Button reads 0 when pressed because of pull-up wiring
        bool button_pressed = gpio_get(BUTTON_PIN) == 0;

        if (button_pressed) {
            // Send a burst of pulses to the RF transmitter
            // This makes the signal easier for the receiver to detect
            for (int i = 0; i < 20; i++) {
                gpio_put(TX_PIN, 1);   // Send HIGH signal
                sleep_ms(10);

                gpio_put(TX_PIN, 0);   // Send LOW signal
                sleep_ms(10);
            }

            // Small delay to prevent repeated triggers from one button press
            sleep_ms(300);
        } else {
            // Keep transmitter LOW when button is not pressed
            gpio_put(TX_PIN, 0);
        }

        // Small delay for button checking
        sleep_ms(10);
    }
}