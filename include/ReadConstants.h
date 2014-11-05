#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <G4SystemOfUnits.hh> // this has appeared in GEANT4_10

#include <G4Material.hh> // need for G4double etc.


using namespace std;

class ReadConstants
{
public:
	ReadConstants(string file_name, G4double x_dimension, G4double y_dimension);
	void show();

	int get_array_size();
	G4double* get_x_array();
	G4double* get_y_array();

private:
	G4double *x_array;
	G4double *y_array;
	
	vector<double> x_vector;
	vector<double> y_vector;

	int array_size;

};