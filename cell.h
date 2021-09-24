#pragma once
#include <vector>
#include <string>

class Cell
{
public:
	Cell(double left, double top, double right, double bottom, std::string type);
	//bool IsEmpty();
	void Draw(CDC& dc, CRect & clientRect, bool selected);
	void AddCard(int index);
	bool IsClicked(int x, int y); // in pixel coordinates
	double getmLeft() {return mLeft;}
	double getmTop() {return mTop;}
	double getmRight() {return mRight;}
	double getmBottom() {return mBottom;}
	std::string getType() { return mType; }
	std::vector<int> getmCards() { return mCards; }
	void pop() { mCards.pop_back(); }

private:
	std::vector<int> mCards;
	double mLeft, mTop, mRight, mBottom; // in world coordinates
	double mX1, mX2, mY1, mY2; // in pixel coordinates
	std::string mType;
};
