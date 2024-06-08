
// sudoku_gui_trialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "sudoku_gui_trial.h"
#include "sudoku_gui_trialDlg.h"
#include "afxdialogex.h"
#include "sudoku_generating.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int solvedGrid[SIZE][SIZE];
int puzzleGrid[SIZE][SIZE];

void createSudoku() {
	srand(time(0));

	fillGrid(solvedGrid);

	// Copy solvedGrid to puzzleGrid
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			puzzleGrid[row][col] = solvedGrid[row][col];
		}
	}

	hideNumbers(puzzleGrid, 25, 50);
}

char sudoku_data[9][9] = {
	{ '1','2', '3', '1', '1', '1', '1', '1', '1' },
	{ '1',' ', '1', '1', '1', '1', '1', '1', '1' },
	{ '1','1', '4', '1', '1', '1', '1', '1', '1' },
	{ '1','1', '1', '1', '1', '5', '1', '1', '1' },
	{ '1','1', '1', '1', '1', '1', '1', '1', '1' },
	{ '1','1', '1', '1', '1', '1', '1', '1', '1' },
	{ '1','1', '1', '1', '1', '1', '1', '1', '1' },
	{ '1','1', '1', '1', '1', '7', '1', '1', '1' },
	{ '1','1', '1', '1', '1', '1', '1', '1', '1' }
};

int nDX;
int nDY;
int selRow, selCol;
int currentSelData = -1;

//extern int solvedGrid[SIZE][SIZE];
//extern int puzzleGrid[SIZE][SIZE];
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


// Csudoku_gui_trialDlg dialog



Csudoku_gui_trialDlg::Csudoku_gui_trialDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SUDOKU_GUI_TRIAL_DIALOG, pParent)
	, m_n_data_choice(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Csudoku_gui_trialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_CBString(pDX, IDC_DATA_CHOICE, m_n_data_choice);
	DDX_CBIndex(pDX, IDC_DATA_CHOICE, m_n_data_choice);
}

BEGIN_MESSAGE_MAP(Csudoku_gui_trialDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_UPDATE_DATA, &Csudoku_gui_trialDlg::OnBnClickedUpdateData)
END_MESSAGE_MAP()


// Csudoku_gui_trialDlg message handlers

BOOL Csudoku_gui_trialDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	int sudRow, sudCol;
	createSudoku();
	for (sudRow = 0; sudRow < SIZE; sudRow++)
	{
		for (sudCol = 0; sudCol < SIZE; sudCol++)
		{
			if (puzzleGrid[sudRow][sudCol] == 0)
			{
				sudoku_data[sudRow][sudCol] = ' ';
			}
			else
			{
				sudoku_data[sudRow][sudCol] = puzzleGrid[sudRow][sudCol] + '0';
			}
		}
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Csudoku_gui_trialDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Csudoku_gui_trialDlg::OnPaint()
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
		
		draw_grid();
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Csudoku_gui_trialDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int Csudoku_gui_trialDlg::draw_grid()
{
	CPaintDC dc(this); // device context for painting
	CRect rcClient;
	GetClientRect(&rcClient);
	//Put a horizontal line in the middle of the dialog
	nDX = (rcClient.right - rcClient.left) / 13;
	nDY = (rcClient.bottom - rcClient.top) / 13;
	int row, col;

	//Starting point of the line
	dc.MoveTo(nDX, nDY);
	dc.LineTo(10 * nDX, nDY);
	dc.MoveTo(nDX, nDY);
	dc.LineTo(nDX, 10 * nDY);
	for (int i = 2; i <= 10; i++)
	{
		dc.MoveTo(nDX, i * nDY);
		dc.LineTo(10 * nDX, i * nDY);

		dc.MoveTo(i * nDX, nDY);
		dc.LineTo(i * nDX, 10 * nDY);
	}


	for (row = 0; row < 9; row++)
	{
		for (col = 0; col < 9; col++)
		{
			TCHAR sOut[2] = L" ";
			sOut[0] = sudoku_data[row][col];
			dc.TextOutW(nDX*(col + 1) + nDX / 3, nDY*(row + 1) + nDY / 4, sOut);
			//dc.TextOutW(nDX + nDX / 4, nDY + nDY / 4, L"a");
		}
	}





	dc.MoveTo(2 * nDX, nDY);
	dc.LineTo(2 * nDX, 10 * nDY);

	dc.MoveTo(3 * nDX, nDY);
	dc.LineTo(3 * nDX, 10 * nDY);
	return 0;
}


void Csudoku_gui_trialDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	int cursorX, cursorY;
	int tempRow, tempCol;
	cursorX = point.x;
	cursorY = point.y;
	if (currentSelData != -1)
	{
		sudoku_data[selRow][selCol] = currentSelData + '1';///??///
	}
	tempRow = cursorY / nDY - 1;
	tempCol = cursorX / nDX - 1;
	TCHAR ss[100];
	wsprintf(ss, L"Row %d, Col %d", tempRow, selCol);
	if (tempRow < 9 && tempCol < 9 && tempRow >=0 && tempCol >=0)
	{
		//MessageBox(ss);
		int currentData = sudoku_data[tempRow][tempCol];
		if (currentData == ' ')
		{
			m_n_data_choice = currentData - '1';
			currentSelData = m_n_data_choice;
			UpdateData(false);
			selRow = tempRow;
			selCol = tempCol;
			sudoku_data[selRow][selCol] = 'X';
			InvalidateRect(NULL);
		}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void Csudoku_gui_trialDlg::OnBnClickedUpdateData()
{
	int compl = 0;
	UpdateData();
	if (solvedGrid[selRow][selCol] == m_n_data_choice + 1)
	{
		sudoku_data[selRow][selCol] = m_n_data_choice + '1';
		currentSelData = -1;
		InvalidateRect(NULL);
	}
	else
	{
		MessageBox(L"Wrong answer!");
	}
	//check for completion
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			//compl = 0;
			if (sudoku_data[i][j] == ' ')
			{
				compl++;
			}
		}
	}
	if (compl == 0)
	{
		MessageBox(L"Congratulations! You have done it");
	}
	// TODO: Add your control notification handler code here
}


void Csudoku_gui_trialDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnOK();
}


void Csudoku_gui_trialDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	if (MessageBox(L"Do you want to exit?", NULL, MB_YESNO) == IDYES)
	{

		CDialogEx::OnCancel();
	}
}
