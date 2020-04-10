/*
 * CSc103 Project 2: prime numbers.
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 */

#include <iostream>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;

int main()
{
 unsigned long n, i; //able to store large numbers
 while (cin >> n){
  int prime = 1;

  if (((n % 2) == 0) && n != 2 || (n == 1))
   prime = 0;

  for (i = 3; i < sqrt(n) + 1; i += 2){
   if ((n % i) == 0)
    prime = 0;
  }

  cout << prime << endl;
 }

 return 0;
}
