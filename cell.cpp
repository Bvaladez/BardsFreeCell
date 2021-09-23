#include "pch.h"
#include "cell.h"
#include "WindowsCards.h"
#include "iostream"

double W = 100;
double H = 100;

Cell::Cell(double left, double top, double right, double bottom) :
	mLeft(left), mTop(top), mRight(right), mBottom(bottom)
{

}

void Cell::getPixelCoordinates(double x1, double x2, double y1, double y2) {
	mX1 = x1;
	mX2 = x2;
	mY1 = y1;
	mY1 = y2;
}

CRect MakeDrawRect(CRect& clientRect, double left, double bottom, double right, double top)
{
	int w = clientRect.Width();
	int h = clientRect.Height();

	// Reset H to maintain an aspect ratio of 1.5, x pixels to y pixels.
	H = W / w * h * 1.5;
	CRect drawRect((int)(w / W * left), (int)(h / H * bottom), (int)(w / W * right), (int)(h / H * top));
	return drawRect;
}

void Cell::Draw(CDC& dc, CRect& clientRect, bool selected)
{
	CRect pixelRect = MakeDrawRect(clientRect, mLeft, mTop, mRight, mBottom);
	dc.Rectangle(pixelRect);

	// Draw cars within cell
	int inset = 2;
	double verticalOffsetPerCard = 4;
	double verticalOffset = 0;

	for (int i = 0; i < this->mCards.size(); i++) {
		bool selected = false;
		int cardIndex = mCards[i];

		pixelRect = MakeDrawRect(clientRect, mLeft, mTop + verticalOffset, mRight, mBottom + verticalOffset);

		// deteremine what value is small and use that for the card height
		// This stops cards from scaling vertically to fill the entire cell but still scale down when the window is shrunk
		int cardHeight = gCardHeight < pixelRect.Height() ? gCardHeight : pixelRect.Height();

		DrawCardExt(dc, pixelRect.left + inset, pixelRect.top + inset, pixelRect.Width() - 2 * inset, cardHeight,
			mCards[i], selected);

		verticalOffset += verticalOffsetPerCard;
	}
}

void Cell::AddCard(int index) {
	mCards.push_back(index);
}


