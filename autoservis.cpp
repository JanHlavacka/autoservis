#include "autoservis.h"

autoservis::autoservis(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	ui.groupBoxPracovnik->setDisabled(true);
	ui.groupBoxCustomer->setDisabled(true);
	ui.groupBoxAdmin->setDisabled(true);
	ui.groupBoxTechnik->setDisabled(true);
}

autoservis::~autoservis()
{}

void autoservis::readUsers(string name)
{
	FO tmpFO;
	firm tmpFirm;
	technik tmpTechnik;
	administrator tmpAdmin;
	
	string line,tmp, login, password, n, surname, ico, trueOrFalse;
	int number, ID, icoNum, nullOrOne;
	ifstream file(name);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			number = atoi(line.c_str());
			ID = number / 1000;
			if (ID == 1)
			{
				getline(file, login);
				getline(file, password);
				getline(file, n);
				getline(file, surname);
				tmpFO.setParameters(number,n, surname, login, password);
				addFOtoVec(tmpFO);
			}
			else if (ID == 2)
			{
				getline(file, login);
				getline(file, password);
				getline(file, n);
				getline(file, ico);
				icoNum = atoi(ico.c_str());
				getline(file, trueOrFalse);
				nullOrOne = atoi(trueOrFalse.c_str());
				if (nullOrOne)
				{
					tmpFirm.setParameters(number,icoNum, n, login, password,true);
				}
				else
				{
					tmpFirm.setParameters(number, icoNum, n, login, password, false);
				}
				addFirmToVec(tmpFirm);
			}
			else if (ID == 3)
			{
				getline(file, login);
				getline(file, password);
				tmpTechnik.setParameters(number,login,password);
				addTechnikToVec(tmpTechnik);
			}
			else if (ID == 4)
			{
				getline(file, login);
				getline(file, password);
				tmpAdmin.setParameters(number, login, password);
				addAdministratorToVec(tmpAdmin);
			}
			else
			{
				qDebug() << "wrong ID";
			}
		}
		
	}
	else
	{
		qDebug() << "enable to open file";
	}
	file.close();
}

void autoservis::readCars(string name)
{
	cars carTmp;
	string line, manufacturer, model;
	int ID, year, carID;

	ifstream file(name);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			ID = atoi(line.c_str());
			getline(file, manufacturer);
			getline(file, model);
			getline(file, line);
			year = atoi(line.c_str());
			getline(file, line);
			carID = atoi(line.c_str());


			carTmp.setParameter(manufacturer,model, year,ID, carID);
			addCarsToVec(carTmp);
		}
	}
	else
	{
		qDebug() << "enable to open file cars";
	}
	file.close();
}

void autoservis::readSluzby(string name)
{
	sluzba sluzbaTmp;
	string line, sluzba;
	int price;

	ifstream file(name);
	if (file.is_open())
	{
		while (getline(file, sluzba))
		{
			getline(file, line);
			price = atoi(line.c_str());
			sluzbaTmp.setParameters(sluzba, price);
			addSluzbaToVec(sluzbaTmp);
		}
	}
	else
	{
		qDebug() << "enable to open file sluzby";
	}
	file.close();
}

void autoservis::writeSluzby(string name, int currentID)
{
	int numberOfOrders = getNumbersOfOrders();
	//int currentID = getCurrentID();
	int price, stav;
	string ponuka;

	
		ofstream myfile(name);
		if (myfile.is_open())
		{
			for (int i = 0; i < numberOfOrders; i++)
			{
				price = getSluzbaFromOrdersVec(i).getPrice();
				stav = getSluzbaFromOrdersVec(i).getStav();
				ponuka = getSluzbaFromOrdersVec(i).getPonuka();
				myfile << currentID << endl;
				myfile << ponuka << endl;
				myfile << price << endl;
				myfile << stav << endl;
			}
		}
		else
		{
			qDebug() << "enable open to objednaneSluzby";
		}
	
		setRewriteOrders(false);
}

void autoservis::writeSluzby(string name)
{
	int numberOfOrders = getSizeOfOrdersVec();
	int IDzakaznika;
	int price, stav;
	string ponuka;


	ofstream myfile(name);
	if (myfile.is_open())
	{
		for (int i = 0; i < numberOfOrders; i++)
		{
			price = getSluzbaFromOrdersVec(i).getPrice();
			stav = getSluzbaFromOrdersVec(i).getStav();
			ponuka = getSluzbaFromOrdersVec(i).getPonuka();
			IDzakaznika = getSluzbaFromOrdersVec(i).getIdZakaznika();
			myfile << IDzakaznika << endl;
			myfile << ponuka << endl;
			myfile << price << endl;
			myfile << stav << endl;
		}
	}
	else
	{
		qDebug() << "enable open to objednaneSluzby";
	}

	setRewriteOrders(false);
}

