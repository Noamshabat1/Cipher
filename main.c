#include "cipher.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARG_COUNT_TEST 2
#define ARG_COUNT_CMD_TEST 5
#define BUFFER_SIZE 1024
#define BASE 10

#define DECODE "decode"
#define ENCODE "encode"
#define ERR_MSG_WRONG_AMOUNT "The program receives 1 or 4 arguments only.\n"
#define ERR_MSG_INVALID_ONE_ARG "Usage: cipher test\n"
#define ERR_MSG_INVALID_COMMEND "The given command is invalid.\n"
#define ERR_MSG_INVALID_KEY "The given shift value is invalid.\n"
#define ERR_MSG_INVALID_FILE "The given file is invalid.\n"

typedef enum INPUT
{
    COMMAND = 1,
    K,
    INPUT_PATH,
    OUTPUT_PATH
}
    CharType;

int input_for_run_tests (void);
int input_for_enc_dec (char *argv[]);
int run_all_tests (void);
int run_decode_tests (void);
int run_encode_tests (void);
int validate_input (int argc, char *argv[]);

int main (int argc, char *argv[])
{
  if (validate_input (argc, argv) == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }
  return argc == ARG_COUNT_TEST ? input_for_run_tests ()
                                : input_for_enc_dec (argv);
}

/*
 * this function is one out of two function that checking if the input that we
 * received is valid.
 */
int validate_input (int argc, char *argv[])
{
  char *command = argv[COMMAND];
  char *key = argv[K];
  if (argc != ARG_COUNT_TEST && argc != ARG_COUNT_CMD_TEST)//invalid arguments
  {
    fprintf (stderr, ERR_MSG_WRONG_AMOUNT);
    return EXIT_FAILURE;
  }
  if (argc == ARG_COUNT_TEST)
  {
    if (strcmp (command, "test") != 0)
    {
      fprintf (stderr, ERR_MSG_INVALID_ONE_ARG); // "test"
      return EXIT_FAILURE;
    }
  }
  else // if theres five arguments.
  {
    if (strcmp (command, DECODE) != 0 && strcmp (command, ENCODE) != 0)
    { // invalid commend.
      fprintf (stderr, ERR_MSG_INVALID_COMMEND);
      return EXIT_FAILURE;
    }
    // invalid K check
    char *ptr;
    strtol (key, &ptr, BASE);
    if (*ptr != '\0')
    {
      fprintf (stderr, ERR_MSG_INVALID_KEY);
      return EXIT_FAILURE;
    }
    for (int i = 0; i < (int) strlen (key); i++)
    {
      if (key[i] == '.')
      {
        fprintf (stderr, ERR_MSG_INVALID_KEY);
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}

/*
 * this function is running all of the tests
 */
int input_for_run_tests (void)
{
  if (run_all_tests () == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/*
 * this function is second function that checks validation and also checking
 * decoding and encoding by a given commend or calls to run the tests.
 */
int input_for_enc_dec (char *argv[])
{
  char *command = argv[COMMAND];
  char *input_path = argv[INPUT_PATH];
  char *output_path = argv[OUTPUT_PATH];
  char *key = argv[K];
  char *endptr;
  long int k = strtol (key, &endptr, BASE);
  FILE *input_f;
  FILE *output_f;

  input_f = fopen (input_path, "r");
  output_f = fopen (output_path, "w");
  if (NULL != input_f)
  {
    if (NULL != output_f)
    {
      char buf[BUFFER_SIZE];
      if (strcmp (command, DECODE) == 0)
      {
        while (fgets (buf, BUFFER_SIZE, input_f) != NULL)
        {
          decode (buf, (int) k);
          fputs (buf, output_f);
        }
      }
      else if (strcmp (command, ENCODE) == 0)
      {

        while (fgets (buf, BUFFER_SIZE, input_f) != NULL)
        {
          encode (buf, (int) k);
          fputs (buf, output_f);
        }
      }
      fclose (input_f);
      fclose (output_f);
      return EXIT_SUCCESS;
    }
    fclose (input_f);
  }
  fprintf (stderr, ERR_MSG_INVALID_FILE);
  return EXIT_FAILURE;
}

/*
 * this function determent if the tests finished without a problem.
 */
int run_all_tests (void)
{
  if (run_decode_tests () == EXIT_FAILURE
      || run_encode_tests () == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

/*
 * this function contain the tests for the decoding process.
 */
int run_encode_tests (void)
{
  if (test_encode_non_cyclic_lower_case_positive_k () == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  if (test_encode_cyclic_lower_case_special_char_positive_k () == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  if (test_encode_cyclic_lower_case_negative_k () == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  if (test_encode_cyclic_upper_case_positive_k () == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  if (test_encode_non_cyclic_lower_case_special_char_negative_k ()
      == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/*
 * this function contain the tests for the encoding process.
 */
int run_decode_tests (void)
{
  if (test_decode_non_cyclic_lower_case_positive_k () == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  if (test_decode_cyclic_lower_case_special_char_positive_k () == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  if (test_decode_non_cyclic_lower_case_special_char_negative_k ()
      == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  if (test_decode_cyclic_lower_case_negative_k () == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  if (test_decode_cyclic_upper_case_positive_k () == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}