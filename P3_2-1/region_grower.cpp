// implement your class here
// sigh, :(

#include "Stack.hpp"
#include "region_grower.hpp"
#include <iostream>
//#include <image.h>

/*
* DESCRIPTION: Default constructor that sets the private data members to 0, or EMPTY.
* Instantiates the variables to default valeues
*/
RegionGrower::RegionGrower()
{
	// all variables are set to default value
	seed = ImagePos{ 0, 0 };
	imageOne = Image<Pixel>();
	replacementColor = BLACK;
	selectedPos = Stack<ImagePos>();
}

/*
* DESCRIPTION: Copy constructor that sets the private data members as the value of the rhs RegionGrower object
* Instantiates the variables to the given objects' variables
*/
RegionGrower::RegionGrower(const RegionGrower& rg)
{
	// all variables are set to the rhs value of the other RegionGrower object
	this->seed = rg.seed;
	this->imageOne = rg.imageOne;
	this->replacementColor = rg.replacementColor;
	this->selectedPos = rg.selectedPos;
}

/*
 * DESCRIPTION: Destructor that erases the memory to prevent memory leaks and delete all the set values for the object
 * Destroys the variabkes using the clear() function
 */
RegionGrower::~RegionGrower()
{
	// use the clear function to clear the stack
	selectedPos.clear();
}

/*
* DESCRIPTION: Sets the image from the input path that is provided by the user. Utilizes try-catch algorithm
* to cacth the runtime and other errors. Returns bool, takes the path as a parameter
* @param input - the image input
* @return true if image is set successfully, false otherwise
*/
bool RegionGrower::SetImage(std::string input) {
	// try the piece of code
	try {
		imageOne = readFromFile(input); // read input from file
	}

	// if runtime error is caught
	catch (std::runtime_error) {
		// return false
		return false;
	}

	// if any other error is caught
	catch (...) {
		// return false
		return false;
	}

	// if no errors are caught
	return true;
}

/*
* DESCRIPTION: Sets the seed value to the desired x and y coordinate values.
* if x and y are out of bounds, return false.
* @param x - the x coordinate
* @param y - the y coordinate
* @return true if seed is set successfully, false otherwise
*/
bool RegionGrower::SetSeed(uint16_t x, uint16_t y) {
	bool decision;
	// if pixel coordinate is greater than the image pixel value, then out of bounds
	if ((x > imageOne.width()) || (y > imageOne.height())) {
		decision = false;
		return decision;
	}

	// otherwise, set.
	this->seed = ImagePos{ x, y };
	decision = true;
	return decision;
}


/*
* DESCRIPTION: Sets the pixel replacement
* @param p - the Pixel class' object
* @return true if replacement is set successfully, false otherwise
*/
bool RegionGrower::SetReplacement(const Pixel& p) {
	// try this statement
	try {
		//set the replacement color to be the value of p
		replacementColor = p;
	}
	// if runtime error is caught
	catch (std::runtime_error) {
		return false;
	}
	// if any other error is caught
	catch (...) {
		return false;
	}

	// if statement works and errors arent caught, return false
	return true;
}

/*
* DESCRIPTION: Updates the stack by pushing the structure that was just colored. Utilizes struct and pushes the element to the stack
* Returns void, takes no parameter
*/
void RegionGrower::Update() {
	// push the main seed pixel on the stack
	selectedPos.push(seed);

	// while stack is not empty
	while (!selectedPos.isEmpty()) {
		ImagePos curr = selectedPos.peekPop();

		int width_h = imageOne.width() - 1;
		int height_h = imageOne.height() - 1;

		// if it is above
		if ((curr.y > 0)
			&& (imageOne(curr.x, curr.y - 1) != replacementColor)
			&& (imageOne(curr.x, curr.y - 1) == imageOne(curr.x, curr.y))) {
			//std::cout << "Pushed something\n";
			selectedPos.push(ImagePos{ curr.x, curr.y - 1 });
		}

		// if it is below
		if ((curr.y < (height_h))
			&& (imageOne(curr.x, curr.y + 1) != replacementColor)
			&& (imageOne(curr.x, curr.y + 1) == imageOne(curr.x, curr.y))) {
			//std::cout << "Pushed something\n";
			selectedPos.push(ImagePos{ curr.x, curr.y + 1 });
		}

		// if it is on the left
		if ((curr.x > 0)
			&& (imageOne(curr.x - 1, curr.y) != replacementColor) &&
			(imageOne(curr.x - 1, curr.y) == imageOne(curr.x, curr.y))) {
			//std::cout << "Pushed something\n";
			selectedPos.push(ImagePos{ curr.x - 1, curr.y });
		}

		// if it is on the right
		if ((curr.x < (width_h))
			&& (imageOne(curr.x + 1, curr.y) != replacementColor)
			&& (imageOne(curr.x + 1, curr.y) == imageOne(curr.x, curr.y))) {
			selectedPos.push(ImagePos{ curr.x + 1, curr.y });
		}

		// set the color of the image pixel to the desired color
		imageOne(curr.x, curr.y) = replacementColor;
	}
}


/*
* DESCRIPTION: gets the output from the file and returns bool value based on if the output is successfully returned or not
* uses try catch implementation
* @param output - the output from the terminal
* @return true if output is found successfully, false otherwise
*/
bool RegionGrower::GetOutput(std::string output) {
	// try this statement
	try {
		writeToFile(imageOne, output);
	}

	// catch the runtime error here
	catch (std::runtime_error) {
		return false;
	}

	// catch all the other errors here
	catch (...) {
		return false;
	}

	// if no errors are caught, return true
	return true;
}
