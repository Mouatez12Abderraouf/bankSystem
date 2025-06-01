#include<iostream>
#include<vector>
#include<fstream>
#include <iomanip>
#include<string>
#include "C:/abderraouf/project.C++/ProgrammingAdvaices/inputLib_h"
using namespace std;

const string fileUsers = "C:/abderraouf/database_project7/bankAdmin.txt";

const string nameFile = "C:/abderraouf/database_project7/bankClient.txt";

enum opTransaction 
{Deposit = 1, Withdraw = 2, TotalBalances = 3, MainMenu = 4};

enum opMineMenu 
{ ShowClientsList = 1, AddNewClient = 2, DeleteClient = 3, UpdateClientInfo = 4, FindClient = 5, Transactions = 6, ManageUsers = 7, Logout = 8};

enum opManageMenu
{ListUsers = 1, AddNewUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, MainMenue = 6};

struct bankClient
{
    string numberAccount, pinCode, nameClient, phoneClient;
    double accountBalance;
    bool MarkForDelete = false;
};

struct bankUsers 
{
    string userName, password;
    short permeation = 0;
    bool MarkForDelete = false;
};

bankUsers correntUser;

vector<string> readFromFile(string fileName)
{
    fstream myFile;
    vector<string> vString;

    myFile.open(fileName, ios::in);

    if (myFile.is_open())
    {
        string line;

        while (getline(myFile, line))
        {
            vString.push_back(line);
        }
        myFile.close();
    }
    return vString;
}

void printData(bankClient b1)
{
    cout << "The follwing are client details:\n\n";
    cout << string(35, '-') << endl;

    cout << "Account Numbe  : " << b1.numberAccount << endl;
    cout << "Pin code       : " << b1.pinCode << endl;
    cout << "Name           : " << b1.nameClient << endl;
    cout << "phone          : " << b1.phoneClient << endl;
    cout << "Account Balance: " << b1.accountBalance << endl;
    cout << string(35, '-') << endl << endl;
}

void printData(bankUsers b1)
{
    cout << "The follwing are client details:\n\n";
    cout << string(35, '-') << endl;

    cout << "username       : " << b1.userName << endl;
    cout << "password       : " << b1.password << endl;
    cout << "permeation     : " << b1.permeation << endl;
 
    cout << string(35, '-') << endl << endl;
}

vector<string> splitString(string s1, string delim = "#//#")
{
    vector<string> vString;
    short pos;
    string subString;

    while ((pos = s1.find(delim)) != string::npos)
    {
        subString = s1.substr(0, pos);

        if (subString != "")
        {
            vString.push_back(subString);
        }

        s1 = s1.erase(0, pos + delim.length());
    }

    if (s1 != "")
    {
        vString.push_back(s1);
    }
    return vString;
}

bankClient convertStringToRecordClient(string data, string delim = "#//#")
{
    bankClient b1;
    vector<string> vString;

    vString = splitString(data, delim);
    b1.numberAccount = vString.at(0);
    b1.pinCode = vString.at(1);
    b1.nameClient = vString.at(2);
    b1.phoneClient = vString.at(3);
    b1.accountBalance = stod(vString[4]);

    return b1;
}

bankUsers convertStringToRecordUser(string data, string delim = "#//#")
{
    bankUsers b1;
    vector<string> vString;

    vString = splitString(data, delim);

    b1.userName = vString.at(0);
    b1.password = vString.at(1);
    b1.permeation = stoi(vString.at(2));

    return b1;
}

vector<bankClient> FillListOfClients()
{
    vector<bankClient> ListClients;
    vector<string> ContainerOfFile;

    ContainerOfFile = readFromFile(nameFile);

    for (short i = 0; i < ContainerOfFile.size(); i++)
    {
        ListClients.push_back(convertStringToRecordClient(ContainerOfFile.at(i)));
    }
    return ListClients;
}

vector<bankUsers> FillListOfUsers()
{
    vector<bankUsers> ListUsers;
    vector<string> ContainerOfFile;

    ContainerOfFile = readFromFile(fileUsers);

    for (short i = 0; i < ContainerOfFile.size(); i++)
    {
        ListUsers.push_back(convertStringToRecordUser(ContainerOfFile.at(i)));
    }
    return ListUsers;
}

