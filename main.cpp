#include <wx/wx.h>
#include <vector>
#include <map>
#include <string>
#include "GUI_Base.h"

struct Product {
    wxString name;
    double price;
    wxString imagePath;
};

std::map<wxString, wxString> registeredUsers;

std::vector<Product> myCart;

wxString FormatPrice(double price) {
    return wxString::Format("NT$ %.0f", price);
}

class MyPaymentFrame : public PaymentFrameBase
{
public:
    MyPaymentFrame(wxWindow* parent, double totalAmount) : PaymentFrameBase(parent)
    {
        m_lblFinalTotal->SetLabel("Total Amount: " + FormatPrice(totalAmount));
    }

    void OnConfirmClick(wxCommandEvent& event) override
    {
        wxString address = m_textCtrl4->GetValue();
        if (address.IsEmpty()) {
            wxMessageBox("Please enter your shipping address!", "Error", wxOK | wxICON_ERROR);
            return;
        }

        int paymentIndex = m_choicePayment->GetSelection();
        if (paymentIndex == 0 || paymentIndex == wxNOT_FOUND) {
            wxMessageBox("Please select a valid payment method!", "Error", wxOK | wxICON_ERROR);
            return;
        }

        wxMessageBox("Order Placed Successfully!\nThank you for shopping.", "Success", wxOK | wxICON_INFORMATION);
        myCart.clear();
        this->Destroy();
    }
};

class MyCartFrame : public CartFrameBase
{
public:
    MyCartFrame(wxWindow* parent) : CartFrameBase(parent)
    {
        m_cartList->InsertColumn(0, "Product Name", wxLIST_FORMAT_LEFT, 200);
        m_cartList->InsertColumn(1, "Price", wxLIST_FORMAT_RIGHT, 100);
        LoadCartItems();
    }

    void LoadCartItems()
    {
        m_cartList->DeleteAllItems();
        double total = 0;

        for (size_t i = 0; i < myCart.size(); i++) {
            long index = m_cartList->InsertItem(i, myCart[i].name);
            m_cartList->SetItem(index, 1, FormatPrice(myCart[i].price));
            total += myCart[i].price;
        }
        this->SetTitle(wxString::Format("Shopping Cart (%d items) - Total: %s", (int)myCart.size(), FormatPrice(total)));
    }

    void OnRemoveClick(wxCommandEvent& event) override
    {
        long itemIndex = -1;
        itemIndex = m_cartList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

        if (itemIndex != -1) {
            myCart.erase(myCart.begin() + itemIndex);
            LoadCartItems();
            wxMessageBox("Item removed.", "Info", wxOK | wxICON_INFORMATION);
        }
        else {
            wxMessageBox("Please select an item to remove.", "Warning", wxOK | wxICON_WARNING);
        }
    }

    void OnPayClick(wxCommandEvent& event) override
    {
        if (myCart.empty()) {
            wxMessageBox("Your cart is empty!", "Error", wxOK | wxICON_WARNING);
            return;
        }
        double total = 0;
        for (const auto& p : myCart) total += p.price;

        MyPaymentFrame* payFrame = new MyPaymentFrame(NULL, total);
        payFrame->Show(true);
        this->Close();
    }
};

class MyMainFrame : public MainFrameBase
{
private:

    std::vector<Product> inventory;

public:
    MyMainFrame(wxWindow* parent) : MainFrameBase(parent)
    {
        wxInitAllImageHandlers();
        this->SetTitle("Indonesian Perfume Store (Taiwan Branch)");

        AddToInventory("Mykonos - Aphrodite", 450.00, "mykonos.jpg");
        AddToInventory("HMNS - Orgsm", 480.00, "hmns.jpg");
        AddToInventory("Saff & Co - S.O.T.B", 520.00, "saff.jpg");
        AddToInventory("Carl & Claire - Black", 390.00, "carl.jpg");
        AddToInventory("Oullu - Deep Dive", 410.00, "oullu.jpg");
        AddToInventory("Fordive - Atlantis", 350.00, "fordive.jpg");
        AddToInventory("Onix - Scorpio", 290.00, "onix.jpg");
        AddToInventory("Humans - Dark Rose", 460.00, "humans.jpg");

        DisplayProducts("");
    }

    void AddToInventory(wxString name, double price, wxString imagePath) {
        Product p;
        p.name = name;
        p.price = price;
        p.imagePath = imagePath;
        inventory.push_back(p);
    }

