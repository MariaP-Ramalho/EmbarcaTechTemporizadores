#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

//Definições dos pinos
#define led_blue 11
#define led_red 12
#define led_green 13
#define button_a 5

//Declarações de variáveis
bool led_active = false;
int led_state = 3;
int interval = 3000;

//Declaração de funções
int64_t turn_off_callback(alarm_id_t id, void *user_data);
void init_hardware();

int main()
{
    //Inicializa hardware
    init_hardware();

    while (true)
    {
        if (gpio_get(button_a) == 0 && !led_active) //Verifica se o botão está precionado e impede o acionamento com led aceso
        {
            sleep_ms(50);
            if (gpio_get(button_a) == 0) // verifica se o botão ainda está precionado
            {
                gpio_put(led_blue, true);
                gpio_put(led_red, true);
                gpio_put(led_green, true); // aciona todos os leds

                led_active = true;

                add_alarm_in_ms(interval, turn_off_callback, NULL, false); // Inicia o desligamento em 3s
            }
        }
        sleep_ms(10);
    }

    return 0;
}

int64_t turn_off_callback(alarm_id_t id, void *user_data)
{
    if (led_state == 3) // Checa o estado dos leds
    {
        gpio_put(led_blue, false); // Desliga led azul primeiro
        led_state--;
        add_alarm_in_ms(interval, turn_off_callback, NULL, false); // Próximo LED após 3s
    }
    else if (led_state == 2)
    {
        gpio_put(led_red, false); // Desliga led vermelho
        led_state--;
        add_alarm_in_ms(interval, turn_off_callback, NULL, false);
    }
    else if (led_state == 1)
    {
        gpio_put(led_green, false); // Desliga LED1
        led_state = 3;             // Reseta para o próximo acionamento
        led_active = false;
    }
    return 0;
}

//Inicialização dos perifericos
void init_hardware() {

    stdio_init_all();

    gpio_init(led_blue);
    gpio_set_dir(led_blue, true);

    gpio_init(led_red);
    gpio_set_dir(led_red, true);

    gpio_init(led_green);
    gpio_set_dir(led_green, true);

    gpio_init(button_a);
    gpio_set_dir(button_a, GPIO_IN);
    gpio_pull_up(button_a);
}