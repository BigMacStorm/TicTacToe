#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "stdlib.h"

using namespace std;

//global data
char sent[9];
int xMem[19682][9];
int oMem[19682][9];

int xMoves[5][2];
int oMoves[4][2];

int xCount = 0;
int oCount = 0;

//function prototypes
//as I was using this as a learning I did use more globals than I should have probably
void print();
void fill();
bool cats();
char won();
void move(bool);
bool valid(int);
int config();
void load();
void save();
void comMove(bool);
int roulette(bool);
void xEnd(bool);
void oEnd(bool);


int main()
{
   bool turn = false;
   bool playerOne, playerTwo = false;
   bool running = true;
   fill();
   load();
   char temp;
   int players = 0;
   int key;
   int runs = 10000;
   int exes, ohs, catsC = 0;
   cout << "How many players are there: ";
   cin >> temp;
   players = temp-48;
   srand (time(NULL));
   
   if(players == 2)
   {
      playerOne = true;
      playerTwo = true;
   }
   else if(players == 1)
   {
      playerOne = true;
   }
   
   //this is if you want to play against someone else
   //takes in commands, checks if done, pretty straight forward.
   //computer does not learn from this.
   while(running && players == 2)
   {      
      print();
      move(turn);
      turn = !turn;
      if(won() == 'X')
      {
         print();
         cout << endl << "Player X Wins!" << endl << endl; 
         fill(); 
         turn = false;   
         cout << endl << endl << "What would you like to do now? (any key = again, q = quit): ";
         cin >> temp;
      }
      
      if(won() == 'O')
      {
         print();
         cout << endl << "Player O Wins!" << endl << endl; 
         fill(); 
         turn = false;   
         cout << endl << endl << "What would you like to do now? (any key = again, q = quit): ";
         cin >> temp;
      }
      
      if(cats())
      {
         print();
         cout << endl << "Cats Game!" << endl << endl; 
         fill();   
         cout << endl << endl << "What would you like to do now? (any key = again, q = quit): ";
         cin >> temp;
      }
      
      if(temp == 'q') running = false;
   }
   //this is if you would like to play against the current memory of the computer
   //uses the same letter for computer always here.
   //same basic idea as above, takes command and checks if someone has won.
   while(running && players == 1)
   {      
      print();
      if(turn == false) move(turn);
      if(turn == true) {comMove(turn);oCount++;}
      turn = !turn;
      if(won() == 'X')
      {
         print();
         cout << endl << "Player X Wins!" << endl << endl; 
         oEnd(false);
         fill(); 
         turn = false;   
         cout << endl << endl << "What would you like to do now? (any key = again, q = quit): ";
         cin >> temp;
      }
      
      if(won() == 'O')
      {
         print();
         cout << endl << "Player O (Computer) Wins!" << endl << endl; 
         oEnd(true);  
         fill(); 
         turn = false; 
         cout << endl << endl << "What would you like to do now? (any key = again, q = quit): ";
         cin >> temp;
      }
      
      if(cats())
      {
         print();
         cout << endl << "Cats Game!" << endl << endl; 
         oEnd(true); 
         fill();   
         turn = false;
         cout << endl << endl << "What would you like to do now? (any key = again, q = quit): ";
         cin >> temp;
      }
      
      if(temp == 'q') running = false;
   }
    
   //finally the meat of the project, this is while loop handles a 0 player game.
   //the computer plays both players and uses markov decision paths to weight optimal moves based on previous inputs.
   while(running && players == 0)
   {
      //makes the turn of whoever is currently up.
      if(turn == false) {comMove(turn);xCount++;}
      if(turn == true) {comMove(turn);oCount++;}
      //the boolean value of turn decides whos turn it is.
      turn = !turn;
      if(won() == 'X')
      {
         oEnd(false); 
         xEnd(true); 
         fill(); 
         turn = false;   
         exes++;
         runs--;
      }
      
      if(won() == 'O')
      {
         oEnd(true); 
         xEnd(false); 
         fill(); 
         turn = false;   
         ohs++;
         runs--;
      }
      
      if(cats())
      {
         oEnd(true); 
         xEnd(true); 
         turn = false;
         fill();   
         catsC++;
         runs--;
      }
      
      //statistical summmary of what has been ran, if you say run it for 1000 games, every 1000 games the amount of cats should rise as it learns more possible options and rare deviations.
      if(runs == 0)
      {
         running = false;
         cout << "Exes: " << exes << " Ohs: " << ohs << " cats: " << catsC << endl;
         cout << endl << endl << "What would you like to do now? (any key = again, q = quit): ";
         cin >> temp;
         if(temp == 'q')
         {
            running = false;
         }
         else
         {
            exes = 0;
            ohs = 0;
            catsC = 0;
            runs = 10000;
            running = true;
         }
      }
   }
   
   //outputs the memory to the data files
   save();
   
   return 0;
}