void autoservis::readOrders(string name)
{
	sluzba sluzbaTmp;
	string line, sluzba;
	int price, stav, ID;
	int currentID = getCurrentID();

	ifstream file(name);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			ID = atoi(line.c_str());
			if (ID == currentID)
			{
				getline(file, sluzba);
				getline(file, line);
				price = atoi(line.c_str());
				sluzbaTmp.setParameters(sluzba, price);
				getline(file, line);
				stav = atoi(line.c_str());
				sluzbaTmp.changeStav(stav);
				addSluzbaToOrders(sluzbaTmp);
			}
			else
			{
				getline(file, line);
				getline(file, line);
				getline(file, line);
			}
		}
	}
	else
	{
		qDebug() << "enable to open file sluzba for write to slozba to vec";
	}
	file.close();
}

void autoservis::readOrdersForTechnik(string name)
{
	sluzba sluzbaTmp;
	string line, sluzba;
	int price, stav, ID;
	int currentID = getCurrentID();

	ifstream file(name);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			ID = atoi(line.c_str());
			getline(file, sluzba);
			getline(file, line);
			price = atoi(line.c_str());
			sluzbaTmp.setParameters(sluzba, price);
			getline(file, line);
			stav = atoi(line.c_str());
			sluzbaTmp.changeStav(stav);
			addSluzbaToOrders(sluzbaTmp);
		}
	}
	else
	{
		qDebug() << "enable to open file sluzba for write to slozba to vec";
	}
	file.close();
}

void autoservis::writeAddedItem(sluzba item, string name)
{
	int numberOfOrders = getNumbersOfOrders();
	int currentID = getCurrentID();
	int price = item.getPrice();
	int	stav = item.getStav();
	string ponuka = item.getPonuka();

	ofstream myfile(name, ios::app);
	if (myfile.is_open())
	{
		myfile << currentID << endl;
		myfile << ponuka << endl;
		myfile << price << endl;
		myfile << stav << endl;
	}
	else
	{
		qDebug() << "enable open to objednaneSluzby";
	}
}

void autoservis::writeAddFoToFile(FO f, string fileName)
{
	int id = f.getID();
	string login = f.getLogin();
	string pass = f.getPassword();
	string name = f.getName();
	string surname = f.getSurname();

	ofstream myfile(fileName, ios::app);
	if (myfile.is_open())
	{
		myfile << id << endl;
		myfile << login << endl;
		myfile << pass << endl;
		myfile << name << endl;
		myfile << surname << endl;
	}
	else
	{
		qDebug() << "enable open to objednaneSluzby";
	}
}

void autoservis::writeAddFirmToFile(firm f, string fileName)
{
	int id = f.getID();
	string login = f.getLogin();
	string pass = f.getPassword();
	string name = f.getName();
	int ico = f.getIco();
	bool tOrf = f.getInfo();

	ofstream myfile(fileName, ios::app);
	if (myfile.is_open())
	{
		myfile << id << endl;
		myfile << login << endl;
		myfile << pass << endl;
		myfile << name << endl;
		myfile << ico << endl;
		if (tOrf)
		{
			myfile << "1" << endl;
		}
		else
		{
			myfile << "0" << endl;
		}
	}
	else
	{
		qDebug() << "enable open to objednaneSluzby";
	}
}

void autoservis::writeAddTechnikToFile(technik t, string fileName)
{
	int id = t.getID();
	string login = t.getLogin();
	string pass = t.getPassword();
	

	ofstream myfile(fileName, ios::app);
	if (myfile.is_open())
	{
		myfile << id << endl;
		myfile << login << endl;
		myfile << pass << endl;
	}
	else
	{
		qDebug() << "enable open to objednaneSluzby";
	}
}

void autoservis::writeAddAdministrator(administrator a, string fileName)
{
	int id = a.getID();
	string login = a.getLogin();
	string pass = a.getPassword();


	ofstream myfile(fileName, ios::app);
	if (myfile.is_open())
	{
		myfile << id << endl;
		myfile << login << endl;
		myfile << pass << endl;
	}
	else
	{
		qDebug() << "enable open to objednaneSluzby";
	}
}

