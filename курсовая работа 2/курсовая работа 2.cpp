#include "Header.h"
#include <cctype>

vector<User> vectUser(0);
vector<Car> vectCar(0);


void GoToXY(short x, short y);
void ConsoleCursorVisible(bool show, short size);
void Yellow();
void Cyan();
void Orange();
void UserMenu();
void mainMenu();
void adminMenu();
void sortMenu();
void filtrMenu();
void DisplayCars();
void RemoveCar();
void AddCar();

string Password(string password) {
	Cyan();
	password = "";
	char ch;
	bool ctrlPressed = false;
	GoToXY(55, 12);

	cout << "Введите пароль: ";

	while (true) {
		ch = _getch();
		if (ch == 13) { // 13 - код клавиши Enter
			break;
		}
		if (ch == 8 || ch == 127) { // 8 - код клавиши Backspace, 127 - код клавиши Delete
			if (password.length() > 0) {
				password.erase(password.length() - 1);
				cout << "\b \b"; // удаляем последнюю звездочку
			}
		}
		else if (ch >= 32 && ch <= 126 && ch != 0) { // игнорируем клавиши F1-F12
			if (ctrlPressed) { // проверяем, была ли нажата клавиша Ctrl
				if (ch == 'c' || ch == 'C' || ch == 'v' || ch == 'V') { // проверяем, была ли нажата клавиша C или V
					continue; // игнорируем клавиши сочетания
				}
			}
			password += ch;
			cout << '*';
		}
		else if (ch == -32) { // игнорируем коды направлений стрелок
			ch = _getch(); // считываем второй байт кода клавиши
			if (ch == 72 || ch == 75 || ch == 77 || ch == 80) { // проверяем, является ли второй байт кодом стрелки
				continue; // игнорируем стрелки
			}
		}
		else if (ch == 3 || ch == 22 || ch == 24) { // игнорируем клавиши сочетания Ctrl+C, Ctrl+V, Ctrl+X
			ctrlPressed = true;
		}
		else {
			ctrlPressed = false;
		}
	}
	return password;
}

void purchaseCar() {
	vector<int> selectedCars;
	vector<int> quantities;

	int active_menu = 0;
	char ch;

	while (true) {
		int x = 50, y = 12;
		system("cls");
		cout << "Меню заказа автомобилей" << endl;
		cout << "----------------------" << endl;

		for (int i = 0; i < vectCar.size(); i++) {
			if (i == active_menu) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout << i + 1 << ". " << vectCar[i].name << " (Цена: " << vectCar[i].price << " | Количество: " << vectCar[i].quantity << ")" << endl;
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << i + 1 << ". " << vectCar[i].name << " (Цена: " << vectCar[i].price << " | Количество: " << vectCar[i].quantity << ")" << endl;
			}
		}

		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < vectCar.size() - 1)
				++active_menu;
			break;
		case ESC:
			return;
		case ENTER:
			system("cls");
			cout << "Выбрана машина: " << vectCar[active_menu].name << endl;
			cout << "Текущее количество: " << vectCar[active_menu].quantity << endl;

			int quantityToBuy;
			while (true) {
				cout << "Введите количество суток для заказа (0 - отмена): ";
				cin >> quantityToBuy;

				if (quantityToBuy < 0) {
					cout << "Неверное значение. Количество суток должно быть неотрицательным." << endl;
				}
				else {
					break;
				}
			}

			if (quantityToBuy == 0)
				continue;

			// Добавляем выбранную машину и количество в соответствующие векторы
			selectedCars.push_back(active_menu);
			quantities.push_back(quantityToBuy);

			cout << "Заказ успешно добавлен." << endl;
			cout << "----------------------" << endl;
			cout << "1. Продолжить заказ" << endl;
			cout << "2. Завершить заказ" << endl;

			int choice;
			while (true) {
				cout << "Выберите действие: ";
				cin >> choice;

				if (choice == 1 || choice == 2)
					break;
				else
					cout << "Неверный выбор. Пожалуйста, повторите ввод." << endl;
			}


			if (choice == 2) {
				// Вывод чека
				system("cls");
				cout << "Чек" << endl;
				cout << "----------------------------------------" << endl;

				double totalCost = 0.0;

				for (int i = 0; i < selectedCars.size(); i++) {
					int carIndex = selectedCars[i];
					int quantity = quantities[i];
					double price = vectCar[carIndex].price;

					cout << "Машина: " << vectCar[carIndex].name << endl;
					cout << "Цена за сутки: " << price << endl;
					cout << "Количество суток: " << quantityToBuy << endl;
					cout << "Сумма: " << price * quantityToBuy << endl;
					cout << "----------------------------------------" << endl;

					totalCost += price * quantityToBuy;
				}

				cout << "Общая стоимость: " << totalCost << endl;

				// Обновляем количество машин в векторе в векторе
				for (int i = 0; i < selectedCars.size(); i++) {
					int carIndex = selectedCars[i];

					vectCar[carIndex].quantity -= 1;
				}

				// Очищаем векторы выбранных машин и количества
				selectedCars.clear();
				quantities.clear();

				cout << "----------------------------------------" << endl;
				cout << "Спасибо за покупку!" << endl;
				cout << "Нажмите любую клавишу, чтобы продолжить...";
				_getch();

				return;
			}
			else {
				active_menu = 0;
			}

			break;
		}
	}
}

