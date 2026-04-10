#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

// ============================================================
//                  Constants
// ============================================================
const string ClientsFileName = "Clients.txt";

// ============================================================
//                  Data Structures
// ============================================================
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool   MarkForDelete = false;
};

struct sStatistics
{
    int    TotalClients;
    double TotalBalance;
    double HighestBalance;
    double LowestBalance;
    string RichestClient;
    string PoorestClient;
};

// ============================================================
//                  Screen Utilities
// ============================================================
void ClearScreen()
{
    cout << string(50, '\n');
}

void PressEnterToGoBack()
{
    cout << "\n\nPress Enter to go back to Main Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    ClearScreen();
}

void PrintSeparatorLine(int Length = 90)
{
    cout << string(Length, '_') << endl;
}

void PrintScreenHeader(string Title)
{
    ClearScreen();
    cout << "\n===========================================\n";
    cout << "\t" << Title << "\n";
    cout << "===========================================\n";
}

// ============================================================
//                  String Utilities
// ============================================================
vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;

    while ((pos = S1.find(Delim)) != string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
            vString.push_back(sWord);
        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
        vString.push_back(S1);

    return vString;
}

// ============================================================
//                  Record Conversion
// ============================================================
sClient ConvertLineToRecord(string Line, string Separator = "#//#")
{
    sClient Client;
    vector<string> vData = SplitString(Line, Separator);

    Client.AccountNumber  = vData[0];
    Client.PinCode        = vData[1];
    Client.Name           = vData[2];
    Client.Phone          = vData[3];
    Client.AccountBalance = stod(vData[4]);

    return Client;
}

string ConvertRecordToLine(sClient Client, string Separator = "#//#")
{
    return Client.AccountNumber  + Separator +
           Client.PinCode        + Separator +
           Client.Name           + Separator +
           Client.Phone          + Separator +
           to_string(Client.AccountBalance);
}

// ============================================================
//                  File Operations
// ============================================================
vector<sClient> LoadClientsFromFile(string FileName)
{
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
            vClients.push_back(ConvertLineToRecord(Line));
        MyFile.close();
    }

    return vClients;
}

void SaveClientsToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (!C.MarkForDelete)
                MyFile << ConvertRecordToLine(C) << endl;
        }
        MyFile.close();
    }
}

void AppendClientToFile(string FileName, sClient Client)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << ConvertRecordToLine(Client) << endl;
        MyFile.close();
    }
}

// ============================================================
//                  Client Search & Validation
// ============================================================
bool IsAccountNumberExists(string AccountNumber, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        while (getline(MyFile, Line))
        {
            sClient Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
        }
        MyFile.close();
    }

    return false;
}

bool FindClientByAccountNumber(string AccountNumber,
                                vector<sClient> vClients,
                                sClient& Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool IsPinCodeCorrect(string AccountNumber, string PinCode,
                      vector<sClient> vClients)
{
    sClient Client;
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        return (Client.PinCode == PinCode);
    return false;
}

// ============================================================
//                  Print Functions
// ============================================================
void PrintClientRecordLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(35) << left << Client.Name;
    cout << "| " << setw(13) << left << Client.Phone;
    cout << "| " << setw(12) << left << fixed << setprecision(2)
         << Client.AccountBalance;
}

