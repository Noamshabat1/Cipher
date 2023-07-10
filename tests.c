#include "tests.h"
#include <string.h>

#define K_1 3
#define K_2 2
#define K_3 (-1)
#define K_4 (-3)
#define K_5 29

// See full documentation in header file
int test_encode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  encode (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "ab, c";
  char out[] = "cd, e";
  encode (in, K_2);

  char in2[] = "this is a test, cipher algorithm!";
  char out2[] = "vjku ku c vguv, ekrjgt cniqtkvjo!";
  encode (in2, K_2);

  return !(strcmp (in, out) == 0 && strcmp (in2, out2) == 0);
}

// See full documentation in header file
int test_encode_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "bc, d!";
  char out[] = "ab, c!";
  encode (in, K_3);

  char in2[] = "code, is fun!";
  char out2[] = "bncd, hr etm!";
  encode (in2, K_3);

  return !(strcmp (in, out) == 0 && strcmp (in2, out2) == 0);
}

// See full documentation in header file
int test_encode_cyclic_lower_case_negative_k ()
{
  char in[] = "ab, c";
  char out[] = "xy, z";
  encode (in, K_4);

  char in2[] = "this is a test!@@@!";
  char out2[] = "qefp fp x qbpq!@@@!";
  encode (in2, K_4);

  return !(strcmp (in, out) == 0 && strcmp (in2, out2) == 0);
}

// See full documentation in header file
int test_encode_cyclic_upper_case_positive_k ()
{
  char in[] = "CD, E";
  char out[] = "FG, H";
  encode (in, K_5);

  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "def";
  char out[] = "abc";
  decode (in, K_1);

  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "cd, e";
  char out[] = "ab, c";
  decode (in, K_2);

  char in2[] = "vjku ku c vguv!";
  char out2[] = "this is a test!";
  decode (in2, K_2);

  return !(strcmp (in, out) == 0 && strcmp (in2, out2) == 0);
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "wxa, y :) wx, y";
  char out[] = "xyb, z :) xy, z";
  decode (in, K_3);

  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_negative_k ()
{
  char in[] = "xy, z xyz abcd :)";
  char out[] = "ab, c abc defg :)";
  decode (in, K_4);

  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_upper_case_positive_k ()
{
  char in[] = "DEDE, FF OPQR $*& STUVD";
  char out[] = "ABAB, CC LMNO $*& PQRSA";

  decode (in, K_5);
  return strcmp (in, out) != 0;
}