vector<bankClient> loadClientsDataFromFile()    // method of abu-hadhoud, and we can ignore 2 method (fillListOfClients, readFromFile)
{
    fstream myFile;
    vector<bankClient> vClients;

    myFile.open(nameFile, ios::in);
    if (myFile.is_open())
    {
        bankClient b1;
        string line;

        while (getline(myFile, line))
        {
            b1 = convertStringToRecordClient(line);
            vClients.push_back(b1);
        }
        myFile.close();
    }
    return vClients;
}

vector<bankUsers> loadUsersDataFromFile()    // method of abu-hadhoud, and we can ignore 2 method (fillListOfClients, readFromFile)
{
    fstream myFile;
    vector<bankUsers> vUsers;

    myFile.open(fileUsers, ios::in);
    if (myFile.is_open())
    {
        bankUsers b1;
        string line;

        while (getline(myFile, line))
        {
            b1 = convertStringToRecordUser(line);
            vUsers.push_back(b1);
        }
        myFile.close();
    }
    return vUsers;
}

string readAccountNumber()
{
    string AccNumber;

    cout << "Please enter Account Number?\n";
    cin >> AccNumber;

    return AccNumber;
}

string readUsername()
{
    string username;

    cout << "Please enter username?\n";
    cin >> username;

    return username;
}

void printTitleListClients(short numClient)
{
    cout << setw(60) << "Client List (" << numClient << ") Client(s)." << "\n\n";
}

void printHeaderListClients()
{
    cout << string(120, '-');
    cout << "\n\n";
    cout << "| " << left << setw(15) << "Account Number"
        << "| " << left << setw(12) << "Pin Code"
        << "| " << left << setw(60) << "Client Name"
        << "| " << left << setw(15) << "Phone"
        << "| " << left << setw(10) << "Balance";
    cout << "\n";
    cout << string(120, '-');
}

void printDataOfRecord(bankClient client)
{

    cout << "| " << left << setw(15) << client.numberAccount
        << "| " << left << setw(12) << client.pinCode
        << "| " << left << setw(60) << client.nameClient
        << "| " << left << setw(15) << client.phoneClient
        << "| " << left << setw(10) << client.accountBalance
        << endl;

}

void printListTableOfClients()
{
    system("cls");

    vector<bankClient> vClients = loadClientsDataFromFile();
    printTitleListClients(vClients.size());
    printHeaderListClients();

    cout << "\n\n";

    for (bankClient& client : vClients)
    {
        printDataOfRecord(client);
    }

    cout << string(120, '-');
}

void printMenu()
{
	cout << string(50, '=') << endl;
	cout << right << setw(34) <<  "Main Menu Screen \n";
	cout << string(50, '=') << endl;
	cout << right << setw(33) << "[1] Show Clients List. \n";
	cout << right << setw(30) << "[2] Add New Client. \n";
	cout << right << setw(29) << "[3] Delete Client. \n";
	cout << right << setw(34) << "[4] Update Client Info. \n";
	cout << right << setw(27) << "[5] Find Client. \n";
	cout << right << setw(28) << "[6] Transactions. \n";
    cout << right << setw(28) << "[7] Manage Users. \n";
    cout << right << setw(22) << "[8] Logout. \n";
	cout << string(50, '=') << endl;

}

short readChoice()
{
    short choice;
    cout << "choose what do you want to do? [1 - 8]? ";
    cin >> choice;
    return choice;
}

void printHeaderToAddClient()
{
    system("cls");
    cout << string(35, '-') << endl;
    cout << right << setw(29) << "Add New Clients Screen" << endl;
    cout << string(35, '-') << endl;

}

void printHeaderToAddUser()
{
    system("cls");
    cout << string(35, '-') << endl;
    cout << right << setw(29) << "Add New User Screen" << endl;
    cout << string(35, '-') << endl;

}

void printHeaderToDeleteClient()
{
    system("cls");
    cout << string(35, '-') << endl;
    cout << right << setw(29) << "Delete Client screen" << endl;
    cout << string(35, '-') << endl;

}

void printHeaderToFindClient()
{
    system("cls");
    cout << string(35, '-') << endl;
    cout << right << setw(29) << "find Client screen" << endl;
    cout << string(35, '-') << endl;

}

