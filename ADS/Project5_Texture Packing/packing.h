#pragma once
#ifndef PACKING_H
#define PACKING_H
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <time.h>
#include <iomanip>
using namespace std;

struct Rect {
	int x;
	int y; //position of the left-bottom corner of the rectangle
	int width;
	int height;//size of the rectangle
};

class ShelfBinPack
{
public:
	ShelfBinPack() :binWidth(0), binHeight(0), currentY(0) {}

	//Clears all previously packed rectangles and starts packing from scratch into a bin of the given width
	ShelfBinPack(int width);

	//Different heuristic rules that can be used in the packing process
	enum ShelfChoiceHeuristic
	{
		ShelfNextFit, //NF: Always put the new rectangle to the last open shelf
		ShelfFirstFit, //FF: Always put the new rectangle to the first where it fits
		ShelfBestAreaFit, //BAF: Choose the shelf with smallest remaining shelf area
		ShelfWorstAreaFit, //WAF: Choose the shelf with the largest remaining shelf area
		ShelfBestHeightFit, //BHF: Choose the smallest shelf (height-wise) where the rectangle fits
		ShelfBestWidthFit, //BWF: Choose the shelf that has the least remaining horizontal shelf space available after packing
		ShelfWorstWidthFit, //WWF: Choose the shelf that will have most remainining horizontal shelf space available after packing
	};

	//Inserts a single rectangle into the bin. The packer might rotate the rectangle.
	//method: the heuristic rule to use for choosing a shelf if multiple ones are possible.
	Rect Insert(int width, int height, ShelfChoiceHeuristic method);

	//Get the height of the bin
	int GetHeight();

private:
	int binWidth;
	int binHeight;

	int currentY;//The starting y-coordinate of the latest (topmost) shelf

				 //A horizontal slab of space where rectangles may be placed
	struct Shelf
	{
		//The x-coordinate that specifies where the used shelf space ends
		//[0, currentX]:already used. [currentX, binWidth]:still available.
		int currentX;

		//The y-coordinate of where this shelf starts
		int startY;

		//The height of this shelf
		//The topmost shelf is "open" and its height may grow.
		int height;

		//All the rectangles in this shelf
		vector<Rect> usedRectangles;
	};

	vector<Shelf> shelves;

	//Returns true if the rectangle of size width * height fits on the given shelf, possibly rotated.
	bool FitsOnShelf(const Shelf &shelf, int width, int height) const;

	//If desirable, flips width and height so that the rectangle fits the given shelf the best.
	void RotateToShelf(const Shelf &shelf, int &width, int &height) const;

	//Adds the rectangle of size width * height into the given shelf, possibly rotated.
	void AddToShelf(Shelf &shelf, int width, int height, Rect &newNode);

	//Creates a new shelf of the given starting height, which will become the topmost 'open' shelf.
	void StartNewShelf(int startingHeight);
};

#endif // !PACKING_H