void updateCarQuantity() {
	int y = 0;
	string* menu = new string[vectCar.size()];

	for (int i = 0; i < vectCar.size(); i++) {
		menu[i] = vectCar[i].name;
	}

	int active_menu = 0; char ch;
	while (true) {
		int x = 55, y = 12;
		system("cls");
		GoToXY(x, y);
		for (int i = 0; i < vectCar.size(); i++) {
			if (i == active_menu) Yellow();
			else Cyan();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < vectCar.size() - 1)
				++active_menu;
			break;
		case ESC:
			delete[] menu;
			return;
		case ENTER:
			system("cls");
			GoToXY(55, 12);
			cout << "Выбрана машина: ";
			GoToXY(72, 12);
			cout << vectCar[active_menu].name;
			GoToXY(55, 13);
			cout << "Текущее количество: " << vectCar[active_menu].quantity;

			int newQuantity;
			while (true) {
				GoToXY(55, 14);
				cout << "Введите количество которое вы хотите добавить: ";
				cin >> newQuantity;

				if (newQuantity < 0) {
					GoToXY(55, 15);
					cout << "Неверное значение. Количество должно быть неотрицательным." << endl;
				}
				else {
					break;
				}
			}

			vectCar[active_menu].quantity += newQuantity;

			GoToXY(55, 16);
			cout << "Количество машин \"" << vectCar[active_menu].name << "\" изменено на: " << vectCar[active_menu].quantity << endl;
			_getch();
			delete[] menu;
			return;

		default:
			break;
		}
	}
	_getch();
	system("cls");
}

void AddCar() {
	Cyan();
	Car car;
	GoToXY(55, 12);
	cout << "Введите название машины: ";
	getline(cin, car.name);

	GoToXY(55, 13);
	cout << "Введите цену машины за сутки: ";

	while (!(cin >> car.price))
	{
		cin.clear();
		while (cin.get() != '\n'); {

			cout << "Неверный ввод. Повторите." << endl;
		}
		if (car.price < 0) {
			cout << "Неверный ввод. Повторите." << endl;
		}
	}


	GoToXY(55, 14);
	cout << "Введите производителя машины: ";
	cin.ignore();
	getline(cin, car.manufacturer);

	GoToXY(55, 15);
	cout << "Введите количество машин: ";
	while (!(cin >> car.quantity))
	{
		cin.clear();
		while (cin.get() != '\n'); {

			cout << "Неверный ввод. Повторите." ;
		}
		if (car.quantity < 0) {
			cout << "Неверный ввод. Повторите." ;
		}
	}

	GoToXY(55, 16);
	cout << "Введите минимальный стаж вождения для машины: ";
	while (!(cin >> car.minAge))
	{
		cin.clear();
		while (cin.get() != '\n'); {

			cout << "Неверный ввод. Повторите." << endl;
		}
		if (car.minAge < 0) {
			cout << "Неверный ввод. Повторите." << endl;
		}
	}


	GoToXY(55, 17);
	cout << "Введите кол-во мест для машины: ";
	while (!(cin >> car.quantityseats))
	{
		cin.clear();
		while (cin.get() != '\n'); {

			cout << "Неверный ввод. Повторите." << endl;
		}
		if (car.minAge < 0) {
			cout << "Неверный ввод. Повторите." << endl;
		}
	}

	GoToXY(55, 18);
	cout << "Введите расход топлива для машины: ";
	while (!(cin >> car.fuelcosumption))
	{
		cin.clear();
		while (cin.get() != '\n'); {

			cout << "Неверный ввод. Повторите." << endl;
		}
		if (car.minAge < 0) {
			cout << "Неверный ввод. Повторите." << endl;
		}
	}

	GoToXY(55, 19);
	cout << "Введите кузов машины: ";
	cin.ignore();
	getline(cin, car.body);
	vectCar.push_back(car);

	GoToXY(55, 20);
	cout << "Машина успешно добавлена.";
	_getch();
	system("cls");
}

void deleteCar() {
	int y = 0;
	string* menu = new string[vectCar.size()];

	for (int i = 0; i < vectCar.size(); i++) {
		GoToXY(55, y++);
		menu[i] = vectCar[i].name;
	}

	int active_menu = 0;
	char ch;

	while (true) {
		int x = 50, y = 12;
		GoToXY(x, y);
		for (int i = 0; i < vectCar.size(); i++) {
			if (i == active_menu)
				Yellow();
			else
				Cyan();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32)
			ch = _getch();
		switch (ch) {
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < vectCar.size() - 1)
				++active_menu;
			break;
		case ESC:
			exit(0);
		case ENTER:
			system("cls");
			GoToXY(55, 12);
			cout << "Машина " << vectCar[active_menu].name << " удалена";
			_getch();
			system("cls");
			vectCar.erase(vectCar.begin() + active_menu);
			return;
		default:
			break;
		}
	}
	_getch();
	system("cls");
}

void TaxiCar() {
	Cyan();
	GoToXY(55, 9);
	cout << "Спасибо что выбрали наш таксопарк!";
	GoToXY(55, 11);
	std::cout << "         ________   " << std::endl;
	GoToXY(55, 12);
	std::cout << "    ____/        \\_______ " << std::endl;
	GoToXY(55, 13);
	std::cout << "   |  __   Taxi    __    |  " << std::endl;
	GoToXY(55, 14);
	std::cout << "   `-|  |---------|  |-''  " << std::endl;
	GoToXY(55, 15);
	std::cout << "     |__|         |__|  " << std::endl;
	/*GoToXY(50, 16);
	std::cout << "_______________________________________________  " << std::endl;*/

	GoToXY(61, 20);
	cout << "Возвращайтесь еще)";
	cin.ignore();

}

