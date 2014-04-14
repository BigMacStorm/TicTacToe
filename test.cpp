#include <iostream>
#include <cmath>
#include <fstream>
#include "stdlib.h"

using namespace std;

char sent[9];
int xMem[19682][9];
int oMem[19682][9];

int xMoves[5][2];
int oMoves[4][2];

int xCount = 0;
int oCount = 0;

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
    
   while(running && players == 0)
   {      
      //print();
      if(turn == false) {comMove(turn);xCount++;}
      if(turn == true) {comMove(turn);oCount++;}
      turn = !turn;
      if(won() == 'X')
      {
         //print();
         //cout << endl << "Player X (computer)Wins!" << endl << endl; 
         oEnd(false); 
         xEnd(true); 
         fill(); 
         turn = false;   
         exes++;
         runs--;
      }
      
      if(won() == 'O')
      {
         //print();
         //cout << endl << "Player O (Computer) Wins!" << endl << endl; 
         oEnd(true); 
         xEnd(false); 
         fill(); 
         turn = false;   
         ohs++;
         runs--;
      }
      
      if(cats())
      {
         //print();
        // cout << endl << "Cats Game!" << endl << endl; 
         oEnd(true); 
         xEnd(true); 
         turn = false;
         fill();   
         catsC++;
         runs--;
      }
      
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
   
   save();
   
   return 0;
}

bool cats()
{
   bool result = true;
   for(int x = 0; x<9; x++)
   {
      if(sent[x] == ' ') result = false;
   }
   return result;
   
}
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
void fill()
{
   for(int x = 0; x<9; x++)
   {
      sent[x] = ' ';
   }
   oCount = 0;
   xCount = 0;
}

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
      
      if(!valid(x-1)) cout << "Sorry, spot is taken, try again..." << endl << endl;
      else run = !run;
   }
   
   if(player == false) sent[x-1] = 'X';
   if(player == true) sent[x-1] = 'O';
   
}

bool valid(int x)
{
   if(!(x >= 0 && x <=8)) return false;
   if(sent[x] == ' ') return true;
   return false;
}

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

void comMove(bool player)
{
   char temp;
   int x;
   bool run = true;
     
   x = roulette(player);   
   
   if(!player)
   {
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

int roulette(bool passed)
{
   int x = 0;
   int y = 0;
   char temp;
   bool checkVal = true;
   int one = 0, two = 0, three = 0, four = 0, five = 0, six = 0, seven = 0, eight = 0, nine= 0;
   while(checkVal)
   {
      if(!passed)
      {
   one = 0; two = 0; three = 0; four = 0; five = 0; six = 0; seven = 0; eight = 0; nine= 0;
         one = xMem[config()][0];
         two = one + xMem[config()][1];
         three = two + xMem[config()][2];
         four = three + xMem[config()][3];
         five = four + xMem[config()][4];
         six = five + xMem[config()][5];
         seven = six + xMem[config()][6];
         eight = seven + xMem[config()][7];
         nine = eight + xMem[config()][8];
         
         if(nine == 0){x = rand() % 9 + 1;}
         else
         {
            y = rand() % nine;
            if(y < one) x = 1;
            else if(y < two) x = 2;
            else if(y < three) x = 3;
            else if(y < four) x = 4;
            else if(y < five) x = 5;
            else if(y < six) x = 6;
            else if(y < seven) x = 7;
            else if(y < eight) x = 8;
            else if(y < nine) x = 9;
         }
      }
      
      if(passed)
      {
   one = 0; two = 0; three = 0; four = 0; five = 0; six = 0; seven = 0; eight = 0; nine= 0;
         one = oMem[config()][0];
         two = one + oMem[config()][1];
         three = two + oMem[config()][2];
         four = three + oMem[config()][3];
         five = four + oMem[config()][4];
         six = five + oMem[config()][5];
         seven = six + oMem[config()][6];
         eight = seven + oMem[config()][7];
         nine = eight + oMem[config()][8];
         
         if(nine == 0){x = rand() % 9 + 1;}
         else
         {
            y = rand() % nine;
            if(y < one) x = 1;
            else if(y < two) x = 2;
            else if(y < three) x = 3;
            else if(y < four) x = 4;
            else if(y < five) x = 5;
            else if(y < six) x = 6;
            else if(y < seven) x = 7;
            else if(y < eight) x = 8;
            else if(y < nine) x = 9;
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










