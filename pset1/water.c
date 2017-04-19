#include <stdio.h>
#include <cs50.h>

int main(void) {
    //ask user how long is shower?
    printf("Minutes: ");
    int minutes = get_int();
    int bott = minutes*12;
    //multiply minutes of shower by bottles of water used

    printf("Bottles: %i \n", bott);
} 