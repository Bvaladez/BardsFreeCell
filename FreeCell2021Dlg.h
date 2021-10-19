
// FreeCell2021Dlg.h : header file
//

#pragma once
#include <fstream>
#include "cell.h"

// CFreeCell2021Dlg dialog
class CFreeCell2021Dlg : public CDialogEx
{
// Construction
public:
	CFreeCell2021Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FREECELL2021_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	Cell* mCells[16];
	int mFirstClickedCell = -1;
	bool LoadImages(const CString& theDeck);
	CImage mCardImages[52];
	bool mUseImages;
	bool mEnabledImages;

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	int getIndexFromCard(int suit, int rank);
	int getRankFromIndex(int index);
	int getSuitFromIndex(int index);
	int getColorFromSuit(int suit);
	void swapCards(int src, int dst);
	void CFreeCell2021Dlg::swapAllCards(int startIndex, int src, int dst);


	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	afx_msg void OnFileQuit();
	afx_msg void OnFileScoobycards();
	afx_msg void OnFileDefaultcards();
	afx_msg void OnFileNewgame();
};
