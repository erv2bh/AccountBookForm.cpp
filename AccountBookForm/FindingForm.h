//FindingForm.h
#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H
#include <afxwin.h>
#include "resource.h"
typedef signed long int Long;

class FindingForm :public CDialog {
public:
	enum { IDD = IDD_FINDINGFORM };
public:
	FindingForm(BOOL isFinding, CWnd* parent = NULL);
	virtual BOOL OnInitDialog();
public:
	BOOL isFinding;
	Long(*indexes);
	Long count;

protected:
	afx_msg void OnClose();
	afx_msg void OnFindButtonClicked();
	afx_msg void OnCalculateButtonClicked();
	afx_msg void OnListViewItemDoubleClicked(NMHDR* pNotifystruct, LRESULT* result);
	DECLARE_MESSAGE_MAP()
};

#endif //_FINDINGFORM_H