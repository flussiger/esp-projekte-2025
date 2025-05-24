//---------------------------------------------------------------------------------------------------------------------
// Password manager program:
// In this program, you can enter upto 5 passwords as long as they comply with certain rules such as length and the
// usage of certain characters. After every password input, one can choose to exit or enter another one, but after 5
// the program ends. It is only written in stdio.h
//
// Tutor: --
//
// Author: --
//---------------------------------------------------------------------------------------------------------------------
//


#include <stdio.h>

#define MAX_PW_LENGTH 15
#define MIN_PW_LENGTH 8
#define MAX_PASSWORDS 5
#define GOOD_RETURN_VALUE 1
#define BAD_RETURN_VALUE 0

//---------------------------------------------------------------------------------------------------------------------
/// The function calculates the length of the input (char* password). It cannot change it since it is a const.
/// @param password password to get length of
/// @return returns the length
int getLength(const char* password)
{
  int length = 0;  
  for (int i = 0; password[i] != '\0'; i++)
  {
    length++;
  }

  return length;
}


//---------------------------------------------------------------------------------------------------------------------
/// Checks whether the given password is a duplicate of an already existing passwords.
/// 
/// Compares the input password against all stored passwords. If an exact match is found,
/// the function returns BAD_RETURN_VALUE. Otherwise, it returns GOOD_RETURN_VALUE.
/// 
/// @param password The password to check for duplication.
/// @param password_count The number of passwords already stored.
/// @param passwords The array containing all stored passwords.
/// @return BAD_RETURN_VALUE if the password is a duplicate, GOOD_RETURN_VALUE otherwise.
int checkDuplicate(const char* password, int password_count, char passwords[MAX_PASSWORDS][MAX_PW_LENGTH + 1])
{
  for (int i = 0; i < password_count; i++)
  {
    int match = 1;
    for (int j = 0; j < MAX_PW_LENGTH; j++)
    {
      if (passwords[i][j] != password[j])
      {
        match = 0;
        break;
      }
      if (password[j] == '\0' && passwords[i][j] == '\0')
      {
        break;
      }
    }

    if (match == 1)
    {
      return BAD_RETURN_VALUE; 
    }
  }

  return GOOD_RETURN_VALUE;
}


//---------------------------------------------------------------------------------------------------------------------
/// Checks whether the password and 3 integers (which are meant as indexes of the password) are integers between 0-9.
/// Checks wheter password at index one, two, three is an integer, if yes returns BAD_RETURN_VALUE 
/// if not, returns GOOD RETURN VALUE 
/// 
/// @param password The password to check for duplication.
/// @param one Index for password
/// @param two Index for password
/// @param three Index for password
/// @return BAD_RETURN_VALUE password at the indexes are integers, GOOD_RETURN_VALUE otherwise.
int isDigit(const char* password, int one, int two, int three)
{
  if ((password[one] >= '0' && password[one] <= '9') && (password[two] >= '0' && password[two] <= '9') &&
      (password[three] >= '0' && password[three] <= '9'))
      {
        return BAD_RETURN_VALUE;
      }
  else
  {
    return GOOD_RETURN_VALUE;
  }
}


//---------------------------------------------------------------------------------------------------------------------
/// Compares two strings sente1 and sente2. Loops through both sentences for every character in it until length
/// and returns BAD_RETURN_VALUE if they are not equal
/// @param sente1 Sentence 1 first string
/// @param sente2 Sentence 2 second string
/// @param length Number of characters that are supposted to be compared 
/// @return BAD_RETURN_VALUE they are not equal, GOOD_RETURN_VALUE they are equal.
int compareTwoStrings(const char* sente1, const char* sente2, int length)
{
  for (int i = 0; i < length; i++)
  {
    if (sente1[i] != sente2[i])
    {
      return BAD_RETURN_VALUE;
    }
  }
  return GOOD_RETURN_VALUE;
}


