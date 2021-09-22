#pragma once
#include <vector>

class Cell
{
public:
	Cell(double left, double top, double right, double bottom);
	//bool IsEmpty();
	void Draw(CDC& dc, CRect & clientRect, bool selected);
	void AddCard(int index);
	bool IsClicked(int x, int y); // in pixel coordinates
	double getmLeft() {return mLeft;}
	double getmTop() {return mTop;}
	double getmRight() {return mRight;}
	double getmBottom() {return mBottom;}
	std::vector<int> getmCards() { return mCards; }
	void pop() { mCards.pop_back(); }

private:
	std::vector<int> mCards;
	double mLeft, mTop, mRight, mBottom; // in world coordinates
};
