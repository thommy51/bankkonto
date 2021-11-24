#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <string>

using namespace std;

string pin;
string checkpin;
string kontonr;
string guthaben;
string recipient;
string betrag;

int kontoStart();
int einzahlung(string& s);
int auszahlen(string& s);
int checkguthaben(void* NotUsed, int argc, char** argv, char** azColName);
int guthabenabfrage();
int transfer(string& r, string& b);




int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        checkpin = argv[i];
    }
    return 0;
}


int startQuery(string &s) {
    sqlite3* db;
    char* zErrMsg = 0;
    string rc;


    rc = sqlite3_open("E:\\sqlite\\databases\\bank.db", &db);
    string query = "SELECT pin from user WHERE kontonr = " + s;
    rc = sqlite3_exec(db, query.c_str(), callback, NULL, &zErrMsg);

    sqlite3_close(db);

    return 0;
}
int checkguthaben(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        guthaben = argv[i];
        return 0;
    }
}
int checkPin(string &s) {

    if (checkpin == pin)
    {
        system("cls");
        kontoStart();
    }
    else {
        exit(0);
    };

    return 0;
}

int kontoStart() {

    int entscheidung;
    string einzahlen;
    string ausbezahlen;

    do{
        system("cls");
        guthabenabfrage();
        std::cout << "\nIhr Kontostand betraegt: " << guthaben;

        cout << "\n\n 1. Moechten Sie Geld einzahlen ?";
        cout << "\n 2. Moechten Sie Geld auszahlen ?";
        cout << "\n 3. Geld zu überweisen.\n\n";
        cout << "\n 4. Um zu verlassen.\n\n";
        cin >> entscheidung;

        if (entscheidung == 1)
        {
            system("cls");

            cout << "Wie viel Geld moechten Sie einzahlen ?: "; cin >> einzahlen;

            einzahlung(einzahlen);

        }
        else if (entscheidung == 2) {
            system("cls");

            cout << "Wie viel Geld moechten Sie ausbezahlen ?: "; cin >> ausbezahlen;

            auszahlen(ausbezahlen);
        }
        else if (entscheidung == 3) {
            system("cls");

            cout << ("Bitte geben Sie die Kontonr des Empfaengers ein: "); cin >> recipient;
            cout << ("Bitte geben Sie den Betrag ein: "); cin >> betrag;

            transfer(recipient, betrag);
           
        }
    } while (entscheidung != 4);
    return 0;
}

int transfer(string& r, string& b) {
    sqlite3* db;
    string rc;

    rc = sqlite3_open("E:\\sqlite\\databases\\bank.db", &db);

    string query = "UPDATE user SET guthaben = (guthaben - " + b + ") WHERE kontonr = " + kontonr + "; UPDATE user SET guthaben = (guthaben + " + b + ") WHERE kontonr = " + r +";";

    rc = sqlite3_exec(db, query.c_str(), checkguthaben, NULL, NULL);

    sqlite3_close(db);

    return 0;
}

int guthabenabfrage() {

    sqlite3* db;
    string rc;

    rc = sqlite3_open("E:\\sqlite\\databases\\bank.db", &db);

    string query = "SELECT guthaben FROM user WHERE kontonr =" + kontonr;

    rc = sqlite3_exec(db, query.c_str(), checkguthaben, NULL, NULL);

    sqlite3_close(db);

    return 0;

}

int einzahlung(string &s) {
    sqlite3* db;
    string rc;

    rc = sqlite3_open("E:\\sqlite\\databases\\bank.db", &db);

    string query = "UPDATE user SET guthaben = ( guthaben +"+ s +") WHERE kontonr = " + kontonr;

    rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);

    sqlite3_close(db);

    return 0;
}

int auszahlen(string& s) {
    sqlite3* db;
    string rc;

    rc = sqlite3_open("E:\\sqlite\\databases\\bank.db", &db);

    string query = "UPDATE user SET guthaben = ( guthaben -" + s + ") WHERE kontonr = " + kontonr;

    rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);

    sqlite3_close(db);

    return 0;
}

int main()
{

    cout << "Geben Sie ihre Kontonr ein: "; cin >> kontonr;
    startQuery(kontonr);

    cout << "Geben Sie ihre Pin ein: "; cin >> pin;
    checkPin(pin);

    return 0;
}