void autoservis::writeAddNewCar(cars c, string fileName)
{
	int id = c.getID();
	int carID = c.getCarID();
	string manufacturer = c.getManufacturer();
	string model = c.getModel();
	int year = c.getYear();

	ofstream myfile(fileName, ios::app);
	if (myfile.is_open())
	{
		myfile << id << endl;
		myfile << manufacturer << endl;
		myfile << model << endl;
		myfile << year << endl;
		myfile << carID << endl;
	}
	else
	{
		qDebug() << "enable open to objednaneSluzby";
	}
}

void autoservis::setBoxCustomer()
{
	QString QstringTMP;
	string manufacturerer, model;
	int stav;
	for (int i = 0; i < getSizeOfSluzbaVec(); i++)
	{
		QstringTMP = QString::fromStdString(getSluzbaFromVec(i).getPonuka());
		ui.comboBoxChoiceItem->addItem(QstringTMP);	
	}
	for (int i = 0; i < getSizeOfCarsVec(); i++)
	{
		if (getCarFormVec(i).getID() == getCurrentID()) {
			addCurrentIdCarsToVec(getCarFormVec(i));
		}
	}
	if (getSizeCurrentIdCarsVec() > 0)
	{
		manufacturerer = getCurrentIdCarFormVec(0).getManufacturer();
		model = getCurrentIdCarFormVec(0).getModel();
		QstringTMP = QString::fromStdString(manufacturerer);
		ui.lineEditManufacturer->setText(QstringTMP);
		QstringTMP = QString::fromStdString(model);
		ui.lineEditChangeModel->setText(QstringTMP);
	}
	
	setCurrentCar(0);
	setNumberOfOrders(0);
	readOrders("objednaneSluzby.txt");
	
	for (int i = 0; i < getSizeOfOrdersVec(); i++)
	{
		QTableWidgetItem* itemSluzba = new QTableWidgetItem();
		QTableWidgetItem* itemPrice = new QTableWidgetItem();
		QTableWidgetItem* itemStav = new QTableWidgetItem();
		ui.tableWidgetPolozky->insertRow(0);
		QstringTMP = QString::fromStdString(getSluzbaFromOrdersVec(i).getPonuka());
		itemSluzba->setText(QstringTMP);
		QstringTMP = QString::number(getSluzbaFromOrdersVec(i).getPrice());
		itemPrice->setText(QstringTMP);
		ui.tableWidgetPolozky->setItem(0,0,itemSluzba);
		ui.tableWidgetPolozky->setItem(0, 1, itemPrice);
		stav = getSluzbaFromOrdersVec(0).getStav();
		if (stav == 0)
		{
			QstringTMP = "objednana";
			itemStav->setText(QstringTMP);
			ui.tableWidgetPolozky->setItem(0, 2, itemStav);
		}
		else if (stav == 1)
		{
			QstringTMP = "rozrobena";
			itemStav->setText(QstringTMP);
			ui.tableWidgetPolozky->setItem(0, 2, itemStav);
		}
		else if (stav == 3)
		{
			QstringTMP = "dokoncena";
			itemStav->setText(QstringTMP);
			ui.tableWidgetPolozky->setItem(0, 2, itemStav);
		}
	}
}