void countDown(int seconds) {
	Cyan();
	int x = 55;
	GoToXY(54, 13);
	cout << "------------------------";
	GoToXY(54, 15);
	cout << "------------------------";
	GoToXY(54, 14);
	cout << "|";
	GoToXY(55, 14);
	cout << "||";
	GoToXY(77, 14);
	cout << "|";
	for (int i = seconds; i > 0; --i) {

		GoToXY(x = x + 2, 14);
		cout << "||";

		/*cout <<"Осталось: " << i <<" секунд" << endl;*/
		this_thread::sleep_for(chrono::seconds(1));

	}

}

void ReadUserFromFile() {
	User user;
	fstream file("users.txt", fstream::in);
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, user.login, '|');
			getline(file, user.password, '|');
			file >> user.isAdmin;
			file.ignore();
			file >> user.isBanned;
			file.ignore();
			getline(file, user.info.FIO, '|');
			file >> user.info.age;
			file.ignore();
			vectUser.push_back(user);
		}
	}
	else {
		cout << "Ошибка открытия файла\n";
	}
}

void Registration() {
	Cyan();
	bool isExist = false;
	int att = 0;
	User user;
	while (att != 3) {

		GoToXY(55, 12);
		cout << "Введите имя пользователя: ";
		getline(cin, user.login);
		system("cls");
		if (user.login.find(' ') != string::npos) {
			GoToXY(55, 12);
			cout << "Логин не должен содержать пробелы." << endl;
			_getch();
			system("cls");
			att++;
		}
		else {
			break;
		}
		if (att == 3) {
			GoToXY(55, 12);
			cout << "Превышено максимальное кол-во попыток, повторите еще раз через 10 секунд\n";
			countDown(10);
			att = 0;
			system("cls");
			string menu[] = { "Ввести данные заново", "Выйти" };
			int active_menu = 0;
			char ch;
			continue;
		}
	}

	for (int i = 0; i < vectUser.size(); i++) {
		if (user.login == vectUser[i].login) {
			isExist = true;
			break;
		}
	}
	if (isExist) {
		GoToXY(55, 12);
		cout << "Пользователь с таким именем уже существует";
		att++;
		_getch();
		system("cls");
	}
	else {
		int att2 = 0;
		while (att2 != 3) {
			GoToXY(55, 12);
			cout << "Введите пароль: ";
			getline(cin, user.password);
			system("cls");
			if (user.password.size() < 8) {
				GoToXY(55, 12);
				cout << "Пароль должен содержать больше 8 символов." << endl;
				att2++;
				_getch();
				system("cls");
			}
			else {
				break;
			}
			if (att2 == 3) {
				GoToXY(55, 12);
				cout << "Превышено максимальное кол-во попыток, повторите еще раз через 10 секунд\n";
				countDown(10);
				system("cls");
				att2 = 0;
				continue;
			}
		}
		setlocale(LC_ALL, "Russian");

		string FIO;
		int age;
		while (true) {
			GoToXY(55, 12);
			cout << "Введите ФИО: ";
			getline(cin, FIO);
			system("cls");
			bool hasDigits = false;
			for (char c : FIO) {
				if (isdigit(c)) {
					hasDigits = true;
					break;
				}
			}
			if (hasDigits) {
				GoToXY(55, 12);
				cout << "ФИО не должно содержать цифры." << endl;
				_getch();
				system("cls");
				continue;
			}
			else {
				user.info.FIO = FIO;
				break;
			}
		}

		while (true) {
			GoToXY(55, 12);
			cout << "Введите стаж вождения: ";
			while (!(cin >> age))
			{
				cin.clear();
				while (cin.get() != '\n'); {

					cout << "Неверный ввод. Повторите." << endl;
				}
			}

			if (age < 0) {
				GoToXY(55, 12);
				cout << "Стаж вождения не может быть отрицательным." << endl;
				_getch();
				system("cls");
				continue;
			}
			else {
				user.info.age = age;
				break;
			}
		}
		GoToXY(55, 12);
		cout << "Пользователь успешно зарегестрирован";

		user.isAdmin = false;
		user.isBanned = false;
		vectUser.push_back(user);
		getchar();
	}
}

bool authenticateUser() {
	Cyan();
	const int MAX_ATTEMPTS = 3;
	int attempts = 0;
	bool authenticated = false;

	// Read user data from file

	string username;
	GoToXY(55, 12);
	cout << "Введите логин: ";
	getline(cin, username);
	system("cls");
	auto user = find_if(vectUser.begin(), vectUser.end(), [username](const User& u) { return u.login == username; });
	if (user == vectUser.end()) {
		GoToXY(55, 12);
		cout << "Логин неверный. Аутентификация невозможна." << endl;
		_getch();
		system("cls");
		return authenticated;
	}

	if (user->isBanned) {
		GoToXY(55, 12);
		cout << "Ваш аккаунт заблокирован." << endl;
		_getch();
		system("cls");
		return authenticated;
	}

	if (user->isAdmin) {
		while (attempts < MAX_ATTEMPTS) {
			string password;
			GoToXY(55, 12);
			cout << "Введите пароль: ";
			password = Password(password);
			system("cls");
			if (user->password == password) {
				if (user->isBanned == 0) {
					GoToXY(55, 12);
					cout << "Вы вошли как администратор." << endl;
					authenticated = true;
					_getch();
					system("cls");
					adminMenu();

					break;
				}
				else {
					GoToXY(55, 12);
					cout << "Ваш аккаунт заблокирован." << endl;
					_getch();
					system("cls");
					return authenticated;
				}
			}
			else {
				attempts++;
				GoToXY(55, 12);

				cout << "Пароль неверный. Пожалуйста, повторите попытку." << endl;
				_getch();
				system("cls");
			}
			if (attempts == MAX_ATTEMPTS) {
				GoToXY(55, 12);
				cout << "Превышено максимальное кол - во попыток,повторите еще раз через 10 секунд\n";
				countDown(10);
				attempts = 0;
				system("cls");
				continue;
			}
			return authenticated;
		}

	}

	while (attempts < MAX_ATTEMPTS) {
		string password;
		password = Password(password);

		if (user->password == password) {
			if (user->isBanned == 0) {
				GoToXY(55, 12);
				cout << "Аутентификация успешна. Вы вошли как пользователь" << endl;
				_getch();
				system("cls");
				UserMenu();

				authenticated = true;
				break;
			}
			else {
				GoToXY(55, 12);
				cout << "Ваш аккаунт заблокирован." << endl;
				return authenticated;
			}
		}
		else {
			attempts++;
			GoToXY(55, 12);
			cout << "Пароль неверный. Пожалуйста, повторите попытку." << endl;
			_getch();
			system("cls");


		}
		if (attempts == MAX_ATTEMPTS) {
			GoToXY(55, 12);
			cout << "Превышено максимальное кол - во попыток,повторите еще раз через 10 секунд\n";
			countDown(10);
			attempts = 0;
			system("cls");
			continue;
		}
	}


	return authenticated;
}

