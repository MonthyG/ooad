#include <wx/wx.h>
#include <wx/msgdlg.h>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include "GUI_Base.h"

struct Variant {
    wxString sizeName;
    double price;
};

struct Product {
    wxString name;
    std::vector<Variant> variants;
    wxString imagePath;
    wxString description;
};

struct CartEntry {
    Product product;
    int variantIndex;
    int quantity;
    bool isSelected;
};

struct Order {
    int orderId;
    std::vector<CartEntry> items;
    double totalPaid;
    wxString paymentMethod;
    wxString date;
};

struct User {
    wxString username;
    wxString password;
};

std::vector<Product> g_inventory;
std::vector<CartEntry> g_cart;
std::vector<Order> g_orderHistory;
std::vector<User> g_registeredUsers;
User* g_currentUser = nullptr;

wxString FormatPrice(double price) {
    wxString s = wxString::Format("%.0f", price);
    int len = s.Length();
    if (len > 3) {
        for (int i = len - 3; i > 0; i -= 3) {
            s.insert(i, ",");
        }
    }
    return "NT$ " + s;
}

class OrderHistoryInterface : public OrderHistoryFrameBase {
public:
    using OrderHistoryFrameBase::OrderHistoryFrameBase;
};

class PaymentInterface : public PaymentFrameBase {
public:
    using PaymentFrameBase::PaymentFrameBase;
protected:
    virtual void OnMethodChange(wxCommandEvent& event) override = 0;
    virtual void OnConfirmClick(wxCommandEvent& event) override = 0;
};

class LoginInterface : public LoginFrameBase {
public:
    using LoginFrameBase::LoginFrameBase;
protected:
    virtual void OnLoginClicked(wxCommandEvent& event) override = 0;
};

class CartInterface : public CartFrameBase {
public:
    using CartFrameBase::CartFrameBase;
protected:
    virtual void OnPayClick(wxCommandEvent& event) override = 0;
};

class ProductDetailsInterface : public ProductDetailsFrameBase {
public:
    using ProductDetailsFrameBase::ProductDetailsFrameBase;
protected:
    virtual void OnAddClick(wxCommandEvent& event) override = 0;
};

class MainFrameInterface : public MainFrameBase {
public:
    using MainFrameBase::MainFrameBase;
protected:
    virtual void OnSearchClick(wxCommandEvent& event) override = 0;
    virtual void OnViewCartClick(wxCommandEvent& event) override = 0;
    virtual void OnViewOrdersClick(wxCommandEvent& event) override = 0;
};


class OrderHistoryFrame : public OrderHistoryInterface {
public:
    OrderHistoryFrame(wxWindow* parent) : OrderHistoryInterface(parent) {
        this->SetTitle("My Order History");
        PopulateHistory();
    }

