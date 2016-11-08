#include <string.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fstream>

using namespace std;


int main( int argc, char *argv[])  {
  FILE * fp;
  unsigned int width=0;
  unsigned int height=0;
 
  //Abrimos el fichero:
  fp=fopen (argv[4],"r"); //argv[4] is the parameter where the image is
    fseek(fp, 0, SEEK_END);
    //unsigned int size=ftell(fp);   
    
    rewind(fp);
    size_t return1 = fread(&altura,4,1,fp);
    size_t return2 = fread(&anchura,4,1,fp);
  //Matrix creation:
   if (return1 > 0 && return2 > 0) {
   	 unsigned int matrixRed[width][height];
   	 unsigned int matrixGreen[width][height];
  	 unsigned int matrixBlue[width][height];
  	 unsigned int matrixGrey[width][height];
   
   unsigned int intr=0;
   double redCoef = 0.3;
   double greenCoef = 0.59;
   double blueCoef = 0.11;


   for(unsigned int i=0;i<width;i++) {
    	for(unsigned int j=0;j<height;j++) {
        	size_t return5 = fread(&intr,1,1,fp);
    		if (return5 > 0) {
				matrixRed[i][j]=intr;
			}
     	}
    }

    for(unsigned int i=0;i<width;i++) {
    	for(unsigned int j=0;j<height;j++) {
    		size_t return3 = fread(&intr,1,1,fp);
    		if (return3 > 0) {
				matrixGreen[i][j]=intr;
			}
    	}
    }
 
    for(unsigned int i=0;i < width;i++) {
    	for(unsigned int j=0;j < height;j++) {
    		size_t return4 = fread(&intr,1,1,fp);
    		if (return4 > 0) {
				matrixBlue[i][j]=intr;
			}
		}    
    }

    //fclose(fp);
    for (unsigned int i = 0; i < width; ++i) {
     	for (unsigned int j = 0; j < height; ++j) {
     		matrixGrey[i][j] = matrizRed[i][j]*redCoef + matrixBlue[i][j]*blueCoef + matrixGreen[i][j]*greenCoef; //Convert the image to greyscale
        	//cout << matrixGrey[i][j] << " "; 	
     	}
    }

    if (strcmp(argv[1], "-u") == 0 && *argv[2] == '0' && strcmp(argv[3], "-i") == 0 && strcmp(argv[5], "-o") == 0 && strcmp(argv[7], "-t") == 0) {
    	unsigned int sections = atoi(argv[8]);
    	unsigned int histogram[sections];
    	for (unsigned int i = 0; i < sections; ++i)
    	{
    		histogram[i] = 0;
    	}
    	unsigned int k = 0;
    	float limits[sections];
    	float value = (float)255/sections;
      
    	if (sections > 0) {
        //cout << "The number of sections " << sections << "\n";
        //cout << "Each section " << value << "\n";

        //cout << "Limits array is: " << "\n";  
       	for (unsigned int i = 0; i < sections; ++i) {
       		limits[i] = value*i; //Limits are created 
       		//cout << limits[i] << " ";
       	}

        for (unsigned int i = 0; i < width; ++i) {
      		for (unsigned int j = 0; j < height; ++j) {
      			unsigned int px = matrixGrey[i][j];
				k = 0;
				while (k < sections) {
					if (sections == 1){
						histogram[k] = width*height; //If there is only one section the result will be the total number of pixels
						break;
					}

					if (px >= limits[k] && px <= limits[k+1]) {
						histogram[k]++; //If there 
						break;
					}
					else {
						k++; //If there isn't, next range
					}
				}
           	}
        }

		ofstream myFile (argv[6]); //Offset file creation with the parameter introduced
		
		if (myFile.is_open()) { //If the offset file has been created right.
			//cout << "The histogram has been generated in the file " << argv[6] << "\n";
       		for (unsigned int i = 0; i < sections; ++i) {
       			myFile << histogram[i] << " "; //The txt file is filled with the results(histogram)
       		}
        	myFile.close(); //Close the offset file
     	}

      	else {
       		//cout << "The parameters format are incorrect\n";
      	}     
    }
}
 
}
}
