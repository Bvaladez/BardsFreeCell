#pragma once
#include <vector>

class Cell
{
public:
	Cell(double left, double top, double right, double bottom);
	//bool IsEmpty();
	void Draw(CDC& dc, CRect & clientRect);
	void AddCard(int index);
	//bool IsClicked(int x, int y); // in pixel coordinates

private:
	std::vector<int> mCards;
	double mLeft, mTop, mRight, mBottom; // in world coordinates
};
