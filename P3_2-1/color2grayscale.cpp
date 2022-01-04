/*
  This code shows you an example of how to use the Image library.
  It is not part of the assignment.
*/

#include <iostream>
#include <math.h>
using std::cout; using std::endl;

#include "image.h"

int main( int argc, char* argv[] )
{
  if( argc != 3 ){
    cout << "Usage: color2grayscale"
	 << "<input_filename> <output_filename>"
	 << endl << endl;
    return 1;
  }

  // declare and read the bitmap
  Image<Pixel> Input;
  Input = readFromFile(argv[1]);

  // convert each pixel to grayscale using RGB->YUV
  for( int j=0 ; j < Input.height() ; j++)
    {
      for( int i=0 ; i < Input.width() ; i++)
	{
	  int Temp = (int) floor( 0.299*Input(i,j).red +
				  0.587*Input(i,j).green +
				  0.114*Input(i,j).blue );
	  uint8_t TempBYTE = (uint8_t) Temp;
	  Input(i,j).red = TempBYTE;
	  Input(i,j).green = TempBYTE;
	  Input(i,j).blue = TempBYTE;
	}
    }

  // write the output file
  writeToFile(Input,argv[2]); 

  return 0;
}