void printHeaderToFindUser()
{
    system("cls");
    cout << string(35, '-') << endl;
    cout << right << setw(29) << "find User screen" << endl;
    cout << string(35, '-') << endl;

}

void printHeaderToDeleteUser()
{
    system("cls");
    cout << string(35, '-') << endl;
    cout << right << setw(29) << "Delete User screen" << endl;
    cout << string(35, '-') << endl;

}

void printHeaderToUpdateClient()
{
    system("cls");
    cout << string(35, '-') << endl;
    cout << right << setw(29) << "Update Client info Screen" << endl;
    cout << string(35, '-') << endl;

}

void printHeaderToUpdateUser()
{
    system("cls");
    cout << string(35, '-') << endl;
    cout << right << setw(29) << "Update User info Screen" << endl;
    cout << string(35, '-') << endl;

}

void printHeaderToFindClientByAccountNumber()
{
    system("cls");
    cout << string(35, '-') << endl;
    cout << right << setw(29) << "find Client Screen" << endl;
    cout << string(35, '-') << endl;

}

void printheaderToEndProgram()
{
    system("cls");
    cout << string(35, '-') << endl;
    cout << right << setw(29) << "programme Ends" << endl;
    cout << string(35, '-') << endl;

}

bool findClientByAccountNumber(string AccNumber, vector<bankClient> vClients, bankClient& b1)
{
    for (bankClient& c : vClients)
    {
        if (c.numberAccount == AccNumber)
        {
            b1 = c;
            return true;
        }
    }
    return false;
}

bool findUserByUsername(string username, vector<bankUsers> vUsers, bankUsers& b1)
{
    for (bankUsers& u : vUsers)
    {
        if (u.userName == username)
        {
            b1 = u;
            return true;
        }
    }
    return false;
}

bool findClientByAccountNumber(string AccNumber)
{
    vector<bankClient> vClients = loadClientsDataFromFile();

    for (bankClient& c : vClients)
    {
        if (c.numberAccount == AccNumber)
        {
            return true;
        }
    }
    return false;
}

bool findUserByUsername(string Username)
{
    vector<bankUsers> vUsers = loadUsersDataFromFile();

    for (bankUsers& u : vUsers)
    {
        if (u.userName == Username)
        {
            return true;
        }
    }
    return false;
}

void printResultOfFindingClient()
{
    bankClient* ptrClient;
    string AccNumber;
    vector<bankClient> vClients = loadClientsDataFromFile();

    printHeaderToFindClient();
    AccNumber = readAccountNumber();
    ptrClient = new bankClient;

    if (findClientByAccountNumber(AccNumber, vClients, *ptrClient))
    {
        printData(*ptrClient);
        cout << "\n\n";
    }
    else
    {
        cout << "Client with Account Number (" << AccNumber << ") Not found!\n\n";
    }

    delete ptrClient;
}

void printResultOfFindingUser()
{
    bankUsers* ptrUser;
    string username;
    vector<bankUsers> vUser = loadUsersDataFromFile();

    printHeaderToFindUser();
    username = readUsername();
    ptrUser = new bankUsers;

    if (findUserByUsername(username, vUser, *ptrUser))
    {
        printData(*ptrUser);
        cout << "\n\n";
    }
    else
    {
        cout << "user with username (" << username << ") Not found!\n\n";
    }

    delete ptrUser;
}

bankClient readInfoClient()
{
    bankClient b1;

    cout << "Enter Account Number? ";
    do {
        b1.numberAccount = inputPrimitive::readString();
        if (!findClientByAccountNumber(b1.numberAccount))
        {
            break;
        }
        cout << "Client with [" << b1.numberAccount << "] already exists, Enter another Account Number?\n";

    } while (true);


    cout << "Enter PinCode? ";
    cin >> b1.pinCode;

    cin.ignore();

    cout << "Enter Name? ";
    b1.nameClient = inputPrimitive::readString();

    cout << "Enter Phone? ";
    cin >> b1.phoneClient;

    cout << "Enter AccountBalance? ";
    cin >> b1.accountBalance;

    return b1;
}

