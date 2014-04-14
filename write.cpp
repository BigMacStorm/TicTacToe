#include <iostream>
#include <fstream>

using namespace std;

int main()
{
   ofstream fout;
   fout.open("Xdata");
   
   for(int x = 0; x<19682; x++)
   {
      fout << x << ';';
      for(int y = 0; y<9; y++)
      {
         fout << 30 << ';';
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
         fout << 30 << ';';
      }
      fout << endl;
   }
   
   fout.close();
   
   
   return 0;
}
