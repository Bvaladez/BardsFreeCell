#include "pch.h"
#include "cell.h"
#include "WindowsCards.h"
#include "iostream"

double W = 100;
double H = 100;

Cell::Cell(double left, double top, double right, double bottom, std::string type) :
	mLeft(left), mTop(top), mRight(right), mBottom(bottom), mType(type)
{

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

void Cell::Draw(CDC& dc, CRect & clientRect, bool useImages,CImage cardImages[51], bool selected){

	CRect pixelRect = MakeDrawRect(clientRect, mLeft, mTop, mRight, mBottom);
	dc.Rectangle(pixelRect);

	// Draw cards within cell
	int inset = 2;
	double verticalOffsetPerCard;

	this->getType() == "END" ? verticalOffsetPerCard = 0 : verticalOffsetPerCard = 4;

	double verticalOffset = 0;

	for (int i = 0; i < this->mCards.size(); i++) {

		pixelRect = MakeDrawRect(clientRect, mLeft, mTop + verticalOffset, mRight, mBottom + verticalOffset);
		int cardHeight = gCardHeight < pixelRect.Height() ? gCardHeight : pixelRect.Height();
		if (useImages) {
			int index = mCards[i];
			CImage& localCopy = cardImages[index];
			if (!localCopy.IsNull()) {
				BOOL ok = localCopy.StretchBlt(dc, pixelRect.left + inset, pixelRect.top + inset,
					pixelRect.Width() - 2 * inset, cardHeight, SRCCOPY);
			}
		}
		else {
			DrawCardExt(dc, pixelRect.left + inset, pixelRect.top + inset, pixelRect.Width() - 2 * inset, cardHeight,
			mCards[i], selected && i == mCards.size() -1);
		}
			verticalOffset += verticalOffsetPerCard;
	}
}

void Cell::AddCard(int index) {
	mCards.push_back(index);
}


