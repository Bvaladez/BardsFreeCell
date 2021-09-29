
// FreeCell2021Dlg.cpp : implementation file
//

#include <vector>

#include "pch.h"
#include "framework.h"
#include "FreeCell2021.h"
#include "cell.h"
#include "FreeCell2021Dlg.h"
#include "afxdialogex.h"
#include "WindowsCards.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CFreeCell2021Dlg dialog



CFreeCell2021Dlg::CFreeCell2021Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FREECELL2021_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFreeCell2021Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFreeCell2021Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CFreeCell2021Dlg message handlers

BOOL CFreeCell2021Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	bool ok = InitializeCards();
	if (!ok)
	{
		MessageBox(L"InitializeCards failed.", L"Error", MB_ICONHAND);
		exit(1);
	}
	

	// TOP ROW 8 CELLS
	mCells[0] = new Cell(2, 4, 12, 24, "FREE");
	mCells[1] = new Cell(14, 4, 24, 24, "FREE");
	mCells[2] = new Cell(26, 4, 36, 24, "FREE");
	mCells[3] = new Cell(38, 4, 48, 24, "FREE");
	mCells[4] = new Cell(50, 4, 60, 24, "END");
	mCells[5] = new Cell(62, 4, 72, 24, "END");
	mCells[6] = new Cell(74, 4, 84, 24, "END");
	mCells[7] = new Cell(86, 4, 96, 24, "END");

	// BOTTOM ROW 8 CELLS (STACKED)
	mCells[8] = new Cell(2, 28, 12, 96, "START");
	mCells[9] = new Cell(14, 28, 24, 96, "START");
	mCells[10] = new Cell(26, 28, 36, 96, "START");
	mCells[11] = new Cell(38, 28, 48, 96, "START");
	mCells[12] = new Cell(50, 28, 60, 96, "START");
	mCells[13] = new Cell(62, 28, 72, 96, "START");
	mCells[14] = new Cell(74, 28, 84, 96, "START");
	mCells[15] = new Cell(86, 28, 96, 96, "START");

	srand(time(0));
	int index = rand() % 52;

//	for (int cell = 0; cell < 12; cell++) {
//		mCells[cell]->AddCard(deck[index++]);
//	}
	std::vector<int> deck;

	for (int i = 0; i < 52; i++) {
		deck.push_back(i);
	}


	while (deck.size() > 0) {
		for (int cell = 8; cell < 16; cell++) {
			int lastCard = deck.size() - 1;

			//the first 4 cells get 7 cards each cell after only gets 6 so we need to cut the while loop early
			// better implementation???
			if (deck.size() == 0) {
				break;
			}
			//select a random card, put it in back of vector, deal it then pop it
			// do this on reapeat til we have no more cards
			int index = rand() % deck.size();
			std::swap(deck[index], deck[lastCard]);
			int card = deck[lastCard];
			deck.pop_back();
			mCells[cell]->AddCard(card);
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFreeCell2021Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFreeCell2021Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		COLORREF backGroundColor = RGB(50, 255, 25);
		CBrush backgroundBrush(backGroundColor);

		CPaintDC dc(this); // device context for painting
		dc.SelectObject(backgroundBrush);
		CRect clientRect;
		GetClientRect(&clientRect);

		// Brush is for fill color
		// Pen is for outline color
		dc.SelectStockObject(WHITE_BRUSH);
		dc.SelectStockObject(BLACK_PEN);
		// Homemade Green Brush and Blue Pen, using variables:
		COLORREF greenColor(RGB(0, 190, 0));
		CBrush greenBrush;
		greenBrush.CreateSolidBrush(greenColor);
		dc.SelectObject(&greenBrush);

		//Go through each cell and draw  the cards contained in mCards for each cell
		for (int i = 0; i < 16; i++) {
			bool selected = false; // 0 for face up 2 for highlighted
			if (mFirstClickedCell == i) {
				selected = true;
			}
			mCells[i]->Draw(dc, clientRect, selected);
		}

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFreeCell2021Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFreeCell2021Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	Invalidate();
}


void CFreeCell2021Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	double H = 100;
	double W = 100;

	CRect rect;
	GetClientRect(&rect);
	int w = rect.Width();
	int h = rect.Height();
	int x1, x2, x3, x4;
	int picked = -1;
	// for each each cell check if point is in range on x and y axis
	for (int cell = 0; cell < 16; cell++) {
		// World Quardinates 
		double left = mCells[cell]->getmLeft();
		double right = mCells[cell]->getmRight();
		double top = mCells[cell]->getmBottom();
		double bottom = mCells[cell]->getmTop();
		// convert world coordinates to pixel
		H = W / w * h * 1.5;
		double x1World = (int)(w / W * left);
		double x2World = (int)(w / W * right);
		double y1World = (int)(h / H * top);
		double y2World = (int)(h / H * bottom);
		// check if mouse up click is insinde cell in pixel coordinates
		double x = point.x;
		double y = point.y;
		if (x > x1World && x < x2World && y < y1World && y > y2World) {
			picked = cell;
		}
	}
	// user didnt click on card
	if (picked == -1) {
		return;
	}
	// first clicked cell, source of the move
	if (mFirstClickedCell == -1) {
		// only count a first click if a cell has cards
		if (mCells[picked]->getmCards().size() > 0) {
			mFirstClickedCell = picked;
		}
	}
	// second click. the picked cell is the destination of the move
	else { 
		Cell* dstCell = mCells[picked];
		Cell* srcCell = mCells[mFirstClickedCell];
		std::vector<int> srcCards = srcCell->getmCards();
		std::vector<int> dstCards = dstCell->getmCards();
		int srcSize = srcCards.size();
		int dstSize = dstCards.size();

		// MOVING FROM STARTCELL TO FREECELL
		if (dstCell->getType() == "FREE" && srcCell->getType() == "START"
			&& dstCards.size() == 0) {
			swapCards(mFirstClickedCell, picked);
		}
		// MOVING FROM STARTCELL TO STARTCELL OR FREECELL TO STARTCELL
		if ((srcCell->getType() == "START" || srcCell->getType() == "FREE" ) && dstCell->getType() == "START" 
			&& srcCards.size() > 0) {
			// given a dst is a startCell with no cards all moves are legal
			if (dstCards.size() == 0) {
				swapCards(mFirstClickedCell, picked);
			}
			// src cards and dst cards have cards in them check for color and value legality
			// we need to move the highest suit card possible so if the entire src cell is in order to be added to another startcell we move the entire cell
			bool swap = true;
			for (int i = 0; i < srcSize; i++) {
				if (getColorFromSuit(getSuitFromIndex(srcCards[i])) != getColorFromSuit(getSuitFromIndex(dstCards[dstSize - 1]))
					&& getRankFromIndex(srcCards[i]) == getRankFromIndex(dstCards[dstSize - 1]) - 1) {
					// we found the first card in the cell that could be transfered make ssure the following cards obey the rules too then swap all cards
					for (int j = i; j < srcSize - 1; j++) {
						if (getColorFromSuit(getSuitFromIndex(srcCards[i + 1])) != getColorFromSuit(getSuitFromIndex(srcCards[i]))
							&& getRankFromIndex(srcCards[i + 1]) == getRankFromIndex(srcCards[i]) - 1) {
						}
						else {
							// if we find a card that doesnt obey we stop checking the rest and move down the list of canidate cards in the src cell
							swap = false;
							break;
						}
					}
					if (swap){
						swapAllCards(i,mFirstClickedCell,picked);
					}
				}
			}
		}

		// MOVING FROM A STARTCELL OR FREECELL TO ENDCELL
		if ((srcCell->getType() == "START" || srcCell->getType() == "FREE") && dstCell->getType() == "END" ) {
			if (dstSize == 0 && (srcCards[srcSize - 1] == 0) || (srcCards[srcSize - 1] == 1) || (srcCards[srcSize - 1] == 2) || (srcCards[srcSize - 1] == 3)) {
				swapCards(mFirstClickedCell, picked);
			}
			else if (dstSize != 0
				&& getRankFromIndex(srcCards[srcSize - 1]) == getRankFromIndex(dstCards[dstSize - 1]) + 1
				&& getSuitFromIndex(srcCards[srcSize - 1]) == getSuitFromIndex(dstCards[dstSize - 1])) {
				swapCards(mFirstClickedCell, picked);
			}
		}

		mFirstClickedCell = -1;
	}

	Invalidate();

	CDialogEx::OnLButtonUp(nFlags, point);
}

