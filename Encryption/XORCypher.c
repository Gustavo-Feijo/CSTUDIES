#include "XORCypher.h"
#include <stdio.h>
#include <stdlib.h>

// Create a XOR cypher for a given key. Decrypt and Encrypt use same logic.
void XORCypher(char *buffer, char key) {
  if (buffer == NULL) {
    printf("Can't encrypt or decrypt empty buffer\n");
    return;
  }

  // Simply do the XOR for each letter.
  while (*buffer != '\0') {
    *buffer ^= key;
  }
}
