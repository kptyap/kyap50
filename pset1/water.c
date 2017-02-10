#include <stdio.h>
#include <cs50.h>

int main(void) {
    //ask user how long is shower?
    printf("How many minutes do you shower for?");
    int minutes = GetInt();
    int bott = minutes*12;
    //multiply minutes of shower by bottles of water used

    printf("bottles: %i \n", bott);
} 