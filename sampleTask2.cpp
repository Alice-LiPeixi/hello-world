#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int LENGTH = 5;
const int COUNT = 3;

int main() {
  char barcodes[COUNT][LENGTH] = {
    {'.', '.', '|', '|', ','},
    {'.', '|', '.', '|', '|'},
    {'|', '.', '|', ',', '|'},
  };

  char sampleChars[100] = { '.', '|', '.', '|', '|', '|', '.', '|', ',', '|', '.', '.', '|', '|', ',', '|', '.', '|', ',', '|', '|', '|', '|', '|', '|'};

  int len = strlen(sampleChars);

  int s = 0;
  bool a[100];

  for (int i = 0; i < len; i++) {
    char ch = sampleChars[i];
    // cout << ch << ", s: " << s << " ";

    // init a[]
    if (s == 0) {
      for (int j = 0; j < LENGTH; j++) {
        a[j] = true;
      }
    }

    // filter
    for (int j = 0; j < COUNT; j++) {
      if (ch != barcodes[j][s]) {
        // cout << "set a[j] false: " << j << endl;
        a[j] = false;
      }
    }
    s++;

    // check is valid
    if (s == LENGTH) {
      int index = -1;
      for (int j = 0; j < COUNT; j++) {
        // cout << a[j] << endl;
        if (a[j]) {
          index = j;
        }
      }
      cout << index;
      if (index == -1 ) {
        cout << "invalid...";
      }
      s = 0;
    }
  }
  cout << endl;
}
