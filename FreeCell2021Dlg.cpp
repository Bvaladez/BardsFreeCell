
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
	mCells[0] = new Cell(2, 4, 12, 24);
	mCells[1] = new Cell(14, 4, 24, 24);
	mCells[2] = new Cell(26, 4, 36, 24);
	mCells[3] = new Cell(38, 4, 48, 24);
	mCells[4] = new Cell(50, 4, 60, 24);
	mCells[5] = new Cell(62, 4, 72, 24);
	mCells[6] = new Cell(74, 4, 84, 24);
	mCells[7] = new Cell(86, 4, 96, 24);

	// BOTTOM ROW 8 CELLS (STACKED)
	mCells[8] = new Cell(2, 28, 12, 96);
	mCells[9] = new Cell(14, 28, 24, 96);
	mCells[10] = new Cell(26, 28, 36, 96);
	mCells[11] = new Cell(38, 28, 48, 96);
	mCells[12] = new Cell(50, 28, 60, 96);
	mCells[13] = new Cell(62, 28, 72, 96);
	mCells[14] = new Cell(74, 28, 84, 96);
	mCells[15] = new Cell(86, 28, 96, 96);

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
		CPaintDC dc(this); // device context for painting
		CRect clientRect;
		GetClientRect(&clientRect);

		//Go through each cell and draw  the cards contained in mCards for each cell
		for (int i = 0; i < 16; i++) {
			mCells[i]->Draw(dc, clientRect);
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
	// Select car when releasing left button

	CDialogEx::OnLButtonUp(nFlags, point);
}