//---------------------------------------------------------------------------------------------------------------------
/// 
/// This function checks if there are any repeating patterns withtin the password, with at least length 3
/// and if they occur it returns BAD_RETURN_VALUE, if there are none, it returns GOOD_RETURN_VALUE
///
/// @param password is the entered password
/// @return BAD_RETURN_VALUE there are patterns, GOOD_RETURN_VALUE if there are none
int checkNumericPattern(const char* password) //I got this function from chatgpt.
{
  int len = getLength(password);
  
  for (int index = 0; index < len; index++)
  {
    if (password[index] >= '0' && password[index] <= '9')
    {
      int block_len = 0;
      while (index + block_len < len &&
             (password[index + block_len] >= '0' && password[index + block_len] <= '9'))
      {
        block_len++;
      }
      for (int pattern_length = 3; pattern_length <= block_len; pattern_length++)
      {
        for (int start = index + pattern_length; start <= len - pattern_length; start++)
        {
          int pattern_index;
          for (pattern_index = 0; pattern_index < pattern_length; pattern_index++)
          {
            if (!(password[start + pattern_index] >= '0' && password[start + pattern_index] <= '9'))
            {
              break;
            }
          }
          if (pattern_index == pattern_length && compareTwoStrings(password + index, password + start, pattern_length))
          {
            return BAD_RETURN_VALUE;
          }
        }
      }
      index += block_len - 1;
    }
  }
  return GOOD_RETURN_VALUE;
}

//---------------------------------------------------------------------------------------------------------------------
/// 
/// This function checks if the entered password is a palindrome by comparing each char from the left and right 
/// simultaneously.
/// and if it is palindrom = BAD_RETURN_VALUE, if it isnt, it returns GOOD_RETURN_VALUE
///
/// @param length length of the passsword
/// @param password is the entered password
/// @return BAD_RETURN_VALUE = palindrom, GOOD_RETURN_VALUE = no palindrome
int checkPalindrome(const char* password, int length)
{
  int from_left = 0;
  int from_right = length - 1;

  do
  {
    if (password[from_left] != password[from_right])
    {
      return GOOD_RETURN_VALUE; //not a palindrome
    }
    from_left++;
    from_right--;
  } while(from_left < from_right);
  return BAD_RETURN_VALUE;
}

//---------------------------------------------------------------------------------------------------------------------
/// 
/// This function checks if the entered password has any special characters, by using the integer values of the special
/// characters and checking if any special character is within these bounds.
/// If there is a special char = GOOD_RETURN_VALUE. If there is no special character = BAD_RETURN_VALUE
///
/// @param length length of the passsword
/// @param password is the entered password
/// @return BAD_RETURN_VALUE = no special char, GOOD_RETURN_VALUE = special char
int checkSpecialChar(const char* password, int length)
{
  for (int pw_index = 0; pw_index < length; pw_index++)
  {
    if ((password[pw_index] >= 32 && password[pw_index] <= 47) || (password[pw_index] >= 58 && password[pw_index] <= 64) ||
        (password[pw_index] >= 91 && password[pw_index] <= 96) || (password[pw_index] >= 123 && password[pw_index] <= 126))
    {
      return GOOD_RETURN_VALUE;
    }
  }

  return BAD_RETURN_VALUE;
}


//---------------------------------------------------------------------------------------------------------------------
/// 
/// This function checks if the entered password has any integers in it self by checking every char for a digit.
/// 
/// If there is a digit = GOOD_RETURN_VALUE. If there is no digit = BAD_RETURN_VALUE
///
/// @param length length of the passsword
/// @param password is the entered password
/// @return BAD_RETURN_VALUE = no digit, GOOD_RETURN_VALUE = digit
int checkDigit(const char* password, int length)
{
  for (int pw_index = 0; pw_index < length; pw_index++)
  {
    if (password[pw_index] >= '0' && password[pw_index] <= '9')
    {
      return GOOD_RETURN_VALUE;
    }
  }

  return BAD_RETURN_VALUE;
}