void banUser() {
	Cyan();
	int y = 0;
	string* menu = new string[vectUser.size()];

	for (int i = 0; i < vectUser.size(); i++) {
		GoToXY(55, y++);
		menu[i] = vectUser[i].login + ": " + vectUser[i].info.FIO;
	}

	int active_menu = 0; char ch;
	while (true) {
		int x = 50, y = 12;
		GoToXY(x, y);
		for (int i = 0; i < vectUser.size(); i++) {
			if (i == active_menu)Yellow();
			else Orange();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32)ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < vectUser.size() - 1)
				++active_menu;
			break;
		case ESC:
			exit(0);
		case ENTER:
			if (vectUser[active_menu].isBanned == 0) {
				vectUser[active_menu].isBanned = 1;
				system("cls");
				GoToXY(55, 12);

				cout << "Пользователь '" << vectUser[active_menu].login << "' заблокирован";
				_getch();
				system("cls");
			}
			else {
				system("cls");
				GoToXY(55, 12);

				cout << "Пользователь '" << vectUser[active_menu].login << " 'уже заблокирован";
				_getch();
				system("cls");

			}
			return;





		default:
			break;
		}

	}

}

void unblockUser() {
	int y = 0;
	string* menu = new string[vectUser.size()];

	for (int i = 0; i < vectUser.size(); i++) {
		GoToXY(55, y++);
		menu[i] = vectUser[i].login + ": " + vectUser[i].info.FIO;
	}

	int active_menu = 0; char ch;
	while (true) {
		int x = 50, y = 12;
		GoToXY(x, y);
		for (int i = 0; i < vectUser.size(); i++) {
			if (i == active_menu)Yellow();
			else Orange();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32)ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < vectUser.size() - 1)
				++active_menu;
			break;
		case ESC:
			exit(0);
		case ENTER:
			if (vectUser[active_menu].isBanned == 1) {
				vectUser[active_menu].isBanned = 0;
				system("cls");
				GoToXY(55, 12);
				cout << "Пользователь '" << vectUser[active_menu].login << "' разблокирован";
				_getch();
				system("cls");
			}
			else {
				system("cls");
				GoToXY(55, 12);
				cout << "Пользователь '" << vectUser[active_menu].login << "' уже разблокирован";
				_getch();
				system("cls");

			}
			return;





		default:
			break;
		}

	}
}

void deleteUser() {
	int y = 0;
	string* menu = new string[vectUser.size()];

	for (int i = 0; i < vectUser.size(); i++) {
		GoToXY(55, y++);
		menu[i] = vectUser[i].login + ": " + vectUser[i].info.FIO;
	}

	int active_menu = 0; char ch;
	while (true) {
		int x = 50, y = 12;
		GoToXY(x, y);
		for (int i = 0; i < vectUser.size(); i++) {
			if (i == active_menu)Yellow();
			else Orange();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32)ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < vectUser.size() - 1)
				++active_menu;
			break;
		case ESC:
			exit(0);
		case ENTER:
			system("cls");
			GoToXY(55, 12);
			cout << "Пользователь " << vectUser[active_menu].login << "' удален";
			_getch();
			system("cls");
			vectUser.erase(vectUser.begin() + active_menu);
			return;





		default:
			break;
		}

	}

}

void OverwriteUser() {

	fstream inf;

	inf.open("users.txt", fstream::out);
	for (int i = 0; i < vectUser.size(); i++) {
		inf << vectUser[i].login << "|" << vectUser[i].password << "|" <<
			vectUser[i].isAdmin << "|" << vectUser[i].isBanned << "|" <<
			vectUser[i].info.FIO << "|" << vectUser[i].info.age;
		if (i != vectUser.size() - 1) {
			inf << endl;
		}
	}
	inf.close();
}

void ReadCarsFromFile() {
	Car cars;
	ifstream infile("cars.txt");
	if (infile.is_open()) {
		while (getline(infile, cars.name, '|')) {
			infile >> cars.price;
			infile.ignore();
			getline(infile, cars.manufacturer, '|');
			infile >> cars.quantity;
			infile.ignore();
			infile >> cars.minAge;
			infile.ignore();
			infile >> cars.quantityseats;
			infile.ignore();
			infile >> cars.fuelcosumption;
			infile.ignore();
			getline(infile, cars.body, '|');
			infile.ignore();


			vectCar.push_back(cars);
		}
		infile.close();
	}
	else {
		cout << "Ошибка открытия файла\n";
	}
}