    void DisplayProducts(wxString query)
    {
        wxSizer* grid = m_scrolledWindow->GetSizer();

        grid->Clear(true);

        wxString lowerQuery = query.Lower();

        for (const auto& p : inventory) {

            if (query.IsEmpty() || p.name.Lower().Contains(lowerQuery)) {

                wxPanel* card = new wxPanel(m_scrolledWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER);
                card->SetBackgroundColour(*wxWHITE);
                wxBoxSizer* vSizer = new wxBoxSizer(wxVERTICAL);

                wxImage image;
                if (image.LoadFile(p.imagePath, wxBITMAP_TYPE_ANY)) {
                    image.Rescale(120, 120, wxIMAGE_QUALITY_HIGH);
                    wxBitmap bitmap(image);
                    wxStaticBitmap* imgCtrl = new wxStaticBitmap(card, wxID_ANY, bitmap);
                    vSizer->Add(imgCtrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
                }
                else {
                    wxPanel* placeholder = new wxPanel(card, wxID_ANY, wxDefaultPosition, wxSize(120, 120));
                    placeholder->SetBackgroundColour(wxColour(230, 230, 230));
                    vSizer->Add(placeholder, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
                    wxStaticText* noImg = new wxStaticText(card, wxID_ANY, "No Image");
                    vSizer->Add(noImg, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 0);
                }

                wxStaticText* lblName = new wxStaticText(card, wxID_ANY, p.name);
                lblName->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
                lblName->Wrap(150);
                vSizer->Add(lblName, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

                wxStaticText* lblPrice = new wxStaticText(card, wxID_ANY, FormatPrice(p.price));
                lblPrice->SetForegroundColour(wxColour(0, 100, 0));
                vSizer->Add(lblPrice, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

                wxButton* btnAdd = new wxButton(card, wxID_ANY, "Add to Cart");
                vSizer->Add(btnAdd, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);

                wxString pName = p.name;
                double pPrice = p.price;

                btnAdd->Bind(wxEVT_BUTTON, [=](wxCommandEvent&) {
                    Product cartItem;
                    cartItem.name = pName;
                    cartItem.price = pPrice;
                    myCart.push_back(cartItem);
                    m_btnViewCart->SetLabel(wxString::Format("My Cart (%d)", (int)myCart.size()));
                    wxMessageBox(pName + " added to cart!", "Success", wxOK | wxICON_INFORMATION);
                    });

                card->SetSizer(vSizer);
                grid->Add(card, 0, wxEXPAND | wxALL, 10);
            }
        }

        m_scrolledWindow->Layout();
    }

    void OnViewCartClick(wxCommandEvent& event) override
    {
        MyCartFrame* cartFrame = new MyCartFrame(NULL);
        cartFrame->Show(true);
    }

    void OnSearchClick(wxCommandEvent& event) override
    {
        wxString query = m_searchBar->GetValue();
        DisplayProducts(query);
    }
};

class MyLoginFrame : public LoginFrameBase
{
public:
    MyLoginFrame(wxWindow* parent) : LoginFrameBase(parent)
    {
        registeredUsers["admin"] = "admin";
        m_btnRegister->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyLoginFrame::OnRegisterClicked), NULL, this);
    }

    void OnLoginClicked(wxCommandEvent& event) override
    {
        wxString user = m_textCtrl1->GetValue();
        wxString pass = m_textPass->GetValue();

        if (registeredUsers.count(user) && registeredUsers[user] == pass) {
            wxMessageBox("Login Successful!", "Welcome", wxOK);
            MyMainFrame* mainWin = new MyMainFrame(NULL);
            mainWin->Show(true);
            this->Close();
        }
        else {
            wxMessageBox("Invalid Username or Password", "Error", wxOK | wxICON_ERROR);
        }
    }

    void OnRegisterClicked(wxCommandEvent& event)
    {
        wxString user = m_textCtrl1->GetValue();
        wxString pass = m_textPass->GetValue();

        if (user.IsEmpty() || pass.IsEmpty()) {
            wxMessageBox("Fields cannot be empty", "Error", wxOK | wxICON_ERROR);
            return;
        }
        if (registeredUsers.count(user)) {
            wxMessageBox("User already exists!", "Error", wxOK | wxICON_ERROR);
        }
        else {
            registeredUsers[user] = pass;
            wxMessageBox("Registration Successful! Please Login.", "Info", wxOK);
        }
    }
};

class PerfumeApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        MyLoginFrame* frame = new MyLoginFrame(NULL);
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(PerfumeApp);