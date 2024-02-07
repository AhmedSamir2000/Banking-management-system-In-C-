#include <iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>

using namespace std;

const string ClientsName = "Clients.text";

void ShowMainMenueScreen();

void ShowTransactionsMenueScreen();

enum enMainMenueOptions {
    eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
    eUpdateClient = 4, eFindClient = 5, eTransations = 6, Exit = 7
};

enum enTransactionsMenueOptions
{
    eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, MainMenue = 4
};

struct stClient
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

vector<string> SplitString(string Line, string Seperator)
{
    vector<string> vString;
    short pos = 0;
    string sWord = "";

    while ((pos = Line.find(Seperator)) != string::npos)
    {
        sWord = Line.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        Line.erase(0, pos + Seperator.length());
    }

    if (Line != "")
    {
        vString.push_back(Line);
    }

    return vString;
}

stClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    vector<string> vString = SplitString(Line, Seperator);
    stClient Client;

    Client.AccountNumber = vString[0];
    Client.PinCode = vString[1];
    Client.Name = vString[2];
    Client.Phone = vString[3];
    Client.AccountBalance = stod(vString[4]);

    return Client;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    vector<stClient> vClients;
    fstream MyFile;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile,Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return false;
}

stClient ReadNewClient()
{
    stClient Client;

    cout << "\nEnter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "\nEnter Pin Code? ";
    getline(cin, Client.PinCode);

    cout << "\nEnter Name? ";
    getline(cin, Client.Name);

    cout << "\nEnter Phone? ";
    getline(cin, Client.Phone);

    cout << "\nEnter Account Balance? ";
    cin >> Client.AccountBalance;

    return Client;
}

string ConvertRecordDataToLine(stClient Client, string Separetor = "#//#")
{
    string Line = "";

    Line += Client.AccountNumber + Separetor;
    Line += Client.PinCode + Separetor;
    Line += Client.Name + Separetor;
    Line += Client.Phone + Separetor;
    Line += to_string(Client.AccountBalance);

    return Line;
}

void AddDataLineToFile(string FileName, string Line)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << Line << endl;
        MyFile.close();
    }
}

void AddNewClient()
{
    stClient Client = ReadNewClient();
    AddDataLineToFile(ClientsName, ConvertRecordDataToLine(Client));
}

void AddClients()
{
    char AddMore = 'Y';

    do
    {
        cout << "\nAdding New Client" << endl;

        AddNewClient();

        cout << "\nClient Added Successfully, do you want to add more clients?";
        cin >> AddMore;

    } while (AddMore == 'Y' || AddMore == 'y');
}

void ShowAddClientsScreen()
{
    cout << "\n-------------------------------" << endl;
    cout << "\tAdd Clients Screen";
    cout << "\n-------------------------------" << endl;

    AddClients();
}

