#pragma once

#include <QtWidgets/QMainWindow>
#include <QTableWidget>
#include <QMessageBox>
#include "ui_autoservis.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class FO
{
public:
    FO();
    ~FO();
    FO(int i, string n, string sur, string log, string pass);
    void setParameters(int i, string n, string sur, string log, string pass) { id = i; name = n; surname = sur; login = log; password = pass; };

    string getLogin() { return login; };
    string getPassword() { return password; };
    string getName() { return name; };
    string getSurname() { return surname; };

    int getID() { return id; };
private:
    int id;
    string name, surname, login,password;

};

class firm
{
public:
    firm();
    ~firm();
    firm(int i, int ic, string n, string log, string pass, bool platca);
    void setParameters(int i, int ic, string n, string log, string pass, bool platca) { id = i; ico = ic; name = n; login = log; password = pass; platcaDPH = platca; };

    string getLogin() { return login; };
    string getPassword() { return password; };
    string getName() { return name; };

    int getID() { return id; };
    int getIco() { return ico; };

    bool getInfo() { return platcaDPH; };
private:
    int id, ico;
    string name, login, password;
    bool platcaDPH;
};

class technik
{
public:
    technik();
    ~technik();
    technik(int i, string log, string pass);
    void setParameters(int i, string log, string pass) { id = i; login = log; password = pass; };
    string getLogin() { return login; };
    string getPassword() { return password; };

    int getID() { return id; };
private:
    int id;
    string login, password;
};

class administrator
{
public:
    administrator();
    ~administrator();
    administrator(int i, string log, string pass);
    void setParameters(int i, string log, string pass) { id = i; login = log; password = pass; };
    string getLogin() { return login; };
    string getPassword() { return password; };

    int getID() { return id; };
private:
    int id;
    string login, password;
};

class cars
{
public:
    cars();
    ~cars();

    void setParameter(string manu, string mod, int y, int i, int carIdentificator) { manufacturer = manu; model = mod; year = y; ID = i; carID = carIdentificator; };
    void setManufacturer(string manu) { manufacturer = manu; };
    void setModel(string mod) { model = mod; };
    void setYear(int y) { year = y; };
    void setCarID(int i) { carID = i; };
    void setIDOwner(int i) { ID = i; };


    int getID() { return ID; };
    int getYear() { return year; };
    int getCarID() { return carID; };
    string getManufacturer() { return manufacturer; };
    string getModel() { return model; };
private:
    string manufacturer, model;
    int year, ID, carID;
};

class sluzba
{
public:
    sluzba();
    ~sluzba();

    void setParameters(string pon, int p) { ponuka = pon; price = p; };
    void setParameters(string pon, int p, int n) { ponuka = pon; price = p; numbersOfItems = n; };
    void changeNumbersOfItems(int numbers) { numbersOfItems = numbers; };
    void changeStav(int newStav) { stav = newStav; };
    void setIdZakaznika(int id) { idZakaznika = id; };
    void setStav(int aktualny) { stav = aktualny; };
    void setPrice(int p) { price = p; };

    string getPonuka() { return ponuka; };
    int getPrice() { return price; };
    int getStav() { return stav; };
    int getIdZakaznika() { return idZakaznika; };
private:
    string ponuka;
    int price;
    int numbersOfItems;
    int stav;
    int idZakaznika;
};



class autoservis : public QMainWindow
{
    Q_OBJECT

public:
    autoservis(QWidget *parent = nullptr);
    ~autoservis();
    void readUsers(string name);
    void readCars(string name);
    void readSluzby(string name);
    void writeSluzby(string name, int currentID);
    void writeSluzby(string name);
    void readOrders(string name);
    void readOrdersForTechnik(string name);

    void addFOtoVec(FO fyzickaOsoba) { foVec.append(fyzickaOsoba); };
    void addFirmToVec(firm firma) { firmVec.append(firma); };
    void addTechnikToVec(technik tech) { technikVec.append(tech); };
    void addAdministratorToVec(administrator admin) { administratorVec.append(admin); };
    void addCarsToVec(cars car) { carsVec.append(car); };
    void addCurrentIdCarsToVec(cars car) { CurrentIdCarsVec.append(car); };
    void addSluzbaToVec(sluzba ponuka) { sluzbaVec.append(ponuka); };
    void addSluzbaToOrders(sluzba ponuka) { ordersVec.append(ponuka); };
    void addNumberOfOrders() { numberOfOrders++; };
    void setNumberOfOrders(int i) { numberOfOrders = i; };
    
