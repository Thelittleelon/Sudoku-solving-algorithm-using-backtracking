
// sudoku_gui_trialDlg.h : header file
//

#pragma once


// Csudoku_gui_trialDlg dialog
class Csudoku_gui_trialDlg : public CDialogEx
{
// Construction
public:
	Csudoku_gui_trialDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUDOKU_GUI_TRIAL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int draw_grid();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	CString m_n_data_choice;
	int m_n_data_choice;
	afx_msg void OnBnClickedUpdateData();
	virtual void OnOK();
	virtual void OnCancel();
};
