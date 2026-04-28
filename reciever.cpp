#include "pico/stdlib.h"

// RF receiver DATA pin is connected to GPIO 16
#define RX_PIN 16

// LED is connected to GPIO 15
#define LED_PIN 15

int main() {
    // Initialize standard input/output
    stdio_init_all();

    // Set up RF receiver pin as an input
    gpio_init(RX_PIN);
    gpio_set_dir(RX_PIN, GPIO_IN);

    // Set up LED pin as an output
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Make sure LED starts OFF
    gpio_put(LED_PIN, 0);

    while (true) {
        // Read the incoming signal from the RF receiver
        int received_signal = gpio_get(RX_PIN);

        // If a HIGH signal is received, flash the LED
        if (received_signal == 1) {
            // Flash LED for 60 seconds
            // Each loop takes 1 second total:
            // 0.5 seconds ON + 0.5 seconds OFF
            for (int i = 0; i < 60; i++) {
                gpio_put(LED_PIN, 1);  // Turn LED ON
                sleep_ms(500);

                gpio_put(LED_PIN, 0);  // Turn LED OFF
                sleep_ms(500);
            }
        }

        // Small delay before checking receiver again
        sleep_ms(10);
    }
}