//AccountBookApp.cpp
#include "accountBookApp.h"
#include "accountBookForm.h"

AccountBookApp accountBookApp;
BOOL AccountBookApp::InitInstance() {
	AccountBookForm accountBookForm;
	this->m_pMainWnd = &accountBookForm;
	accountBookForm.DoModal();
	return TRUE;
}