//---------------------------------------------------------------------------------------------------------------------
/// 
/// This function checks if the entered password has any lowercase characters by checking every char.
/// 
/// If there is a lowercase char = GOOD_RETURN_VALUE. If there is no lowercase character = BAD_RETURN_VALUE
///
/// @param length length of the passsword
/// @param password is the entered password
/// @return BAD_RETURN_VALUE = no lowercase char, GOOD_RETURN_VALUE =  lowercase char
int checkLowercase(const char* password, int length)
{
  for (int pw_index = 0; pw_index < length; pw_index++)
  {
    if (password[pw_index] >= 'a' && password[pw_index] <= 'z')
    {
      return GOOD_RETURN_VALUE;
    }
  }

  return BAD_RETURN_VALUE;
}

//---------------------------------------------------------------------------------------------------------------------
/// 
/// This function checks if the entered password has any uppercase characters by checking every char.
/// 
/// If there is a uppercase char = GOOD_RETURN_VALUE. If there is no uppercase character = BAD_RETURN_VALUE
///
/// @param length length of the passsword
/// @param password is the entered password
/// @return BAD_RETURN_VALUE = no uppercase char, GOOD_RETURN_VALUE =  uppercase char
int checkUppercase(const char* password, int length)
{
  for (int pw_index = 0; pw_index < length; pw_index++)
  {
    if (password[pw_index] >= 'A' && password[pw_index] <= 'Z')
    {
      return GOOD_RETURN_VALUE;
    }
  }

  return BAD_RETURN_VALUE;
}

//---------------------------------------------------------------------------------------------------------------------
/// 
/// This function checks if the entered password has a valid length. so under 8 and over 15 is invalid
/// 
/// If length is valid = GOOD_RETURN_VALUE. If length is invalid = BAD_RETURN_VALUE
///
/// @param length length of the passsword
/// @return BAD_RETURN_VALUE = invalid length, GOOD_RETURN_VALUE =  valid length
int validatePWLength(int length)
{
  if (length < MIN_PW_LENGTH)
  {
    printf("Password must be at least 8 characters long.\n");
    return BAD_RETURN_VALUE;
  }
  else if (length > MAX_PW_LENGTH)
  {
    printf("Password must not be more than 15 characters long.\n");
    return BAD_RETURN_VALUE;
  }
  return GOOD_RETURN_VALUE;
}

//---------------------------------------------------------------------------------------------------------------------
/// 
/// This function is called if all checks were good and now the password is stored in this function. And 0 terminated
/// 
/// 
/// @param password current input password
/// @param password_count number of already stored passwords
/// @param passwords array of all passwords
/// 
void storePassword(const char* password, int* password_count, char passwords[MAX_PASSWORDS][MAX_PW_LENGTH + 1])
{
  int i = 0;
  while (password[i] != '\0' && i < MAX_PW_LENGTH)
  {
    passwords[*password_count][i] = password[i];
    i++;
  }
  passwords[*password_count][i] = '\0';
  (*password_count)++;
}

