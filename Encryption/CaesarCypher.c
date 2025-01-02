#include "CaesarCypher.h"
#include <stdio.h>
#include <stdlib.h>

// Receives a buffer and the jump size and do the cypher.
void CaesarCypher(char *buffer, int jump, bool decrypt) {
  // Verify the buffer.
  if (buffer == NULL) {
    printf("Can't encrypt or decrypt empty buffer\n");
    return;
  }
  // Normalize the jump.
  jump = jump % 26;
  if (decrypt > 0)
    jump *= -1;
  // Loop through each char.
  while (*buffer != '\0') {
    // Get the base character.
    char base = 0;

    // Verify if the buffer char is a letter.
    if (*buffer >= 'a' && *buffer <= 'z')
      base = 'a';
    else if (*buffer >= 'A' && *buffer <= 'Z')
      base = 'A';

    // Verify if it's alphanumerical.
    if (base != 0) {
      // Change the buffer.
      *buffer = base + ((*buffer - base + jump + 26) % 26);
    }
    buffer++;
  }
}
