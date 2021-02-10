#include "stdafx.h"
#include "packing.h"

using namespace std;

ShelfBinPack::ShelfBinPack(int width)
{
	//Create a bin of given width
	binWidth = width;
	binHeight = 0;
	currentY = 0;
	shelves.clear();
	StartNewShelf(0);
}

void ShelfBinPack::StartNewShelf(int startingHeight)
{
	//Create a new shelf of startingheight.
	Shelf shelf;
	shelf.currentX = 0;
	shelf.height = startingHeight;
	shelf.startY = currentY;
	
	shelves.push_back(shelf); //store the shelf
	binHeight += shelf.height; //update the binHeight
}

bool ShelfBinPack::FitsOnShelf(const Shelf &shelf, int width, int height) const
{
	if ((shelf.currentX + width <= binWidth) || (shelf.currentX + height <= binWidth))
		return true; //The rectangle can fit on the given shelf, possibly rotated.(consider the width)
	else
		return false; //cannot fit on the shelf
}

void ShelfBinPack::RotateToShelf(const Shelf &shelf, int &width, int &height) const
{
	//If the width > height and the long edge of the new rectangle fits vertically onto the current shelf,flip it. 
	//If the short edge is larger than the current shelf height, store the short edge vertically.
	if ((width > height && width > binWidth - shelf.currentX) ||
		(width > height && width < shelf.height) ||
		(width < height && height > shelf.height && height <= binWidth - shelf.currentX))
		swap(width, height);
}

void ShelfBinPack::AddToShelf(Shelf &shelf, int width, int height, Rect &newNode)
{
	assert(FitsOnShelf(shelf, width, height));//if cannot fit on the shelf,error!

	//Swap width and height if the rectangle can fit better that way
	RotateToShelf(shelf, width, height);

	//Add the rectangle to the shelf
	newNode.x = shelf.currentX;
	newNode.y = shelf.startY; //position of the new rectangle
	newNode.width = width;
	newNode.height = height; //size of the new rectangle
	shelf.usedRectangles.push_back(newNode);

	//Advance the shelf end position horizontally
	shelf.currentX += width;
	assert(shelf.currentX <= binWidth);

	//Grow the shelf height
	binHeight -= shelf.height;
	shelf.height = max(shelf.height, height);
	binHeight += shelf.height;
	assert(shelf.height <= binHeight);
}