void autoservis::setBoxAdmin()
{
	QString tmpQstring;;

	//QTableWidgetItem* itemUser = new QTableWidgetItem();
	//QTableWidgetItem* itemUserID = new QTableWidgetItem();
	int id;
	//int index = 0;
	setIndexTableOfUsers(0);

	for (int i = 0; i < getSizeOfFOVec(); i++)
	{		
		ui.tableWidgetUsers->insertRow(getIndexTableOfUsers());
		QTableWidgetItem* item = new QTableWidgetItem();
		QTableWidgetItem* itemID = new QTableWidgetItem();
		tmpQstring = QString::fromStdString(getFyzickaOsobaFromVec(i).getLogin());
		item->setText(tmpQstring);
		ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 1, item);
		id = getFyzickaOsobaFromVec(i).getID();
		itemID->setText(QString::number(id));
		ui.tableWidgetUsers->setItem(getIndexTableOfUsers(),0,itemID);

		addIndexTableOfUsers();
	}
	for (int i = 0; i < getSizeOfFirmVec(); i++)
	{
		ui.tableWidgetUsers->insertRow(getIndexTableOfUsers());
		QTableWidgetItem* item = new QTableWidgetItem();
		QTableWidgetItem* itemID = new QTableWidgetItem();
		tmpQstring = QString::fromStdString(getFirmFromVec(i).getLogin());
		item->setText(tmpQstring);
		ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 1, item);

		id = getFirmFromVec(i).getID();
		itemID->setText(QString::number(id));
		ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 0, itemID);

		addIndexTableOfUsers();
	}
	for (int i = 0; i < getSizeOfTechnikVec(); i++)
	{
		ui.tableWidgetUsers->insertRow(getIndexTableOfUsers());
		QTableWidgetItem* item = new QTableWidgetItem();
		QTableWidgetItem* itemID = new QTableWidgetItem();
		tmpQstring = QString::fromStdString(getTechnikVec(i).getLogin());
		item->setText(tmpQstring);
		ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 1, item);

		id = getTechnikVec(i).getID();
		itemID->setText(QString::number(id));
		ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 0, itemID);

		addIndexTableOfUsers();
	}
	for (int i = 0; i < getSizeOfAdminVec(); i++)
	{
		ui.tableWidgetUsers->insertRow(getIndexTableOfUsers());
		QTableWidgetItem* item = new QTableWidgetItem();
		QTableWidgetItem* itemID = new QTableWidgetItem();
		tmpQstring = QString::fromStdString(getAdminFromVec(i).getLogin());
		item->setText(tmpQstring);
		ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 1, item);

		id = getAdminFromVec(i).getID();
		itemID->setText(QString::number(id));
		ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 0, itemID);

		addIndexTableOfUsers();
	}
}

void autoservis::setBoxTechnik()
{
	QString QstringTMP;
	string order, state;
	int stav, id;

	readOrdersForTechnik("objednaneSluzby.txt");

	for (int i = 0; i < getSizeOfOrdersVec(); i++)
	{
		ui.tableWidgetOrdersWorker->insertRow(0);

		QTableWidgetItem* item = new QTableWidgetItem();
		QTableWidgetItem* itemState = new QTableWidgetItem();
		//QTableWidgetItem* itemID = new QTableWidgetItem();


		order = getSluzbaFromOrdersVec(i).getPonuka();
		QstringTMP = QString::fromStdString(order);
		item->setText(QstringTMP);
		stav = getSluzbaFromOrdersVec(i).getStav();
		if (stav == 0)
		{
			itemState->setText("objednane");
		}
		else if (stav == 1)
		{
			itemState->setText("rozpracovane");
		}
		else
		{
			itemState->setText("hotovo");
		}
		//id = getSluzbaFromOrdersVec(i).getIdZakaznika();
		//QstringTMP = QString::number(id);
		//itemID->setText(QstringTMP);

		ui.tableWidgetOrdersWorker->setItem(0, 0, item);
		ui.tableWidgetOrdersWorker->setItem(0, 1, itemState);
		//ui.tableWidgetOrdersWorker->setItem(0, 2, itemID);
	}
	ui.spinBoxChooseOrder->setMaximum(getSizeOfOrdersVec());
}

void autoservis::on_pushButtonCustomOut_clicked()
{
	ui.lineEditManufacturer->clear();
	ui.lineEditChangeModel->clear();



	clearCurrentIdCarsVec();
	ui.groupBoxCustomer->setDisabled(true);
	ui.tableWidgetPolozky->clear();
	for (int i = ui.tableWidgetPolozky->rowCount(); i >= 0; i--)
	{
		ui.tableWidgetPolozky->removeRow(i);
	}
	if (getRewriteOrders())
	{
		writeSluzby("objednaneSluzby.txt", getCurrentID());
	}
	clearVecOfOrders();

	ui.comboBoxChoiceItem->clear();
}

void autoservis::on_pushButtonPracovnikOut_clicked()
{
	ui.groupBoxPracovnik->setDisabled(true);
	ui.groupBoxAdmin->setDisabled(true);
	ui.groupBoxTechnik->setDisabled(true);

	for (int i = ui.tableWidgetUsers->rowCount(); i >=0 ; i--)
	{
		ui.tableWidgetUsers->removeRow(i);
	}
	if (getReWriteUsers())
	{
		ofstream myfile("users.txt");
		if (myfile.is_open())
		{
			for (int i = 0; i < getSizeOfFOVec(); i++) {
				writeAddFoToFile(getFyzickaOsobaFromVec(i),"users.txt");
			}
			for (int i = 0; i < getSizeOfFirmVec(); i++)
			{
				writeAddFirmToFile(getFirmFromVec(i), "users.txt");
			}
			for (int i = 0; i < getSizeOfTechnikVec(); i++)
			{
				writeAddTechnikToFile(getTechnikVec(i), "users.txt");
			}
			for (int i = 0; i < getSizeOfAdminVec(); i++)
			{
				writeAddAdministrator(getAdminFromVec(i), "users.txt");
			}
		}
		else
		{
			qDebug() << "enable open to objednaneSluzby";
		}
	}
	for (int i = ui.tableWidgetOrdersWorker->rowCount(); i >= 0; i--)
	{
		ui.tableWidgetOrdersWorker->removeRow(i);
	}

	if (getRewriteOrders())
	{
		writeSluzby("objednaneSluzby.txt");
	}

	clearVecOfOrders();
}

