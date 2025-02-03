#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definições dos pipnos
#define led_red 11
#define led_yellow 12
#define led_green 13

static volatile uint current_led = 0;

//Declaração de funções
bool repeating_timer_callback(struct repeating_timer *timer);
void init_hardware();

int main()
{
    init_hardware(); // inicialização dos periféricos

    struct repeating_timer timer; //cria timer

    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer); //aciona callback a cada 3s

    while (true) {
        sleep_ms(1000);
        printf("Passou 1 segundo\n"); //mensagem no monitor a cada 1s
    }
}

//função callback
bool repeating_timer_callback(struct repeating_timer *timer){
    gpio_put(led_red, 0);
    gpio_put(led_yellow, 0);
    gpio_put(led_green, 0); //Desliga todos os leds

    // Liga o próximo LED com base na variável current_led
    if (current_led == 0) {
        gpio_put(led_red, 1);
    } else if (current_led == 1) {
        gpio_put(led_yellow, 1);
    } else if (current_led == 2) {
        gpio_put(led_green, 1);
    }

    // Alterna para o próximo LED na sequência
    current_led = (current_led + 1) % 3;

    printf("LED alternado\n");
    return true; // Mantém o temporizador repetindo
}

//Inicializa periféricos
void init_hardware() {

    stdio_init_all();

    gpio_init(led_red);
    gpio_set_dir(led_red, true);

    gpio_init(led_yellow);
    gpio_set_dir(led_yellow, true);

    gpio_init(led_green);
    gpio_set_dir(led_green, true);
}