void OverwriteCars() {

	fstream inf;

	inf.open("cars.txt", fstream::out);
	for (int i = 0; i < vectCar.size(); i++) {

		inf << vectCar[i].name << '|'
			<< vectCar[i].price << '|'
			<< vectCar[i].manufacturer << '|'
			<< vectCar[i].quantity << '|'
			<< vectCar[i].minAge << '|'
			<< vectCar[i].quantityseats << '|'
			<< vectCar[i].fuelcosumption << '|'
			<< vectCar[i].body << '|';
		if (i != vectCar.size() - 1) {
			inf << endl;
		}

	}
	inf.close();
}

void DisplayCars() {
	Cyan();

	cout << left << setw(40) << "Название" << '|'
		<< setw(10) << "Цена" << '|'
		<< setw(15) << "Производитель" << '|'
		<< setw(10) << "Количество" << '|'
		<< setw(19) << "Минимальный стаж" << '|'
		<< setw(11) << "Кол-во мест" << '|'
		<< setw(15) << "Расход топлива" << '|'
		<< setw(10) << "Кузов авто" << '|' << endl;

	cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
	for (int i = 0; i < vectCar.size(); i++) {

		cout << left << setw(40) << vectCar[i].name << '|'
			<< setw(10) << vectCar[i].price << '|'
			<< setw(15) << vectCar[i].manufacturer << '|'
			<< setw(10) << vectCar[i].quantity << '|'
			<< setw(19) << vectCar[i].minAge << '|'
			<< setw(11) << vectCar[i].quantityseats << '|'
			<< setw(15) << vectCar[i].fuelcosumption << '|'
			<< setw(10) << vectCar[i].body << '|' << endl;

		cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
	}
}

void AdminDisplayCars() {
	Cyan();

	cout << left << setw(40) << "Название" << '|'
		<< setw(10) << "Цена" << '|'
		<< setw(15) << "Производитель" << '|'
		<< setw(10) << "Количество" << '|'
		<< setw(19) << "Минимальный стаж" << '|'
		<< setw(11) << "Кол-во мест" << '|'
		<< setw(15) << "Расход топлива" << '|'
		<< setw(10) << "Кузов авто" << '|' << endl;

	cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
	for (int i = 0; i < vectCar.size(); i++) {
		if (vectCar[i].quantity < 10) {
			cout << "\033[31m";  // Set text color to red
		}

		cout << left << setw(40) << vectCar[i].name << '|'
			<< setw(10) << vectCar[i].price << '|'
			<< setw(15) << vectCar[i].manufacturer << '|'
			<< setw(10) << vectCar[i].quantity << '|'
			<< setw(19) << vectCar[i].minAge << '|'
			<< setw(11) << vectCar[i].quantityseats << '|'
			<< setw(15) << vectCar[i].fuelcosumption << '|'
			<< setw(10) << vectCar[i].body << '|' << endl;

		if (vectCar[i].quantity < 10) {
			Cyan();
		}

		cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
	}
	_getch();
	system("cls");
}

void sortCarsByName() {
	for (int i = 0; i < vectCar.size() - 1; i++) {
		for (int j = i + 1; j < vectCar.size(); j++) {
			if (vectCar[i].name > vectCar[j].name) {
				swap(vectCar[i], vectCar[j]);
			}
		}
	}
}

void sortByPrice() {
	for (int i = 0; i < vectCar.size() - 1; i++) {
		for (int j = 0; j < vectCar.size() - i - 1; j++) {
			if (vectCar[j].price > vectCar[j + 1].price) {
				Car temp = vectCar[j];
				vectCar[j] = vectCar[j + 1];
				vectCar[j + 1] = temp;
			}
		}
	}
}

void sortByQuantity() {
	for (int i = 0; i < vectCar.size() - 1; i++) {
		for (int j = 0; j < vectCar.size() - i - 1; j++) {
			if (vectCar[j].quantity > vectCar[j + 1].quantity) {
				swap(vectCar[j], vectCar[j + 1]);
			}
		}
	}
}

void sortByQuantitySeats() {
	for (int i = 0; i < vectCar.size() - 1; i++) {
		for (int j = 0; j < vectCar.size() - i - 1; j++) {
			if (vectCar[j].quantityseats > vectCar[j + 1].quantityseats) {
				swap(vectCar[j], vectCar[j + 1]);
			}
		}
	}
}

void sortByFuelConsumption() {
	for (int i = 0; i < vectCar.size() - 1; i++) {
		for (int j = 0; j < vectCar.size() - i - 1; j++) {
			if (vectCar[j].fuelcosumption > vectCar[j + 1].fuelcosumption) {
				swap(vectCar[j], vectCar[j + 1]);
			}
		}
	}
}

