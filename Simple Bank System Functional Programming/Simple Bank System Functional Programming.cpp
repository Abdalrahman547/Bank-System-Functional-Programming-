#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

enum enMainMenueOptions
{  eShowClientList = 1, eAddClient = 2,
    eDeleteClient = 3, eUpdateClientInfo = 4,
    eFindClient = 5, eTransactions = 6,
    eManageUsers = 7, eExit = 8
};

enum enMainMenuePermissions
{
    eAll = -1, pListClients = 1,
    pAddNewClient = 2, pDeleteClient = 4,
    pUpdateClient = 8, pFindClient = 16,
    pTransactions = 32, pManageUsers = 64

};

enum enManageUserMenueOptions
{
    eListUsers = 1, eAddNewUser = 2,
    eDeleteUser = 3, eUpdateUser = 4,
    eFindUser = 5, eGoBackMeneuScreen = 6
};

enum enTransactionOptions
{
    enDeposit = 1, enWithdraw = 2,
    enTotalBalance = 3, enMainMenue = 4
};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0;
    bool MarkForDelete = false;

};

struct stUser
{
    string Usermame;
    string Password;
    int Permisions;
    bool MarkForDelete = false;

};

stUser CurrentUser;

void ShowMainMinueScreen();

void ShowTransactionsMenueScreen();

void ShowManageUsersMenueScreen();

void Login();

int ReadPermissionsToSet();

string ReadAccountNumer()
{
    string AccountNumber;

    cout << "Please enter Accoutn Numebr? ";

    cin >> AccountNumber;

    return AccountNumber;
}

string ReadUsername()
{
    string Username;

    cout << "Please enter Username? ";

    cin >> Username;

    return Username;
}

stClient ChangeClientRecord(string AccountForUpdate)
{
    stClient Client;

    Client.AccountNumber = AccountForUpdate;


    cout << "Enter Pin Code? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;

    return Client;
}

stUser ChangeUserRecord(string UserForUpdate)
{
    stUser User;

    User.Usermame = UserForUpdate;


    cout << "Enter Password? ";
    getline(cin >> ws, User.Password);

    User.Permisions = ReadPermissionsToSet();

    return User;
}

string ConvertRecordToLine(stClient Client, string delim = "#//#")
{
    string DataLine = "";

    DataLine += Client.AccountNumber + delim;
    DataLine += Client.PinCode + delim;
    DataLine += Client.Name + delim;
    DataLine += Client.Phone + delim;
    DataLine += to_string(Client.AccountBalance);

    return DataLine;
}

string ConvertUserRecordToLine(stUser User, string delim = "#//#")
{
    string DataLine = "";

    DataLine += User.Usermame + delim;
    DataLine += User.Password + delim;
    DataLine += to_string(User.Permisions);


    return DataLine;
}

vector<string> SplitString(string S1, string delim)
{
    vector<string> vString;

    short pos = 0;
    string sWord;

    while ((pos = S1.find(delim)) != string::npos)
    {
        sWord = S1.substr(0, pos);

        if (sWord != "")
            vString.push_back(sWord);

        S1.erase(0, pos + delim.length());
    }

    if (S1 != "")
        vString.push_back(S1);

    return vString;
}

stClient ConvertLineToRecord(string DataLine)
{
    vector<string> vClient = SplitString(DataLine, "#//#");

    stClient Client;

    Client.AccountNumber = vClient[0];
    Client.PinCode = vClient[1];
    Client.Name = vClient[2];
    Client.Phone = vClient[3];
    Client.AccountBalance = stod(vClient[4]);

    return Client;

}

stUser ConvertUserLineToRecord(string DataLine)
{
    vector<string> vUserDate = SplitString(DataLine, "#//#");

    stUser User;

    User.Usermame = vUserDate[0];
    User.Password = vUserDate[1];
    User.Permisions = stoi(vUserDate[2]);

    return User;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <stClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
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

bool UserExistsByUsername(string Username, string FileName)
{

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        stUser User;

        while (getline(MyFile, Line))
        {
            User = ConvertUserLineToRecord(Line);
            if (User.Usermame == Username)
            {
                MyFile.close();
                return true;
            }
        }

        MyFile.close();

    }
    return false;
}