vector<stClient> LoadClientsDataFromFile(string FileName)
{
    vector<stClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void PrintClientCard(stClient Client)
{
    cout << "| " << setw(15) << Client.AccountNumber;
    cout << "| " << setw(10) << Client.PinCode;
    cout << "| " << setw(40) << Client.Name;
    cout << "| " << setw(12) << Client.Phone;
    cout << "| " << setw(12) << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
    vector<stClient> vClients = LoadClientsDataFromFile(ClientsName);

    cout << "\n\t\t\t\t\tClint List (" << vClients.size() << ") Client(s).";
    cout << "\n----------------------------------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n----------------------------------------------------------------------------------------------------\n" << endl;

    if (vClients.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available  In The System! ";
    }
    else
    {
        for (stClient Client : vClients)
        {
            PrintClientCard(Client);
            cout << endl;
        }
    }

    cout << "\n----------------------------------------------------------------------------------------------------" << endl;
}

string ReadClientAccountNumber()
{
    string AccountNumber;

    cout << "\nplease enter Account Number? ";
    cin >> AccountNumber;

    return AccountNumber;
}

bool IsFindClientByAccountNumber(string AccountNumber, vector<stClient> vClients, stClient& Client)
{

    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

void PrintClientInfo(stClient Client)
{
    cout << "\nThe Following are the Client Details:\n" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Account Number :" << Client.AccountNumber << endl;
    cout << "Pin Code       :" << Client.PinCode << endl;
    cout << "Name           :" << Client.Name << endl;
    cout << "Phone          :" << Client.Phone << endl;
    cout << "Account Balance:" << Client.AccountBalance << endl;
    cout << "----------------------------------------" << endl;
}

void ShowFindClientScreen()
{
    cout << "---------------------------------------" << endl;
    cout << "\tFind Client Screen" << endl;
    cout << "---------------------------------------" << endl;

    vector<stClient> vClients = LoadClientsDataFromFile(ClientsName);
    string AccountNumber = ReadClientAccountNumber();
    stClient Client;

    if (IsFindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientInfo(Client);
    }
    else
    {
        cout << "\nClient With Account Number [" << AccountNumber << "] Not Found!" << endl;
    }
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector<stClient> SaveClientDataToFile(string FileName,vector<stClient> vClients)
{
    fstream MyFile;
    stClient Client;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {
        string Line;

        for (stClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                Line = ConvertRecordDataToLine(C);
                MyFile << Line << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{
    char Answer;

    stClient Client;

    if (IsFindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientInfo(Client);

        cout << "Are you sure you want delete this client? [Yes/No]: ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientDataToFile(ClientsName, vClients);

            vClients = LoadClientsDataFromFile(ClientsName);

            cout << "\nClient Deleted Successfully." << endl;
        }
        return true;
    }
    else
    {
        cout << "\nClient With Account Number [" << AccountNumber << "] Not Found!" << endl;
        return false;
    }
}

void ShowDeleteScreen()
{
    cout << "---------------------------------------" << endl;
    cout << "\tDelete Client Screen" << endl;
    cout << "---------------------------------------" << endl;

    vector<stClient> vClients = LoadClientsDataFromFile(ClientsName);
    string AccountNumber = ReadClientAccountNumber();

    DeleteClientByAccountNumber(AccountNumber, vClients);
}

stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\nEnter PinCode: ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name: ";
    getline(cin, Client.Name);

    cout << "Enter Phone: ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance: ";
    cin >> Client.AccountBalance;

    return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{
    char Answer;

    stClient Client;

    if (IsFindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientInfo(Client);

        cout << "Are you sure you want update this client? [Yes/No]: ";
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            for (stClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientDataToFile(ClientsName, vClients);

            cout << "\nClient Updated Successfully." << endl;
        }
        return true;
    }
    else
    {
        cout << "\nClient With Account Number [" << AccountNumber << "] Not Found!" << endl;
        return false;
    }
}

void ShowUpdateScreen()
{
    cout << "---------------------------------------" << endl;
    cout << "\tUpdate Client Screen" << endl;
    cout << "---------------------------------------" << endl;

    vector<stClient> vClients = LoadClientsDataFromFile(ClientsName);
    string AccountNumber = ReadClientAccountNumber();

    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void GoBackToMainMenu()
{
    cout << "\nPress any key to go back to main menu....." << endl;
    system("pause>0");
    ShowMainMenueScreen();
}

short ReadChooseMainMenuOptions()
{
    short Choose = 0;

    cout << "Choose What do you want to do? [1 to 7]?";
    cin >> Choose;

    return Choose;
}

void ShowEndScreen()
{
    cout << "\n-------------------------------" << endl;
    cout << "\tProgramme Ends -)" << endl;
    cout << "\n-------------------------------" << endl;
}

double ReadDepositAmount()
{
    double Amount = 0;

    cout << "Please Enter Deposit Amount? ";
    cin >> Amount;

    return Amount;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<stClient>& vClients)
{
    char Answer = 'n';

    cout << "\nAre you sure you want perform this Transactions? [Yes/No]: ";
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y')
    {
        for (stClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;

                SaveClientDataToFile(ClientsName, vClients);
                cout << "\nDone Successfully, New Balance: " << C.AccountBalance << endl;
                return true;
            }
        }
        return false;
    }
}

void DepositScreen()
{
    cout << "------------------------------------" << endl;
    cout << "\tDeposit Screen" << endl;
    cout << "------------------------------------" << endl;

    stClient Client;

    vector<stClient> vClients = LoadClientsDataFromFile(ClientsName);
    string AccountNumber = ReadClientAccountNumber();

    while (!IsFindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient With Account Number [" << AccountNumber << "] Not Found!" << endl;
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientInfo(Client);

    double Amount = ReadDepositAmount();

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void CheckBalance(double &Amount, stClient Client)
{
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the Balance, you can withdraw up to: " << Client.AccountBalance << endl;
        Amount = ReadDepositAmount();
    }
}

void WithDrawScreen()
{
    cout << "------------------------------------" << endl;
    cout << "\tWithDraw Screen" << endl;
    cout << "------------------------------------" << endl;

    stClient Client;

    vector<stClient> vClients = LoadClientsDataFromFile(ClientsName);
    string AccountNumber = ReadClientAccountNumber();

    while (!IsFindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient With Account Number [" << AccountNumber << "] Not Found!" << endl;
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientInfo(Client);

    double Amount = ReadDepositAmount();

    CheckBalance(Amount, Client);

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void TotalBalancesScreen()
{
    vector<stClient> vClients = LoadClientsDataFromFile(ClientsName);

    double TotalBalances = 0;

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n----------------------------------------------------------------------------------------------------" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n----------------------------------------------------------------------------------------------------\n" << endl;

    if (vClients.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available  In The System! ";
    }
    else
    {
        for (stClient Client : vClients)
        {
            cout << "| " << setw(15) << Client.AccountNumber;
            cout << "| " << setw(40) << Client.Name;
            cout << "| " << setw(12) << Client.AccountBalance;
            TotalBalances += Client.AccountBalance;
            cout << endl;
        }
    }

    cout << "\n----------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\tTotal Balances = " << TotalBalances << endl;
}

void GoBackToTransactionsMenu()
{
    cout << "\nPress any key to go back to Transactions Menue....." << endl;
    system("pause>0");
    ShowTransactionsMenueScreen();
}

short ReadChooseTransactionsMenueOptions()
{
    short Choose = 0;

    cout << "Choose What do you want to do? [1 to 4]?";
    cin >> Choose;

    return Choose;
}

void PerformTransactionsMenuOption(enTransactionsMenueOptions TransactionsMenueOptions)
{
    switch (TransactionsMenueOptions)
    {
    case enTransactionsMenueOptions::eDeposit:
        system("cls");
        DepositScreen();
        GoBackToTransactionsMenu();
        break;

    case enTransactionsMenueOptions::eWithdraw:
        system("cls");
        WithDrawScreen();
        GoBackToTransactionsMenu();
        break;

    case enTransactionsMenueOptions::eTotalBalances:
        system("cls");
        TotalBalancesScreen();
        GoBackToTransactionsMenu();
        break;

    case enTransactionsMenueOptions::MainMenue:
        ShowMainMenueScreen();
        break;
    }
}

void ShowTransactionsMenueScreen()
{
    system("cls");
    cout << "=============================================" << endl;
    cout << "\t\tTransactions Menu Screen" << endl;
    cout << "=============================================" << endl;
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "=============================================" << endl;

    PerformTransactionsMenuOption(enTransactionsMenueOptions(ReadChooseTransactionsMenueOptions()));
}

void PerformMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenu();
        break;

    case enMainMenueOptions::eAddNewClient:
    {
        system("cls");
        ShowAddClientsScreen();
        GoBackToMainMenu();
        break;
    }

    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteScreen();
        GoBackToMainMenu();
        break;

    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateScreen();
        GoBackToMainMenu();
        break;

    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenu();
        break;

    case enMainMenueOptions::eTransations:
        system("cls");
        ShowTransactionsMenueScreen();
        break;

    case enMainMenueOptions::Exit:
        system("cls");
        ShowEndScreen();
        break;
    }
}

void ShowMainMenueScreen()
{
    system("cls");
    cout << "=============================================" << endl;
    cout << "\t\tMain Menu Screen" << endl;
    cout << "=============================================" << endl;
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit" << endl;
    cout << "=============================================" << endl;

    PerformMainMenueOption((enMainMenueOptions)ReadChooseMainMenuOptions());
}

int main()
{
    ShowMainMenueScreen();

    system("pause>0");

    return 0;
}

