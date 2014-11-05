#include "ReadConstants.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

ReadConstants::ReadConstants(string file_name, G4double x_dimension, G4double y_dimension)
{
	ifstream myfile (file_name);
	if (myfile.is_open())
	{
		double value;
		string line;

		while (getline(myfile, line) )
		{
			if(line != "")
			{
				istringstream iss(line);
				iss >> value;
				x_vector.push_back(value);
				iss >> value;
				y_vector.push_back(value);
			}
		}

		myfile.close();
	}
	else 
	{  
		cout << "Unable to open file"; 
	}


	array_size = x_vector.size(); //weak point

	x_array = new G4double[array_size];
	y_array = new G4double[array_size];

	for (int i = 0; i < array_size; i++)
	{
		x_array[i] = x_vector[i] * x_dimension;
		y_array[i] = y_vector[i] * y_dimension;
	} 

}

void ReadConstants::show()
{
	G4cout << "x_vector \t y_vector"  << endl;
	for (int i = 0; i < array_size; i++)
	{
		G4cout << x_array[i] << "\t" << y_array[i] << endl;
	}
}

int ReadConstants::get_array_size()
{
	return array_size;
}

G4double* ReadConstants::get_x_array()
{
	return x_array;
}

G4double* ReadConstants::get_y_array()
{
	return y_array;
}