// Swap card from src cell to dst cell
void CFreeCell2021Dlg::swapCards(int src, int dst) {
	// get cards in src cell
	std::vector<int> srcCards = mCells[src]->getmCards();
	// get src card from src cards
	int srcCard = srcCards[srcCards.size() - 1];
	// remove src card from src cell
	mCells[src]->pop();
	// add source card to picked cell
	mCells[dst]->AddCard(srcCard);

}
// move all cards from srcCard to end onto the end of dst
void CFreeCell2021Dlg::swapAllCards(int srcCardIdx, int srcCell, int dst) {
	std::vector<int> srcCards = mCells[srcCell]->getmCards();
	// for every card starting at src to end move to dst cell
	for (int i = srcCardIdx; i < srcCards.size(); i++) {
		mCells[dst]->AddCard(srcCards[i]);
	}

	for (int j = srcCardIdx; j < srcCards.size(); j++) {
		mCells[srcCell]->pop();
	}
	
}

/* index	suit		rank
   -----	----		----
	0		clubs		ace
	1		diamonds	ace
	2		hearts		ace
	3		spades		ace

	4		clubs		two
	...

	48		clubs		king
	49		diamond		king
	50		hearts		king
	51		spaces		king
*/


int CFreeCell2021Dlg::getIndexFromCard(int suit, int rank) {
	int index = rank * 4 + suit;
	return index;
}

int CFreeCell2021Dlg::getSuitFromIndex(int index) {
	int suit = index%4;
	return suit;
}

int CFreeCell2021Dlg::getRankFromIndex(int index){
	int rank = index / 4;

	return rank;
}
// zero is black (clubs, spades) 1 is red (hearts, diamonds).
int CFreeCell2021Dlg::getColorFromSuit(int suit) {
	if (suit == 0) {
		return 0;
	}
	if (suit == 1) {
		return 1;
	}
	if (suit == 2) {
		return 1;
	}
	if (suit == 3) {
		return 0;
	}



}



HBRUSH CFreeCell2021Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	HBRUSH backGround = CreateSolidBrush(RGB(20,101,19));
	return backGround;
	//return (HBRUSH)GetStockObject(BLACK_BRUSH);

	// TODO:  Change any attributes of the DC here

	// TODO:  Return a different brush if the default is not desired
	//return hbr;
}