void PrintClientCard(sClient Client)
{
    cout << "\n-----------------------------------";
    cout << "\n  Client Details";
    cout << "\n-----------------------------------";
    cout << "\nAccount Number : " << Client.AccountNumber;
    cout << "\nPin Code       : " << Client.PinCode;
    cout << "\nName           : " << Client.Name;
    cout << "\nPhone          : " << Client.Phone;
    cout << "\nBalance        : " << fixed << setprecision(2)
         << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

void PrintTableHeader()
{
    PrintSeparatorLine();
    cout << "| " << setw(15) << left << "Account Number";
    cout << "| " << setw(10) << left << "Pin Code";
    cout << "| " << setw(35) << left << "Client Name";
    cout << "| " << setw(13) << left << "Phone";
    cout << "| " << setw(12) << left << "Balance";
    cout << endl;
    PrintSeparatorLine();
}

void PrintStatistics(sStatistics Stats)
{
    cout << "\n==========================================";
    cout << "\n           Bank Statistics";
    cout << "\n==========================================";
    cout << "\n  Total Clients   : " << Stats.TotalClients;
    cout << "\n  Total Balance   : " << fixed << setprecision(2)
         << Stats.TotalBalance;
    cout << "\n  Highest Balance : " << Stats.HighestBalance
         << "  (" << Stats.RichestClient << ")";
    cout << "\n  Lowest Balance  : " << Stats.LowestBalance
         << "  (" << Stats.PoorestClient << ")";
    cout << "\n  Average Balance : " << fixed << setprecision(2)
         << (Stats.TotalBalance / Stats.TotalClients);
    cout << "\n==========================================\n";
}

// ============================================================
//                  Input Functions
// ============================================================
string ReadAccountNumber()
{
    string AccountNumber;
    cout << "\nEnter Account Number: ";
    cin >> AccountNumber;
    cin.ignore();
    return AccountNumber;
}

string ReadPinCode()
{
    string PinCode;
    cout << "Enter Pin Code: ";
    getline(cin, PinCode);
    return PinCode;
}

short ReadMenuOption(short From, short To)
{
    short Choice = 0;
    cout << "\nChoose [" << From << " to " << To << "]: ";
    cin >> Choice;
    cin.ignore();
    return Choice;
}

// ============================================================
//                  Read New / Updated Client
// ============================================================
sClient ReadNewClientData()
{
    sClient Client;

    cout << "Enter Account Number : ";
    getline(cin >> ws, Client.AccountNumber);

    while (IsAccountNumberExists(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nAccount [" << Client.AccountNumber
             << "] already exists! Enter another: ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter Pin Code       : ";
    getline(cin, Client.PinCode);

    cout << "Enter Name           : ";
    getline(cin, Client.Name);

    cout << "Enter Phone          : ";
    getline(cin, Client.Phone);

    cout << "Enter Balance        : ";
    cin  >> Client.AccountBalance;
    cin.ignore();

    return Client;
}

sClient ReadUpdatedClientData(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;

    cout << "Enter New Pin Code   : ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter New Name       : ";
    getline(cin, Client.Name);

    cout << "Enter New Phone      : ";
    getline(cin, Client.Phone);

    cout << "Enter New Balance    : ";
    cin  >> Client.AccountBalance;
    cin.ignore();

    return Client;
}

// ============================================================
//                  PinCode Verification
// ============================================================
bool VerifyClientPinCode(string AccountNumber, vector<sClient> vClients)
{
    string EnteredPin = ReadPinCode();

    if (!IsPinCodeCorrect(AccountNumber, EnteredPin, vClients))
    {
        cout << "\nWrong Pin Code! Access Denied." << endl;
        return false;
    }

    cout << "\nPin Code Verified!" << endl;
    return true;
}

// ============================================================
//                  Statistics
// ============================================================
sStatistics CalculateStatistics(vector<sClient> vClients)
{
    sStatistics Stats;
    Stats.TotalClients   = vClients.size();
    Stats.TotalBalance   = 0;
    Stats.HighestBalance = vClients[0].AccountBalance;
    Stats.LowestBalance  = vClients[0].AccountBalance;
    Stats.RichestClient  = vClients[0].Name;
    Stats.PoorestClient  = vClients[0].Name;

    for (sClient C : vClients)
    {
        Stats.TotalBalance += C.AccountBalance;

        if (C.AccountBalance > Stats.HighestBalance)
        {
            Stats.HighestBalance = C.AccountBalance;
            Stats.RichestClient  = C.Name;
        }

        if (C.AccountBalance < Stats.LowestBalance)
        {
            Stats.LowestBalance = C.AccountBalance;
            Stats.PoorestClient = C.Name;
        }
    }

    return Stats;
}

// ============================================================
//                  Sorting (Bubble Sort)
// ============================================================
enum enSortBy
{
    eSortByName          = 1,
    eSortByBalance       = 2,
    eSortByAccountNumber = 3
};

vector<sClient> SortClients(vector<sClient> vClients, enSortBy SortBy)
{
    int n = vClients.size();
    sClient Temp;
    bool ShouldSwap = false;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            ShouldSwap = false;

            if (SortBy == eSortByName)
                ShouldSwap = (vClients[j].Name > vClients[j + 1].Name);

            else if (SortBy == eSortByBalance)
                ShouldSwap = (vClients[j].AccountBalance > vClients[j + 1].AccountBalance);

            else if (SortBy == eSortByAccountNumber)
                ShouldSwap = (vClients[j].AccountNumber > vClients[j + 1].AccountNumber);

            if (ShouldSwap)
            {
                Temp             = vClients[j];
                vClients[j]      = vClients[j + 1];
                vClients[j + 1]  = Temp;
            }
        }
    }

    return vClients;
}

// ============================================================
//                  Client Operations
// ============================================================
void AddNewClient()
{
    sClient Client = ReadNewClientData();
    AppendClientToFile(ClientsFileName, Client);
    cout << "\nClient Added Successfully!" << endl;
}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        cout << "\n--- New Client Form ---\n";
        AddNewClient();
        cout << "\nAdd another client? (Y/N): ";
        cin >> AddMore;
        cin.ignore();
    } while (toupper(AddMore) == 'Y');
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
    sClient Client;

    if (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient [" << AccountNumber << "] Not Found!" << endl;
        return false;
    }

    PrintClientCard(Client);

    cout << "\nEnter Pin Code to confirm deletion: ";
    if (!VerifyClientPinCode(AccountNumber, vClients))
        return false;

    char Answer = 'n';
    cout << "\nAre you sure you want to DELETE this client? (Y/N): ";
    cin >> Answer;
    cin.ignore();

    if (toupper(Answer) == 'Y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.MarkForDelete = true;
                break;
            }
        }

        SaveClientsToFile(ClientsFileName, vClients);
        vClients = LoadClientsFromFile(ClientsFileName);
        cout << "\nClient Deleted Successfully!" << endl;
        return true;
    }

    cout << "\nDeletion Cancelled." << endl;
    return false;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
    sClient Client;

    if (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient [" << AccountNumber << "] Not Found!" << endl;
        return false;
    }

    PrintClientCard(Client);

    cout << "\nEnter Pin Code to confirm update: ";
    if (!VerifyClientPinCode(AccountNumber, vClients))
        return false;

    char Answer = 'n';
    cout << "\nAre you sure you want to UPDATE this client? (Y/N): ";
    cin >> Answer;
    cin.ignore();

    if (toupper(Answer) == 'Y')
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C = ReadUpdatedClientData(AccountNumber);
                break;
            }
        }

        SaveClientsToFile(ClientsFileName, vClients);
        cout << "\nClient Updated Successfully!" << endl;
        return true;
    }

    cout << "\nUpdate Cancelled." << endl;
    return false;
}