//---------------------------------------------------------------------------------------------------------------------
/// 
/// This is the main handling function and checks if every criteria of the password is met (BAD RETURN VALUE if not)
/// and GOOD_RETURN_VALUE if yes. It checks every criteria-function for the criteria like length.
///
/// @param password current input password
/// @param passwords array of all passswords
/// @param password_count number of already stored passwords
/// @return BAD_RETURN_VALUE = invalid length or if any criteria not met, GOOD_RETURN_VALUE =  all criteria passed
int validatePassword(const char* password, char passwords[MAX_PASSWORDS][MAX_PW_LENGTH + 1], int password_count)
{
  int length = getLength(password);
  
  if (validatePWLength(length) == BAD_RETURN_VALUE)
  {
    return BAD_RETURN_VALUE;
  }

  int has_lower = checkLowercase(password, length);
  int has_upper = checkUppercase(password, length);
  int has_digit = checkDigit(password, length);
  int has_special_char = checkSpecialChar(password, length);
  int has_palindrome = checkPalindrome(password, length);
  int has_numeric_pattern = checkNumericPattern(password);
  int has_duplicate = checkDuplicate(password, password_count, passwords);

  if (has_lower == BAD_RETURN_VALUE)
  {
    printf("Password must contain at least one lowercase character.\n");
    return BAD_RETURN_VALUE;
  }

  if (has_upper == BAD_RETURN_VALUE)
  {
    printf("Password must contain at least one uppercase character.\n");
    return BAD_RETURN_VALUE;
  }

  if (has_digit == BAD_RETURN_VALUE)
  {
    printf("Password must contain at least one digit.\n");
    return BAD_RETURN_VALUE;
  }

  if (has_special_char == BAD_RETURN_VALUE)
  {
    printf("Password must contain at least one special character.\n");
    return BAD_RETURN_VALUE;
  }

  if (has_palindrome == BAD_RETURN_VALUE)
  {
    printf("Password must not be a palindrome.\n");
    return BAD_RETURN_VALUE;
  }

  if (has_numeric_pattern == BAD_RETURN_VALUE)
  {
    printf("Password must not contain repeating numeric patterns.\n");
    return BAD_RETURN_VALUE;
  }

  if (has_duplicate == BAD_RETURN_VALUE)
  {
    printf("This password has already been used.\n");
    return BAD_RETURN_VALUE;
  }
  
  return GOOD_RETURN_VALUE;
}

