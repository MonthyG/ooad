#include <wx/wx.h>
#include "GUI_Base.h" // Import your generated header
#include <vector>

// --- MODEL: Data Structure for a Perfume ---
struct Perfume {
    wxString name;
    wxString price;
    wxString imagePath; // Optional: if you want images later
};

// --- CONTROLLER: The Logic Class ---
class MainFrame : public MainFrameBase // Inherits from your generated code
{
public:
    MainFrame(wxWindow* parent) : MainFrameBase(parent)
    {
        // 1. Setup the scroll rate (Make it smooth)
        m_scrolledWindow->SetScrollRate(0, 20);

        // 2. Load Dummy Data (In real app, this comes from Database)
        std::vector<Perfume> inventory;
        inventory.push_back({"Chanel No. 5", "$120"});
        inventory.push_back({"Dior Sauvage", "$95"});
        inventory.push_back({"Versace Eros", "$80"});
        inventory.push_back({"Gucci Bloom", "$110"});
        inventory.push_back({"YSL Black Opium", "$130"});
        inventory.push_back({"Calvin Klein One", "$50"});

        // 3. Loop to create UI for each product
        for (const auto& item : inventory)
        {
            AddProductCard(item);
        }

        // 4. Force layout update so items appear correctly
        m_scrolledWindow->Layout();
        m_scrolledWindow->FitInside(); // Important for scrolling!
    }

    // Helper function to build ONE product card
    void AddProductCard(Perfume p)
    {
        // A. Create a panel to hold the product info
        // IMPORTANT: Parent must be m_scrolledWindow, not 'this'
        wxPanel* card = new wxPanel(m_scrolledWindow, wxID_ANY);
        card->SetBackgroundColour(wxColour(240, 240, 240)); // Light Gray background
        
        // B. Vertical layout for this specific card
        wxBoxSizer* cardSizer = new wxBoxSizer(wxVERTICAL);

        // C. Create Labels and Buttons
        wxStaticText* lblName = new wxStaticText(card, wxID_ANY, p.name);
        lblName->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
        
        wxStaticText* lblPrice = new wxStaticText(card, wxID_ANY, p.price);
        
        wxButton* btnAdd = new wxButton(card, wxID_ANY, "Add to Cart");
        
        // D. Bind Button Event (OOP way)
        // We use a lambda function here to capture the product name
        btnAdd->Bind(wxEVT_BUTTON, [this, p](wxCommandEvent& event) {
            OnAddToCart(p.name);
        });

        // E. Add items to the card sizer
        cardSizer->Add(lblName, 0, wxALIGN_CENTER | wxTOP, 10);
        cardSizer->Add(lblPrice, 0, wxALIGN_CENTER | wxTOP, 5);
        cardSizer->Add(btnAdd, 0, wxALIGN_CENTER | wxALL, 10);

        card->SetSizer(cardSizer);

        // F. Add the finished card to the MAIN GRID
        // m_productGrid comes from MainFrameBase (must be protected!)
        m_productGrid->Add(card, 1, wxEXPAND | wxALL, 10);
    }

    // Logic when "Add to Cart" is clicked
    void OnAddToCart(wxString productName)
    {
        wxMessageBox(productName + " added to cart!", "Success");
        // Update cart logic here later
    }

    // Handle closing the window
    void OnClose(wxCloseEvent& event)
    {
        Destroy();
    }
};

// --- APP ENTRY POINT ---
class MyApp : public wxApp
{
public:
    virtual bool OnInit()
    {
        // For testing, we skip login and go straight to MainFrame
        // In final version, you start LoginFrame here.
        MainFrame* frame = new MainFrame(NULL);
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);