void autoservis::on_pushButtonConfirmChoiceOfItem_clicked()
{
	int index;
	QString tmpQstring;
	int stav, cena, idZakaznika;
	int numberOfOrders = getNumbersOfOrders();
	index = ui.comboBoxChoiceItem->currentIndex();
	if (index>=getSizeOfSluzbaVec())
	{
		QMessageBox::information(this, "order", "something went wrong, try it again, or log out");
		
	}
	else
	{
		sluzba sl = getSluzbaFromVec(index);
		sl.setIdZakaznika(getCurrentID());
		addSluzbaToOrders(sl);

		writeAddedItem(sl, "objednaneSluzby.txt");

		//zapis do tabluky
		ui.tableWidgetPolozky->insertRow(0);
		QTableWidgetItem* itemT = new QTableWidgetItem();
		QTableWidgetItem* itemPrice = new QTableWidgetItem();
		QTableWidgetItem* itemStav = new QTableWidgetItem();
		tmpQstring = QString::fromStdString(getSluzbaFromVec(index).getPonuka());
		itemT->setText(tmpQstring);
		ui.tableWidgetPolozky->setItem(0, 0, itemT);
		cena = getSluzbaFromVec(index).getPrice();
		stav = getSluzbaFromVec(index).getStav();
		tmpQstring = QString::number(cena);
		itemPrice->setText(tmpQstring);
		ui.tableWidgetPolozky->setItem(0, 1, itemPrice);
		tmpQstring = "objednana";
		itemStav->setText(tmpQstring);
		ui.tableWidgetPolozky->setItem(0, 2, itemStav);

		addNumberOfOrders();
	}
}

void autoservis::on_pushButton_Faktura_clicked()
{
	int sumPrices = 0;
	ofstream file("faktura.txt");
	if (file.is_open())
	{
		file << "ID: " << getCurrentID() << endl;
		for (int i = 0; i < getSizeOfOrdersVec(); i++)
		{
			file << getSluzbaFromOrdersVec(i).getPonuka() << "..." << getSluzbaFromOrdersVec(i).getPrice() << endl;
			sumPrices += getSluzbaFromOrdersVec(i).getPrice();
		}
		file << "Sum is ... " << sumPrices << endl;
	}
	else
	{
		qDebug() << "enable to open file cars";
	}
	file.close();
}

void autoservis::on_pushButtonSave_clicked()
{
	QVector<cars> tmpVec;
	cars updatedCar;
	string manufacturer, model;
	int currentCar = getCurrentCar();
	int carID;
	manufacturer = ui.lineEditManufacturer->text().toStdString();
	model = ui.lineEditChangeModel->text().toStdString();
	carID = getCurrentIdCarFormVec(currentCar).getCarID();
	updatedCar.setParameter(manufacturer, model, ui.spinBoxYear->value(), getCurrentID(), carID);

	replaceCarbyNewCar(currentCar, updatedCar);

	for (int i = 0; i < getSizeOfCarsVec(); i++)
	{
		if (getCarFormVec(i).getCarID() == carID)
		{
			replaceCarByNewCarInVecCars(i, updatedCar);
		}
	}
}

void autoservis::on_pushButtonNextCar_clicked()
{
	int numberOfCars = getSizeCurrentIdCarsVec();
	int tmpCar = getCurrentCar();
	tmpCar++;
	if (tmpCar < numberOfCars)
	{
		setCurrentCar(tmpCar);
	}
	else
	{
		setCurrentCar(0);
	}

	string manufacturer;
	QString tmpQString;
	int year;
	manufacturer = getCurrentIdCarFormVec(getCurrentCar()).getManufacturer();
	tmpQString = QString::fromStdString(manufacturer);
	ui.lineEditManufacturer->setText(tmpQString);
	tmpQString = QString::fromStdString(getCurrentIdCarFormVec(getCurrentCar()).getModel());
	ui.lineEditChangeModel->setText(tmpQString);
	year = getCurrentIdCarFormVec(getCurrentCar()).getYear();
	ui.spinBoxYear->setValue(year);

}

