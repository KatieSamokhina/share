

#include <iostream>
#include <sstream>
#include <exception>
#include <vector>
#include <set>
#include <limits>
using namespace std;

//класс, содержащий информацию о бронировании номеров клиентом
class Order {
public:
	//конструктор без параметров
	Order() { 
		time = 0;
		hotel_name = "";
		client_id = 1;
		room_count = 1;
	}
	//конструктор для создания объекта по известным параметрам
	Order(long long t, string hotel, unsigned int client, int count) {
		time = t;
		hotel_name = hotel;
		client_id = client;
		room_count = count;
	}
	//функции для получения данных из приватной секции
	long long GetTime() const {
		return time;
	}
	string GetHotel_name() const {
		return hotel_name;
	}
	unsigned int GetClient_id() const {
		return client_id;
	}
	short GetRoom_count() const {
		return room_count;
	}
private:
	long long time;			//long long из необходимости хранить очень большие числа, ведь время в секундах 
	string hotel_name;		//обычная строка для хранения имени отеля
	unsigned int client_id; //id не может быть отрицательным, поэтому unsigned
	short room_count;		//здесь достаточно и short
};

//функция для нахождения количества различных клиентов, бронировавших номера в отеле hotel за последние сутки
//возвращает short, потому что количество клиентов не может превышать число запросов Q, а оно имеет тип short
short GetClientsByHotel(const vector<Order>& data, string& hotel) {
	int i = data.size() - 1;					//будет индексом для цикла
	long long current_time = data[i].GetTime();	//находим текущий момент, от которого отсчитываем сутки
	set<unsigned int> clients;					//множество для хранения уникальных клиентов
	while (i >= 0 && data[i].GetTime() > (current_time - 86400)) { //цикл с конца вектора заказов до начала суток 
		if (data[i].GetHotel_name() == hotel) {						//если подходящий отель
			clients.insert(data[i].GetClient_id());					//добавляем элемент в множество клиентов
		}
		--i;
	}
	return clients.size();						//размер множества и будет искомым количеством клиентов 
}

//функция для нахождения количества номеров, забронированных за последние сутки в отеле hotel
//возвращает short, потому что количество клиентов не может превышать число запросов Q, а оно имеет тип short
int GetRoomsByHotel(const vector<Order>& data, string& hotel) {
	int i = data.size() - 1;					//будет индексом для цикла
	long long current_time = data[i].GetTime();	//находим текущий момент, от которого отсчитываем сутки
	int room_count = 0;							//искомое количество комнат
	while (i >= 0 && data[i].GetTime() > (current_time - 86400)) {	//цикл с конца вектора заказов до начала суток
		if (data[i].GetHotel_name() == hotel) {						//если подходящий отель
			room_count += data[i].GetRoom_count();					//увеличиваем число номеров
		}
		i--;
	}
	return room_count;
}

int main() {
	short q = 0;									//количество запросов
	vector <Order> data;							//вектор с информацией о бронировании клиентами номеров в отеле
	try {
		if (!(cin >> q))															//если число запросов не было введено
			throw invalid_argument("You forgot to enter the number of commands");	//то бросаем исключение
	}
	catch (invalid_argument& e) {
		cout << e.what() << endl;					//выводим текст ошибки и завершаем программу
	}
	for (int i = 0; i < q; i++) {					//цикл по количеству запросов
		string command;
		try {
			cin >> command;							//ввод запроса
			if (command == "BOOK") {				//обработка запроса BOOK
				long long time;
				string hotel_name;
				unsigned int client_id;
				short room_count;
				if (!(cin >> time >> hotel_name >> client_id >> room_count)) {//если ввели что-то не то
					cin.clear();											//чистим поток ввода
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					throw invalid_argument("Syntax error, please try again");//бросаем исключение
				}
				data.push_back(Order(time, hotel_name, client_id, room_count));//иначе добавляем новую запись в вектор
			}
			else {
				if (command == "CLIENTS") {			//обработка запроса CLIENTS
					string hotel_name;
					cin >> hotel_name;
					cout << GetClientsByHotel(data, hotel_name) << endl;
				}
				else {
					if (command == "ROOMS") {		//обработка запроса ROOMS
						string hotel_name;
						cin >> hotel_name;
						cout << GetRoomsByHotel(data, hotel_name) << endl;
					}
					else {														//если не было введено ни одно ключевое слово
						cin.clear();											//чистим поток
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						throw invalid_argument("Syntax error, please try again");//бросаем исключение
					}
				}
			}
		}
		catch (invalid_argument& e) { //обработка исключений
			cout << e.what() << endl; //выводим текст ошибки
			i--;					//уменьшаем счетчик запросов, чтобы дать пользователю возможность ввести запрос заново
			continue;				//продолжаем выполнение программы
		}
	}
	return 0;
}