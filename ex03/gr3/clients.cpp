#include <iostream>
#include <fstream>
using namespace std;

struct clientData {
  int account;
  char lastName[16];
  char firstName[16];
  float balance;
};

/*
  account
  [ id | firstName | lastName | balance ]
  [ 01 | Pesho     | lastName | 12.10   ]
  [ 13 | Mariika   | lastName | 12.10   ]
*/

void persist(clientData& client) {
  ofstream file("clients.dat", ios::binary | ios::app);
  file.write(reinterpret_cast<char*>(&client), sizeof(client));
  file.close();
}

clientData findByAccount(int account) {
  ifstream file("clients.dat", ios::binary);

  clientData client;
  while (file.read(reinterpret_cast<char*>(&client), sizeof(client))) {
    if (client.account == account) {
      file.close();
      return client;
    }
  }

  file.close();
  return clientData();
}

void changeBalance(int account, float newBalance) {
  fstream file("clients.dat", ios::binary);

  clientData client;
  while (file.read(reinterpret_cast<char*>(&client), sizeof(client))) {
    if (client.account == account) {
      file.seekp(-sizeof(client), ios::cur);
      client.balance = newBalance;

      file.write(reinterpret_cast<char*>(&client), sizeof(client));

      file.close();
    }
  }

  file.close();
}

int main() {
  // clientData client1 = {41, "Ivan", "Petrov", 12.10 };
  // clientData client2 = {42, "Petar", "Ivanov", 14.10 };
  // clientData client3 = {43, "Gosho", "Petrov", 43.10 };
  // persist(client1);
  // persist(client2);
  // persist(client3);

  // changeBalance(43, 50.00);
  cout << findByAccount(43).lastName << endl;
  cout << findByAccount(43).firstName << endl;
  cout << findByAccount(43).balance << endl;
  cout << findByAccount(43).account << endl;

}