Rect ShelfBinPack::Insert(int width, int height, ShelfChoiceHeuristic method)
{
	Rect newNode;

	switch (method)
	{
	case ShelfNextFit:
		//Always put the new rectangle to the last open shelf
		if (FitsOnShelf(shelves.back(), width, height))
		{
			AddToShelf(shelves.back(), width, height, newNode);
			return newNode;
		}
		break;

	case ShelfFirstFit:
		//Always put the new rectangle to the first where it fits
		for (size_t i = 0; i < shelves.size(); ++i)
			if (FitsOnShelf(shelves[i], width, height))
			{
				AddToShelf(shelves[i], width, height, newNode);
				return newNode;
			}
		break;

	case ShelfBestAreaFit:
	{
		//Choose the shelf with smallest remaining shelf area.
		Shelf *bestShelf = 0;
		unsigned long bestShelfSurfaceArea = (unsigned long)-1;
		for (size_t i = 0; i < shelves.size(); ++i)
		{
			//Pre-rotate the rect onto the shelf here already
			RotateToShelf(shelves[i], width, height);
			if (FitsOnShelf(shelves[i], width, height))
			{
				unsigned long surfaceArea = (binWidth - shelves[i].currentX) * shelves[i].height;
				if (surfaceArea < bestShelfSurfaceArea)
				{
					bestShelf = &shelves[i];
					bestShelfSurfaceArea = surfaceArea;
				}
			}//find the shelf with smallest remaining shelf area
		}
		if (bestShelf)
		{
			AddToShelf(*bestShelf, width, height, newNode);
			return newNode;
		}
	}
	break;

	case ShelfWorstAreaFit:
	{
		//Choose the shelf with largest remaining shelf area.
		Shelf *bestShelf = 0;
		int bestShelfSurfaceArea = -1;
		for (size_t i = 0; i < shelves.size(); ++i)
		{
			//Pre-rotate the rect onto the shelf here already
			RotateToShelf(shelves[i], width, height);
			if (FitsOnShelf(shelves[i], width, height))
			{
				int surfaceArea = (binWidth - shelves[i].currentX) * shelves[i].height;
				if (surfaceArea > bestShelfSurfaceArea)
				{
					bestShelf = &shelves[i];
					bestShelfSurfaceArea = surfaceArea;
				}
			}//find the shelf with largest remaining shelf area
		}
		if (bestShelf)
		{
			AddToShelf(*bestShelf, width, height, newNode);
			return newNode;
		}
	}
	break;

	case ShelfBestHeightFit:
	{
		//Choose the shelf with best-matching height
		Shelf *bestShelf = 0;
		int bestShelfHeightDifference = 0x7FFFFFFF;
		for (size_t i = 0; i < shelves.size(); ++i)
		{
			//Pre-rotate the rect onto the shelf here already
			RotateToShelf(shelves[i], width, height);
			if (FitsOnShelf(shelves[i], width, height))
			{
				int heightDifference = max(shelves[i].height - height, 0);
				assert(heightDifference >= 0);

				if (heightDifference < bestShelfHeightDifference)
				{
					bestShelf = &shelves[i];
					bestShelfHeightDifference = heightDifference;
				}
			}//find the shelf with best-matching height
		}
		if (bestShelf)
		{
			AddToShelf(*bestShelf, width, height, newNode);
			return newNode;
		}
	}
	break;

	case ShelfBestWidthFit:
	{
		//Choose the shelf with smallest remaining shelf width.
		Shelf *bestShelf = 0;
		int bestShelfWidthDifference = 0x7FFFFFFF;
		for (size_t i = 0; i < shelves.size(); ++i)
		{
			// Pre-rotate the rect onto the shelf here already
			RotateToShelf(shelves[i], width, height);
			if (FitsOnShelf(shelves[i], width, height))
			{
				int widthDifference = binWidth - shelves[i].currentX - width;
				assert(widthDifference >= 0);
				if (widthDifference < bestShelfWidthDifference)
				{
					bestShelf = &shelves[i];
					bestShelfWidthDifference = widthDifference;
				}
			}//find the shelf with smallest remaining shelf width
		}

		if (bestShelf)
		{
			AddToShelf(*bestShelf, width, height, newNode);
			return newNode;
		}
	}
	break;

	case ShelfWorstWidthFit:
	{
		//Choose the shelf with smallest remaining shelf width.
		Shelf *bestShelf = 0;
		int bestShelfWidthDifference = -1;
		for (size_t i = 0; i < shelves.size(); ++i)
		{
			// Pre-rotate the rect onto the shelf here already
			RotateToShelf(shelves[i], width, height);
			if (FitsOnShelf(shelves[i], width, height))
			{
				int widthDifference = binWidth - shelves[i].currentX - width;
				assert(widthDifference >= 0);
				if (widthDifference > bestShelfWidthDifference)
				{
					bestShelf = &shelves[i];
					bestShelfWidthDifference = widthDifference;
				}
			}//find the shelf with smallest remaining shelf width
		}
		if (bestShelf)
		{
			AddToShelf(*bestShelf, width, height, newNode);
			return newNode;
		}
	}
	break;

	}

	//The rectangle did not fit on any of the shelves. Open a new shelf.

	//Flip the rectangle so that the long side is horizontal.
	if (width < height && height <= binWidth)
		swap(width, height);

	StartNewShelf(height);
	assert(FitsOnShelf(shelves.back(), width, height));//if cannot fit on,error
	AddToShelf(shelves.back(), width, height, newNode);
	return newNode;

	//The rectangle didn't fit.
	memset(&newNode, 0, sizeof(Rect));
	return newNode;
}

int ShelfBinPack::GetHeight()
{
	return binHeight;
}

