///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/scrolwin.h>
#include <wx/listctrl.h>
#include <wx/choice.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class LoginFrameBase
///////////////////////////////////////////////////////////////////////////////
class LoginFrameBase : public wxFrame
{
private:

protected:
	wxStaticText* m_staticText1;
	wxStaticText* m_staticText2;
	wxTextCtrl* m_textCtrl1;
	wxStaticText* m_staticText3;
	wxTextCtrl* m_textPass;
	wxButton* m_btnLogin;
	wxButton* m_btnRegister;

	// Virtual event handlers, override them in your derived class
	virtual void OnLoginClicked(wxCommandEvent& event) { event.Skip(); }


public:

	LoginFrameBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Login Perfume Store"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 300), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~LoginFrameBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrameBase
///////////////////////////////////////////////////////////////////////////////
class MainFrameBase : public wxFrame
{
private:

protected:
	wxTextCtrl* m_searchBar;
	wxButton* m_btnSearch;
	wxButton* m_btnViewCart;
	wxScrolledWindow* m_scrolledWindow;

	// Virtual event handlers, override them in your derived class
	virtual void OnSearchClick(wxCommandEvent& event) { event.Skip(); }
	virtual void OnViewCartClick(wxCommandEvent& event) { event.Skip(); }


public:

	MainFrameBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Perfume Store - Main Menu"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(800, 600), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~MainFrameBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class CartFrameBase
///////////////////////////////////////////////////////////////////////////////
class CartFrameBase : public wxFrame
{
private:

protected:
	wxListCtrl* m_cartList;
	wxButton* m_btnPay;
	wxButton* m_btnRemove;

	// Virtual event handlers, override them in your derived class
	virtual void OnPayClick(wxCommandEvent& event) { event.Skip(); }
	virtual void OnRemoveClick(wxCommandEvent& event) { event.Skip(); }


public:

	CartFrameBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Shopping Cart"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(600, 400), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~CartFrameBase();

};

///////////////////////////////////////////////////////////////////////////////
/// Class PaymentFrameBase
///////////////////////////////////////////////////////////////////////////////
class PaymentFrameBase : public wxFrame
{
private:

protected:
	wxStaticText* m_staticText6;
	wxStaticText* m_lblFinalTotal;
	wxStaticText* m_staticText8;
	wxChoice* m_choicePayment;
	wxStaticText* m_staticText9;
	wxTextCtrl* m_textCtrl4;
	wxButton* m_btnConfirmOrder;

	// Virtual event handlers, override them in your derived class
	virtual void OnConfirmClick(wxCommandEvent& event) { event.Skip(); }


public:

	PaymentFrameBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Checkout & Payment"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400, 500), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~PaymentFrameBase();

};