void searchByName()
{
	Cyan();
	string searchName;
	bool found = false;
	GoToXY(55, 12);
	cout << "Введите название машины, которую желаете найти: ";

	while (true) {
		char ch = _getch();
		if (ch == '\r') {  // Enter key
			break;
		}
		if (ch == '\b') {  // Backspace key
			if (!searchName.empty()) {
				searchName.pop_back();
				system("cls");
			}
			continue;
		}
		searchName += tolower(ch);
		system("cls");
		found = false;
		cout << "Введите название машины, которую желаете найти: " << searchName;
		for (int i = 0; i < vectCar.size(); i++) {
			string carName = vectCar[i].name;
			string lowerCarName;
			for (char& c : carName) {
				c = tolower(c);
			}
			if (carName.find(searchName) == 0) {
				if (!found) {
					cout << "\n" << left << setw(40) << "Название" << '|'
						<< setw(10) << "Цена" << '|'
						<< setw(15) << "Производитель" << '|'
						<< setw(10) << "Количество" << '|'
						<< setw(19) << "Минимальный стаж" << '|'
						<< setw(11) << "Кол-во мест" << '|'
						<< setw(15) << "Расход топлива" << '|'
						<< setw(10) << "Кузов авто" << '|' << endl;
					cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
					found = true;
				}
				cout << left << setw(40) << vectCar[i].name << '|'
					<< setw(10) << vectCar[i].price << '|'
					<< setw(15) << vectCar[i].manufacturer << '|'
					<< setw(10) << vectCar[i].quantity << '|'
					<< setw(19) << vectCar[i].minAge << '|'
					<< setw(11) << vectCar[i].quantityseats << '|'
					<< setw(15) << vectCar[i].fuelcosumption << '|'
					<< setw(10) << vectCar[i].body << '|' << endl;
				cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
			}
		}
		if (!found) {
			GoToXY(55, 12);
			cout << "Машина с таким именем не найдена." << endl;
		}
	}




	if (searchName.empty()) {  // Show all cars if searchName is empty
		found = true;
		for (int i = 0; i < vectCar.size(); i++) {
			if (!found) {
				cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
			}
			cout << left << setw(40) << vectCar[i].name << '|'
				<< setw(10) << vectCar[i].price << '|'
				<< setw(15) << vectCar[i].manufacturer << '|'
				<< setw(10) << vectCar[i].quantity << '|'
				<< setw(19) << vectCar[i].minAge << '|'
				<< setw(11) << vectCar[i].quantityseats << '|'
				<< setw(15) << vectCar[i].fuelcosumption << '|'
				<< setw(10) << vectCar[i].body << '|' << endl;
			cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
			found = true;
		}
	}


	if (!found) {
		GoToXY(55, 12);
		cout << "Машина с таким именем не найдена." << endl;
	}

}

void searchByBody()
{
	Cyan();
	string searchBody;
	bool found = false;
	GoToXY(55, 12);
	cout << "Введите вид машины, которую желаете найти: ";
	setlocale(LC_ALL, "RUS");
	while (true) {
		char ch = _getch();
		if (ch == '\r') {  // Enter key
			break;
		}
		if (ch == '\b') {  // Backspace key
			if (!searchBody.empty()) {
				searchBody.pop_back();
				system("cls");
			}
			continue;
		}
		searchBody += tolower(ch);
		system("cls");
		found = false;
		cout << "Введите вид машины, которую желаете найти: " << searchBody;
		for (int i = 0; i < vectCar.size(); i++) {
			string carBody = vectCar[i].body;
			string lowerCarName;
			for (char& c : carBody) {
				c = tolower(c);
			}
			if (carBody.find(searchBody) == 0) {
				if (!found) {
					cout << "\n" << left << setw(40) << "Название" << '|'
						<< setw(10) << "Цена" << '|'
						<< setw(15) << "Производитель" << '|'
						<< setw(10) << "Количество" << '|'
						<< setw(19) << "Минимальный стаж" << '|'
						<< setw(11) << "Кол-во мест" << '|'
						<< setw(15) << "Расход топлива" << '|'
						<< setw(10) << "Кузов авто" << '|' << endl;
					cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
					found = true;
				}
				cout << left << setw(40) << vectCar[i].name << '|'
					<< setw(10) << vectCar[i].price << '|'
					<< setw(15) << vectCar[i].manufacturer << '|'
					<< setw(10) << vectCar[i].quantity << '|'
					<< setw(19) << vectCar[i].minAge << '|'
					<< setw(11) << vectCar[i].quantityseats << '|'
					<< setw(15) << vectCar[i].fuelcosumption << '|'
					<< setw(10) << vectCar[i].body << '|' << endl;
				cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
			}
		}
		if (!found) {
			GoToXY(55, 12);
			cout << "Машина такого вида не найдена." << endl;
		}
	}




	if (searchBody.empty()) {  // Show all cars if searchName is empty
		found = true;
		for (int i = 0; i < vectCar.size(); i++) {
			if (!found) {
				cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
			}
			cout << left << setw(40) << vectCar[i].name << '|'
				<< setw(10) << vectCar[i].price << '|'
				<< setw(15) << vectCar[i].manufacturer << '|'
				<< setw(10) << vectCar[i].quantity << '|'
				<< setw(19) << vectCar[i].minAge << '|'
				<< setw(11) << vectCar[i].quantityseats << '|'
				<< setw(15) << vectCar[i].fuelcosumption << '|'
				<< setw(10) << vectCar[i].body << '|' << endl;
			cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
			found = true;
		}
	}


	if (!found) {
		GoToXY(55, 12);
		cout << "Машина такого вида не найдена." << endl;
	}

}

void searchCarsByAge() {
	Cyan();
	int age;
	GoToXY(55, 12);

	cout << "Введите стаж для поиска машины: ";
	cin >> age;
	system("cls");
	bool found = false;
	for (int i = 0; i < vectCar.size(); i++) {
		if (vectCar[i].minAge <= age) {
			if (!found) {
				cout << left << setw(40) << "Название" << '|'
					<< setw(10) << "Цена" << '|'
					<< setw(15) << "Производитель" << '|'
					<< setw(10) << "Количество" << '|'
					<< setw(19) << "Минимальный стаж" << '|'
					<< setw(11) << "Кол-во мест" << '|'
					<< setw(15) << "Расход топлива" << '|'
					<< setw(10) << "Кузов авто" << '|' << endl;
				cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
				found = true;
			}
			cout << left << setw(40) << vectCar[i].name << '|'
				<< setw(10) << vectCar[i].price << '|'
				<< setw(15) << vectCar[i].manufacturer << '|'
				<< setw(10) << vectCar[i].quantity << '|'
				<< setw(19) << vectCar[i].minAge << '|'
				<< setw(11) << vectCar[i].quantityseats << '|'
				<< setw(15) << vectCar[i].fuelcosumption << '|'
				<< setw(10) << vectCar[i].body << '|' << endl;
			cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
		}
	}
	if (!found) {
		GoToXY(55, 12);

		cout << "Машина для данного стажа не найдены." << endl;
		_getch();
		system("cls");
	}
}