//this is a simple program to check wether the game is a cats game.
bool cats()
{
   bool result = true;
   for(int x = 0; x<9; x++)
   {
      if(sent[x] == ' ') result = false;
   }
   return result;
   
}

//pretty hacky check to see if someone has won the current board of tic tac toe.
//not pretty but fairly quick and simple.
//was not the point of the project so spent about 0 seconds planning it.
char won()
{
   if(sent[0] == sent[1] && sent[1] == sent[2])
      if(sent[0] != ' ') 
         return sent[0];
   if(sent[3] == sent[4] && sent[4] == sent[5])
      if(sent[3] != ' ') 
         return sent[3];
   if(sent[6] == sent[7] && sent[7] == sent[8])
      if(sent[6] != ' ') 
         return sent[6];
         
         
   if(sent[0] == sent[3] && sent[3] == sent[6])
      if(sent[0] != ' ') 
         return sent[0];
   if(sent[1] == sent[4] && sent[4] == sent[7])
      if(sent[1] != ' ') 
         return sent[1];
   if(sent[2] == sent[5] && sent[5] == sent[8])
      if(sent[2] != ' ') 
         return sent[2];
         
         
  
   if(sent[0] == sent[4] && sent[4] == sent[8])
      if(sent[0] != ' ') 
         return sent[0];
   if(sent[2] == sent[4] && sent[4] == sent[6])
      if(sent[2] != ' ') 
         return sent[2];
         
   return 'Z';
}

//simple print function used for both actual players to play instead of just computers and
//also useful for verbose output in order to see what the program is doing to test.
void print()
{
   cout << endl << endl << endl << endl << endl << endl;
   cout << "   The current table is as follows" << endl << endl;
   cout << "          1   2   3" << endl;
   cout << "       +0 " << sent[0] << " | " << sent[1] << " | " << sent[2] << endl;
   cout << "          ----------" << endl;
   cout << "       +3 " << sent[3] << " | " << sent[4] << " | " << sent[5] << endl;
   cout << "          ----------" << endl;
   cout << "       +6 " << sent[6] << " | " << sent[7] << " | " << sent[8] << endl << endl;
   cout << "   Table Configuration: " << config();
   cout << endl << endl << endl << endl << endl << endl;
}

//single loop that cleans the board at the start of each game.
void fill()
{
   for(int x = 0; x<9; x++)
   {
      sent[x] = ' ';
   }
   oCount = 0;
   xCount = 0;
}

//figures out whos move it is and lets the player make a move
void move(bool player)
{
   char temp;
   int x;
   bool run = true;
   
   while(run)
   {
      cout << "Enter your move: ";
      cin >> temp;
      x = temp-48;
      
      //uses a secondary function for error checking to make sure spot isnt taken already or out of bounds
      if(!valid(x-1)) cout << "Sorry, spot is taken, try again..." << endl << endl;
      else run = !run;
   }
   
   if(player == false) sent[x-1] = 'X';
   if(player == true) sent[x-1] = 'O';
   
}

//checks the spot is either empty or out of bounds.
bool valid(int x)
{
   if(!(x >= 0 && x <=8)) return false;
   if(sent[x] == ' ') return true;
   return false;
}

//turns the board in a numerical value that can be accessed in the programs memory
int config()
{
   int sum = 0;
   int temp = 0;
   for(int x=0; x<9; x++)
   {
      if(sent[x]==' ') temp = 0;
      if(sent[x]=='X') temp = 1;
      if(sent[x]=='O') temp = 2;
      sum += (temp*pow(3, x));
   }
   return sum;   
}

//loads the player data in from the text file that they are stored in.
void load()
{
   ifstream fin;
   int tempI;
   char tempC;
   fin.open("Xdata");
   
   for(int x=0; x<19682; x++)
   {
      fin >> tempI;
      fin >> tempC;
      for(int y=0; y<9; y++)
      {
         fin >> tempI;
         xMem[x][y] = tempI;
         fin >> tempC;
      }
   }
   
   fin.close();
   fin.open("Odata");
   
   for(int x=0; x<19682; x++)
   {
      fin >> tempI;
      fin >> tempC;
      for(int y=0; y<9; y++)
      {
         fin >> tempI;
         oMem[x][y] = tempI;
         fin >> tempC;
      }
   }  
   
   fin.close(); 
   
}