void autoservis::on_spinBoxYear_valueChanged(int value)
{
	ui.spinBoxYear->setValue(value);
}

void autoservis::on_pushButtonNewCar_clicked()
{
	cars newCar;
	QString manufacturerer, model;
	string tmpString;
	int newYear;
	newCar.setCarID(getSizeOfCarsVec());
	newCar.setIDOwner(getCurrentID());
	manufacturerer = ui.lineEditNewManufacturer->text();
	tmpString = manufacturerer.toStdString();
	newCar.setManufacturer(tmpString);
	model = ui.lineEditNewModel->text();
	tmpString = model.toStdString();
	newCar.setModel(tmpString);
	newYear = ui.spinBoxNewYear->value();
	newCar.setYear(newYear);

	addCurrentIdCarsToVec(newCar);
	addCarsToVec(newCar);
	ui.lineEditNewManufacturer->clear();
	ui.lineEditNewModel->clear();
	ui.spinBoxNewYear->setValue(2023);

	writeAddNewCar(newCar,"cars.txt");
}

void autoservis::on_pushButtonAddUser_clicked()
{
	QString login, password;
	string log, pass;
	int user;
	user = ui.comboBoxPosition->currentIndex();
	login = ui.lineEditSetLogin->text();
	password = ui.lineEditSetPass->text();

	log = login.toStdString();
	pass = password.toStdString();
	if (log.size() == 0 || pass.size() == 0)
	{
		QMessageBox::information(this, "add User", "you have to fill login and password");
	}
	else
	{
		if (user==0)
		{
			int id = getSizeOfFOVec() + 1000;
			FO fyzOsoba;
			QString name,surname;
			string n,s;
			name = ui.lineEditSetName->text();
			surname = ui.lineEditSetSurname->text();
			n = name.toStdString();
			s = surname.toStdString();
			fyzOsoba.setParameters(id,n,s,log,pass);
			addFOtoVec(fyzOsoba);

			ui.tableWidgetUsers->insertRow(getIndexTableOfUsers());
			QTableWidgetItem* item = new QTableWidgetItem();
			QTableWidgetItem* itemID = new QTableWidgetItem();
			item->setText(login);
			ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 1, item);
			itemID->setText(QString::number(id));
			ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 0, itemID);
			addIndexTableOfUsers();

			writeAddFoToFile(fyzOsoba, "users.txt");
		}
		if (user==1)
		{
			int id = getSizeOfFirmVec() + 2000;
			firm firma;
			QString name, ico;
			string n;
			int ic;
			name = ui.lineEditSetName->text();
			ico = ui.lineEditSetSurname->text();
			n = name.toStdString();
			ic = ico.toInt();
			firma.setParameters(id,ic,n,log,pass,true);
			addFirmToVec(firma);

			ui.tableWidgetUsers->insertRow(getIndexTableOfUsers());
			QTableWidgetItem* item = new QTableWidgetItem();
			QTableWidgetItem* itemID = new QTableWidgetItem();
			item->setText(login);
			ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 1, item);
			itemID->setText(QString::number(id));
			ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 0, itemID);
			addIndexTableOfUsers();

			writeAddFirmToFile(firma, "users.txt");
		}
		if (user == 2)
		{
			int id = getSizeOfTechnikVec() + 3000;
			technik tech;
			tech.setParameters(id, log, pass);
			addTechnikToVec(tech);

			ui.tableWidgetUsers->insertRow(getIndexTableOfUsers());
			QTableWidgetItem* item = new QTableWidgetItem();
			QTableWidgetItem* itemID = new QTableWidgetItem();
			item->setText(login);
			ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 1, item);
			itemID->setText(QString::number(id));
			ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 0, itemID);
			addIndexTableOfUsers();

			writeAddTechnikToFile(tech, "users.txt");
		}
		if (user == 3)
		{
			int id = getSizeOfAdminVec() + 4000;
			administrator admin;
			admin.setParameters(id, log, pass);
			addAdministratorToVec(admin);

			ui.tableWidgetUsers->insertRow(getIndexTableOfUsers());
			QTableWidgetItem* item = new QTableWidgetItem();
			QTableWidgetItem* itemID = new QTableWidgetItem();
			item->setText(login);
			ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 1, item);
			itemID->setText(QString::number(id));
			ui.tableWidgetUsers->setItem(getIndexTableOfUsers(), 0, itemID);
			addIndexTableOfUsers();

			writeAddAdministrator(admin, "users.txt");
		}


		ui.lineEditSetLogin->clear();
		ui.lineEditSetPass->clear();
		ui.lineEditSetName->clear();
		ui.lineEditSetSurname->clear();
	}
}

