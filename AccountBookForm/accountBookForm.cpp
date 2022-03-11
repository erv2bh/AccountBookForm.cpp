//AccountBookForm.cpp
#include "accountBookForm.h"
#include "AccountBook.h"
#include <afxcmn.h>
#include <afxdtctl.h>
#include "Income.h"
#include "Outgo.h"
#include "FindingForm.h"

BEGIN_MESSAGE_MAP(AccountBookForm, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnRecordButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CORRECT, OnCorrectButtonClicked)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ACCOUNT, OnListViewItemDoubleClicked)
	ON_EN_KILLFOCUS(IDC_EDIT_AMOUNT, OnAmountEditKillFocus)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnFindButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE,OnCalculateButtonClicked)
	ON_WM_CLOSE()
	END_MESSAGE_MAP()

AccountBookForm::AccountBookForm(CWnd* parent)
	:CDialog(AccountBookForm::IDD, parent) {
	this->accountBook = NULL;
}

void AccountBookForm::OnClose() {
	if (this->accountBook != 0) {
		Save();
		delete this -> accountBook;
	}
	this->OnOK();
}

BOOL AccountBookForm::OnInitDialog() {
	CDialog::OnInitDialog();
	LVCOLUMN lvcolumn;
	this->accountBook = new AccountBook;
	((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);

	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertColumn(0, "일자", LVCFMT_CENTER, 100);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertColumn(1, "적요", LVCFMT_LEFT, 70);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertColumn(2, "금액", LVCFMT_RIGHT, 80);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertColumn(3, "잔액", LVCFMT_RIGHT, 80);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertColumn(4, "비고", LVCFMT_LEFT, 50);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	Load();
	int i = 0;
	while (i < this->accountBook->GetLength()) {
		Account* account = this->accountBook->GetAt(i);
		Date date = account->GetDate();
		CString contents = CString(account->GetContents().c_str());
		Currency amount = account->GetAmount();
		if (amount < 0) {
			amount *= -1;
		}
		Currency balance = account->GetBalance();
		CString note = CString(account->GetNote().c_str());

		CString date_;
		date_.Format("%4d-%02d-%02d", date.GetYear(), date.GetMonth(), date.GetDay());
		
		CString amount_;
		amount_.Format("%.0f", amount);
		int j = 0;
		j = amount_.GetLength() - 3;
		while (j > 0) {
			amount_.Insert(j, ',');
			j = j - 3;
		}

		CString balance_;
		balance_.Format("%.0f", balance);
		j = balance_.GetLength() - 3;
		while (j > 0) {
			balance_.Insert(j, ',');
			j = j - 3;
		}
		if (dynamic_cast<Income*>(account)) {
			((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertItem(i, _T(""), 2);
		}
		else {
			((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertItem(i, _T(""), 1);
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i, 0, date_);
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i, 1, contents);
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i, 2, amount_);
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i, 3, balance_);
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(i, 4, note);
		i++;
	}

	return FALSE;
}

void AccountBookForm::OnRecordButtonClicked() {
	CTime time;
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_DATE))->GetTime(time);
	int year, month, day;
	year = time.GetYear();
	month = time.GetMonth();
	day = time.GetDay();
	CString contents;
	Currency amount;
	CString amount_;
	CString note;
	GetDlgItem(IDC_EDIT_CONTENTS)->GetWindowTextA(contents);
	GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowTextA(amount_);
	GetDlgItem(IDC_EDIT_NOTE)->GetWindowTextA(note);

	amount = atof(amount_);
	
	Date date(year, static_cast<Month>(month), day);

	int outgoCheck = ((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->GetCheck();
	
	if (outgoCheck == BST_CHECKED) {
		amount = amount * -1;
	}

	Long index = this->accountBook->Record(date, (LPCTSTR)contents, amount, (LPCTSTR)note);
	Insert(index);
	Account* account = this->accountBook->GetAt(index);
	
	date = account->GetDate();
	contents = CString(account->GetContents().c_str());
	amount = account->GetAmount();
	if (amount < 0) {
		amount *= -1;
	}
	Currency balance = account->GetBalance();
	note = CString(account->GetNote().c_str());

	CString date_;
	date_.Format("%4d-%02d-%02d", date.GetYear(), date.GetMonth(), date.GetDay());

	amount_.Format("%.0f", amount);
	int i = 0;
	i = amount_.GetLength() - 3;
	while (i > 0) {
		amount_.Insert(i, ',');
		i = i - 3;
	}

	CString balance_;
	balance_.Format("%.0f", balance);
	i = balance_.GetLength() - 3;
	while (i > 0) {
		balance_.Insert(i, ',');
		i = i - 3;
	}
	if (dynamic_cast<Income*>(account)) {
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertItem(i, _T(""), 2);
	}
	else {
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->InsertItem(i, _T(""), 1);
	}
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(index, 1, date_);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(index, 2, contents);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(index, 3, amount_);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(index, 4, balance_);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(index, 5, note);
}

void AccountBookForm::OnCorrectButtonClicked() {
	Long index;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->GetSelectionMark();
	CString amount_;
	CString note;
	GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowTextA(amount_);
	GetDlgItem(IDC_EDIT_NOTE)->GetWindowTextA(note);
	Currency amount;
	amount = atof(amount_);
	int outgoCheck = ((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->GetCheck();

	if (outgoCheck == BST_CHECKED) {
		amount = amount * -1;
	}

	index = this->accountBook->Correct(index, amount, (LPCTSTR)note);
	Modify(index);
	Account* account = this->accountBook->GetAt(index);
	amount = account->GetAmount();
	if (amount < 0) {
		amount *= -1;
	}
	int i = 0;
	i = amount_.GetLength() - 3;
	while (i > 0) {
		amount_.Insert(i, ',');
		i = i - 3;
	}
	Currency balance = account->GetBalance();
	CString balance_;
	balance_.Format("%.0f", balance);
	i = 0;
	i = balance_.GetLength() - 3;
	while (i > 0) {
		balance_.Insert(i, ',');
		i = i - 3;
	}
	note = CString(account->GetNote().c_str());
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(index, 3, amount_);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(index, 4, balance_);
	((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(index, 5, note);
	GetDlgItem(IDC_EDIT_BALANCE)->SetWindowTextA(balance_);
	i = 1;
	while (index + i < this->accountBook->GetLength()) {
		account = this->accountBook->GetAt(index + i);
		balance = account->GetBalance();
		balance_.Format("%.0f", balance);
		int j = 0;
		j = balance_.GetLength() - 3;
		while (j > 0) {
			balance_.Insert(j, ',');
			j = j - 3;
		}
		((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->SetItemText(index + i, 4, balance_);
		i++;
	}
}

void AccountBookForm::OnListViewItemDoubleClicked(NMHDR* pNotifystruct, LRESULT* result) {
	Long index;
	CString date;
	CString contents;
	CString amount;
	CString balance;
	CString note;
	index = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->GetSelectionMark();
	date = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->GetItemText(index, 0);
	contents = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->GetItemText(index, 1);
	amount = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->GetItemText(index, 2);
	balance = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->GetItemText(index, 3);
	note = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->GetItemText(index, 4);
	
	amount.Remove(',');
	balance.Remove(',');
	CString year, month, day;
	AfxExtractSubString(year, date, 0, '-');
	AfxExtractSubString(month, date, 1, '-');
	AfxExtractSubString(day, date, 2, '-');
	CTime temp(atoi(year), atoi(month), atoi(day),0,0,0);
	CTime date_ = temp;
	Account* account = this->accountBook->GetAt(index);
	if (dynamic_cast<Income*>(account)) {
		((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_UNCHECKED);
	}
	else if (dynamic_cast<Outgo*>(account)) {
		((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->SetCheck(BST_CHECKED);
		((CButton*)GetDlgItem(IDC_RADIO_INCOME))->SetCheck(BST_UNCHECKED);
	}
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER_DATE))->SetTime(&date_);
	GetDlgItem(IDC_EDIT_CONTENTS)->SetWindowTextA(contents);
	GetDlgItem(IDC_EDIT_AMOUNT)->SetWindowTextA(amount);
	GetDlgItem(IDC_EDIT_BALANCE)->SetWindowTextA(balance);
	GetDlgItem(IDC_EDIT_NOTE)->SetWindowTextA(note);
}

void AccountBookForm::OnAmountEditKillFocus() {
	Long index;

	Currency balance;
	Account* account=0;
	if (this->accountBook->GetLength() > 0) {
		index = ((CListCtrl*)GetDlgItem(IDC_LIST_ACCOUNT))->GetSelectionMark();
		if (index == -1) {
			account = this->accountBook->GetAt(this->accountBook->GetLength() - 1);
			balance = account->GetBalance();
			Currency newBalance;
			CString amount;
			GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowTextA(amount);
			Currency amount_;
			amount_ = atof(amount);
			int outgoChecked;
			outgoChecked = ((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->GetCheck();
			if (outgoChecked == BST_CHECKED) {
				amount_ = amount_ * -1;
			}
			newBalance = balance + amount_;
			CString newBalance_;
			newBalance_.Format("%.0f", newBalance);
			GetDlgItem(IDC_EDIT_BALANCE)->SetWindowTextA(newBalance_);

		}
		else if (index==0){ 
			CString amount;
			GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowTextA(amount);
			GetDlgItem(IDC_EDIT_BALANCE)->SetWindowTextA(amount);
		}
		else if (index > 0) {
			account = this->accountBook->GetAt(index - 1);
			balance = account->GetBalance();
			Currency newBalance;
			CString amount;
			GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowTextA(amount);
			Currency amount_;
			amount_ = atof(amount);
			int outgoChecked;
			outgoChecked = ((CButton*)GetDlgItem(IDC_RADIO_OUTGO))->GetCheck();
			if (outgoChecked == BST_CHECKED) {
				amount_ = amount_ * -1;
			}
			newBalance = balance + amount_;
			CString newBalance_;
			newBalance_.Format("%.0f", newBalance);
			GetDlgItem(IDC_EDIT_BALANCE)->SetWindowTextA(newBalance_);
		}
		
	}
	else {
		CString amount;
		GetDlgItem(IDC_EDIT_AMOUNT)->GetWindowTextA(amount);
		GetDlgItem(IDC_EDIT_BALANCE)->SetWindowTextA(amount);
	}
}

void AccountBookForm::OnFindButtonClicked() {
	FindingForm findingForm(TRUE);
	findingForm.DoModal();
}

void AccountBookForm::OnCalculateButtonClicked() {
	FindingForm findingForm(FALSE);
	findingForm.DoModal();
}
#include <afxdb.h>
void AccountBookForm::Load() {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT account.date,account.contents,account.amount,account.note FROM account;";
	db.OpenEx("DSN=accountBook;UID=root;PWD=Pagaous08217!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CDBVariant date;
	CString contents;
	CString amount;
	CString note;
	while (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, date);
		rs.GetFieldValue((short)1, contents);
		rs.GetFieldValue((short)2, amount);
		rs.GetFieldValue((short)3, note);
		CTime time(date.m_pdate->year, date.m_pdate->month, date.m_pdate->day, 0, 0, 0);
		int year, month, day;
		year = time.GetYear();
		month = time.GetMonth();
		day = time.GetDay();
		Date date_(year, static_cast<Month>(month), day);
		Currency amount_;
		amount_ = atof(amount);
		this->accountBook->Record(date_, (LPCTSTR)contents, amount_, (LPCTSTR)note);
		rs.MoveNext();
	}
	rs.Close();
	db.Close();
}

CString AccountBookForm::MakeCode(Long index) {
	CDatabase db;
	CRecordset rs(&db);
	Account* account = this->accountBook->GetAt(index);
	Date date = account->GetDate();
	CString date_;
	date_.Format("%4d-%02d-%02d", date.GetYear(), date.GetMonth(), date.GetDay());
	CString sql;
	sql.Format("SELECT account.code FROM account WHERE account.date='%s' ORDER BY code DESC;",(LPCTSTR)date_);
	db.OpenEx("DSN=accountBook;UID=root;PWD=Pagaous08217!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString number = "0000";
	if (!rs.IsEOF()) {
		rs.GetFieldValue((short)0, number);
	}
	int codeNumber = _ttoi(number.Right(4));
	codeNumber++;
	CString code;
	code.Format("%4d%02d%02d%04d",date.GetYear(),date.GetMonth(),date.GetDay(), codeNumber);
	rs.Close();
	db.Close();
	return code;
}

void AccountBookForm::Insert(Long index) {
	CDatabase db;
	Account* account = this->accountBook->GetAt(index);
	CString sql;
	CString code = MakeCode(index);
	Date date = account->GetDate(); 
	CString date_;
	date_.Format("%4d-%02d-%02d", date.GetYear(), date.GetMonth(), date.GetDay());
	Currency amount = account->GetAmount();
	
	
	CString amount_;
	amount_.Format("%.0f", amount);
	sql.Format("INSERT INTO account(code,date,contents,amount,note)"
		"VALUES('%s','%s','%s','%s','%s');",
		(LPCTSTR)code,
		(LPCTSTR)date_, account->GetContents().c_str(), (LPCTSTR)amount_, account->GetNote().c_str());
	db.OpenEx("DSN=accountBook;UID=root;PWD=Pagaous08217!");
	db.ExecuteSQL(sql);
	db.Close();
}

void AccountBookForm::Modify(Long index) {
	CDatabase db;
	CRecordset rs(&db);
	CString sql = "SELECT code FROM account;";
	db.OpenEx("DSN=accountBook;UID=root;PWD=Pagaous08217!");
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	CString code;
	int i = 0;
	while (!rs.IsEOF() && i <= index) {
		rs.GetFieldValue((short)0, code);
		rs.MoveNext();
		i++;
	}

	Account* account = this->accountBook->GetAt(index);
	Currency amount = account->GetAmount();


	CString amount_;
	amount_.Format("%.0f", amount);
	sql.Format("UPDATE account SET amount='%s',note='%s' WHERE code='%s';", (LPCTSTR)amount_, account->GetNote().c_str(), (LPCTSTR)code);
	db.ExecuteSQL(sql);
	rs.Close();
	db.Close();
}

void AccountBookForm::Save() {
	CDatabase db;
	CRecordset rs(&db);
	CString code;
	db.OpenEx("DSN=accountBook;UID=root;PWD=Pagaous08217!");
	CString sql = "SELECT code FROM account;";
	rs.Open(AFX_DB_USE_DEFAULT_TYPE, sql);
	sql = "DELETE FROM account;";
	db.ExecuteSQL(sql);
	int i = 0;
	while (i < this->accountBook->GetLength()) {
		rs.GetFieldValue((short)0, code);
		Account* account = this->accountBook->GetAt(i);
		Date date = account->GetDate();
			CString date_;
		date_.Format("%4d-%02d-%02d", date.GetYear(), date.GetMonth(), date.GetDay());
		Currency amount = account->GetAmount();
		
		CString amount_;
		amount_.Format("%.0f", amount);
		sql.Format("INSERT INTO account(code,date,contents,amount,note)"
			"VALUES('%s','%s','%s','%s','%s');",
			(LPCTSTR)code,
			(LPCTSTR)date_, account->GetContents().c_str(), (LPCTSTR)amount_, account->GetNote().c_str());
		db.ExecuteSQL(sql);
		rs.MoveNext();
		i++;
	}
	rs.Close();
	db.Close();
}