    void PopulateHistory() {
        wxSizer* sizer = m_scrolledOrderHistory->GetSizer();
        if (!sizer) {
            sizer = new wxBoxSizer(wxVERTICAL);
            m_scrolledOrderHistory->SetSizer(sizer);
        }
        sizer->Clear(true);

        if (g_orderHistory.empty()) {
            wxStaticText* lbl = new wxStaticText(m_scrolledOrderHistory, wxID_ANY, "No orders found.");
            sizer->Add(lbl, 0, wxALL | wxALIGN_CENTER, 20);
        }
        else {
            for (int i = g_orderHistory.size() - 1; i >= 0; i--) {
                const Order& ord = g_orderHistory[i];

                wxPanel* pOrd = new wxPanel(m_scrolledOrderHistory, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME);
                pOrd->SetBackgroundColour(*wxWHITE);
                wxBoxSizer* ordSizer = new wxBoxSizer(wxVERTICAL);

                wxString titleStr = wxString::Format("Order #%d  |  %s", ord.orderId, ord.date);
                wxStaticText* lblTitle = new wxStaticText(pOrd, wxID_ANY, titleStr);
                lblTitle->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
                lblTitle->SetForegroundColour(wxColour(0, 50, 150));
                ordSizer->Add(lblTitle, 0, wxALL, 8);

                for (const auto& item : ord.items) {
                    wxBoxSizer* row = new wxBoxSizer(wxHORIZONTAL);
                    wxImage img;
                    if (wxFileExists(item.product.imagePath) && img.LoadFile(item.product.imagePath)) {
                        img.Rescale(40, 40, wxIMAGE_QUALITY_HIGH);
                        wxStaticBitmap* bmp = new wxStaticBitmap(pOrd, wxID_ANY, wxBitmap(img));
                        row->Add(bmp, 0, wxRIGHT, 10);
                    }
                    wxString desc = wxString::Format("%s (%s) x%d", item.product.name, item.product.variants[item.variantIndex].sizeName, item.quantity);
                    wxStaticText* lblDesc = new wxStaticText(pOrd, wxID_ANY, desc);
                    row->Add(lblDesc, 1, wxALIGN_CENTER_VERTICAL);
                    ordSizer->Add(row, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
                }

                wxStaticLine* line = new wxStaticLine(pOrd);
                ordSizer->Add(line, 0, wxEXPAND | wxALL, 5);

                wxBoxSizer* footer = new wxBoxSizer(wxHORIZONTAL);
                footer->Add(new wxStaticText(pOrd, wxID_ANY, "Payment: " + ord.paymentMethod), 1, wxLEFT, 8);
                wxStaticText* total = new wxStaticText(pOrd, wxID_ANY, FormatPrice(ord.totalPaid));
                total->SetFont(wxFont(11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
                footer->Add(total, 0, wxRIGHT, 8);

                ordSizer->Add(footer, 0, wxEXPAND | wxBOTTOM, 8);
                pOrd->SetSizer(ordSizer);
                sizer->Add(pOrd, 0, wxEXPAND | wxALL, 10);
            }
        }
        m_scrolledOrderHistory->Layout();
        m_scrolledOrderHistory->FitInside();
    }
};

class PaymentFrame : public PaymentInterface {
    wxScrolledWindow* m_scrollOrderSummary;
    wxPanel* m_panelCC;
    wxPanel* m_panelBank;
    wxWindow* m_originCartWindow;
    wxTextCtrl* m_txtCCNumber;
    wxTextCtrl* m_txtCCExpiry;
    wxTextCtrl* m_txtCCCVV;

public:
    PaymentFrame(wxWindow* parent, wxWindow* originCartWindow = nullptr)
        : PaymentInterface(parent), m_originCartWindow(originCartWindow)
    {
        this->SetSize(500, 750);
        wxSizer* mainSizer = this->GetSizer();

        m_scrollOrderSummary = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 200), wxVSCROLL);
        m_scrollOrderSummary->SetScrollRate(0, 10);
        m_scrollOrderSummary->SetBackgroundColour(wxColour(245, 245, 245));

        wxBoxSizer* summarySizer = new wxBoxSizer(wxVERTICAL);
        for (const auto& item : g_cart) {
            if (item.isSelected) {
                wxPanel* pItem = new wxPanel(m_scrollOrderSummary, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
                pItem->SetBackgroundColour(*wxWHITE);
                wxBoxSizer* itemSizer = new wxBoxSizer(wxHORIZONTAL);
                wxImage img;
                if (wxFileExists(item.product.imagePath) && img.LoadFile(item.product.imagePath)) {
                    img.Rescale(50, 50, wxIMAGE_QUALITY_HIGH);
                    itemSizer->Add(new wxStaticBitmap(pItem, wxID_ANY, wxBitmap(img)), 0, wxALL, 5);
                }
                wxBoxSizer* infoSizer = new wxBoxSizer(wxVERTICAL);
                wxStaticText* name = new wxStaticText(pItem, wxID_ANY, item.product.name);
                name->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
                wxString variantStr = item.product.variants[item.variantIndex].sizeName;
                infoSizer->Add(name, 0, wxBOTTOM, 2);
                infoSizer->Add(new wxStaticText(pItem, wxID_ANY, variantStr + " x " + std::to_string(item.quantity)), 0, wxBOTTOM, 2);
                itemSizer->Add(infoSizer, 1, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);

                double lineTotal = item.product.variants[item.variantIndex].price * item.quantity;
                itemSizer->Add(new wxStaticText(pItem, wxID_ANY, FormatPrice(lineTotal)), 0, wxALIGN_CENTER_VERTICAL | wxALL, 10);
                pItem->SetSizer(itemSizer);
                summarySizer->Add(pItem, 0, wxEXPAND | wxALL, 3);
            }
        }
        m_scrollOrderSummary->SetSizer(summarySizer);
        summarySizer->Fit(m_scrollOrderSummary);
        mainSizer->Insert(1, m_scrollOrderSummary, 1, wxEXPAND | wxALL, 10);

        m_panelCC = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME);
        wxBoxSizer* ccSizer = new wxBoxSizer(wxVERTICAL);
        ccSizer->Add(new wxStaticText(m_panelCC, wxID_ANY, "Card Number:"), 0, wxTOP | wxLEFT, 5);
        m_txtCCNumber = new wxTextCtrl(m_panelCC, wxID_ANY);
        ccSizer->Add(m_txtCCNumber, 0, wxEXPAND | wxALL, 5);
        wxBoxSizer* ccRow = new wxBoxSizer(wxHORIZONTAL);
        ccRow->Add(new wxStaticText(m_panelCC, wxID_ANY, "Exp (MM/YY):"), 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);
        m_txtCCExpiry = new wxTextCtrl(m_panelCC, wxID_ANY, "", wxDefaultPosition, wxSize(60, -1));
        ccRow->Add(m_txtCCExpiry, 0, wxLEFT | wxRIGHT, 5);
        ccRow->Add(new wxStaticText(m_panelCC, wxID_ANY, "CVV:"), 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
        m_txtCCCVV = new wxTextCtrl(m_panelCC, wxID_ANY, "", wxDefaultPosition, wxSize(40, -1));
        ccRow->Add(m_txtCCCVV, 0, wxLEFT, 5);
        ccSizer->Add(ccRow, 0, wxEXPAND | wxBOTTOM, 5);
        m_panelCC->SetSizer(ccSizer);
        m_panelCC->Hide();

        m_panelBank = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME);
        m_panelBank->SetBackgroundColour(wxColour(240, 248, 255));
        wxBoxSizer* bankSizer = new wxBoxSizer(wxVERTICAL);
        wxStaticText* bankTitle = new wxStaticText(m_panelBank, wxID_ANY, "Bank Transfer Info");
        bankTitle->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        bankSizer->Add(bankTitle, 0, wxALL, 5);
        bankSizer->Add(new wxStaticText(m_panelBank, wxID_ANY, "Bank: BCA Digital\nNo: 123-456-789\nA/N: Perfume Store"), 0, wxALL, 5);
        m_panelBank->SetSizer(bankSizer);
        m_panelBank->Hide();

        mainSizer->Insert(5, m_panelBank, 0, wxEXPAND | wxALL, 5);
        mainSizer->Insert(6, m_panelCC, 0, wxEXPAND | wxALL, 5);

        this->Layout();
        UpdateTotal();
    }

    void UpdateTotal() {
        double subtotal = 0;
        for (const auto& item : g_cart) {
            if (item.isSelected) subtotal += item.product.variants[item.variantIndex].price * item.quantity;
        }
        if (m_choicePayment->GetSelection() == 4) subtotal *= 1.05;
        m_lblFinalTotal->SetLabel(FormatPrice(subtotal));
    }

protected:
    void OnMethodChange(wxCommandEvent& event) override {
        int sel = m_choicePayment->GetSelection();
        m_panelBank->Hide(); m_panelCC->Hide();
        if (sel == 1) m_panelBank->Show();
        else if (sel == 4) m_panelCC->Show();
        this->Layout(); UpdateTotal();
    }

    void OnConfirmClick(wxCommandEvent& event) override {
        int methodIdx = m_choicePayment->GetSelection();
        if (methodIdx == 0) { wxMessageBox("Select payment method!", "Error"); return; }
        if (m_txtStreet->GetValue().IsEmpty() || m_txtCity->GetValue().IsEmpty()) { wxMessageBox("Fill address!", "Error"); return; }
        if (methodIdx == 4 && m_txtCCNumber->GetValue().IsEmpty()) { wxMessageBox("Fill CC Info!", "Error"); return; }

        Order newOrder;
        newOrder.orderId = rand() % 90000 + 10000;
        newOrder.paymentMethod = m_choicePayment->GetString(methodIdx);
        time_t now = time(0);
        newOrder.date = wxString(ctime(&now)).Trim();

        double totalPaid = 0;
        for (const auto& item : g_cart) {
            if (item.isSelected) {
                newOrder.items.push_back(item);
                totalPaid += item.product.variants[item.variantIndex].price * item.quantity;
            }
        }
        if (methodIdx == 4) totalPaid *= 1.05;
        newOrder.totalPaid = totalPaid;
        g_orderHistory.push_back(newOrder);

        wxMessageBox("Order Success!", "Success");
        auto it = std::remove_if(g_cart.begin(), g_cart.end(), [](const CartEntry& item) { return item.isSelected; });
        g_cart.erase(it, g_cart.end());

        this->Close();
        if (m_originCartWindow) m_originCartWindow->Close();
    }
};

class LoginFrame : public LoginInterface {
    wxWindow* m_originCartWindow;
public:
    LoginFrame(wxWindow* parent, wxWindow* originCartWindow = nullptr)
        : LoginInterface(parent), m_originCartWindow(originCartWindow)
    {
        m_btnRegister->Bind(wxEVT_BUTTON, &LoginFrame::OnRegisterClicked, this);
    }

protected:
    void OnLoginClicked(wxCommandEvent& event) override {
        wxString user = m_textCtrl1->GetValue();
        wxString pass = m_textPass->GetValue();
        bool found = false;
        for (const auto& u : g_registeredUsers) {
            if (u.username == user && u.password == pass) { found = true; break; }
        }
        if (found) {
            g_currentUser = new User{ user, pass };
            wxMessageBox("Login Success!", "Welcome");
            PaymentFrame* payFrame = new PaymentFrame(NULL, m_originCartWindow);
            payFrame->Show();
            this->Close();
        }
        else {
            wxMessageBox("Invalid Login", "Error");
        }
    }