//---------------------------------------------------------------------------------------------------------------------
/// 
/// This is a simple tolowercase function that converts an input(from stringsmatch) to lowercase if any character is
/// uppercase. and does so until it hits '\0'
///
/// @param input input from stringsMatch function
/// 
void convertToLowerCase(char* input)
{
  for (int i = 0; input[i] != '\0'; i++)
  {
    if (input[i] >= 'A' && input[i] <= 'Z')
    {
      input[i] += 32;
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------
/// 
/// This function checks if two strings are the same so like strcmp. It converts the strings into lowercase, and then
/// compares them letter by letter until \0 is hit. If they arent the same it Returns BAD_RETURN_VALUE.
/// If they are alike it returns 1 = so GOOD_RETURN_VALUE
/// @param a
/// @param b
/// @return BAD_RETURN_VALUE = invalid length or if any criteria not met, GOOD_RETURN_VALUE =  all criteria passed
int stringsMatch(char *a, char *b)
{
  convertToLowerCase(a);
  convertToLowerCase(b);
  int i = 0;

  while (a[i] != '\0' && b[i] != '\0')
  {
    if (a[i] != b[i])
    {
      return BAD_RETURN_VALUE;
    }
    i++;
  }
  return (a[i] == '\0' && b[i] == '\0'); //if both end at same position 1, if not 0
}

//---------------------------------------------------------------------------------------------------------------------
/// 
/// This function asks the user if he would like to enter another password. If yes = he can enter another password
/// if no = he can'T and the program prints a goodbye message in main. All other inputs aren't accepted.
/// It works my getting the input, replacin the newline character, anf if there is no newline
/// meaning the input is tooo long, it flushes the input and
/// loops until a valid input is entered. And also compares the strings as No and nO is acceptable.
/// @return if yes (another password) it returns GOOD_RETURN_VALUE, if no other password it returns BAD_RETURN_VALUE.
int askYesNo(void)
{
  char input[5]; //[y][e][s][\n][\0] -> genug space für newline und 0
  int ch = 0;
  while (1)
  {
    printf("Do you want to set another password? (yes/no)\n");
    printf(" > ");
    if (fgets(input, sizeof(input), stdin) == NULL) //Heard of fgets in Vorlesung, looked it up
    {
      printf("Invalid input. Please enter 'yes' or 'no'.\n");
      continue;
    }
    int newline_found = 0;
    for (size_t i = 0; i < sizeof(input); i++)
    {
      if (input[i] == '\n')
      {
        input[i] = '\0';
        newline_found = 1;
        break;
      }
    }
    if (!newline_found)
    {
      while ((ch = getchar()) != '\n' && ch != EOF);
    }
    
    if (stringsMatch(input, "yes"))
    {
      return GOOD_RETURN_VALUE;
    }
    
    else if (stringsMatch(input, "no"))
    {
      return BAD_RETURN_VALUE;
    }
    printf("Invalid input. Please enter 'yes' or 'no'.\n");
  }
}

//---------------------------------------------------------------------------------------------------------------------
/// 
/// This function handles the ask for another password after one was successfully stored. It just calles the askyesno
/// function and if the askyesno function returns GOOD_RETURN_VALUE
/// 
/// @return BAD_RETURN_VALUE = if the user doesnt want to add another password
/// if he wants to add another password = GOOD_RETURN_VALUE
int askForAnotherPassword(void)
{
  int another_password = askYesNo();

  if (another_password == GOOD_RETURN_VALUE)
  {
    return GOOD_RETURN_VALUE;
  }
  else
  {
    return BAD_RETURN_VALUE;
  }
}

//---------------------------------------------------------------------------------------------------------------------
/// 
/// This function handles the enter password phase when the user wants to add a password. By fgetc it gets char by char
/// from the password and saves it into password. When count gets bigger then MAX_PW_LENGTH it is marked as too long
/// and it prints that it must not be too long. After valid length password, a password is null terminated. It loops
/// until a valid password is entered. fgetc runs until it hits a newline char (so enter) or EOF char. 
///
/// @param password current input password
/// 
void enterPassword(char* password)
{
  int c = 0;

  while (1)
  {
    int count = 0;
    int too_long = 0;
    printf("Please enter a password\n");
    printf(" > ");

    while ((c = fgetc(stdin)) != '\n' && c != EOF) //Heard of fgetc in vorlesung, looked it up.
    {
      if (count < MAX_PW_LENGTH)
      {
        password[count] = (char)c; //typecast von int -> char weil fgetc int macht
        count++;
      }
      else
      {
        too_long = 1;
      }
    }

    password[count] = '\0';

    if (too_long)
    {
      printf("Password must not be more than %d characters long.\n", MAX_PW_LENGTH);
      continue;
    }

    break;
  }
}

//---------------------------------------------------------------------------------------------------------------------
/// 
/// This is the main function and handles everything in the programm. It creates 5 arrays size 15+1 and intializes them
/// then it initializes password_count. and prints welcome message. 
/// So while password_count < MAX_PASSWORDS(5), it loops by first initializing another array size 16 for the entered
/// password and calls enterPassword where a password is entered
/// with it. Then it calls validatePassword and there it checks if the password is valid. If its valid, its stored
/// If the password_count (number of storedPasswords) is eqaul to 5 (MAX_PASSWORDS) it exits the program and returns 5
/// after successfully entering a password and storing it askForAnotherPassword is called and asks if the user wants
/// to input another password. If no, it Exits the passwordmanager and returns BAD_RETURN_VALUE.
///
/// @return 5 if capacity exhausted, BAD_RETURN_VALUE if user doesnt want to input another password and
/// GOOD_RETURN_VALUE  
int main(void)
{
  char passwords[MAX_PASSWORDS][MAX_PW_LENGTH + 1] = {{0}};
  int password_count = 0;
  printf("Welcome to the ESP password manager!\n\n");
  
  while (password_count < MAX_PASSWORDS)
  {
    char password[MAX_PW_LENGTH + 1];
    
    enterPassword(password);

    if (validatePassword(password, passwords, password_count) == GOOD_RETURN_VALUE)
    {
      storePassword(password, &password_count, passwords);
      printf("Password set successfully.\n");

      if (password_count == MAX_PASSWORDS)
      {
        printf("Capacity exhausted! Go touch some grass!\n");
        return 5;
      }

      if (askForAnotherPassword() == BAD_RETURN_VALUE)
      {
        printf("Exiting password manager. Goodbye!\n");
        return BAD_RETURN_VALUE;
      }
    }

  }
}
