#include <iostream>
using namespace std;

 char space[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
 int row;
 int column;
 char token='x';
 bool tie=false;
 string P1="x ";
 string P2="O ";

void f1()
{

  
  
 //structure of a game board    
   
    
    cout<<"   |     |  \n"  ;
    cout<<" "<<space[0][0]<<" | "<<space[0][1]<<"   |"<<space[0][2]<<" \n";
    cout<<"---|-----|---\n";
    cout<<"   |     |  \n"  ;
    cout<<" "<<space[1][0]<<" | "<<space[1][1]<<"   |"<<space[1][2]<<" \n";
    cout<<"   |     |  \n"  ;
    cout<<"---|-----|---\n";
    cout<<" "<<space[2][0]<<" | "<<space[2][1]<<"   |"<<space[2][2]<<" \n";
    cout<<"   |     |  \n"  ;
}
    
  void f2()
  {
     int digit;
     if(token=='x')
     {
         cout<<P1<<" please enter";
         cin>>digit;
     }
     
  else if(token=='O')
     {
         cout<<P2<<" please enter";
         cin>>digit;
     }
     
      if(digit==1)
      {
          row=0;
          column=0;
      }
      if(digit==2)
      {
          row=0;
          column=1;
      }
      if(digit==3)
      {
          row=0;
          column=2;
      }
      if(digit==4)
      {
          row=1;
          column=0;
      }
      if(digit==5)
      {
          row=1;
          column=1;
      }
      if(digit==6)
      {
          row=1;
          column=2;
      }
      if(digit==7)
      {
          row=2;
          column=0;
      }
      if(digit==8)
      {
          row=2;
          column=1;
      }
      if(digit==9)
      {
          row=2;
          column=2;
      }
      else if(digit<1 || digit>9)
      {
          cout<<"Invalid !!!"<<endl;
      }
      // state of the board
      if(token=='x' && space[row][column]!='x' && space[row][column]!='O')
      {
      space[row][column]='x';
      token='O';
      }
      else if(token=='O' && space[row][column]!='x' && space[row][column]!='O')
      {
      space[row][column]='O';
      token='x'; 
      }
      else
      {
          cout<<"there is no empty space"<<endl;
          f2();
      }
      
  }
   
   bool f3()// conditions for winning the game
   {
       for(int i=0;i<3;i++)
       { //vertically check
          if(space[i][0]==space[i][1] && space[i][0]==space[i][2] || space[0][i]==space[1][i] && space[0][i]==space[2][i]) 
          return true;
       }
       if(space[0][0]==space[1][1] && space[1][1]==space[2][2] || space[0][2]==space[1][1] && space[1][1]==space[2][0])// diagonally check
       {
           return true;
       }
       
       // if its  still going on
       for (int i=0;i<3;i++)
       {
           for(int j=0;j<3;j++)
           {
               if(space[i][j]!='x' && space[i][j]!='O')
               {
                   return false;
               }
           }
       }
       tie=true;
       return false;
   }

int main()
{
     
   cout<< "enter the name of 1st player:-\n";
   cin>>P1;
   cout<<"enter the name of 2nd player:-\n";
   cin>>P2;
   cout<<P1 <<" :player 1 will play first\n";
   cout<<P2 <<" :player 2 will play second \n\n";
     
   while(!f3())
   {
       f1();
       f2();
       f3();
   }
   
   if(token=='x' && tie==false)
   {
       cout<<P2<<" :wins :) !!!"<<endl;
       
   }
   else if(token=='O' && tie==false)
   {
       cout<<P1<<" :wins :) !!!"<<endl;
       
   }
   else
   {
       cout<<"Its a draw!!"<<endl;
   }

   char playAgain;
    cout << "Do you want to play again? (y/n): ";
    cin >> playAgain;
    if (playAgain == 'y') 
    {
        main();
    } else
    {
        cout << "Thanks for playing!\n";
    }
     
}
    
    
    
    