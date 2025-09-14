#include <stdio.h>
#include "cases.h"

int main()
{
    remove("data/authenticated.dat");
    displayIntro();

    crypter();

    return 0;
}