int ReadPermissionsToSet()
{
    int Permissions = 0;
    char Answer = 'n';

    cout << "\nDo you want to give full access? Y/N? ";
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y')
        return -1;

    cout << "\nDo you want to give access to: \n";

    cout << "\nShow Client List? Y/N? ";
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y')
        Permissions += enMainMenuePermissions::pListClients;

    cout << "\nAdd New Client? Y/N? ";
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y')
        Permissions += enMainMenuePermissions::pAddNewClient;

    cout << "\nDelete Client? Y/N? ";
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y')
        Permissions += enMainMenuePermissions::pDeleteClient;

    cout << "\nUpdate Client? Y/N? ";
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y')
        Permissions += enMainMenuePermissions::pUpdateClient;

    cout << "\nFind Client? Y/N? ";
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y')
        Permissions += enMainMenuePermissions::pFindClient;

    cout << "\nTransactions? Y/N? ";
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y')
        Permissions += enMainMenuePermissions::pTransactions;

    cout << "\nManage Users? Y/N? ";
    cin >> Answer;

    if (Answer == 'Y' || Answer == 'y')
        Permissions += enMainMenuePermissions::pManageUsers;


    return Permissions;

}

stClient ReadNewClient()
{
    stClient Client;

    cout << "\nEnter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter Pin Code? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;

    return Client;
}

stUser ReadNewUser()
{
    stUser User;

    cout << "\nEnter User Name? ";
    getline(cin >> ws, User.Usermame);

    while (UserExistsByUsername(User.Usermame, UsersFileName))
    {
        cout << "\tUser with [" << User.Usermame << "] already exists, Enter another User Name? ";
        getline(cin >> ws, User.Usermame);
    }

    cout << "Enter Password? ";
    getline(cin, User.Password);

    User.Permisions = ReadPermissionsToSet();

    return User;
}

void AddClientToFile(string FileName, string stDataLine)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

void AddNewClient()
{
    stClient Client;

    Client = ReadNewClient();

    AddClientToFile(ClientsFileName, ConvertRecordToLine(Client));

}

void AddNewUser()
{
    stUser User;

    User = ReadNewUser();

    AddClientToFile(UsersFileName, ConvertUserRecordToLine(User));

}

