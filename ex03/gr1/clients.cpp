#include<iostream>
#include<fstream>

using namespace std;

struct clientData {
  int account;
  char firstName[16];
  char lastName[16];
  float balance;
};

ostream& operator<<(ostream& out, clientData& data) {
  out << "account: " << data.account << endl;
  out << "firstName: " << data.firstName << endl;
  out << "lastName: " << data.lastName << endl;
  out << "balance: " << data.balance << endl;

  return out;
}

bool readClientData(fstream& file, clientData& client) {
  return file.read(reinterpret_cast<char*>(&client), sizeof(client));
}

bool writeClientData(fstream& file, clientData& client) {
  return file.write(reinterpret_cast<char*>(&client), sizeof(client));
}

clientData findClientByAccount(int account) {
  fstream file("clients.dat", ios::binary | ios::in);

  clientData client;

  while (readClientData(file, client)) {
    if (client.account == account) {
      file.close();
      return client;
    }
  }

  file.close();
  return clientData();
}

void updateClient(clientData newClientData) {
  fstream file("clients.dat", ios::binary | ios::in | ios::out);

  clientData client;

  while (readClientData(file, client)) {
    if (client.account == newClientData.account) {
      file.seekp(-sizeof(newClientData), ios::cur);
      cout << "tellg: " << file.tellg() << endl;
      cout << "tellp: " << file.tellp() << endl;
      writeClientData(file, newClientData);
      file.close();
      return;
    }
  }

  file.close();

}

void initWithSampleData() {
  fstream file("clients.dat", ios::binary | ios::out);

  clientData client1 = { 13, "Pesho 0", "Ivanov 0", 1320.12 };
  clientData client2 = { 14, "Pesho 1", "Ivanov 1", 1321.12 };
  clientData client3 = { 15, "Pesho 2", "Ivanov 2", 1322.12 };
  clientData client4 = { 16, "Pesho 3", "Ivanov 3", 1323.12 };

  writeClientData(file, client1);
  writeClientData(file, client2);
  writeClientData(file, client3);
  writeClientData(file, client4);

  file.close();
}

int main() {
  // initWithSampleData();
  clientData client = findClientByAccount(15);
  cout << client << endl;

  client.balance += 100;
  updateClient(client);

  client = findClientByAccount(15);
  cout << client << endl;
}
