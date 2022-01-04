#include <string>

#include "catch.hpp"
#include "image.h"

#include "region_grower.hpp"

const std::string SEP =
#if defined(_WIN32)
"\\";
#else
"/";
#endif

bool compareImages(std::string image1, std::string image2)
{
	Image<Pixel> input1 = readFromFile(image1);
	Image<Pixel> input2 = readFromFile(image2);

	// check size are the same
	if ((input1.width() != input2.width()) ||
		(input1.height() != input2.height()))
	{
		return false;
	}

	// compare each pixel, stop on first difference
	bool ok = true;
	for (intmax_t i = 0; i < input1.width(); ++i)
		for (intmax_t j = 0; j < input1.height(); ++j) {
			if (input1(i, j) != input2(i, j)) {
				ok = false;
				break;
			}
		}

	if (!ok)
	{
		return false;
	}

	return true;
}

TEST_CASE("Image compare", "[region_grower]") {
	// REQUIRE(compareImages("P3_2-1" + SEP + "test" + SEP + "hokie.png", "P3_2-1" + SEP + "test" + SEP + "hokie.png"));
	REQUIRE(compareImages("test" + SEP + "hokie.png", "test" + SEP + "hokie.png"));
}

//test case for setimage() function
TEST_CASE("SetImage & SetSeed") {
	RegionGrower rg;
	
	REQUIRE(rg.SetImage("test" + SEP + "hokie.png"));
	REQUIRE_FALSE(rg.SetImage("test" + SEP + "idkwhatimdoing.png"));

	REQUIRE(rg.SetImage("test" + SEP + "hokie.png"));

	REQUIRE(rg.SetSeed(69, 420));
	REQUIRE_FALSE(rg.SetSeed(10000, 10000));
	REQUIRE(rg.SetSeed(1, 1));
	REQUIRE(rg.SetSeed(100, 100));
	REQUIRE_FALSE(rg.SetSeed(9999999, 9999999));
}

// testing for coloring head, chest, background
TEST_CASE("Background") {
	RegionGrower rg;

	rg.SetImage(std::string("test" + SEP + "hokie.png"));
	rg.SetReplacement({ 232, 117, 17, 255 });
	rg.SetSeed(0, 0);
	rg.Update();
	rg.GetOutput(std::string("test" + SEP + "hokie_back_ground_aadi.png"));
}

// testing for coloring chest, background
TEST_CASE("Chest")
{
	RegionGrower rg;

	rg.SetImage("test" + SEP + "hokie_back_ground_aadi.png");
	rg.SetReplacement(Pixel{ 142, 35, 68, 255 });
	rg.SetSeed(350, 350);
	rg.Update();
	rg.GetOutput("test" + SEP + "hokie_chest_aadi.png");
	REQUIRE(compareImages("test" + SEP + "hokie_chest.png", "test" + SEP + "hokie_chest_aadi.png"));
}

// testing for coloring chest, leg, background
TEST_CASE("Legs")
{
	RegionGrower rg;

	rg.SetImage("test" + SEP + "hokie_chest_aadi.png");
	rg.SetReplacement(Pixel{ 142, 35, 68, 255 });
	rg.SetSeed(350, 450);
	rg.Update();
	rg.GetOutput("test" + SEP + "hokie_legs_aadi.png");
	REQUIRE(compareImages("test" + SEP + "hokie_legs.png", "test" + SEP + "hokie_legs_aadi.png"));
}

// testing for coloring head, chest, leg, background
TEST_CASE("Head")
{
	RegionGrower fillclr;

	fillclr.SetImage("test" + SEP + "hokie_legs_aadi.png");
	fillclr.SetReplacement(Pixel{ 142, 35, 68, 255 });
	fillclr.SetSeed(125, 315);
	fillclr.Update();
	fillclr.GetOutput("test" + SEP + "hokie_head_aadi.png");
	REQUIRE(compareImages("test" + SEP + "hokie_cool.png", "test" + SEP + "hokie_head_aadi.png"));
}