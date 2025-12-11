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

	m_btnMyOrders = new wxButton(this, wxID_ANY, _("My Orders"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer4->Add(m_btnMyOrders, 0, wxALL, 5);


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
	m_btnMyOrders->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrameBase::OnViewOrdersClick), NULL, this);
}

MainFrameBase::~MainFrameBase()
{
}

CartFrameBase::CartFrameBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxVERTICAL);

	m_scrolledCartItems = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_scrolledCartItems->SetScrollRate(0, 20);
	bSizer5->Add(m_scrolledCartItems, 1, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxVERTICAL);

	m_staticline2 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer9->Add(m_staticline2, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText13 = new wxStaticText(this, wxID_ANY, _("Total:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText13->Wrap(-1);
	m_staticText13->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));

	bSizer10->Add(m_staticText13, 0, wxALL, 5);

	m_lblTotal = new wxStaticText(this, wxID_ANY, _("$0"), wxDefaultPosition, wxDefaultSize, 0);
	m_lblTotal->Wrap(-1);
	m_lblTotal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));

	bSizer10->Add(m_lblTotal, 0, wxALL, 5);


	bSizer9->Add(bSizer10, 0, wxALIGN_CENTER_HORIZONTAL, 5);

	m_btnCheckout = new wxButton(this, wxID_ANY, _("Proceed to Checkout"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer9->Add(m_btnCheckout, 0, wxALL | wxEXPAND, 10);


	bSizer5->Add(bSizer9, 0, wxEXPAND, 5);


	this->SetSizer(bSizer5);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_btnCheckout->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CartFrameBase::OnPayClick), NULL, this);
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

	m_lblFinalTotal = new wxStaticText(this, wxID_ANY, _("Calculated at checkout..."), wxDefaultPosition, wxDefaultSize, 0);
	m_lblFinalTotal->Wrap(-1);
	m_lblFinalTotal->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));

	bSizer7->Add(m_lblFinalTotal, 0, wxALL, 5);

	m_staticText8 = new wxStaticText(this, wxID_ANY, _("Select Payment Method"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText8->Wrap(-1);
	bSizer7->Add(m_staticText8, 0, wxALL, 5);

	wxString m_choicePaymentChoices[] = { _("Select Payment Method..."), _("Bank Transfer"), _("Cash On Delivery"), _("E-Wallet"), _("Credit Card (+5% Fee)"), wxEmptyString, wxEmptyString };
	int m_choicePaymentNChoices = sizeof(m_choicePaymentChoices) / sizeof(wxString);
	m_choicePayment = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choicePaymentNChoices, m_choicePaymentChoices, 0);
	m_choicePayment->SetSelection(0);
	bSizer7->Add(m_choicePayment, 0, wxALL | wxEXPAND, 5);

	m_staticText9 = new wxStaticText(this, wxID_ANY, _("Shipping Address:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText9->Wrap(-1);
	bSizer7->Add(m_staticText9, 0, wxALL, 5);

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer(0, 2, 10, 10);
	fgSizer1->AddGrowableCol(1);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_staticText10 = new wxStaticText(this, wxID_ANY, _("Street Address:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText10->Wrap(-1);
	fgSizer1->Add(m_staticText10, 0, wxALL, 5);

	m_txtStreet = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1->Add(m_txtStreet, 0, wxALL | wxEXPAND, 5);

	m_staticText11 = new wxStaticText(this, wxID_ANY, _("City:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText11->Wrap(-1);
	fgSizer1->Add(m_staticText11, 0, wxALL, 5);

	m_txtCity = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1->Add(m_txtCity, 0, wxALL | wxEXPAND, 5);

	m_staticText12 = new wxStaticText(this, wxID_ANY, _("Zip Code:"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText12->Wrap(-1);
	fgSizer1->Add(m_staticText12, 0, wxALL, 5);

	m_txtZip = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1->Add(m_txtZip, 0, wxALL | wxEXPAND, 5);


	bSizer7->Add(fgSizer1, 1, wxEXPAND, 5);

	m_btnConfirmOrder = new wxButton(this, wxID_ANY, _("PLACE ORDER"), wxDefaultPosition, wxDefaultSize, 0);
	m_btnConfirmOrder->SetFont(wxFont(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
	m_btnConfirmOrder->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
	m_btnConfirmOrder->SetBackgroundColour(wxColour(0, 255, 0));

	bSizer7->Add(m_btnConfirmOrder, 0, wxALL, 5);


	this->SetSizer(bSizer7);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_choicePayment->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(PaymentFrameBase::OnMethodChange), NULL, this);
	m_btnConfirmOrder->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PaymentFrameBase::OnConfirmClick), NULL, this);
}

PaymentFrameBase::~PaymentFrameBase()
{
}

ProductDetailsFrameBase::ProductDetailsFrameBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer(wxHORIZONTAL);

	m_bmpProduct = new wxStaticBitmap(this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0);
	bSizer12->Add(m_bmpProduct, 0, wxALL | wxEXPAND, 5);

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer(wxVERTICAL);

	m_lblTitle = new wxStaticText(this, wxID_ANY, _("Product Name"), wxDefaultPosition, wxDefaultSize, 0);
	m_lblTitle->Wrap(-1);
	m_lblTitle->SetFont(wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));

	bSizer13->Add(m_lblTitle, 0, wxALL, 5);

	m_lblPrice = new wxStaticText(this, wxID_ANY, _("$0.00"), wxDefaultPosition, wxDefaultSize, 0);
	m_lblPrice->Wrap(-1);
	m_lblPrice->SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));

	bSizer13->Add(m_lblPrice, 0, wxALL, 5);

	m_btnAddCart = new wxButton(this, wxID_ANY, _("Add to Cart"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer13->Add(m_btnAddCart, 0, wxTOP, 10);


	bSizer12->Add(bSizer13, 1, wxEXPAND, 5);


	bSizer11->Add(bSizer12, 1, wxEXPAND, 5);

	m_staticline3 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
	bSizer11->Add(m_staticline3, 0, wxEXPAND | wxALL, 5);

	m_staticText17 = new wxStaticText(this, wxID_ANY, _("Description"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText17->Wrap(-1);
	bSizer11->Add(m_staticText17, 0, wxALL, 5);

	m_txtDesc = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	bSizer11->Add(m_txtDesc, 1, wxALL | wxEXPAND, 5);


	this->SetSizer(bSizer11);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_btnAddCart->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ProductDetailsFrameBase::OnAddClick), NULL, this);
}

ProductDetailsFrameBase::~ProductDetailsFrameBase()
{
}

OrderHistoryFrameBase::OrderHistoryFrameBase(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer(wxVERTICAL);

	m_scrolledOrderHistory = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL | wxVSCROLL);
	m_scrolledOrderHistory->SetScrollRate(0, 10);
	bSizer12->Add(m_scrolledOrderHistory, 1, wxEXPAND | wxALL, 5);


	this->SetSizer(bSizer12);
	this->Layout();

	this->Centre(wxBOTH);
}

OrderHistoryFrameBase::~OrderHistoryFrameBase()
{
}