    void OnRegisterClicked(wxCommandEvent& event) {
        g_registeredUsers.push_back({ m_textCtrl1->GetValue(), m_textPass->GetValue() });
        wxMessageBox("Registered!", "Success");
    }
};

class CartFrame : public CartInterface {
public:
    CartFrame(wxWindow* parent) : CartInterface(parent) {
        if (m_scrolledCartItems->GetSizer() == nullptr) {
            m_scrolledCartItems->SetSizer(new wxBoxSizer(wxVERTICAL));
        }
        PopulateCart();
    }

    void UpdateTotalLabel() {
        double total = 0;
        for (const auto& item : g_cart) if (item.isSelected) total += item.product.variants[item.variantIndex].price * item.quantity;
        m_lblTotal->SetLabel(FormatPrice(total));
    }

    void PopulateCart() {
        wxSizer* sizer = m_scrolledCartItems->GetSizer();
        sizer->Clear(true);
        for (size_t i = 0; i < g_cart.size(); ++i) {
            wxPanel* rowPanel = new wxPanel(m_scrolledCartItems, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
            wxBoxSizer* rowSizer = new wxBoxSizer(wxHORIZONTAL);

            wxCheckBox* chk = new wxCheckBox(rowPanel, wxID_ANY, "");
            chk->SetValue(g_cart[i].isSelected);
            chk->Bind(wxEVT_CHECKBOX, [this, i](wxCommandEvent& evt) { g_cart[i].isSelected = evt.IsChecked(); UpdateTotalLabel(); });
            rowSizer->Add(chk, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

            wxImage img;
            if (wxFileExists(g_cart[i].product.imagePath) && img.LoadFile(g_cart[i].product.imagePath)) {
                img.Rescale(60, 60);
                rowSizer->Add(new wxStaticBitmap(rowPanel, wxID_ANY, wxBitmap(img)), 0, wxALL, 5);
            }

            wxBoxSizer* infoSizer = new wxBoxSizer(wxVERTICAL);
            infoSizer->Add(new wxStaticText(rowPanel, wxID_ANY, g_cart[i].product.name), 0, wxBOTTOM, 2);

            wxChoice* choiceSize = new wxChoice(rowPanel, wxID_ANY);
            for (const auto& v : g_cart[i].product.variants) choiceSize->Append(v.sizeName);
            choiceSize->SetSelection(g_cart[i].variantIndex);
            infoSizer->Add(choiceSize, 0, wxBOTTOM, 2);

            wxStaticText* priceLabel = new wxStaticText(rowPanel, wxID_ANY, FormatPrice(g_cart[i].product.variants[g_cart[i].variantIndex].price));
            infoSizer->Add(priceLabel, 0, wxALL, 0);

            choiceSize->Bind(wxEVT_CHOICE, [this, i, priceLabel](wxCommandEvent& evt) {
                int newIdx = evt.GetSelection();
                g_cart[i].variantIndex = newIdx;
                priceLabel->SetLabel(FormatPrice(g_cart[i].product.variants[newIdx].price));
                UpdateTotalLabel();
                });
            rowSizer->Add(infoSizer, 1, wxLEFT, 10);

            // Plus Minus buttons
            wxButton* btnMinus = new wxButton(rowPanel, wxID_ANY, "-", wxDefaultPosition, wxSize(30, 30));
            wxStaticText* txtQty = new wxStaticText(rowPanel, wxID_ANY, std::to_string(g_cart[i].quantity));
            wxButton* btnPlus = new wxButton(rowPanel, wxID_ANY, "+", wxDefaultPosition, wxSize(30, 30));

            btnMinus->Bind(wxEVT_BUTTON, [this, i](wxCommandEvent&) { if (g_cart[i].quantity > 1) g_cart[i].quantity--; else g_cart.erase(g_cart.begin() + i); PopulateCart(); });
            btnPlus->Bind(wxEVT_BUTTON, [this, i](wxCommandEvent&) { g_cart[i].quantity++; PopulateCart(); });

            rowSizer->Add(btnMinus); rowSizer->Add(txtQty); rowSizer->Add(btnPlus);
            rowPanel->SetSizer(rowSizer);
            sizer->Add(rowPanel, 0, wxEXPAND | wxALL, 5);
        }
        UpdateTotalLabel();
        m_scrolledCartItems->Layout();
        m_scrolledCartItems->FitInside();
    }

protected:
    void OnPayClick(wxCommandEvent& event) override {
        bool hasSelection = false;
        for (const auto& item : g_cart) if (item.isSelected) hasSelection = true;
        if (!hasSelection) { wxMessageBox("Select item first!", "Info"); return; }

        if (g_currentUser == nullptr) {
            LoginFrame* login = new LoginFrame(this);
            login->Show();
        }
        else {
            PaymentFrame* payFrame = new PaymentFrame(NULL, this);
            payFrame->Show();
        }
    }
};

class ProductDetailsFrame : public ProductDetailsInterface {
    Product m_product;
    wxChoice* m_choiceSize;
public:
    ProductDetailsFrame(wxWindow* parent, const Product& p) : ProductDetailsInterface(parent), m_product(p) {
        wxImage img;
        if (wxFileExists(m_product.imagePath) && img.LoadFile(m_product.imagePath)) {
            img.Rescale(200, 200, wxIMAGE_QUALITY_HIGH);
            m_bmpProduct->SetBitmap(wxBitmap(img));
        }
        m_lblTitle->SetLabel(m_product.name);
        m_txtDesc->SetValue(m_product.description);
        m_txtDesc->SetEditable(false);

        wxSizer* contentSizer = m_lblPrice->GetContainingSizer();
        contentSizer->Insert(2, new wxStaticText(this, wxID_ANY, "Select Size:"), 0, wxTOP, 5);
        m_choiceSize = new wxChoice(this, wxID_ANY);
        for (const auto& v : m_product.variants) m_choiceSize->Append(v.sizeName);
        m_choiceSize->SetSelection(0);
        contentSizer->Insert(3, m_choiceSize, 0, wxEXPAND | wxBOTTOM, 10);

        UpdatePriceLabel();
        m_choiceSize->Bind(wxEVT_CHOICE, [this](wxCommandEvent&) { UpdatePriceLabel(); });
        this->Layout();
    }

    void UpdatePriceLabel() {
        int sel = m_choiceSize->GetSelection();
        if (sel != wxNOT_FOUND) m_lblPrice->SetLabel(FormatPrice(m_product.variants[sel].price));
    }

protected:
    void OnAddClick(wxCommandEvent& event) override {
        int selectedIndex = m_choiceSize->GetSelection();
        if (selectedIndex == wxNOT_FOUND) return;
        bool found = false;
        for (auto& item : g_cart) {
            if (item.product.name == m_product.name && item.variantIndex == selectedIndex) {
                item.quantity++; found = true; break;
            }
        }
        if (!found) g_cart.push_back({ m_product, selectedIndex, 1, true });
        wxMessageBox("Added to cart!", "Success");
        this->Close();
    }
};

class MainFrame : public MainFrameInterface {
public:
    MainFrame() : MainFrameInterface(NULL) {
        PopulateGrid("");
    }

    void PopulateGrid(wxString search) {
        wxSizer* sizer = m_scrolledWindow->GetSizer();
        sizer->Clear(true);
        for (const auto& prod : g_inventory) {
            if (!search.IsEmpty() && prod.name.Lower().Find(search.Lower()) == wxNOT_FOUND) continue;

            wxPanel* card = new wxPanel(m_scrolledWindow, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
            wxBoxSizer* cardSizer = new wxBoxSizer(wxVERTICAL);

            wxImage img;
            wxBitmap displayBmp(120, 120);
            if (wxFileExists(prod.imagePath) && img.LoadFile(prod.imagePath)) {
                img.Rescale(120, 120); displayBmp = wxBitmap(img);
            }
            cardSizer->Add(new wxStaticBitmap(card, wxID_ANY, displayBmp), 0, wxALIGN_CENTER | wxALL, 5);

            wxStaticText* title = new wxStaticText(card, wxID_ANY, prod.name);
            title->Wrap(140);
            cardSizer->Add(title, 0, wxALIGN_CENTER, 2);

            double priceVal = prod.variants.empty() ? 0 : prod.variants[0].price;
            cardSizer->Add(new wxStaticText(card, wxID_ANY, "Starts: " + FormatPrice(priceVal)), 0, wxALIGN_CENTER, 2);

            wxButton* btnView = new wxButton(card, wxID_ANY, "View Details");
            cardSizer->Add(btnView, 0, wxALIGN_CENTER | wxALL, 5);

            btnView->Bind(wxEVT_BUTTON, [this, prod](wxCommandEvent&) {
                ProductDetailsFrame* f = new ProductDetailsFrame(this, prod);
                f->Show();
                });
            card->SetSizer(cardSizer);
            sizer->Add(card, 0, wxEXPAND | wxALL, 10);
        }
        m_scrolledWindow->Layout();
        m_scrolledWindow->FitInside();
    }

protected:
    void OnSearchClick(wxCommandEvent& event) override {
        PopulateGrid(m_searchBar->GetValue());
    }

    void OnViewCartClick(wxCommandEvent& event) override {
        CartFrame* cart = new CartFrame(this);
        cart->Show();
    }

    void OnViewOrdersClick(wxCommandEvent& event) override {
        OrderHistoryFrame* h = new OrderHistoryFrame(this);
        h->Show();
    }
};

class MyApp : public wxApp {
public:
    void AddToInventory(wxString name, std::vector<Variant> variants, wxString path, wxString desc) {
        g_inventory.push_back({ name, variants, path, desc });
    }

    virtual bool OnInit() {
        wxInitAllImageHandlers();
        AddToInventory("Mykonos - Aphrodite",
            { {"50ml", 289.00}, {"100ml", 450.00} },
            "C:\\Users\\stephen\\source\\repos\\Project OOAD\\aphro.jpg",
            "Love is an obsession, it possesses you. So, before you let the obsession towards someone else possess you, Ignite the inner Aphrodite within you. Warm, woody & aromatic Myrrh hypnotises at first spray, transitioning into sweet & smoky burnt cinnamon, with a breeze of elegant white florals, dancing on a stage of sexy yet subtle tobacco. Can you feel it possessing you slowly?  Be your very own obsession.\n\nLongevity: 7-9 hours \nSillage: Heavy \nProjection: 1.5-2 meters\n\nNotes:\nTop: Jasmine, Burnt Cinnamon\nMid: Cedarwood\nBase: White Musk");
        AddToInventory("HMNS - Orgsm",
            { {"30ml", 145.00}, {"100ml", 480.00} },
            "C:\\Users\\stephen\\source\\repos\\Project OOAD\\hmns.jpg",
            "HMNS 'O' is our very first feminine perfume with the power of making you irresistible with a scent that produces insatiable thirst. Inspired by worlds' most bestselling notes for women, HMNS 'O' perfume will be released worldwide, So don't miss your chance <3. This is the first formulation from the Gen - XX Series, HMNS 'O' comes with top notes of red apple, middle notes of florals from Rose, Jasmine, Peony which give a rich, luxurious, & romantic impression. As well as warm & sweet gourmand notes of Vanilla Beans & amber at the end with a balanced balance. \n\nLongevity: 6 hours \nSillage: Medium \nProjection: 2 meters \n\nNotes:\nTop: Red Apple\nMid: Rose, Jasmine\nBase: Vanilla Beans");
        AddToInventory("Saff & Co - S.O.T.B",
            { {"30ml", 189.00} },
            "C:\\Users\\stephen\\source\\repos\\Project OOAD\\saff.jpg",
            "S. O. T. B captures the perfect summer dream like no other: sun-kissed skin, colorful swimwear, fun pool parties, and a glass of refreshing S*x on the Beach! Designed with an exciting blend of mandarin, sweet floral notes, and rich vanilla musk, this tropical scent will remind you of warm sea breeze, soft sands, and lush palm trees on a hot summer day.\n\nLongevity: 8-12+ hours \nSillage: Beast Mode \nProjection: 2+ meters\n\nNotes:\nTop: Mandarin\nMid: Tuberose\nBase: Musk");
        AddToInventory("Carl & Claire - Black",
            { {"30ml", 120.00}, {"50ml", 250.00}, {"100ml", 390.00} },
            "C:\\Users\\stephen\\source\\repos\\Project OOAD\\carl.jpg",
            "A sweet-smelling scent filled up the night. The black dahlia blooms in the dark.' \nDeep in the forest, the Black Dahlia sends out its elegant yet seductive scent that filled the midnight hour. Mixing the sweet notes of Vanilla and Coffee with woody, ambery, and musky scents, this bold fragrance exudes a sense of mystery and sensuality.\n\nLongevity: 5-6 hours \nSillage: Moderate \nProjection: 1 meters\n\nNotes:\nTop: Coffee\nMid: Woody\nBase: Sweet");
        AddToInventory("Oullu - Deep Dive",
            { {"15ml", 99.00}, {"50ml", 410.00} },
            "C:\\Users\\stephen\\source\\repos\\Project OOAD\\oullu.jpg",
            "A fresh aquatic scent that reminds you of the deep blue ocean.\n\nLongevity: 4-6 hours \nSillage: Intimate to Moderate \nProjection: 1-1.5 meters\n\nNotes:\nTop: Lemon\nMid: Sage\nBase: Oak Moss");
        AddToInventory("Fordive - Atlantis",
            { {"40ml", 199.00}, {"100ml", 350.00} },
            "C:\\Users\\stephen\\source\\repos\\Project OOAD\\fordive.jpg",
            "Fordive Atlantis is a refreshing and charming perfume that is suitable for use in the heat. Its fresh and aquatic scent gives a fresh sensation and is suitable for use during exercise. \nTop notes of Grapefruit, Black Currant, Sea Salt provide a refreshing and sweet fragrance of the sea without giving a fishy impression, making the scent even more pleasant when sweating. Middle notes of Lily of the Valley & Jasmine add a soft touch of white floral fragrance, wrapped in pine which provides a refreshing sensation. Bottom notes of Amber, Praline close with a touch of a slightly sweet and comfortable aroma.\n\nLongevity: 5-7 hours \nSillage: Moderate \nProjection: 1-1.5 meters\n\nNotes:\nTop: Grapefruit\nMid: Pine\nBase: Amber");
        AddToInventory("Onix - Scorpio",
            { {"37ml", 150.00}, {"90ml", 290.00} },
            "C:\\Users\\stephen\\source\\repos\\Project OOAD\\onix.jpg",
            "SCORPIOS ARE ONE OF THE MOST INTENSE AND PASSIONATE SIGNS✨' \nDo you agree, Scorpios? If you are an intense and passionate person, then this bottle of Scorpio is suitable for you! With notes of Vanilla, Coffee, and Pink Pepper, the scent of this perfume is very intense and suitable for passionate people like Scorpios.\n\nLongevity: 6-7 hours \nSillage: Moderate \nProjection: 2 meters\n\nNotes:\nTop: Pink Pepper\nMid: Coffee\nBase: Vanilla");
        AddToInventory("Mykonos - Dreamscape",
            { {"50ml", 460.00} },
            "C:\\Users\\stephen\\source\\repos\\Project OOAD\\mykonos.jpg",
            "Dreamscape is a scent that feels like a dream you don’t want to wake up from. It starts with a mouthwatering mix of ripe mango, citrus and red berries, juicy, bright, and irresistibly addictive. As it settles, soft jasmine, warm cedarwood, and a hint of sweetness from coumarin begin to shine through. In the end, it dries down to a cozy blend of musk, woods, and amber. Addictive and comforting, Dreamscape leaves a lasting impression, a hypnotic glow that stays with you long after the moment has passed. It's more than a fragrance, it's a vivid escape.\n\nLongevity: 6-8 hours \nSillage: Moderate \nProjection: 1.5-2 meters\n\nNotes:\nTop: Mango\nMid: Ginger\nBase: Cedar");
        MainFrame* frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);