void autoservis::on_pushButton_zmenStav_clicked()
{
	int stav, index;
	index = ui.spinBoxChooseOrder->value() - 1;
	stav = ui.comboBoxChooseState->currentIndex();

	qDebug() << index <<"   " << stav << "   " << getSluzbaFromOrdersVec(index).getStav() << "   "<< getSluzbaFromOrdersVec(index).getPrice();

	getSluzbaFromOrdersVec(index).setStav(stav);
	

	qDebug() << getSluzbaFromOrdersVec(index).getStav() << getSluzbaFromOrdersVec(index).getPrice();


	if (stav == 0)
	{
		QTableWidgetItem* item = new QTableWidgetItem();
		item->setText("objednane");
		ui.tableWidgetOrdersWorker->setItem(index, 1, item);
	}
	else if (stav == 1)
	{
		QTableWidgetItem* item = new QTableWidgetItem();
		item->setText("rozpracovane");
		ui.tableWidgetOrdersWorker->setItem(index, 1, item);
	}
	else
	{
		QTableWidgetItem* item = new QTableWidgetItem();
		item->setText("dokoncene");
		ui.tableWidgetOrdersWorker->setItem(index, 1, item);
	}

	setRewriteOrders(true);
}

void autoservis::on_tableWidgetPolozky_cellDoubleClicked(int row, int column)
{
	int id = getCurrentID();
	QString polozka,tmp;
	string polozkaString;
	int stav;
	polozka = ui.tableWidgetPolozky->item(row, 0)->text();
	tmp = ui.tableWidgetPolozky->item(row, 2)->text();
	stav = tmp.toInt();
	polozkaString = polozka.toStdString();

	QMessageBox::StandardButton reply = QMessageBox::question(this, "remove", "Are you sure that you wanna remove this item?",QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes)
	{
		if (stav == 0)
		{
			ui.tableWidgetPolozky->removeRow(row);
			setRewriteOrders(true);
			for (int i = 0; i < getSizeOfOrdersVec(); i++)
			{
				if (id==getSluzbaFromOrdersVec(i).getIdZakaznika() && polozkaString == getSluzbaFromOrdersVec(i).getPonuka()) {
					removeOrder(i);
					setRewriteOrders(true);
				}
			}
		}
		else
		{
			QMessageBox::information(this, "order", "order is in process. It is impossible to remove this order");
		}
	}
	else
	{
		
	}
	
}

void autoservis::on_tableWidgetUsers_cellDoubleClicked(int row, int column)
{
	int id;
	QString value;
	value = ui.tableWidgetUsers->item(row, 0)->text();
	id = value.toInt();

	QMessageBox::StandardButton reply = QMessageBox::question(this, "remove", "Are you sure that you wanna remove this user?", QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes)
	{
		if (id == getCurrentID())
		{
			QMessageBox::information(this, "login", "You can remove your account");
		}
		else
		{
			for (int i = 0; i < getSizeOfFOVec(); i++)
			{
				if (getFyzickaOsobaFromVec(i).getID() == id) {
					removeFoFromVec(i);
				}
			}
			for (int i = 0; i < getSizeOfFirmVec(); i++)
			{
				if (getFirmFromVec(i).getID() == id) {
					removeFirmVec(i);
				}
			}
			for (int i = 0; i < getSizeOfTechnikVec(); i++)
			{
				if (getTechnikVec(i).getID() == id) {
					removeTechnikFromVec(i);
				}
			}
			for (int i = 0; i < getSizeOfAdminVec(); i++)
			{
				if (getAdminFromVec(i).getID() == id) {
					removeAdministratorFromvec(i);
				}
			}
			ui.tableWidgetUsers->removeRow(row);
			setRewriteUsers(true);
		}
	}
	else
	{

	}
}

void autoservis::on_tableWidgetOrdersWorker_cellDoubleClicked(int row, int column)
{
	QString order;
	int state;

	if (column == 0)
	{
		QMessageBox::StandardButton reply = QMessageBox::question(this, "remove", "Are you sure that you wanna remove this order?", QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::Yes)
		{
			removeOrder(row);
			ui.tableWidgetOrdersWorker->removeRow(row);
			setRewriteOrders(true);					
		}
	}
}