void filterCarsByPrice() {
	Cyan();
	double min_price, max_price;
	GoToXY(55, 12);

	cout << "Введите минимальную цену: ";
	cin >> min_price;
	GoToXY(55, 13);

	cout << "Введите максимальную цену: ";
	cin >> max_price;
	system("cls");
	cout << left << setw(40) << "Название" << '|'
		<< setw(10) << "Цена" << '|'
		<< setw(15) << "Производитель" << '|'
		<< setw(10) << "Количество" << '|'
		<< setw(19) << "Минимальный стаж" << '|'
		<< setw(11) << "Кол-во мест" << '|'
		<< setw(15) << "Расход топлива" << '|'
		<< setw(10) << "Кузов авто" << '|' << endl;
	cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;

	for (int i = 0; i < vectCar.size(); i++) {
		if (vectCar[i].price >= min_price && vectCar[i].price <= max_price) {
			cout << left << setw(40) << vectCar[i].name << '|'
				<< setw(10) << vectCar[i].price << '|'
				<< setw(15) << vectCar[i].manufacturer << '|'
				<< setw(10) << vectCar[i].quantity << '|'
				<< setw(19) << vectCar[i].minAge << '|'
				<< setw(11) << vectCar[i].quantityseats << '|'
				<< setw(15) << vectCar[i].fuelcosumption << '|'
				<< setw(10) << vectCar[i].body << '|' << endl;
			cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
		}
	}

}

void filterCarsByQuantity() {
	Cyan();
	int min_quantity, max_quantity;
	GoToXY(55, 12);

	cout << "Введите минимальное количество: ";
	cin >> min_quantity;
	GoToXY(55, 13);

	cout << "Введите максимальное количество: ";
	cin >> max_quantity;
	system("cls");
	cout << left << setw(40) << "Название" << '|'
		<< setw(10) << "Цена" << '|'
		<< setw(15) << "Производитель" << '|'
		<< setw(10) << "Количество" << '|'
		<< setw(19) << "Минимальный стаж" << '|'
		<< setw(11) << "Кол-во мест" << '|'
		<< setw(15) << "Расход топлива" << '|'
		<< setw(10) << "Кузов авто" << '|' << endl;
	cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;

	for (int i = 0; i < vectCar.size(); i++) {
		if (vectCar[i].quantity >= min_quantity && vectCar[i].quantity <= max_quantity) {
			cout << left << setw(40) << vectCar[i].name << '|'
				<< setw(10) << vectCar[i].price << '|'
				<< setw(15) << vectCar[i].manufacturer << '|'
				<< setw(10) << vectCar[i].quantity << '|'
				<< setw(19) << vectCar[i].minAge << '|'
				<< setw(11) << vectCar[i].quantityseats << '|'
				<< setw(15) << vectCar[i].fuelcosumption << '|'
				<< setw(10) << vectCar[i].body << '|' << endl;
			cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
		}
	}
}

void filterCarsBySeats() {
	Cyan();
	int min_quantitySeats, max_quantitySeats;
	GoToXY(55, 12);

	cout << "Введите минимальное количество мест: ";
	cin >> min_quantitySeats;
	GoToXY(55, 13);

	cout << "Введите максимальное количество мест: ";
	cin >> max_quantitySeats;
	system("cls");
	cout << left << setw(40) << "Название" << '|'
		<< setw(10) << "Цена" << '|'
		<< setw(15) << "Производитель" << '|'
		<< setw(10) << "Количество" << '|'
		<< setw(19) << "Минимальный стаж" << '|'
		<< setw(11) << "Кол-во мест" << '|'
		<< setw(15) << "Расход топлива" << '|'
		<< setw(10) << "Кузов авто" << '|' << endl;
	cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;

	for (int i = 0; i < vectCar.size(); i++) {
		if (vectCar[i].quantityseats >= min_quantitySeats && vectCar[i].quantityseats <= max_quantitySeats) {
			cout << left << setw(40) << vectCar[i].name << '|'
				<< setw(10) << vectCar[i].price << '|'
				<< setw(15) << vectCar[i].manufacturer << '|'
				<< setw(10) << vectCar[i].quantity << '|'
				<< setw(19) << vectCar[i].minAge << '|'
				<< setw(11) << vectCar[i].quantityseats << '|'
				<< setw(15) << vectCar[i].fuelcosumption << '|'
				<< setw(10) << vectCar[i].body << '|' << endl;
			cout << setfill('-') << setw(138) << '-' << setfill(' ') << endl;
		}
	}
}

void mainMenu() {
	Cyan();
	GoToXY(55, 12);
	cout << "ДОБРОГО ВРЕМЕНИ СУТОК!!";
	GoToXY(50, 13);
	cout << "Вас приветствует таксопарк 'Столица'.";
	GoToXY(50, 14);
	cout << "Чтобы продолжить работу вам необходимо войти в аккаунт";
	GoToXY(50, 15);
	cout << "или зарегистрировать новый аккаунт.";
	_getch();
	system("cls");
	int y = 0;
	string menu[] = { "Зарегистрироваться","Авторизация","Просмотреть каталог машин","Завершить программу" };



	int active_menu = 0; char ch;
	while (true) {
		int x = 50, y = 12;
		GoToXY(x, y);
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)Yellow();
			else Orange();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32)ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < size(menu) - 1)
				++active_menu;
			break;

		case ENTER:

			switch (active_menu)
			{
			case 0:
				system("cls");

				Registration();
				_getch();
				system("cls");
				break;
			case 1:
				system("cls");

				authenticateUser();

				break;
			case 2:
				system("cls");

				DisplayCars();
				_getch();
				system("cls");
				break;
			case 3:
				system("cls");
				TaxiCar();
				OverwriteUser();
				OverwriteCars();
				exit(0);
			}





		default:
			break;
		}
	}

}