// ============================================================
//                  Screens
// ============================================================
void ShowAllClientsScreen()
{
    PrintScreenHeader("Client List");

    vector<sClient> vClients = LoadClientsFromFile(ClientsFileName);
    cout << "\n\tTotal Clients: " << vClients.size() << "\n";

    PrintTableHeader();

    if (vClients.empty())
        cout << "\n\t\tNo Clients Available in the System!\n";
    else
    {
        for (sClient C : vClients)
        {
            PrintClientRecordLine(C);
            cout << endl;
        }
    }

    PrintSeparatorLine();
    PressEnterToGoBack();
}

void ShowAddClientsScreen()
{
    PrintScreenHeader("Add New Clients");
    AddNewClients();
    PressEnterToGoBack();
}

void ShowDeleteClientScreen()
{
    PrintScreenHeader("Delete Client");

    vector<sClient> vClients = LoadClientsFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);

    PressEnterToGoBack();
}

void ShowUpdateClientScreen()
{
    PrintScreenHeader("Update Client");

    vector<sClient> vClients = LoadClientsFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

    PressEnterToGoBack();
}

void ShowFindClientScreen()
{
    PrintScreenHeader("Find Client");

    vector<sClient> vClients = LoadClientsFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumber();
    sClient Client;

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient [" << AccountNumber << "] Not Found!" << endl;

    PressEnterToGoBack();
}

