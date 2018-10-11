#include <iostream>
#include <cstring>

using namespace std;

const char NULL_CHAR = '\0';

/*
 * Function: digits_to_barcode
 * To convert the given digit string to a barcode string
 * Return nothing (void)
 */

/* ADD YOUR CODE HERE */

int str_len(const char s[])
{
    int j;
    for (j = 0; s[j] != NULL_CHAR; j++);
    return j;
}



void digits_to_barcode (const char barcodes[][6], char input_string[], char output_barcode[2506]){
    memset(output_barcode, '\0', 2506);
    int s = str_len(input_string);
    int sum = 0;
    int a = 0;
    for (int i = 0; i < s; i++) {
        a += (int)(input_string[s - 1 - i] - 48);
    }
    sum = sum + a;

    for (int j = 0; j < s; j ++){
        int b = input_string[j] - 48;
        strcat(output_barcode, barcodes[b]);
        cout << "output_barcode = " << output_barcode << endl;
    }
    int c = (10 - sum % 10) % 10;
    strcat(output_barcode, barcodes[c]);
}

/*
 * Function: barcode_to_digits
 * Return true and store the digits in digit_string if barcode is valid;
 * Return false otherwise
 */

/* ADD YOUR CODE HERE */

bool barcode_to_digits (const char barcodes[][6], char input_string[2506], char digit_string[501]) {
    int len = str_len(input_string);
    bool a[100];
    char c[501];
    char e[1];
    int t = 0;
    if (len == 0) {
        return false;
    } else if (len % 5 == 0 && len != 0) {
        for (int b = 0; b < (len / 5); b++) {
            for (int j = 0; j < 10; j++) {
                a[j] = true;
                for (int i = 0; i < 5; i++) {
                    if (input_string[i + 5 * b] != barcodes[j][i]) {
                        a[j] = false;
                    }
                }
                if (a[j] && b != len / 5 - 1) {
                    digit_string[b] = j + 48;
                }
                digit_string[len / 5 - 1] = NULL_CHAR;
                if (a[j] && b == len / 5 - 1) {
                    e[0] = j + 48;
                }
            }
            if (b < len / 5 - 1) {
               t = t + (digit_string[b] - 48);
            }
        }
        if ((t + (e[0] - 48)) % 10 != 0) {
            return false;
        }
        return true;
    }
    return false;
}
/*
 * Function: main
 * You are NOT ALLOWED to change ANY CODE in this function
 */
int main()
{
 const char barcodes[][6]=
  {
   "'''||",
   "||'''",
   "|'|''",
   "|''|'",
   "|'''|",
   "'||''",
   "'|'|'",
   "'|''|",
   "''||'",
   "''|'|"
  };

 int option;
 char input_string[501];  // a barcode or digit string

 do {
  cout << endl;
  cout << "Welcome to the barcode program!" << endl;
  cout << "Please select an option to proceed:" << endl;
  cout << "1. Convert digits to barcode" << endl;
  cout << "2. Revert digits from barcode" << endl;
  cout << "3. Exit" << endl << endl;

  cout << "Your option: ";
  cin >> option;

  switch(option)
  {
   case 1:
    cout << "Please enter the digit sequence: ";
    cin >> input_string;

    char output_barcode[2506];  // barcode string
    digits_to_barcode(barcodes, input_string, output_barcode);
    cout << "The barcode is: " << output_barcode << endl;
    break;

   case 2:
    cout << "Please enter the barcode: ";
    cin >> input_string;

    char digit_string[101];
    if (barcode_to_digits(barcodes, input_string, digit_string))
     cout << "The digit sequence is: " << digit_string << endl;
    else
     cout << "Invalid barcode." << endl;
    break;

   case 3:
    break;

   default:
    cout << "Invalid option. Please try again." << endl;
    break;
  }

 } while (option != 3);

 return 0;
}