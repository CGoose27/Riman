/*
Riman is eventually going to be a C mod manager for rimworld!
Right now this is just the base.
*/


#include "Riman.h"
#include <stdio.h>

int main() {
    detectRimworldPath();
    if (parseRimworldXML() != 0) {
        printf("Failed to do stuff");
        return -1;
    }

    printf("%i", modCount);

    for (int i = 0; i < modCount; i++) {
        printf("%s\n", LoadOrder[i]->Name);
      //printf("Description: %s\n",
      //         LoadOrder[i]->Description ? LoadOrder[i]->Description : "N/A");
      }

    printf("Done.");
    return 0;
}