void ShowStatisticsScreen()
{
    PrintScreenHeader("Bank Statistics");

    vector<sClient> vClients = LoadClientsFromFile(ClientsFileName);

    if (vClients.empty())
        cout << "\nNo Clients Available to Show Statistics!\n";
    else
    {
        sStatistics Stats = CalculateStatistics(vClients);
        PrintStatistics(Stats);
    }

    PressEnterToGoBack();
}

void ShowSortMenu()
{
    cout << "\n  Sort By:\n";
    cout << "  [1] Name\n";
    cout << "  [2] Balance\n";
    cout << "  [3] Account Number\n";
}

void ShowSortClientsScreen()
{
    PrintScreenHeader("Sort Clients");

    ShowSortMenu();
    short SortChoice = ReadMenuOption(1, 3);

    vector<sClient> vClients = LoadClientsFromFile(ClientsFileName);
    vClients = SortClients(vClients, (enSortBy)SortChoice);

    PrintTableHeader();
    for (sClient C : vClients)
    {
        PrintClientRecordLine(C);
        cout << endl;
    }
    PrintSeparatorLine();

    char SaveSorted = 'n';
    cout << "\nSave sorted order to file? (Y/N): ";
    cin >> SaveSorted;
    cin.ignore();

    if (toupper(SaveSorted) == 'Y')
    {
        SaveClientsToFile(ClientsFileName, vClients);
        cout << "\nSorted order saved!" << endl;
    }

    PressEnterToGoBack();
}

void ShowEndScreen()
{
    PrintScreenHeader("Goodbye!");
    cout << "\n\tThank you for using Bank System!\n" << endl;
}

// ============================================================
//                  Main Menu
// ============================================================
enum enMainMenuOptions
{
    eListClients    = 1,
    eAddNewClient   = 2,
    eDeleteClient   = 3,
    eUpdateClient   = 4,
    eFindClient     = 5,
    eShowStatistics = 6,
    eSortClients    = 7,
    eExit           = 8
};

void ShowMainMenu();

void PerformMainMenuOption(enMainMenuOptions Option)
{
    switch (Option)
    {
    case eListClients:
        ShowAllClientsScreen();
        break;
    case eAddNewClient:
        ShowAddClientsScreen();
        break;
    case eDeleteClient:
        ShowDeleteClientScreen();
        break;
    case eUpdateClient:
        ShowUpdateClientScreen();
        break;
    case eFindClient:
        ShowFindClientScreen();
        break;
    case eShowStatistics:
        ShowStatisticsScreen();
        break;
    case eSortClients:
        ShowSortClientsScreen();
        break;
    case eExit:
        ShowEndScreen();
        return;
    }

    ShowMainMenu();
}

void ShowMainMenu()
{
    PrintScreenHeader("Bank System - Main Menu");

    cout << "\n\t[1] Show Client List\n";
    cout << "\t[2] Add New Client\n";
    cout << "\t[3] Delete Client\n";
    cout << "\t[4] Update Client Info\n";
    cout << "\t[5] Find Client\n";
    cout << "\t[6] Statistics\n";
    cout << "\t[7] Sort Clients\n";
    cout << "\t[8] Exit\n";
    cout << "===========================================\n";

    PerformMainMenuOption((enMainMenuOptions)ReadMenuOption(1, 8));
}

// ============================================================
//                  Entry Point
// ============================================================
int main()
{
    ShowMainMenu();
    return 0;
}
