///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI_Base.h"

///////////////////////////////////////////////////////////////////////////

LoginFrameBase::LoginFrameBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxVERTICAL);

	m_staticText1 = new wxStaticText(this, wxID_ANY, _("WELCOME USER"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	m_staticText1->SetFont(wxFont(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));

	bSizer1->Add(m_staticText1, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	m_staticText2 = new wxStaticText(this, wxID_ANY, _("Username"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	bSizer1->Add(m_staticText2, 0, wxALL, 5);

	m_textCtrl1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer1->Add(m_textCtrl1, 0, wxALL | wxEXPAND, 5);

	m_staticText3 = new wxStaticText(this, wxID_ANY, _("Password"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);
	bSizer1->Add(m_staticText3, 0, wxALL, 5);

	m_textPass = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
	bSizer1->Add(m_textPass, 0, wxALL | wxEXPAND, 5);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);

	m_btnLogin = new wxButton(this, wxID_ANY, _("Login"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_btnLogin, 0, wxALL, 5);

	m_btnRegister = new wxButton(this, wxID_ANY, _("Register"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer2->Add(m_btnRegister, 0, wxALL, 5);


	bSizer1->Add(bSizer2, 1, wxEXPAND, 5);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_btnLogin->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LoginFrameBase::OnLoginClicked), NULL, this);
}

LoginFrameBase::~LoginFrameBase()
{
}

MainFrameBase::MainFrameBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxHORIZONTAL);

	m_searchBar = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_searchBar, 0, wxALL, 5);

	m_btnSearch = new wxButton(this, wxID_ANY, _("Search"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_btnSearch, 0, wxALL, 5);

	m_btnViewCart = new wxButton(this, wxID_ANY, _("My Cart"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_btnViewCart, 0, wxALL, 5);


	bSizer3->Add(bSizer4, 0, wxEXPAND, 10);

	m_scrolledWindow = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_scrolledWindow->SetScrollRate(0, 20);
	wxGridSizer* m_productGrid;
	m_productGrid = new wxGridSizer(0, 3, 20, 20);


	m_scrolledWindow->SetSizer(m_productGrid);
	m_scrolledWindow->Layout();
	m_productGrid->Fit(m_scrolledWindow);
	bSizer3->Add(m_scrolledWindow, 1, wxEXPAND | wxALL, 5);


	this->SetSizer(bSizer3);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_btnSearch->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::OnSearchClick), NULL, this);
	m_btnViewCart->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::OnViewCartClick), NULL, this);
}

MainFrameBase::~MainFrameBase()
{
}

CartFrameBase::CartFrameBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxVERTICAL);

	m_cartList = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_SINGLE_SEL);
	bSizer5->Add(m_cartList, 1, wxALL | wxEXPAND, 5);

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxHORIZONTAL);

	m_btnPay = new wxButton(this, wxID_ANY, _("Proceed to Checkout"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer6->Add(m_btnPay, 0, wxALL, 5);

	m_btnRemove = new wxButton(this, wxID_ANY, _("Remove Selected Item"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer6->Add(m_btnRemove, 0, wxALL, 5);


	bSizer5->Add(bSizer6, 0, wxALIGN_CENTER_HORIZONTAL, 5);


	this->SetSizer(bSizer5);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_btnPay->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CartFrameBase::OnPayClick), NULL, this);
	m_btnRemove->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CartFrameBase::OnRemoveClick), NULL, this);
}

CartFrameBase::~CartFrameBase()
{
}

PaymentFrameBase::PaymentFrameBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxVERTICAL);

	m_staticText6 = new wxStaticText(this, wxID_ANY, _("Payment Confirmation"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText6->Wrap(-1);
	m_staticText6->SetFont(wxFont(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));

	bSizer7->Add(m_staticText6, 0, wxALL, 5);

	m_lblFinalTotal = new wxStaticText(this, wxID_ANY, _("Total Amount: $0"), wxDefaultPosition, wxDefaultSize, 0);
	m_lblFinalTotal->Wrap(-1);
	bSizer7->Add(m_lblFinalTotal, 0, wxALL, 5);

	m_staticText8 = new wxStaticText(this, wxID_ANY, _("Select Payment Method"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText8->Wrap(-1);
	bSizer7->Add(m_staticText8, 0, wxALL, 5);

	wxString m_choicePaymentChoices[] = { _("..."), _("Bank Transfer"), _("Cash On Delivery"), _("E-Wallet"), _("Credit Card"), wxEmptyString };
	int m_choicePaymentNChoices = sizeof(m_choicePaymentChoices) / sizeof(wxString);
	m_choicePayment = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choicePaymentNChoices, m_choicePaymentChoices, 0);
	m_choicePayment->SetSelection(0);
	bSizer7->Add(m_choicePayment, 0, wxALL | wxEXPAND, 5);

	m_staticText9 = new wxStaticText(this, wxID_ANY, _("Shipping Address:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText9->Wrap(-1);
	bSizer7->Add(m_staticText9, 0, wxALL, 5);

	m_textCtrl4 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	bSizer7->Add(m_textCtrl4, 0, wxALL | wxEXPAND, 5);

	m_btnConfirmOrder = new wxButton(this, wxID_ANY, _("PLACE ORDER"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(m_btnConfirmOrder, 0, wxALL, 5);


	this->SetSizer(bSizer7);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_btnConfirmOrder->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PaymentFrameBase::OnConfirmClick), NULL, this);
}

PaymentFrameBase::~PaymentFrameBase()
{
}
