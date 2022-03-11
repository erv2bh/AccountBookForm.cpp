//FindingForm.cpp
#include "FindingForm.h"
#include "AccountBook.h"
#include "accountBookForm.h"
#include <afxcmn.h>
#include <afxdtctl.h>
#include "Income.h"
#include "Outgo.h"
BEGIN_MESSAGE_MAP(FindingForm,CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_FIND,OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE,OnCalculateButtonClicked)
	ON_NOTIFY(NM_DBLCLK,IDC_LIST_ACCOUNT,OnListViewItemDoubleClicked)
	END_MESSAGE_MAP()

FindingForm::FindingForm(BOOL isFinding, CWnd* parent)
	:CDialog(FindingForm::IDD, parent) {
	this->isFinding = isFinding;
	this->indexes = NULL;
	this->count = 0;
}

void FindingForm::OnClose() {
	if (this->indexes != 0) {
		delete[] indexes;
	}
	this->OnOK();
}


BOOL FindingForm::OnInitDialog() {
	CDialog::OnInitDialog();
	((CButton*)GetDlgItem(IDC_CHECK_DATE))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_CHECK_CONTENTS))->SetCheck(BST_CHECKED);
	if (isFinding == TRUE) {
		GetDlgItem(IDC_STATIC_TOTALINCOME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_TOTALOUTGO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_BALANCE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_TOTALINCOME)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_TOTALOUTGO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_BALANCE)->ShowWindow(SW_HIDE);
		
	}
	
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertColumn(0, "일자", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertColumn(1, "적요", LVCFMT_LEFT, 70);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertColumn(2, "금액", LVCFMT_RIGHT, 80);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertColumn(3, "잔액", LVCFMT_RIGHT, 80);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertColumn(4, "비고", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return FALSE;
}

void FindingForm::OnFindButtonClicked() {
	CTime startTime;
	CTime endTime;
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_STARTDATE))->GetTime(startTime);
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_ENDDATE))->GetTime(endTime);
	int startYear, startMonth, startDay;
	int endYear, endMonth, endDay;
	startYear = startTime.GetYear();
	startMonth = startTime.GetMonth();
	startDay = startTime.GetDay();
	endYear = endTime.GetYear();
	endMonth = endTime.GetMonth();
	endDay = endTime.GetDay();
	Date startDate(startYear, static_cast<Month>(startMonth), startDay);
	Date endDate(endYear, static_cast<Month>(endMonth), endDay);
	CString contents;
	Currency balance_ = 0;
	GetDlgItem(IDC_EDIT_CONTENTS)->GetWindowTextA(contents);
	AccountBookForm* accountBookForm = (AccountBookForm*)CWnd::FindWindowA("#32770", "가계부");
	if (((CButton*)GetDlgItem(IDC_CHECK_DATE))->GetCheck() == TRUE && ((CButton*)GetDlgItem(IDC_CHECK_CONTENTS))->GetCheck() == FALSE) {
		accountBookForm->accountBook->Find(startDate, endDate, &(this->indexes), &(this->count));
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_DATE))->GetCheck() == FALSE && ((CButton*)GetDlgItem(IDC_CHECK_CONTENTS))->GetCheck() == TRUE) {
		accountBookForm->accountBook->Find((LPCTSTR)contents, &(this->indexes), &(this->count));
	}
	if (((CButton*)GetDlgItem(IDC_CHECK_DATE))->GetCheck() == TRUE && ((CButton*)GetDlgItem(IDC_CHECK_CONTENTS))->GetCheck() == TRUE) {
		accountBookForm->accountBook->Find(startDate, endDate,(LPCTSTR)contents, &(this->indexes), &(this->count));
	}
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->DeleteAllItems();
	int i = 0;
	while (i < this->count) {
		Account* account = accountBookForm->accountBook->GetAt(indexes[i]);
		CString date_;
		Date date = account->GetDate();
		date_.Format("%4d-%02d-%02d", date.GetYear(), date.GetMonth(), date.GetDay());
		if (dynamic_cast<Income*>(account)) {
			((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertItem(i, _T(""), 2);
		}
		else {
			((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertItem(i, _T(""), 1);
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i,0, date_);
		contents = CString(account->GetContents().c_str());
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i, 1, contents);
		Currency amount_ = account->GetAmount();
		balance_ = balance_ + amount_;
		if (amount_ < 0) {
			amount_ *= -1;
		}
		CString amount;
		amount.Format("%.0f", amount_);
		int j = 0;
		j = amount.GetLength() - 3;
		while (j > 0) {
			amount.Insert(j, ',');
			j = j - 3;
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i, 2, amount);
		
		
		CString balance;
		balance.Format("%.0f", balance_);
		j = balance.GetLength() - 3;
		while (j > 0) {
			balance.Insert(j, ',');
			j = j - 3;
		}
		
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i, 3, balance);
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i, 4, account->GetNote().c_str());
		i++;
	}

	GetDlgItem(IDC_STATIC_TOTALINCOME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_TOTALOUTGO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_BALANCE)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_TOTALINCOME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_TOTALOUTGO)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_BALANCE)->ShowWindow(SW_HIDE);
}