//staves the player data out to text files.
void save()
{
   system("rm Xdata");
   system("rm Odata");   
      
   ofstream fout;
   fout.open("Xdata");
   
   for(int x = 0; x<19682; x++)
   {
      fout << x << ';';
      for(int y = 0; y<9; y++)
      {
         fout << xMem[x][y] << ';';
      }
      fout << endl;
   }
   
   fout.close();
   
   
   fout.open("Odata");
   
   for(int x = 0; x<19682; x++)
   {
      fout << x << ';';
      for(int y = 0; y<9; y++)
      {
         fout << oMem[x][y] << ';';
      }
      fout << endl;
   }
   
   fout.close();
}

//makes the move for the computer by numerating the current board position and then
//checking the players memory for that board position, and then runs a roulette program
//on that current board position in its memory, making sure that the options that win more
//are chosen more.

void comMove(bool player)
{
   char temp;
   int x;
   bool run = true;
     
   x = roulette(player);  
   
   if(!player)
   {
      //store the made moves in arrays for each player to modify win rate stats later.
      xMoves[xCount][0] = config();
      xMoves[xCount][1] = x-1;
      
   }
   
   if(player)
   {
      oMoves[oCount][0] = config();
      oMoves[oCount][1] = x-1;
   }
      
   if(player == false) sent[x-1] = 'X';
   if(player == true) sent[x-1] = 'O';
}

//adds up the odds of every possible move and sets the data good.
int roulette(bool passed)
{
   int x = 0;
   int y = 0;
   char temp;
   bool checkVal = true;
   char dummy;
   vector<int> wheel(9,0);
   while(checkVal)
   {   
     //empty the vector
     for(int q=0; q<9; q++)
     {
        wheel[q] = 0;
     }
      if(!passed)
      {
         wheel[x] = xMem[config()][1];
         for(int x=1; x<9; x++)
         {
            wheel[x] = wheel[x-1] + xMem[config()][x];
         }
      }
      
      if(passed)
      {
         //add up all of the possible options in a roulette wheel style
         wheel[x] = oMem[config()][1];
         for(int x=1; x<9; x++)
         {
            wheel[x] = wheel[x-1] + oMem[config()][x];
         }
      }
           
     //if every option is bad just randomly choose something.
     if(wheel[8] == 0){x = rand() % 9 + 1;}
     //else, roll the wheel and use the one that you land on.
     else
     {
        y = rand() % wheel[8];
        for(int z=8; z>=0; z--)
        {
            if(y<wheel[z]) x=z+1;
        }
     }
      if(valid(x-1)) checkVal = false;
      else
      {
         if(!passed)
         {
            xMem[config()][x-1] = 0;
         }
         else if(passed)
         {
            oMem[config()][x-1] = 0;
         }
      }
   }
   
   return x;
}

//modify the memory based on how the outcome of the game went
void xEnd(bool outcome)
{
   char temp;
   if(outcome)
   {
      for(int z = 0; z<xCount && z<5; z++)
      {
         xMem[xMoves[z][0]][xMoves[z][1]] += 1;
         if(xMem[xMoves[z][0]][xMoves[z][1]] == -1) xMem[xMoves[z][0]][xMoves[z][1]] += 1;
      }
   }
   
   if(!outcome)
   {
      for(int z = 0; z<xCount && z<5; z++)
      {
         xMem[xMoves[z][0]][xMoves[z][1]] -= 1;
         if(xMem[xMoves[z][0]][xMoves[z][1]] == -1) xMem[xMoves[z][0]][xMoves[z][1]] += 1;
      }
   }
}

//modify the o memory based on how the game ended.
void oEnd(bool outcome)
{
   if(outcome)
   {
      for(int z = 0; z<oCount && z<4; z++)
      {
         oMem[oMoves[z][0]][oMoves[z][1]] += 1;
         if(oMem[oMoves[z][0]][oMoves[z][1]] == -1) oMem[oMoves[z][0]][oMoves[z][1]] += 1;
      }
   }
   
   if(!outcome)
   {
      for(int z = 0; z<oCount && z<4; z++)
      {
         oMem[oMoves[z][0]][oMoves[z][1]] -= 1;
        if(oMem[oMoves[z][0]][oMoves[z][1]] == -1) oMem[oMoves[z][0]][oMoves[z][1]] += 1;
      }
   }
}