short shift(short num, short pos)
{
    short permeation = num;
    for (short i = 0; i < pos; i++)
    {
        permeation = permeation << 1;
    }

    return permeation;
}

short setPermeation()
{
    short permeation = 0, Co = 0;
    char off_on;

    cout << "\nDo you want to give access to:\n\n";
    while (Co != 7)
    {
        switch (Co)
        {
        case 0:
            cout << "Show Client List? [y/n]? ";
            break;

        case 1:
            cout << "Add New Client? [y/n]? ";
            break;

        case 2:
            cout << "Delete Client? [y/n]? ";
            break;

        case 3:
            cout << "Update Client? [y/n]? ";
            break;

        case 4:
            cout << "Find Client? [y/n]? ";
            break;

        case 5:
            cout << "Transactions? [y/n]? ";
            break;

        case 6:
            cout << "Manage Users? [y/n]? ";
            break;
        }
        cin >> off_on;
        cout << "\n";
        if (toupper(off_on) == 'Y')
        {
            permeation += shift(1, Co);
        }
        Co++;
    }
    return permeation;
}

bankUsers readInfoUser()
{
    bankUsers b1;
    char AllPermeation;
    

    cout << "Adding New User:\n\n";

    cout << "Enter Username? ";
    do {
        b1.userName = inputPrimitive::readString();
        if (!findUserByUsername(b1.userName))
        {
            break;
        }
        cout << "user with [" << b1.userName << "] already exists, Enter another username?\n";

    } while (true);


    cout << "Enter password? ";
    b1.password = inputPrimitive::readString();

    cout << "Do you want to give full access? [y/n]? ";
    cin >> AllPermeation;

    if (toupper(AllPermeation) == 'Y')
    {
        b1.permeation = -1;
        return b1;
    }
    else
    {
        b1.permeation = setPermeation();
    }
    return b1;
}

string convertRecordToString(bankClient b1, string delim = "#//#")
{
    return b1.numberAccount + delim + b1.pinCode + delim + b1.nameClient + delim
        + b1.phoneClient + delim + to_string(b1.accountBalance);
}

string convertRecordToString(bankUsers b1, string delim = "#//#")
{
    return b1.userName + delim + b1.password + delim + to_string(b1.permeation);
}


void writeDataInFile(string fileName,string s1)
{
    fstream myFile;

    myFile.open(fileName, ios::out | ios::app);

    if (myFile.is_open())
    {
        myFile << s1 << endl;

        myFile.close();
    }
}

void addCient()
{
    bankClient b1;

    b1 = readInfoClient();
    writeDataInFile(nameFile, convertRecordToString(b1));
}

void addUser()
{
    bankUsers b1;

    b1 = readInfoUser();
    writeDataInFile(fileUsers, convertRecordToString(b1));
}

void addListOfClient()
{
    char off_on;
    vector<bankClient> vClients = loadClientsDataFromFile();

    do
    {
        system("cls");
        printHeaderToAddClient();

        addCient();
        vClients = loadClientsDataFromFile();

        cout << "Client Successfully, do you want to add more clients?[y/n]?:\n";

    errorInput:

        cin >> off_on;

        if (toupper(off_on) != 'Y' && toupper(off_on) != 'N')
        {
            cout << "Enter [y/n]?: ";
            goto errorInput;
        }

    } while (toupper(off_on) == 'Y');

}

void addListOfUser()
{
    char off_on;
    vector<bankUsers> vUsers = loadUsersDataFromFile();

    do
    {
        system("cls");
        printHeaderToAddUser();

        addUser();
        vUsers = loadUsersDataFromFile();

        cout << "User Successfully, do you want to add more users?[y/n]?:\n";

    errorInput:

        cin >> off_on;

        if (toupper(off_on) != 'Y' && toupper(off_on) != 'N')
        {
            cout << "Enter [y/n]?: ";
            goto errorInput;
        }

    } while (toupper(off_on) == 'Y');

}

string joinString(bankClient b1, string delim = "#//#")
{
    return b1.numberAccount + delim + b1.pinCode + delim + b1.nameClient + delim
        + b1.phoneClient + delim + to_string(b1.accountBalance);
}

string joinString(bankUsers b1, string delim = "#//#")
{
    return b1.userName + delim + b1.password + delim + to_string(b1.permeation);
}

