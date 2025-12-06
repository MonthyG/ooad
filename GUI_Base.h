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

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class LoginFrameBase
///////////////////////////////////////////////////////////////////////////////
class LoginFrameBase : public wxFrame
{
	private:

	protected:
		wxStaticText* m_staticText3;
		wxStaticText* m_staticText4;
		wxTextCtrl* m_textUser;
		wxStaticText* m_textPass;
		wxTextCtrl* m_textCtrl4;
		wxButton* m_btnLogin;
		wxButton* m_btnRegister;

		// Virtual event handlers, override them in your derived class
		virtual void OnLoginClicked( wxCommandEvent& event ) { event.Skip(); }


	public:

		LoginFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Login to Web Perfume"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 476,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

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
		wxGridSizer* m_productGrid; // <--- IT MUST BE HERE!

	public:

		MainFrameBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Main Menu"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainFrameBase();

};

