#include "Singleton.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Singleton::Singleton()
{
	summ_number_of_photons = 0;

	
}

Singleton* Singleton::get() 
{

	if(Singleton::single==NULL)
	{
		single = new Singleton();
	}

	return single;

}
