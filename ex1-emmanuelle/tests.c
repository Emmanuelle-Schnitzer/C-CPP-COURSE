#include "tests.h"
# include <string.h>
#include <stdio.h>
#define K_1 3
#define K_2 2
#define K_3 (-1)
#define K_4 (-3)
#define K_5 29

// See full documentation in header file
int test_cipher_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  cipher (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "b6i.9p";
  char out[] = "d6k.9r";
  cipher (in, K_2);
  return strcmp (in, out) == 0;
}

// See full documentation in header file
int test_cipher_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "t(u**v";
  char out[] = "s(t**u";
  cipher (in, K_3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_cyclic_lower_case_negative_k ()
{
  char in[] = "xyz";
  char out[] = "uvw";
  cipher (in, K_4);
  return strcmp (in, out) == 0;
}

// See full documentation in header file
int test_cipher_cyclic_upper_case_positive_k ()
{
  char in[] = "DPY";
  char out[] = "GSB";
  cipher (in, K_5);
  return strcmp (in, out) == 0;
}

// See full documentation in header file
int test_decipher_non_cyclic_lower_case_positive_k ()
{
  char in[] = "def";
  char out[] = "abc";
  decipher (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decipher_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "b6i.9p";
  char out[] = "z6g.9n";
  decipher (in, K_2);
  return strcmp (in, out) == 0;
}

// See full documentation in header file
int test_decipher_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "t+u!v";
  char out[] = "u+v!w";
  decipher (in, K_3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decipher_cyclic_lower_case_negative_k ()
{
  char in[] = "xyz";
  char out[] = "abc";
  decipher (in, K_4);
  return strcmp (in, out) == 0;
}

// See full documentation in header file
int test_decipher_cyclic_upper_case_positive_k ()
{
  char in[] = "DPY";
  char out[] = "AMV";
  decipher (in, K_5);
  return strcmp (in, out) == 0;
}
