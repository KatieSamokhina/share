

#include <iostream>
#include <sstream>
#include <exception>
#include <vector>
#include <set>
#include <limits>
using namespace std;

//�����, ���������� ���������� � ������������ ������� ��������
class Order {
public:
	//����������� ��� ����������
	Order() { 
		time = 0;
		hotel_name = "";
		client_id = 1;
		room_count = 1;
	}
	//����������� ��� �������� ������� �� ��������� ����������
	Order(long long t, string hotel, unsigned int client, int count) {
		time = t;
		hotel_name = hotel;
		client_id = client;
		room_count = count;
	}
	//������� ��� ��������� ������ �� ��������� ������
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
	long long time;			//long long �� ������������� ������� ����� ������� �����, ���� ����� � �������� 
	string hotel_name;		//������� ������ ��� �������� ����� �����
	unsigned int client_id; //id �� ����� ���� �������������, ������� unsigned
	short room_count;		//����� ���������� � short
};

//������� ��� ���������� ���������� ��������� ��������, ������������� ������ � ����� hotel �� ��������� �����
//���������� short, ������ ��� ���������� �������� �� ����� ��������� ����� �������� Q, � ��� ����� ��� short
short GetClientsByHotel(const vector<Order>& data, string& hotel) {
	int i = data.size() - 1;					//����� �������� ��� �����
	long long current_time = data[i].GetTime();	//������� ������� ������, �� �������� ����������� �����
	set<unsigned int> clients;					//��������� ��� �������� ���������� ��������
	while (i >= 0 && data[i].GetTime() > (current_time - 86400)) { //���� � ����� ������� ������� �� ������ ����� 
		if (data[i].GetHotel_name() == hotel) {						//���� ���������� �����
			clients.insert(data[i].GetClient_id());					//��������� ������� � ��������� ��������
		}
		--i;
	}
	return clients.size();						//������ ��������� � ����� ������� ����������� �������� 
}

//������� ��� ���������� ���������� �������, ��������������� �� ��������� ����� � ����� hotel
//���������� short, ������ ��� ���������� �������� �� ����� ��������� ����� �������� Q, � ��� ����� ��� short
int GetRoomsByHotel(const vector<Order>& data, string& hotel) {
	int i = data.size() - 1;					//����� �������� ��� �����
	long long current_time = data[i].GetTime();	//������� ������� ������, �� �������� ����������� �����
	int room_count = 0;							//������� ���������� ������
	while (i >= 0 && data[i].GetTime() > (current_time - 86400)) {	//���� � ����� ������� ������� �� ������ �����
		if (data[i].GetHotel_name() == hotel) {						//���� ���������� �����
			room_count += data[i].GetRoom_count();					//����������� ����� �������
		}
		i--;
	}
	return room_count;
}

int main() {
	short q = 0;									//���������� ��������
	vector <Order> data;							//������ � ����������� � ������������ ��������� ������� � �����
	try {
		if (!(cin >> q))															//���� ����� �������� �� ���� �������
			throw invalid_argument("You forgot to enter the number of commands");	//�� ������� ����������
	}
	catch (invalid_argument& e) {
		cout << e.what() << endl;					//������� ����� ������ � ��������� ���������
	}
	for (int i = 0; i < q; i++) {					//���� �� ���������� ��������
		string command;
		try {
			cin >> command;							//���� �������
			if (command == "BOOK") {				//��������� ������� BOOK
				long long time;
				string hotel_name;
				unsigned int client_id;
				short room_count;
				if (!(cin >> time >> hotel_name >> client_id >> room_count)) {//���� ����� ���-�� �� ��
					cin.clear();											//������ ����� �����
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					throw invalid_argument("Syntax error, please try again");//������� ����������
				}
				data.push_back(Order(time, hotel_name, client_id, room_count));//����� ��������� ����� ������ � ������
			}
			else {
				if (command == "CLIENTS") {			//��������� ������� CLIENTS
					string hotel_name;
					cin >> hotel_name;
					cout << GetClientsByHotel(data, hotel_name) << endl;
				}
				else {
					if (command == "ROOMS") {		//��������� ������� ROOMS
						string hotel_name;
						cin >> hotel_name;
						cout << GetRoomsByHotel(data, hotel_name) << endl;
					}
					else {														//���� �� ���� ������� �� ���� �������� �����
						cin.clear();											//������ �����
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						throw invalid_argument("Syntax error, please try again");//������� ����������
					}
				}
			}
		}
		catch (invalid_argument& e) { //��������� ����������
			cout << e.what() << endl; //������� ����� ������
			i--;					//��������� ������� ��������, ����� ���� ������������ ����������� ������ ������ ������
			continue;				//���������� ���������� ���������
		}
	}
	return 0;
}