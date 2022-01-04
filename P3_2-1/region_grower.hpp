// define your class here
#ifndef _REGION_GROWER_HPP_
#define _REGION_GROWER_HPP_

#include <utility>
#include "Stack.hpp"
//#include "image.h"
#include "lib/image.h"

// a structure containing the x and y values
// for the pixel image was created to allow for easier configuration
struct ImagePos
{
	std::size_t x;
	std::size_t y;
};

class RegionGrower
{
private:

	// the png image from windows path
	Image<Pixel> imageOne;

	// the seed structure that contains an x, and y coordinate
	ImagePos seed;

	// the Pixel class object with rgb values
	Pixel replacementColor;

	// the Stack of the seed structure that will contain all the pixel seed values
	Stack<ImagePos> selectedPos;

public:
	/*
	* DESCRIPTION: Default constructor that sets the private data members to 0, or EMPTY.
	* Instantiates the variables to default valeues
	*/
	RegionGrower();

	/*
	* DESCRIPTION: Copy constructor that sets the private data members as the value of the rhs RegionGrower object
	* Instantiates the variables to the given objects' variables
	*/
	RegionGrower(const RegionGrower& rg);

	/*
	* DESCRIPTION: Destructor that erases the memory to prevent memory leaks and delete all the set values for the object
	* Destroys the variabkes using the clear() function
	*/
	~RegionGrower();


	/*
	* DESCRIPTION: Sets the image from the input path that is provided by the user. Utilizes try-catch algorithm
	* to cacth the runtime and other errors. Returns bool, takes the path as a parameter
	* @param input - the image input
	* @return true if image is set successfully, false otherwise
	*/
	bool SetImage(std::string input);

	/*
	* DESCRIPTION: Sets the seed value to the desired x and y coordinate values.
	* if x and y are out of bounds, return false.
	* @param x - the x coordinate
	* @param y - the y coordinate
	* @return true if seed is set successfully, false otherwise
	*/
	bool SetSeed(uint16_t x, uint16_t y); //width, height

	/*
	* DESCRIPTION: Sets the pixel replacement
	* @param p - the Pixel class' object
	* @return true if replacement is set successfully, false otherwise
	*/
	bool SetReplacement(const Pixel& p);

	/*
	* DESCRIPTION: Updates the stack by pushing the structure that was just colored. Utilizes struct and pushes the element to the stack
	* Returns void, takes no parameter
	*/
	void Update();

	/*
	* DESCRIPTION: gets the output from the file and returns bool value based on if the output is successfully returned or not
	* uses try catch implementation
	* @param output - the output from the terminal
	* @return true if output is found successfully, false otherwise
	*/
	bool GetOutput(std::string output);
};

#endif
