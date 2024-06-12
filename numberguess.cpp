#include <iostream>
#include <time.h>
using namespace std;
int main()
{
    int number,userNumber,myNumber=0;
    srand(time(0)); //seed random number generator
	number = rand() % 100 + 1; // random number between 1 and 100
    cout<<"guess a number game\n";
    
    do
    {
     cout<<"guess a number between 1 to 100:";
     cin>>userNumber;
     myNumber++;
     
     if(userNumber==number)
     {
      cout<<"correct Guess!!:)\n";
     }
     else if(userNumber>number)
     {
        cout<<"your number is too large!!!:( \n" ;
     
    }
    else
    {
        cout<<"your number is too small!!:(\n" ;
    }
    }while(userNumber!=0);


    return 0;
}