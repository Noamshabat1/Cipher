#include "cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.

#define ALPHABET_SIZE 26 // The amount of alphabet in English.

#define ALPHABET_UPPER_START 'A'
#define ALPHABET_UPPER_END 'Z'

#define ALPHABET_LOWER_START 'a'
#define ALPHABET_LOWER_END 'z'

/*
 * this function holds the logic of the encoding process.
 */
void encode (char s[], int k)
{
  unsigned long length = strlen (s);

  for (int i = 0; i < (int) length; i++)
  {
    if (s[i] >= ALPHABET_LOWER_START && s[i] <= ALPHABET_LOWER_END)
      //LOWER_CHAR

    {
      s[i] = ALPHABET_LOWER_START + ((s[i] - ALPHABET_LOWER_START + k) %
                                     ALPHABET_SIZE + ALPHABET_SIZE)
                                    % ALPHABET_SIZE;
    }

    else if (s[i] >= ALPHABET_UPPER_START && s[i] <= ALPHABET_UPPER_END)
      //UPPER_CHAR
    {
      s[i] = ALPHABET_UPPER_START + ((s[i] - ALPHABET_UPPER_START + k) %
                                     ALPHABET_SIZE + ALPHABET_SIZE)
                                    % ALPHABET_SIZE;
    }
  }
}

/*
 * this function holds the logic of the decoding process which is
 * symmetrical to the decoding with (-key).
 */
void decode (char s[], int k)
{
  encode (s, -k);
}