void FindingForm::OnCalculateButtonClicked() {
	if (isFinding == TRUE) {
		GetDlgItem(IDC_STATIC_TOTALINCOME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_TOTALOUTGO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_BALANCE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_TOTALINCOME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_TOTALOUTGO)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT_BALANCE)->ShowWindow(SW_SHOW);
	}
	int i = 0;
	
		CTime startTime;
		CTime endTime;
		((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_STARTDATE))->GetTime(startTime);
		((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_ENDDATE))->GetTime(endTime);
		int startYear, startMonth, startDay;
		int endYear, endMonth, endDay;
		startYear = startTime.GetYear();
		startMonth = startTime.GetMonth();
		startDay = startTime.GetDay();
		endYear = endTime.GetYear();
		endMonth = endTime.GetMonth();
		endDay = endTime.GetDay();
		Date startDate(startYear, static_cast<Month>(startMonth), startDay);
		Date endDate(endYear, static_cast<Month>(endMonth), endDay);
		AccountBookForm* accountBookForm = (AccountBookForm*)CWnd::FindWindowA("#32770", "가계부");
		Currency totalIncome, totalOutgo, diffBalance;
		accountBookForm->accountBook->Calculate(startDate, endDate, &totalIncome, &totalOutgo, &diffBalance);
		CString totalIncome_;
		CString totalOutgo_;
		CString diffBalance_;
		totalIncome_.Format("%.0f", totalIncome);
		i = totalIncome_.GetLength() - 3;
		while (i > 0) {
			totalIncome_.Insert(i, ',');
			i = i - 3;
		}
		if (totalOutgo < 0) {
			totalOutgo *= -1;
		}
		totalOutgo_.Format("%.0f", totalOutgo);
		i = totalOutgo_.GetLength() - 3;
		while (i > 0) {
			totalOutgo_.Insert(i, ',');
			i = i - 3;
		}
		diffBalance_.Format("%.0f", diffBalance);
		i = diffBalance_.GetLength() - 3;
		while (i > 0) {
			diffBalance_.Insert(i, ',');
			i = i - 3;
		}
		GetDlgItem(IDC_EDIT_TOTALINCOME)->SetWindowTextA(totalIncome_);
		GetDlgItem(IDC_EDIT_TOTALOUTGO)->SetWindowTextA(totalOutgo_);
		GetDlgItem(IDC_EDIT_BALANCE)->SetWindowTextA(diffBalance_);
	
		accountBookForm->accountBook->Find(startDate, endDate, &(this->indexes), &(this->count));
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->DeleteAllItems();
		i = 0;
		Currency balance_ = 0;
		while (i < this->count) {
			Account* account = accountBookForm->accountBook->GetAt(indexes[i]);
			CString date_;
			Date date = account->GetDate();
			date_.Format("%4d-%02d-%02d", date.GetYear(), date.GetMonth(), date.GetDay());
			if (dynamic_cast<Income*>(account)) {
				((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertItem(i, _T(""), 2);
			}
			else {
				((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertItem(i, _T(""), 1);
			}
			((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i,0, date_);
			CString contents = CString(account->GetContents().c_str());
			((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i, 1, contents);
			Currency amount_ = account->GetAmount();
			balance_ = balance_ + amount_;
			if (amount_ < 0) {
				amount_ *= -1;
			}
			CString amount;
			amount.Format("%.0f", amount_);
			int j = 0;
			j = amount.GetLength() - 3;
			while (j > 0) {
				amount.Insert(j, ',');
				j = j - 3;
			}
			((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i, 2, amount);
			
			CString balance;
			balance.Format("%.0f", balance_);
			j = balance.GetLength() - 3;
			while (j > 0) {
				balance.Insert(j, ',');
				j = j - 3;
			}
			((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i, 3, balance);
			((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i, 4, account->GetNote().c_str());
			i++;
		}
}

void FindingForm::OnListViewItemDoubleClicked(NMHDR* pNotifystruct, LRESULT* result) {
	CString date, contents, amount, balance, note;
	Long index = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->GetSelectionMark();
	date = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->GetItemText(index, 1);
	contents = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->GetItemText(index, 2);
	amount = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->GetItemText(index, 3);
	amount.Remove(',');
	balance = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->GetItemText(index, 4);
	note = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->GetItemText(index, 5);
	AccountBookForm* accountBookForm = (AccountBookForm*)CWnd::FindWindowA("#32770", "가계부");
	CString year, month, day;
	AfxExtractSubString(year, date, 0, '-');
	AfxExtractSubString(month, date, 1, '-');
	AfxExtractSubString(day, date, 2, '-');
	CTime temp(atoi(year), atoi(month), atoi(day), 0, 0, 0);
	CTime date_ = temp;
	Account* account = accountBookForm->accountBook->GetAt(index);
	if (dynamic_cast<Income*>(account)) {
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_CHECKED);
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_UNCHECKED);
	}
	else if (dynamic_cast<Outgo*>(account)) {
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);
		((CButton*)accountBookForm->GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
	}
	((CDateTimeCtrl*)accountBookForm->GetDlgItem(IDC_DATETIMEPICKER_DATE))->SetTime(&date_);
	accountBookForm->GetDlgItem(IDC_EDIT_CONTENTS)->SetWindowTextA(contents);
	accountBookForm->GetDlgItem(IDC_EDIT_AMOUNT)->SetWindowTextA(amount);
	accountBookForm->GetDlgItem(IDC_EDIT_BALANCE)->SetWindowTextA(balance);
	accountBookForm->GetDlgItem(IDC_EDIT_NOTE)->SetWindowTextA(note);
	((CListCtrl*)accountBookForm->GetDlgItem(IDC_LIST_ACCOUNT))->SetSelectionMark(indexes[index]);
	((CListCtrl*)accountBookForm->GetDlgItem(IDC_LIST_ACCOUNT))->SetItemState(indexes[index], LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	((CListCtrl*)accountBookForm->GetDlgItem(IDC_LIST_ACCOUNT))->SetFocus();
	if (indexes != 0) {
		delete[]indexes;
	}
	this->OnOK();
}