bool MarkClientForDeleteByAccountNumber(string AccNumber, vector<bankClient>& vClients)
{
    for (bankClient& c : vClients)
    {
        if (c.numberAccount == AccNumber)
        {
            c.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

bool MarkUserForDeleteByAccountNumber(string username, vector<bankUsers>& vUsers)
{
    for (bankUsers& c : vUsers)
    {
        if (c.userName == username)
        {
            c.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector<bankClient> saveClientDataToFile(vector<bankClient> vClients)
{
    fstream myFile;

    myFile.open(nameFile, ios::out);

    if (myFile.is_open())
    {
        string data;

        for (bankClient& c : vClients)
        {
            if (!c.MarkForDelete)
            {
                data = joinString(c);
                myFile << data << endl;
            }
        }
        myFile.close();
    }
    return vClients;
}

vector<bankUsers> saveUserDataToFile(vector<bankUsers> vUsers)
{
    fstream myFile;

    myFile.open(fileUsers, ios::out);

    if (myFile.is_open())
    {
        string data;

        for (bankUsers& c : vUsers)
        {
            if (!c.MarkForDelete)
            {
                data = joinString(c);
                myFile << data << endl;
            }
        }
        myFile.close();
    }
    return vUsers;
}

bool deleteClientFromFile()
{
    bankClient b1;
    char off_on;
    string AccNumber;

    printHeaderToDeleteClient();
    AccNumber = readAccountNumber();

    vector<bankClient> vClients = loadClientsDataFromFile();

    if (findClientByAccountNumber(AccNumber, vClients, b1))
    {
        printData(b1);
        cout << "\n\nAre you sure you want to delete this client? [y/n]:";
        cin >> off_on;

        if (toupper(off_on) == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccNumber, vClients);
            saveClientDataToFile(vClients);

            vClients = loadClientsDataFromFile();
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccNumber
            << ") is Not Found!";
        return false;
    }
}

bool deleteUserFromFile()
{
    bankUsers b1;
    char off_on;
    string userName;

    printHeaderToDeleteUser();
    userName = readUsername();

    vector<bankUsers> vUsers = loadUsersDataFromFile();

    if (findUserByUsername(userName, vUsers, b1))
    {
        if (b1.permeation == -1)
        {
            cout << "You cannot delete this user.\n\n";
            return false;
        }
        printData(b1);
        cout << "\n\nAre you sure you want to delete this user? [y/n]:";
        cin >> off_on;

        if (toupper(off_on) == 'Y')
        {
            MarkUserForDeleteByAccountNumber(userName, vUsers);
            saveUserDataToFile(vUsers);

            vUsers = loadUsersDataFromFile();
            cout << "\n\nClient user Successfully.";
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        cout << "\nUser with username (" << userName
            << ") is Not Found!";
        return false;
    }
}

bankClient updateClientData(bankClient b1)
{

    cout << "Enter PinCode? ";
    cin >> b1.pinCode;

    cout << "Enter Name? ";
    b1.nameClient = inputPrimitive::readString();

    cout << "Enter Phone? ";
    cin >> b1.phoneClient;

    cout << "Enter AccountBalance? ";
    cin >> b1.accountBalance;

    return b1;
}

bankUsers updateUserData(bankUsers b1)
{
    char AllPermeation;

    cout << "Enter password? ";

    b1.password = inputPrimitive::readString();

    cout << "Do you want to give full access? [y/n]? ";
    cin >> AllPermeation;

    if (toupper(AllPermeation) == 'Y')
    {
        b1.permeation = -1;
        return b1;
    }
    else
    {
        b1.permeation = setPermeation();
    }
    return b1;
    

    return b1;
}

bool updateClientDataByAccountNumber()
{
    bankClient b1;
    char off_on;
    string AccNumber;

    printHeaderToUpdateClient();
    AccNumber = readAccountNumber();
    vector<bankClient> vClients = loadClientsDataFromFile();

    if (findClientByAccountNumber(AccNumber, vClients, b1))
    {
        printData(b1);
        cout << "Are you sure you want to update this client? [y/n]? ";
        cin >> off_on;

        if (toupper(off_on) == 'Y')
        {
            b1 = updateClientData(b1);

            for (bankClient& c : vClients)
            {
                if (c.numberAccount == AccNumber)
                {
                    c = b1;
                    saveClientDataToFile(vClients);
                    cout << "\n\nClient updated Successfully.";
                    return true;
                }
            }

        }
    }
    else
    {
        cout << "\n\nClient with Account Number (" << AccNumber << ") Not found!\n";
        return false;
    }
}

bool updateUserDataByUsername()
{
    bankUsers b1;
    char off_on;
    string username;

    printHeaderToUpdateUser();
    username = readUsername();
    vector<bankUsers> vUsers = loadUsersDataFromFile();

    if (findUserByUsername(username, vUsers, b1))
    {
        printData(b1);
        cout << "Are you sure you want to update this user? [y/n]? ";
        cin >> off_on;

        if (toupper(off_on) == 'Y')
        {
            b1 = updateUserData(b1);

            for (bankUsers& c : vUsers)
            {
                if (c.userName == username)
                {
                    c = b1;
                    saveUserDataToFile(vUsers);
                    cout << "\n\nUser updated Successfully.";
                    return true;
                }
            }

        }
    }
    else
    {
        cout << "\n\nUser with username (" << username << ") Not found!\n";
        return false;
    }
}

void printHeaderTransactions()
{
    system("cls");
    cout << string(35, '-') << endl;
    cout << right << setw(29) << "Transaction menu Screen" << endl;
    cout << string(35, '-') << endl;
}

void printHeaderDeposit()
{
    system("cls");
    cout << string(35, '-') << endl;
    cout << right << setw(29) << "Deposite Screen" << endl;
    cout << string(35, '-') << endl;
}

void printHeaderWithDraw()
{
    system("cls");
    cout << string(35, '-') << endl;
    cout << right << setw(29) << "Withdraw Screen" << endl;
    cout << string(35, '-') << endl;
}

void showMenuOfTransaction();

bool DepositBalancesToClientsByAccountNumber(string AccNumber, float Amount, vector<bankClient>& vClients)
{

    for (bankClient& c : vClients)
    {
        if (c.numberAccount == AccNumber)
        {
            c.accountBalance += Amount;
            saveClientDataToFile(vClients);
            cout << "done successfully new balance : " << c.accountBalance << endl;
            cout << "press any key to go back to transaction menu...";
            system("pause>0");
            return true;
        }
    }
    return false;
}

void DepositClient()
{
    vector<bankClient> vClients;
    bankClient b1;
    float Amount;
    char check;
    string AccNumber;

    printHeaderDeposit();

    vClients = loadClientsDataFromFile();

    begin:
    AccNumber = readAccountNumber();

    if (findClientByAccountNumber(AccNumber, vClients, b1))
    {
        printData(b1);
        cout << "Please enter deposit amount? ";
        cin >> Amount;

        cout << "\n\nAre you sure you want perform this transaction? [y/n]? ";
        cin >> check;
        if (toupper(check) == 'Y')
        {
            DepositBalancesToClientsByAccountNumber(AccNumber, Amount, vClients);
            
        }

        showMenuOfTransaction();
    }
    else
    {
        cout << "\n\nClient with Account Number (" << AccNumber << ") Not found!\n";
        goto begin;
    }
}

void WithdrawClient()
{
    vector<bankClient> vClients;
    bankClient b1;
    float Amount;
    char check;
    string AccNumber;

    printHeaderWithDraw();

    vClients = loadClientsDataFromFile();

begin:
    AccNumber = readAccountNumber();

    if (findClientByAccountNumber(AccNumber, vClients, b1))
    {
        printData(b1);
        inputWithdraw:
        cout << "Please enter withdraw amount? ";
        cin >> Amount;

        if (Amount > b1.accountBalance)
        {
            cout << "Amount Exceeds the balance, you can withdraw up to : " << b1.accountBalance << endl;
            goto inputWithdraw;
        }

        cout << "\n\nAre you sure you want perform this transaction? [y/n]? ";
        cin >> check;
        if (toupper(check) == 'Y')
        {
            DepositBalancesToClientsByAccountNumber(AccNumber, -1 * Amount, vClients);
        }

        showMenuOfTransaction();
    }
    else
    {
        cout << "\n\nClient with Account Number (" << AccNumber << ") Not found!\n";
        goto begin;
    }
}

void printHeaderTransaction()
{
    cout << string(120, '-');
    cout << "\n\n";
    cout << "| " << left << setw(15) << "Account Number"
        << "| " << left << setw(60) << "Client Name"
        << "| " << left << setw(10) << "Balance";
    cout << "\n";
    cout << string(120, '-');
}

void printDataOfRecordTransaction(bankClient client)
{

    cout << "| " << left << setw(15) << client.numberAccount
        << "| " << left << setw(60) << client.nameClient
        << "| " << left << setw(10) << client.accountBalance
        << endl;

}

float CalculateTotalBalances(vector<bankClient> vClient)
{
    float total = 0;
    for (bankClient& C : vClient)
    {
        total += C.accountBalance;
    }
    return total;
}

void printTable()
{
    vector<bankClient> vClient;
    system("cls");
    vClient = loadClientsDataFromFile();

    printTitleListClients(vClient.size());
    printHeaderTransaction();

    cout << "\n\n";

    for (bankClient& client : vClient)
    {
        printDataOfRecordTransaction(client);
    }

    cout << string(120, '-') << endl;

    cout << "\t\t\t\t\t\tTotal Balances = " << CalculateTotalBalances(vClient) << endl << endl;

    cout << "press any key to go back to Transaction menu...";
    system("pause>0");

    showMenuOfTransaction();

}

opTransaction readChoiceOfTransaction()
{
    short ch;
    do
    {
        cout << "Choice what do you want to do? [1 to 4]? ";
        cin >> ch;

    } while (ch < 1 || ch > 4);
    return (opTransaction)ch;
}

void performTransactionOption(opTransaction opTransaction)
{
    switch (opTransaction)
    {
    case Deposit: 
        DepositClient();
        break;
    case Withdraw:
        WithdrawClient();
        break;
    case TotalBalances:
        printTable();
        break;
    case MainMenu:
        return;
    default:
        break;
    }
}

void showMenuOfTransaction()
{
    printHeaderTransactions();
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Mine menu.\n";
    cout << string(35, '-') << endl;

    performTransactionOption(readChoiceOfTransaction());
}

void witeToGoMineMenu()
{
    cout << "press any key to go back to main menu...";
    system("pause>0");
}

void printLoginHeader()
{
    system("cls");
    cout << string(35, '=') << endl;
    cout << right << setw(29) << "Login Screen" << endl;
    cout << string(35, '=') << endl;
}

void printManageHeader()
{
    system("cls");
    cout << string(35, '=') << endl;
    cout << right << setw(29) << "Manage Users Menu Screen" << endl;
    cout << string(35, '=') << endl;
}

opManageMenu readChoiceOfManage()
{
    short ch;
    do
    {
        cout << "Choice what do you want to do? [1 to 6]? ";
        cin >> ch;

    } while (ch < 1 || ch > 6);
    return (opManageMenu)ch;
}

bool isUser(string username, string password, bankUsers& correntUser)
{
    vector<bankUsers> vUsers;

    vUsers = FillListOfUsers();
    for (bankUsers user : vUsers)
    {
        if (user.userName == username && user.password == password)
        {
            correntUser = user;
            return true;
        }
        
    }
    return false;
}

void printManageMenu()
{
    printManageHeader();
   
    cout << right << setw(26) << "[1] List Users. \n";
    cout << right << setw(28) << "[2] Add New User. \n";
    cout << right << setw(27) << "[3] Delete User. \n";
    cout << right << setw(27) << "[4] Update User. \n";
    cout << right << setw(26) << "[5] Find User. \n";
    cout << right << setw(25) << "[6] Main Menu. \n";
    cout << string(35, '=') << endl;

}

void printTitleListUsers(short numUsers)
{
    cout << setw(60) << "Users List (" << numUsers << ") User(s)." << "\n\n";
}

void printHeaderListUsers()
{
    cout << string(120, '-');
    cout << "\n\n";
    cout << "| " << left << setw(10) << "User Name"
        << "| " << left << setw(12) << "Password"
        << "| " << left << setw(60) << "Permissions";
    cout << "\n";
    cout << string(120, '-');
}

void printDataOfRecord(bankUsers user)
{

    cout << "| " << left << setw(10) << user.userName
        << "| " << left << setw(12) << user.password
        << "| " << left << setw(60) << user.permeation
        << endl;

}

void printListTableOfUsers()
{
    system("cls");
    vector<bankUsers> vUsers = loadUsersDataFromFile();

    printTitleListUsers(vUsers.size());
    printHeaderListUsers();

    cout << "\n\n";

    for (bankUsers& user : vUsers)
    {
        printDataOfRecord(user);
    }

    cout << string(120, '-');
}

void showManageMenu();

void performManageOption(opManageMenu opManage)
{
    switch (opManage)
    {
    case opManageMenu::ListUsers:
        printListTableOfUsers();
        witeToGoMineMenu();
        break;
    case opManageMenu::AddNewUser:
        addListOfUser();
        witeToGoMineMenu();
        break;
    case opManageMenu::DeleteUser:
        deleteUserFromFile();
        witeToGoMineMenu();
        break;
    case opManageMenu::UpdateUser:
        updateUserDataByUsername();
        witeToGoMineMenu();
        break;
    case opManageMenu::FindUser:
        printResultOfFindingUser();
        witeToGoMineMenu();
        break;
    case opManageMenu::MainMenue:
        return;
    default:
        cout << "your chice is not valide.\n";
        witeToGoMineMenu();
        break;
    }
    showManageMenu();
}

void showManageMenu()
{
    system("cls");
    printManageMenu();
    opManageMenu choice = readChoiceOfManage();
    performManageOption(choice);

    return;
}

void loginScreen();

void selectOperation(short userChoice)
{
    switch (userChoice)
    {
    case opMineMenu::ShowClientsList:
        printListTableOfClients();
        witeToGoMineMenu();
        break;

    case opMineMenu::AddNewClient:
        addListOfClient();
        break;
        

    case opMineMenu::DeleteClient:
        deleteClientFromFile();
        witeToGoMineMenu();
        break;

    case opMineMenu::UpdateClientInfo:
        updateClientDataByAccountNumber();
        witeToGoMineMenu();
        break;

    case opMineMenu::FindClient:
        printResultOfFindingClient();
        witeToGoMineMenu();
        break;

    case opMineMenu::Transactions:
        showMenuOfTransaction();
        break;

    case opMineMenu::ManageUsers:
        showManageMenu();
        break;

    case opMineMenu::Logout:
        loginScreen();
        break;

    default:
        cout << "Error, your choice is not exist.\n\n";
        witeToGoMineMenu();
    }
    return;
}

bool checkUHavePermeation(short userChoice)
{
    vector<bankUsers> vUsers = loadUsersDataFromFile();

    if (correntUser.permeation == -1 || userChoice == 8)
    {
        return true;
    }
    else
    {
        userChoice = shift(1, userChoice - 1);
        return (userChoice & correntUser.permeation) ? true : false;
    }
}

void printUNotHavePermeation()
{
    cout << string(50, '-') << endl;
    cout << "Access Denied,\n"
         << "you dont have permeation To do this,\n"
         << "Please contact your admin.\n";
    cout << string(50, '-') << endl;

}

void startProgramme()
{
    
    opMineMenu userChoice;

    while (true)
    {
    begin:

        system("cls");
        printMenu();
        userChoice = (opMineMenu)readChoice();

        if (checkUHavePermeation(userChoice))
            selectOperation(userChoice);
        else
        { 
            system("cls");
            printUNotHavePermeation();
            witeToGoMineMenu();
            goto begin;
        }
        

    }

    printheaderToEndProgram();
    system("pause>0");
    return;


}

void loginScreen()
{
    
    string userName, password;
    bool loginFaild = false;
    do
    {
        system("cls");
        printLoginHeader();


        if (loginFaild)
        {
            cout << "Invlaid username/password!\n\n";
        }

        cout << "Enter Username? ";
        userName = inputPrimitive::readString();
        cout << "Enter password? ";
        password = inputPrimitive::readString();

        loginFaild = !isUser(userName, password, correntUser);

    } while (loginFaild);
    
        startProgramme();
        return;
   
}

int main()
{
    loginScreen();

    return 0;
}
