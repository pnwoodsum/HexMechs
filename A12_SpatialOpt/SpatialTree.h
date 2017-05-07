#pragma once

#include "RE\ReEng.h"

class Node 
{
public:
	//center of current grid spot
	vector3 position;
	//holds the x width, y width and z width of current grid section
	vector3 widths;

	Node();
	~Node();


};

class SpatialTree
{
public:
	Node* head;

	SpatialTree();
	~SpatialTree();
};

