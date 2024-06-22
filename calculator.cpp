#include <iostream>
using namespace std;
int main()
{
    float num1,num2,total;
    cout<<"enter two numbers:";
    cin>>num1>>num2;
    int choice;
    cout<<"enter your choice: 1=addition,\n2=subtraction,\n3=multiplication,\n4=division\n";
    cin>>choice;
    
    switch(choice)
    {
        case 1:total=num1+num2;
        cout<<"The sum of two numbers is:"<<total;
        break;
        
         case 2:total=num1-num2;
        cout<<"The difference of two numbers is:"<<total;
        break;
        
         case 3:total=num1*num2;
        cout<<"The multiplication of two numbers is:"<<total;
        break;
        
         case 4:total=num1/num2;
        cout<<"The division of two numbers is:"<<total;
        break;
        
        case 5:default:
        cout<<"enter correct choice...!!";
          
          return 0;
    }
}