void autoservis::on_pushButtonLogin_clicked()
{
	bool correctLogin = false;
	bool correctPassword = false;
	QString password = ui.lineEditPass->text();
	QString login = ui.lineEditLogin->text();
	string tmp;
	QString Qtmp;
	for (int i = 0; i < getSizeOfFOVec(); i++)
	{
		tmp = getFyzickaOsobaFromVec(i).getLogin();
		Qtmp = QString::fromStdString(tmp);
		if (login == Qtmp)
		{
			correctLogin = true;
			tmp = getFyzickaOsobaFromVec(i).getPassword();
			Qtmp = QString::fromStdString(tmp);
			if (password == Qtmp)
			{
				correctPassword = true;
				ui.groupBoxCustomer->setDisabled(false);
				setCurrentID(getFyzickaOsobaFromVec(i).getID());
				ui.lineEditPass->clear();
				ui.lineEditLogin->clear();
				setBoxCustomer();
				break;
			}
		}
	}
	
	for (int i = 0; i < getSizeOfFirmVec(); i++)
	{
		if (correctLogin && correctPassword)
		{
			break;
		}
		tmp =getFirmFromVec(i).getLogin();
		Qtmp = QString::fromStdString(tmp);
		if (login == Qtmp)
		{
			correctLogin = true;
			tmp = getFirmFromVec(i).getPassword();
			Qtmp = QString::fromStdString(tmp);
			if (password == Qtmp)
			{
				correctPassword = true;
				ui.groupBoxCustomer->setDisabled(false);

				ui.lineEditPass->clear();
				ui.lineEditLogin->clear();
				setCurrentID(getFirmFromVec(i).getID());

				setBoxCustomer();
				break;
			}
		}
	}

	for (int i = 0; i < getSizeOfTechnikVec(); i++)
	{
		if (correctLogin && correctPassword)
		{
			break;
		}
		tmp = getTechnikVec(i).getLogin();
		Qtmp = QString::fromStdString(tmp);
		if (login == Qtmp)
		{
			correctLogin = true;
			tmp = getTechnikVec(i).getPassword();
			Qtmp = QString::fromStdString(tmp);
			if (password == Qtmp)
			{
				correctPassword = true;
				ui.groupBoxPracovnik->setDisabled(false);
				ui.groupBoxTechnik->setDisabled(false);

				ui.lineEditPass->clear();
				ui.lineEditLogin->clear();

				setCurrentID(getTechnikVec(i).getID());
				setBoxTechnik();
				break;
			}
		}
	}
	//
	for (int i = 0; i < getSizeOfAdminVec(); i++)
	{
		if (correctLogin && correctPassword)
		{
			break;
		}
		tmp =getAdminFromVec(i).getLogin();
		Qtmp = QString::fromStdString(tmp);
		if (login == Qtmp)
		{
			correctLogin = true;
			tmp = getAdminFromVec(i).getPassword();
			Qtmp = QString::fromStdString(tmp);
			if (password == Qtmp)
			{
				correctPassword = true;
				ui.groupBoxPracovnik->setDisabled(false);
				ui.groupBoxAdmin->setDisabled(false);

				ui.lineEditPass->clear();
				ui.lineEditLogin->clear();

				setCurrentID(getAdminFromVec(i).getID());
				setBoxAdmin();
				break;
			}
		}
	}
	if (!correctLogin || !correctPassword)
	{
		QMessageBox::information(this,"login","Wrong password or login");
	}
}

//fyzicka osoba*******
FO::FO()
{
}

FO::~FO() {

}

FO::FO(int i, string n, string sur, string log, string pass)
{
	id = i;
	surname = sur;
	name = n;
	login = log;
	password = pass;	
}

//firma **************
firm::firm()
{
}

firm::~firm()
{
}

firm::firm(int i, int ic, string n, string log, string pass, bool platca)
{
	id = i;
	ico = ic;
	name = n;
	login = log;
	password = pass;
	platcaDPH = platca;
}

//technik**************
technik::technik()
{
}

technik::~technik()
{
}

technik::technik(int i, string log, string pass)
{
	id = i;
	login = log;
	password = pass;
}

//administrator********
administrator::administrator()
{
}

administrator::~administrator()
{
}

administrator::administrator(int i, string log, string pass)
{
	id = i;
	login = log;
	password = pass;
}

//cars***************
cars::cars()
{
}

cars::~cars()
{
}

//sluzby*********
sluzba::sluzba()
{
}

sluzba::~sluzba()
{
}