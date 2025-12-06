///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI_Base.h"

///////////////////////////////////////////////////////////////////////////

LoginFrameBase::LoginFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_staticText3 = new wxStaticText( this, wxID_ANY, _("WELCOME USER"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	m_staticText3->SetFont( wxFont( 9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer3->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticText4 = new wxStaticText( this, wxID_ANY, _("Username"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer3->Add( m_staticText4, 0, wxALL, 5 );

	m_textUser = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( m_textUser, 0, wxALL|wxEXPAND, 5 );

	m_textPass = new wxStaticText( this, wxID_ANY, _("Password"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textPass->Wrap( -1 );
	bSizer3->Add( m_textPass, 0, wxALL, 5 );

	m_textCtrl4 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	bSizer3->Add( m_textCtrl4, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_btnLogin = new wxButton( this, wxID_ANY, _("Login"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_btnLogin, 0, wxALL, 5 );

	m_btnRegister = new wxButton( this, wxID_ANY, _("Register"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_btnRegister, 0, wxALL, 5 );


	bSizer3->Add( bSizer4, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer3 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_btnLogin->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( LoginFrameBase::OnLoginClicked ), NULL, this );
}

LoginFrameBase::~LoginFrameBase()
{
}

MainFrameBase::MainFrameBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	m_searchBar = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_searchBar, 0, wxALL, 5 );

	m_btnSearch = new wxButton( this, wxID_ANY, _("Search"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_btnSearch, 0, wxALL, 5 );

	m_btnViewCart = new wxButton( this, wxID_ANY, _("My Cart (0)"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_btnViewCart, 0, wxALL, 5 );


	bSizer5->Add( bSizer6, 0, wxEXPAND, 10 );

	m_scrolledWindow = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow->SetScrollRate( 0, 20 );
	wxGridSizer* m_productGrid;
	m_productGrid = new wxGridSizer( 0, 3, 20, 20 );


	m_scrolledWindow->SetSizer( m_productGrid );
	m_scrolledWindow->Layout();
	m_productGrid->Fit( m_scrolledWindow );
	bSizer5->Add( m_scrolledWindow, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer5 );
	this->Layout();

	this->Centre( wxBOTH );
}

MainFrameBase::~MainFrameBase()
{
}