void AddClients()
{
    char AddMore = 'N';

    do
    {
        cout << "Adding New Client: \n\n";

        AddNewClient();

        cout << "\nClient Added Successfully, do you want to add more Clients? Y/N ";

        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

void AddUsers()
{
    char AddMore = 'N';

    do
    {
        cout << "Adding New User: \n\n";

        AddNewUser();

        cout << "\nUser Added Successfully, do you want to add more Users? Y/N ";

        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

bool FindClientsByAccountNumber(string AccoutToFind, vector<stClient> Clients, stClient& Client)
{
    for (auto C : Clients)
    {
        if (C.AccountNumber == AccoutToFind)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool FindUsersByUsername(string UserToFind, vector<stUser> vUsers, stUser& User)
{
    for (auto U : vUsers)
    {
        if (U.Usermame == UserToFind)
        {
            User = U;
            return true;
        }
    }
    return false;
}

vector<stClient> LoadClientsDataFromFile(string FileName)
{
    vector<stClient> vClients;

    fstream MyFile;

    MyFile.open(FileName, ios::in); // ReadOnly


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

vector<stUser> LoadUsersDataFromFile(string UsersFileName)
{
    vector<stUser> vUsers;

    fstream MyFile;

    MyFile.open(UsersFileName, ios::in); // ReadOnly


    if (MyFile.is_open())
    {
        string Line;
        stUser User;

        while (getline(MyFile, Line))
        {
            User = ConvertUserLineToRecord(Line);

            vUsers.push_back(User);
        }

        MyFile.close();
    }

    return vUsers;
}

bool FindUserByUsernameAndPassword(string Username, string Password, stUser& User)
{
    vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    for (auto U : vUsers)
    {
        if (U.Usermame == Username && U.Password == Password)
        {
            User = U;
            return true;
        }
    }

    return false;
}

void PrintClientCard(stClient Client)
{
    cout << "\nThe following are the client details: \n";
    cout << "____________________________________________\n";
    cout << "\nAccount Number : " << Client.AccountNumber << "\n";
    cout << "PinCode        : " << Client.PinCode << "\n";
    cout << "Name	       : " << Client.Name << "\n";
    cout << "Phone          : " << Client.Phone << "\n";
    cout << "AccountBalance : " << Client.AccountBalance << "\n";
    cout << "____________________________________________\n\n";
}

void PrintUserCard(stUser User)
{
    cout << "\nThe following are the User details: \n";
    cout << "____________________________________________\n";
    cout << "\nUser Name    : " << User.Usermame << "\n";
    cout << "\nPassword     : " << User.Password << "\n";
    cout << "\nPermisions   : " << User.Permisions << "\n";
    cout << "____________________________________________\n\n";
}

void PrintClientRecordLine(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintClientRecordLine(stClient Client, bool transaction)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintUserRecordLine(stUser User)
{
    cout << "| " << setw(15) << left << User.Usermame;
    cout << "| " << setw(10) << left << User.Password;
    cout << "| " << setw(40) << left << User.Permisions;
}

void ShowAccessDeniedMessage()
{
    cout << "\n------------------------------------\n";
    cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";
    cout << "\n------------------------------------\n";
}

void ShowAllClients()
{
    vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClients List (" << vClients.size() << ") Client(s)";
    cout << "\n______________________________________________________________________";
    cout << "__________________________________________________\n" << endl;

    cout << "| " << setw(15) << left << "Account Number";
    cout << "| " << setw(10) << left << "Pin Code";
    cout << "| " << setw(40) << left << "Client Name";
    cout << "| " << setw(12) << left << "Phone";
    cout << "| " << setw(12) << left << "Account Balance";

    cout << "\n______________________________________________________________________";
    cout << "__________________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";

    else
    {
        for (auto C : vClients)
        {
            PrintClientRecordLine(C);

            cout << "\n";
        }
    }

    cout << "\n______________________________________________________________________";
    cout << "__________________________________________________\n" << endl;


}

vector<stClient> SaveClientsDataToFile(string FileName, vector<stClient> vClients)
{
    fstream MyFile;

    string Line;

    MyFile.open(FileName, ios::out); //overwrite

    if (MyFile.is_open())
    {
        for (auto C : vClients)
        {
            if (!C.MarkForDelete)
            {
                Line = ConvertRecordToLine(C);

                MyFile << Line << endl;
            }
        }

        MyFile.close();
    }

    return vClients;
}

vector<stUser> SaveUsersDataToFile(string FileName, vector<stUser> vUsers)
{
    fstream MyFile;

    string Line;

    MyFile.open(FileName, ios::out); //overwrite

    if (MyFile.is_open())
    {
        for (auto U : vUsers)
        {
            if (!U.MarkForDelete)
            {
                Line = ConvertUserRecordToLine(U);

                MyFile << Line << endl;
            }
        }

        MyFile.close();
    }

    return vUsers;
}

bool MarkClientForDelete(string AccoutForDelete, vector<stClient>& vClients)
{
    for (auto& C : vClients)
    {
        if (C.AccountNumber == AccoutForDelete)
        {
            C.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

bool MarkUserForDelete(string UserForDelete, vector<stUser>& vUsers)
{
    for (auto& U : vUsers)
    {
        if (U.Usermame == UserForDelete)
        {
            U.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

bool DeleteClientByAccountNumber(string AccountForDelete, vector<stClient>& vClients)
{
    stClient Client;

    char del = 'N';

    if (FindClientsByAccountNumber(AccountForDelete, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want to delete this client ? Y/N  ";
        cin >> del;

        if (toupper(del) == 'Y')
        {
            MarkClientForDelete(AccountForDelete, vClients);
            SaveClientsDataToFile(ClientsFileName, vClients);

            vClients = LoadClientsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number(" << AccountForDelete << ") Not exist!";
        return false;
    }
}

bool DeleteUserByUsername(string UserForDelete, vector<stUser>& vUsers)
{
    stUser User;

    char del = 'N';

    if (FindUsersByUsername(UserForDelete, vUsers, User))
    {

        PrintUserCard(User);

        cout << "\n\nAre you sure you want to delete this user ? Y/N  ";
        cin >> del;

        if (toupper(del) == 'Y')
        {
            MarkUserForDelete(UserForDelete, vUsers);
            SaveUsersDataToFile(UsersFileName, vUsers);

            vUsers = LoadUsersDataFromFile(UsersFileName);

            cout << "\nUser Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with Username(" << UserForDelete << ") Not exist!";
        return false;
    }
}

stClient UpdateClientRecord(string AccoutnForUpdate, stClient& Client)
{
    PrintClientCard(Client);

    Client = ChangeClientRecord(AccoutnForUpdate);

    cout << "\n\nClient Updated Successfully";

    return Client;
}

bool UpdateClientByAccountNumber(string AccountForUpdate, vector<stClient>& vClients)
{
    stClient CLient;

    if (FindClientsByAccountNumber(AccountForUpdate, vClients, CLient))
    {
        for (auto& C : vClients)
        {
            if (C.AccountNumber == AccountForUpdate)
            {
                PrintClientCard(C);

                C = ChangeClientRecord(AccountForUpdate);
                break;
            }
        }

        SaveClientsDataToFile(ClientsFileName, vClients);

        cout << "\nClient Updated Successfully";
        return true;

    }
    else
    {
        cout << "\nClient with Account Number(" << AccountForUpdate << ") Not exist!";
        return false;
    }
}

bool UpdateUserByUsername(string UserForUpdate, vector<stUser>& vUsers)
{
    stUser User;

    if (FindUsersByUsername(UsersFileName, vUsers, User))
    {
        for (auto& U : vUsers)
        {
            if (U.Usermame == UserForUpdate)
            {
                PrintUserCard(U);

                U = ChangeUserRecord(UserForUpdate);
                break;
            }
        }

        SaveUsersDataToFile(UsersFileName, vUsers);

        cout << "\nUser Updated Successfully";
        return true;

    }
    else
    {
        cout << "\nClient with Account Number(" << UserForUpdate << ") Not exist!";
        return false;
    }
}

short ReadOption()
{
    short op;
    do
    {
        cout << "Choose what do you to do? [1 to 8]? ";
        cin >> op;

    } while (op < 1 || op > 8);

    return op;
}

short ReadOption(bool transaction)
{
    short op;
    do
    {
        cout << "Choose what do you to do? [1 to 4]? ";
        cin >> op;

    } while (op < 1 || op > 4);

    return op;
}

short ReadManageUsersMenueOption()
{
    short op;
    do
    {
        cout << "Choose what do you to do? [1 to 6]? ";
        cin >> op;

    } while (op < 1 || op > 6);

    return op;
}

void BackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");

    ShowMainMinueScreen();
}

void BackToMainMenue(bool ManageUsersScreen)
{
    ShowMainMinueScreen();
}

bool CheckAccessPermission(enMainMenuePermissions Permission)
{
    if (CurrentUser.Permisions == eAll)
        return true;

    if ((Permission & CurrentUser.Permisions) == Permission)
        return true;
    else
        return false;
}

void ShowAddNewClientsScreen()
{
    if (!CheckAccessPermission(pAddNewClient))
    {
        ShowAccessDeniedMessage();
        BackToMainMenue();
        return;
    }

    cout << "\n____________________________________________\n";
    cout << "\tAdd New CLient Screen\n";
    cout << "____________________________________________\n";

    AddClients();
}

void ShowDeleteClientScreen()
{
    if (!CheckAccessPermission(pDeleteClient))
    {
        ShowAccessDeniedMessage();
        BackToMainMenue();
        return;
    }

    cout << "\n____________________________________________\n";
    cout << "\tDelete CLient Screen\n";
    cout << "____________________________________________\n";

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumer();

    DeleteClientByAccountNumber(AccountNumber, vClients);

}

void ShowUpdateClientScreen()
{
    if (!CheckAccessPermission(pUpdateClient))
    {
        ShowAccessDeniedMessage();
        BackToMainMenue();
        return;
    }

    cout << "\n____________________________________________\n";
    cout << "\tUpdate CLient Info Screen\n";
    cout << "____________________________________________\n";

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadAccountNumer();

    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen()
{
    if (!CheckAccessPermission(pFindClient))
    {
        ShowAccessDeniedMessage();
        BackToMainMenue();
        return;
    }

    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    stClient Client;
    string AccountNumber = ReadAccountNumer();

    if (FindClientsByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number(" << AccountNumber << ") Not exist!";
}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

double ReadAmount(string type)
{
    double amount;

    cout << "Please enter " << type << " amount? ";

    cin >> amount;
    return amount;
}

bool DepositBalanceToClient(string AccountNumber, double Amount, vector<stClient>& vClients)
{
    char Answer = 'N';

    cout << "\nAre you sure you want preform this transaction? Y/N ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {
        for (auto& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveClientsDataToFile(ClientsFileName, vClients);
                cout << "\nDone successfully, new balance = " << C.AccountBalance;
                return true;
            }
        }

    }

    return false;
}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    stClient Client;
    string AccountNumber = ReadAccountNumer();

    while (!FindClientsByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with Account Number(" << AccountNumber << ") Not exist!";
        AccountNumber = ReadAccountNumer();
    }

    PrintClientCard(Client);

    double Amount = ReadAmount("deposit");

    DepositBalanceToClient(AccountNumber, Amount, vClients);
}

void ShowWithdrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\Withdraw Screen";
    cout << "\n-----------------------------------\n";

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    stClient Client;
    string AccountNumber = ReadAccountNumer();

    while (!FindClientsByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with Account Number(" << AccountNumber << ") Not exist!";
        AccountNumber = ReadAccountNumer();
    }

    PrintClientCard(Client);

    double Amount = ReadAmount("withdraw");

    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmout Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << "\n";
        Amount = ReadAmount("withdraw");
    }

    DepositBalanceToClient(AccountNumber, Amount * -1, vClients);
}

void ShowTotalBalanceList()
{
    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClients List (" << vClients.size() << ") Client(s)";
    cout << "\n______________________________________________________________________";
    cout << "__________________________________________________\n" << endl;

    cout << "| " << setw(15) << left << "Account Number";
    cout << "| " << setw(40) << left << "Client Name";
    cout << "| " << setw(12) << left << "Account Balance";

    cout << "\n______________________________________________________________________";
    cout << "__________________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";

    long double Total = 0;

    for (auto C : vClients)
    {
        PrintClientRecordLine(C, 1);
        cout << "\n";
        Total += C.AccountBalance;
    }

    cout << "\n______________________________________________________________________";
    cout << "__________________________________________________\n" << endl;

    cout << "\n\t\t\t\t\tTotal Balances = " << Total;

}

void BackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");

    ShowTransactionsMenueScreen();
}

void PreformTransactionsMenueScreen(enTransactionOptions Option)
{
    switch (Option)
    {
    case enDeposit:
        system("cls");
        ShowDepositScreen();
        BackToTransactionsMenue();
        break;
    case enWithdraw:
        system("cls");
        ShowWithdrawScreen();
        BackToTransactionsMenue();
        break;
    case enTotalBalance:
        system("cls");
        ShowTotalBalanceList();
        BackToTransactionsMenue();
        break;
    case enMainMenue:
        ShowMainMinueScreen();
        break;
    default:
        break;
    }
}

void ShowTransactionsMenueScreen()
{
    if (!CheckAccessPermission(pTransactions))
    {
        ShowAccessDeniedMessage();
        BackToMainMenue();
        return;
    }

    system("cls");

    cout << "==============================================================\n";
    cout << "\t\t\Transactions Minue Screen\n";
    cout << "==============================================================\n";
    cout << "\t [1] Deposit.\n";
    cout << "\t [2] Withdraw.\n";
    cout << "\t [3] TotalBalance.\n";
    cout << "\t [4] MainMenue.\n";
    cout << "==============================================================\n";

    PreformTransactionsMenueScreen((enTransactionOptions)ReadOption(1));

}

void ShowAllUsersScreen()
{
    vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") Client(s)";
    cout << "\n______________________________________________________________________";
    cout << "__________________________________________________\n" << endl;

    cout << "| " << setw(15) << left << "User Name";
    cout << "| " << setw(10) << left << "Password";
    cout << "| " << setw(40) << left << "Permissions";

    cout << "\n______________________________________________________________________";
    cout << "__________________________________________________\n" << endl;

    if (vUsers.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";

    else
    {
        for (auto U : vUsers)
        {
            PrintUserRecordLine(U);

            cout << "\n";
        }
    }

    cout << "\n______________________________________________________________________";
    cout << "__________________________________________________\n" << endl;


}

//======================================================

void ShowListUsersScreen()
{
    if (!CheckAccessPermission(pListClients))
    {
        ShowAccessDeniedMessage();
        BackToMainMenue();
        return;
    }

    ShowAllUsersScreen();
}

void ShowAddNewUserScreen()
{
    cout << "\n____________________________________________\n";
    cout << "\tAdd New User Screen\n";
    cout << "____________________________________________\n";

    AddUsers();
}

void ShowDeleteUsersScreen()
{

    cout << "\n____________________________________________\n";
    cout << "\tDelete User Screen\n";
    cout << "____________________________________________\n";

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUsername();

    DeleteUserByUsername(Username, vUsers);
}

void ShowUpdateUsersScreen()
{
    cout << "\n____________________________________________\n";
    cout << "\tUpdate User Info Screen\n";
    cout << "____________________________________________\n";

    vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUsername();

    UpdateUserByUsername(Username, vUsers);
}

void ShowFindUsersScreen()
{
    cout << "\n____________________________________________\n";
    cout << "\tFind User Screen\n";
    cout << "____________________________________________\n";

    vector<stUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    stUser User;

    string Username = ReadUsername();

    if (FindUsersByUsername(Username, vUsers, User))
        PrintUserCard(User);
    else
        cout << "\nUser with Username(" << Username << ") Not exist!";

}

void BackToManageUsersScreen()
{
    cout << "\n\nPress any key to go back to Manage Users Menue...";
    system("pause>0");

    ShowManageUsersMenueScreen();
}

void PreformManageUsersMenueOption(enManageUserMenueOptions ManageUserOptions)
{
    switch (ManageUserOptions)
    {
    case eListUsers:
        system("cls");
        ShowListUsersScreen();
        BackToManageUsersScreen();
        break;

    case eAddNewUser:
        system("cls");
        ShowAddNewUserScreen();
        BackToManageUsersScreen();
        break;

    case eDeleteUser:
        system("cls");
        ShowDeleteUsersScreen();
        BackToManageUsersScreen();
        break;

    case eUpdateUser:
        system("cls");
        ShowUpdateUsersScreen();
        BackToManageUsersScreen();
        break;

    case eFindUser:
        system("cls");
        ShowFindUsersScreen();
        BackToManageUsersScreen();
        break;

    case eGoBackMeneuScreen:
        system("cls");
        BackToMainMenue(1);
        break;
    }
}

void ShowManageUsersMenueScreen()
{

    if (!CheckAccessPermission(pManageUsers))
    {
        ShowAccessDeniedMessage();
        BackToMainMenue();
        return;
    }

    system("cls");

    cout << "==============================================================\n";
    cout << "\t\t\tManage Users Menu Screen\n";
    cout << "==============================================================\n";
    cout << "\t [1] List Users.\n";
    cout << "\t [2] Add New User.\n";
    cout << "\t [3] Delete User.\n";
    cout << "\t [4] Update User Info.\n";
    cout << "\t [5] Find User.\n";
    cout << "\t [6] Main Menue.\n";
    cout << "==============================================================\n";

    PreformManageUsersMenueOption((enManageUserMenueOptions)ReadManageUsersMenueOption());

}

void PreformMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case eShowClientList:
        system("cls");
        ShowAllClients();
        BackToMainMenue();
        break;

    case eAddClient:
        system("cls");
        ShowAddNewClientsScreen();
        BackToMainMenue();
        break;

    case eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        BackToMainMenue();
        break;

    case eUpdateClientInfo:
        system("cls");
        ShowUpdateClientScreen();
        BackToMainMenue();
        break;

    case eFindClient:
        system("cls");
        ShowFindClientScreen();
        BackToMainMenue();
        break;

    case eTransactions:
        system("cls");
        ShowTransactionsMenueScreen();
        break;

    case eManageUsers:
        system("cls");
        ShowManageUsersMenueScreen();
        break;

    case eExit:
        system("cls");
        //ShowEndScreen();
        Login();
        break;
    }
}

void ShowMainMinueScreen()
{
    system("cls");

    cout << "==============================================================\n";
    cout << "\t\t\tMain Minue Screen\n";
    cout << "==============================================================\n";
    cout << "\t [1] Show Client List.\n";
    cout << "\t [2] Add New Client.\n";
    cout << "\t [3] Delete Client.\n";
    cout << "\t [4] Update Client Info.\n";
    cout << "\t [5] Find Client.\n";
    cout << "\t [6] Transactions.\n";
    cout << "\t [7] Manage Users.\n";
    cout << "\t [8] Logout.\n";
    cout << "==============================================================\n";

    PreformMainMenueOption((enMainMenueOptions)ReadOption());

}

bool LoadUserInfo(string Username, string Password)
{
    if (FindUserByUsernameAndPassword(Username, Password, CurrentUser))
        return true;
    else
        return false;
}

void Login()
{
    string Username, Password;

    bool LoginFaild = false;

    do
    {
        system("cls");

        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";

        if (LoginFaild)
            cout << "Invalid Username/Password!\n";

        cout << "Enter Username? ";
        cin >> Username;


        cout << "Enter Password? ";
        cin >> Password;

        LoginFaild = !LoadUserInfo(Username, Password);

    } while (LoginFaild);

    ShowMainMinueScreen();

}

int main()
{
    Login();

    system("pause>0");
    return 0;
}