void sortMenu() {
	int y = 0;
	string menu[] = { "Сортировать машины по названию","Сортировать машины по цене","Сортировать машины по кол-ву машин","Сортировать машины по кол-ву мест","Сортировать машины по расходу топлива","Назад" };



	int active_menu = 0; char ch;
	while (true) {
		int x = 50, y = 12;
		GoToXY(x, y);
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)Yellow();
			else Orange();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32)ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < size(menu) - 1)
				++active_menu;
			break;
		case ESC:
			exit(0);
		case ENTER:

			switch (active_menu)
			{
			case 0:
				system("cls");

				sortCarsByName();
				DisplayCars();
				_getch();
				system("cls");
				break;
			case 1:
				system("cls");

				sortByPrice();
				DisplayCars();
				_getch();
				system("cls");
				break;
			case 2:
				system("cls");

				sortByQuantity();
				DisplayCars();
				_getch();
				system("cls");
				break;

			case 3:
				system("cls");

				sortByQuantitySeats();
				DisplayCars();
				_getch();
				system("cls");
				break;

			case 4:
				system("cls");

				sortByFuelConsumption();
				DisplayCars();
				_getch();
				system("cls");
				break;
			case 5:
				system("cls");
				UserMenu();
			}





		default:
			break;
		}
	}
}

void filtrMenu() {
	int y = 0;
	string menu[] = { "Фильтровать машину по ценовому промежутку","Фильтровать машины по количеству","Фильтровать машины по стажу","Фильтровать машины по кол-ву мест","Назад" };



	int active_menu = 0; char ch;
	while (true) {
		int x = 50, y = 12;
		GoToXY(x, y);
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)Yellow();
			else Orange();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32)ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < size(menu) - 1)
				++active_menu;
			break;
		case ESC:
			exit(0);
		case ENTER:

			switch (active_menu)
			{

			case 0:
				system("cls");

				filterCarsByPrice();
				_getch();
				system("cls");
				break;
			case 1:
				system("cls");

				filterCarsByQuantity();
				_getch();
				system("cls");
				break;
			case 2:
				system("cls");
				searchCarsByAge();
				_getch();
				system("cls");
				break;
			case 3:
				system("cls");
				filterCarsBySeats();
				_getch();
				system("cls");
				break;
			case 4:
				system("cls");
				UserMenu();
				break;
			}





		default:
			break;
		}
	}
}

void adminMenu() {
	int y = 0;
	string menu[] = { "Заблокировать пользователя","Разблокировать пользователя","Удалить пользователя","Добавить новую машину","Удалить машину","Просмотреть каталог машин","Добавить существующую машину","Выйти из аккаунта" };



	int active_menu = 0; char ch;
	while (true) {
		int x = 50, y = 12;
		GoToXY(x, y);
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)Yellow();
			else Orange();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32)ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < size(menu) - 1)
				++active_menu;
			break;
		case ESC:
			exit(0);
		case ENTER:

			switch (active_menu)
			{
			case 0:
				system("cls");

				banUser();

				break;
			case 1:
				system("cls");

				unblockUser();

				break;
			case 2:
				system("cls");

				deleteUser();

				break;
			case 3:
				system("cls");
				AddCar();
				break;
			case 4:

				system("cls");
				deleteCar();
				break;
			case 5:
				system("cls");
				AdminDisplayCars();
				break;

			case 6:
				system("cls");
				updateCarQuantity();
				system("cls");
				break;

			case 7:
				system("cls");
				mainMenu();
			}





		default:
			break;
		}
	}
}

void UserMenu() {
	int y = 0;
	string menu[] = { "Просмотреть каталог машин","Отсортировать машины по какому-либо параметру","Отфильтровать машины по какому-либо параметру","Совершить заказ","Поиск машины по названию","Поиск машины по кузову","Выйти из аккаунта" };



	int active_menu = 0; char ch;
	while (true) {
		int x = 50, y = 12;
		GoToXY(x, y);
		for (int i = 0; i < size(menu); i++) {
			if (i == active_menu)Yellow();
			else Orange();
			GoToXY(x, y++);
			cout << menu[i] << endl;
		}
		ch = _getch();
		if (ch == -32)ch = _getch();
		switch (ch)
		{
		case UP:
			if (active_menu > 0)
				--active_menu;
			break;
		case DOWN:
			if (active_menu < size(menu) - 1)
				++active_menu;
			break;
		case ESC:
			exit(0);
		case ENTER:

			switch (active_menu)
			{
			case 0:
				system("cls");

				DisplayCars();
				_getch();
				system("cls");
				break;

			case 1:
				system("cls");

				sortMenu();
				_getch();
				system("cls");
				break;

			case 2:
				system("cls");

				filtrMenu();
				_getch();
				system("cls");
				break;

			case 3:
				system("cls");
				purchaseCar();
				system("cls");
				break;

			case 4:
				system("cls");
				searchByName();
				system("cls");
				break;

			case 5:
				system("cls");
				searchByBody();
				system("cls");
				break;

			case 6:
				system("cls");
				mainMenu();
			}





		default:
			break;
		}
	}

}

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ReadUserFromFile();
	ReadCarsFromFile();
	mainMenu();


}
