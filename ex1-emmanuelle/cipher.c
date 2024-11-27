#include "cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define LEN 26

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.
char change_cipher_up(char letter, int k)
{
  int move = k % LEN;
  letter = letter + move;
  // Handle wrap-around within 'a' to 'z'
  if (letter > 'Z') {
    letter = 'A' + (letter - 'Z' - 1);
  } else if (letter < 'A') {
    letter = 'Z' - ('A' - letter - 1);
  }
  return letter;
}

char change_cipher_low(char letter, int k)
{
  int move = k % LEN;
  letter = letter + move;
  // Handle wrap-around within 'a' to 'z'
  if (letter > 'z') {
    letter = 'a' + (letter - 'z' - 1);
  } else if (letter < 'a') {
    letter = 'z' - ('a' - letter - 1);
  }
  return letter;
}

// See full documentation in header file
void cipher (char s[], int k)
{
  int size = strlen(s);
  for (int i = 0; i < size; ++i)
  {
    char ch = s[i];
    if (isupper(ch)){
      s[i] = change_cipher_up(ch,k);
    }
    else if (islower(ch)){
      s[i] = change_cipher_low(ch,k);
    }
  }
}
char change_decipher_up(char letter, int k)
{
  int move = k % LEN;
  letter = letter - move;
  // Handle wrap-around within 'a' to 'z'
  if (letter > 'Z') {
    letter = 'A' + (letter - 'Z' - 1);
  } else if (letter < 'A') {
    letter = 'Z' - ('A' - letter - 1);
  }
  return letter;
}

char change_decipher_low(char letter, int k)
{
  int move = k % LEN;
  letter = letter - move;
  // Handle wrap-around within 'a' to 'z'
  if (letter > 'z') {
    letter = 'a' + (letter - 'z' - 1);
  } else if (letter < 'a') {
    letter = 'z' - ('a' - letter - 1);
  }
  return letter;
}

// See full documentation in header file
void decipher (char s[], int k)
{
  int size = strlen(s);
  for (int i = 0; i < size; ++i)
  {
    char ch = s[i];
    if (isupper(ch)){
      s[i] = change_decipher_up(ch,k);
    }
    else if (islower(ch)){
      s[i] = change_decipher_low(ch,k);
    }
  }
}
