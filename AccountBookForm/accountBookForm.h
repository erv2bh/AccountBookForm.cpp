//accountBookForm.h
#ifndef _ACCOUNTBOOKFORM_H
#define _ACCOUNTBOOKFORM_H
#include <afxwin.h>
#include "resource.h"
typedef signed long int Long;
class AccountBook;
class AccountBookForm :public CDialog {
public:
	enum { IDD = IDD_ACCOUNTBOOKFORM };
public:
	AccountBookForm(CWnd* parent = NULL);
	virtual BOOL OnInitDialog();
public:
	AccountBook* accountBook;
protected:
	afx_msg void OnRecordButtonClicked();
	afx_msg void OnCorrectButtonClicked();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCalculateButtonClicked();
	afx_msg void OnListViewItemDoubleClicked(NMHDR* pNotifystruct, LRESULT* result);
	afx_msg void OnAmountEditKillFocus();	
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	void Load();
	CString MakeCode(Long index);
	void Insert(Long index);
	void Modify(Long index);
	void Save();
};
#endif //_ACCOUNTBOOKFORM_H