    void writeAddedItem(sluzba item, string name);
    void writeAddFoToFile(FO f, string fileName);
    void writeAddFirmToFile(firm f, string fileName);
    void writeAddTechnikToFile(technik t, string fileName);
    void writeAddAdministrator(administrator a, string fileName);
    void writeAddNewCar(cars c, string fileName);

    void removeCarFromVec(int pos) { carsVec.remove(pos); };
    void removeCarFromCurrentCars(int pos) { CurrentIdCarsVec.remove(pos); };
    void replaceCarbyNewCar(int pos, cars newCar) { CurrentIdCarsVec.replace(pos,newCar); };
    void replaceCarByNewCarInVecCars(int pos, cars newCar) { carsVec.replace(pos, newCar); };
    void clearCurrentIdCarsVec() { CurrentIdCarsVec.clear(); };
    void removeFoFromVec(int pos) { foVec.remove(pos); };
    void removeFirmVec(int pos) { firmVec.remove(pos); };
    void removeAdministratorFromvec(int pos) { administratorVec.remove(pos); };
    void removeTechnikFromVec(int pos) { technikVec.remove(pos); };
    void clearVecOfOrders() { ordersVec.clear(); };

    void removeOrder(int pos) { ordersVec.remove(pos); };
    void removeSluzba(int pos) { sluzbaVec.remove(pos); };

    int getSizeOfFOVec() { return foVec.size(); };
    int getSizeOfFirmVec() { return firmVec.size(); };
    int getSizeOfTechnikVec() { return technikVec.size(); };
    int getSizeOfAdminVec() { return administratorVec.size(); };
    int getSizeOfCarsVec() { return carsVec.size(); };
    int getSizeOfSluzbaVec() { return sluzbaVec.size(); };
    int getSizeOfOrdersVec() { return ordersVec.size(); };
    int getSizeCurrentIdCarsVec() { return CurrentIdCarsVec.size(); };
    int getNumbersOfOrders() { return numberOfOrders; };

    int getCurrentID() { return CurrentID; };
    int getCurrentCar() { return CurrentCar; };
    int getIndexTableOfUsers() { return indexTableOfUsers; };
    void addIndexTableOfUsers() { indexTableOfUsers++; };
    void setIndexTableOfUsers(int value) { indexTableOfUsers = value; };

    FO getFyzickaOsobaFromVec(int i) { return foVec.at(i); };
    firm getFirmFromVec(int i) { return firmVec.at(i); };
    technik getTechnikVec(int i) { return technikVec.at(i); };
    administrator getAdminFromVec(int i) { return administratorVec.at(i); };
    cars getCarFormVec(int i) { return carsVec.at(i); };
    cars getCurrentIdCarFormVec(int i) { return CurrentIdCarsVec.at(i); };
    sluzba getSluzbaFromVec(int i) { return sluzbaVec.at(i); };
    sluzba getSluzbaFromOrdersVec(int i) { return ordersVec.at(i); };

    void setBoxCustomer();
    void setBoxAdmin();
    void setBoxTechnik();
    void setCurrentID(int i) { CurrentID = i; };
    void setCurrentCar(int i) { CurrentCar = i; };

    bool getReWriteUsers() { return rewriteUsers; };
    void setRewriteUsers(bool r) { rewriteUsers = r; };
    bool getRewriteOrders() { return rewriteOrders; };
    void setRewriteOrders(bool r) { rewriteOrders = r; };
private:
    Ui::autoservisClass ui;

    QVector<FO> foVec;
    QVector<firm> firmVec;
    QVector<technik> technikVec;
    QVector<administrator> administratorVec;
    QVector<cars> carsVec;
    QVector<cars> CurrentIdCarsVec;
    QVector<sluzba> sluzbaVec;
    QVector<sluzba> ordersVec;

    int CurrentID;
    int CurrentCar;
    int numberOfOrders;
    int indexTableOfUsers;

    bool rewriteUsers = false;
    bool rewriteOrders = false;
public slots:
    void on_pushButtonLogin_clicked();
    void on_pushButtonCustomOut_clicked();
    void on_pushButtonPracovnikOut_clicked();
    void on_pushButtonConfirmChoiceOfItem_clicked();
    void on_pushButton_Faktura_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonNextCar_clicked();
    void on_spinBoxYear_valueChanged(int value);
    void on_pushButtonNewCar_clicked();
    void on_pushButtonAddUser_clicked();
    void on_pushButton_zmenStav_clicked();
    void on_tableWidgetPolozky_cellDoubleClicked(int row, int column);
    void on_tableWidgetUsers_cellDoubleClicked(int row, int column);
    void on_tableWidgetOrdersWorker_cellDoubleClicked(int row, int column);
};






