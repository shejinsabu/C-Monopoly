#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

class node {
public:
  string propertyName;
  string owner;
  int price;
  bool isOwned;
  int rent;
  node *next;
  node(string _propertyName, string _owner, int _price, bool _isOwned, int _rent) {
    propertyName = _propertyName;
    owner = _owner;
    price = _price;
    isOwned = _isOwned;
    rent = _rent;
    next = nullptr;
  }
  void setisOwned(string _owner) {
    isOwned = true;
    owner = _owner;
  }

  bool ifisOwned() { return isOwned; }
  string getpropertyName() { return propertyName; }
  string getOwner() { return owner; }
  int getRent() { return rent; }
  int getPrice() { return price; }
};

class linkedlist {
private:
  node *head;

public:
  linkedlist() { head = nullptr; }
  ~linkedlist() {
    if (head != nullptr) {
      node *cu = head->next;
      while (cu != head) {
        node *temp = cu;
        cu = cu->next;
        delete temp;
      }
      delete cu;
    }
  }

  node *getHead() { return head; }

  void addAtTail(string _propertyName, string _owner, int _price, bool _isOwned, int _rent) {
    node *temp = new node(_propertyName, _owner, _price, _isOwned, _rent);
    if (head == nullptr) {
      head = temp;
      temp->next = head;
    } else {
      node *cu = head;
      while (cu->next != head) {
        cu = cu->next;
      }
      cu->next = temp;
      temp->next = head;
    }
  }

  node *move(int spaces, node *playerposition, int &balance) {
    node *cu = playerposition;
    for (int i = 0; i < spaces; i++) {
      cu = cu->next;
      if(cu == getHead()){
        cout << "You have passed GO, your balance increases by 100 dollars" << endl;
        balance += 100;
        cout << "Your new balance is " << balance << " dollars." << endl;
        cout << endl;
      }
    }
    playerposition = cu;
    return playerposition;
  }

  void print() {
    if (head != nullptr) {
      node *cu = head;
      do {
        cout << cu->propertyName << endl;
        cu = cu->next;
      } while (cu != head);
    }
  }

  void newGame() {
    ifstream fin;
    fin.open("newGame.txt");
    string line;

    string propertyName;
    string propertyOwner;
    int price;
    bool owned = false;
    int rent;

    while (!fin.eof()) {
      getline(fin, line);
      line.erase(remove(line.begin(), line.end(), '\n'), line.end());
      line.erase(remove(line.begin(), line.end(), '\r'), line.end());
      line.erase(remove(line.begin(), line.end(), ' '), line.end());
      propertyName =
          line.substr(line.find(":") + 1, line.length() - line.find(":") + 1);

      getline(fin, line);
      line.erase(remove(line.begin(), line.end(), '\n'), line.end());
      line.erase(remove(line.begin(), line.end(), '\r'), line.end());
      line.erase(remove(line.begin(), line.end(), ' '), line.end());
      propertyOwner =
          line.substr(line.find(":") + 1, line.length() - line.find(":") + 1);

      getline(fin, line);
      line.erase(remove(line.begin(), line.end(), '\n'), line.end());
      line.erase(remove(line.begin(), line.end(), '\r'), line.end());
      line.erase(remove(line.begin(), line.end(), ' '), line.end());
      string price1 =
          (line.substr(line.find(":") + 1, line.length() - line.find(":") + 1));
      stringstream container(price1);
      ;
      container >> price;

      getline(fin, line);
      line.erase(remove(line.begin(), line.end(), '\n'), line.end());
      line.erase(remove(line.begin(), line.end(), '\r'), line.end());
      line.erase(remove(line.begin(), line.end(), ' '), line.end());
      string boolLine =
          line.substr(line.find(":") + 1, line.length() - line.find(":") + 1);
      if (boolLine == "True") {
        owned = true;
      }
      else{
        owned = false;
      }

      getline(fin, line);
      line.erase(remove(line.begin(), line.end(), '\n'), line.end());
      line.erase(remove(line.begin(), line.end(), '\r'), line.end());
      line.erase(remove(line.begin(), line.end(), ' '), line.end());
      string rent1 =
          (line.substr(line.find(":") + 1, line.length() - line.find(":") + 1));
      stringstream container1(rent1);
      container1 >> rent;

      getline(fin, line);
      line.erase(remove(line.begin(), line.end(), '\n'), line.end());
      line.erase(remove(line.begin(), line.end(), '\r'), line.end());
      line.erase(remove(line.begin(), line.end(), ' '), line.end());

      addAtTail(propertyName, propertyOwner, price, owned, rent);
    }

    fin.close();
  }
};

int rollDice() {
  srand(time(NULL));
  int num = (rand() % 6) + 1;
  return num;
}

bool GameOver(int loop) {
  if (loop == 1) {
    return true;
  } else {
    return false;
  }
}

bool checkIfGovernmentOwned(node* playerPosition){
  if(playerPosition->getOwner() == "Government"){
    return true;
  }
  return false;
}

int checkifOwned(node *playerposition, string playerName1, int &balance1, string playerName[], int balance[], int loop) {
  if(playerposition->getpropertyName() == "GO"){
    return 1;
  }
  else if(playerposition->getpropertyName() == "BOOZCRUISE"){
    cout << "Enjoy your free vacation on the Booze Cruise!" << endl;
    cout << endl; 
    return 1;
  }
  else if (playerposition->ifisOwned() == true) {
    if(checkIfGovernmentOwned(playerposition)){
      balance1 = balance1 - playerposition->getRent();
      cout << "You landed on a government owned property. You owe the government " << playerposition->getRent() << " dollars in taxes." << endl;
      cout << endl;
      if (balance1 <= 0) {
        cout << "You are now broke! Game over!" << endl;
        return 2;
      } else {
        cout << "Your new balance is " << balance1 << "." << endl;
        cout << endl;
        return 1;
      }
    }
    else if (playerName1 == playerposition->getOwner()) {
      cout << "You own " << playerposition->getpropertyName() << "." << endl;
      return 1;
    } 
    else {
      cout << playerposition->getOwner() << " owns "
           << playerposition->getpropertyName() << ", you owe "
           << playerposition->getOwner() << " " << playerposition->getRent()
           << " dollars." << endl;
      balance1 = balance1 - playerposition->getRent();
      int i=0;
      while(playerName[i] != playerposition->getOwner()){
        i++;
      }
      balance[i] = balance[i] + playerposition->getRent();
      cout << "The new balance of " << playerposition->getOwner() << " is " << balance[i] << " dollars." << endl;
      if (balance1 <= 0) {
        cout << "You are broke! Game over!" << endl;
        return 2;
      } else {
        cout << "Your new balance is " << balance1 << "." << endl;
        cout << endl;
        return 1;
      }
    }
  } 
  else {
    cout << playerposition->getpropertyName()
         << " is free to purchase." << endl; 
    cout << "The price to purchase this property is "
         << playerposition->getPrice() << " dollars." << endl;
      cout << "Your current balance is "
         << balance1
         << " dollars." << endl;
    cout << endl;
    cout << "Would you like to purchase this property? Reply yes or no."
         << endl;
    cout << endl;
    string reply;
    cin >> reply;
    bool check = true;
    while (check)
      if (reply == "yes") {
        if (playerposition->getPrice() > balance1) {
          cout << "You do not have enough money to buy "
               << playerposition->getpropertyName()
               << ". Better luck next time." << endl;
          cout << endl;
        } else {
          balance1 = balance1 - playerposition->getPrice();
          cout << "You have purchased " << playerposition->getpropertyName() << ". Your new balance is " << balance1 << " dollars." << endl;
          cout << endl;
          playerposition->setisOwned(playerName1);
        }
        check = false;
        return 1;
      } else if (reply == "no") {
        cout << "You have chosen to not purchase "
             << playerposition->getpropertyName() << ". Your balance is still "
             << balance1 << " dollars." << endl;
        cout << endl;
        check = false;
        return 1;
      } else {
        cout << "Invalid entry. Please reply with yes or no." << endl;
        cin >> reply;
      }
  }
}

int main() {
  linkedlist ll;
  ll.newGame();
  int players;
  cout << "Please enter amount of players" << endl;
  cin >> players;
  string playerName[players];
  for (int i = 0; i < players; i++) {
    cout << "Hello player " << i+1 << "! Please enter your username..." << endl;
    cin >> playerName[i];
    cout << "Welcome to C++ Monopoly " << playerName[i] << "!!!" << endl;
    cout << endl;
  }

  int balance[players];
  node *position[players];

  int loop = players;

  for (int i = 0; i < players; i++) {
    balance[i] = 2000;
    position[i] = ll.getHead();
  }
  bool check1 = true;
  bool stuff = false;

  while (!GameOver(loop)) {
    for (int i = 0; i < loop; i++) {
      while (check1) {
        cout << playerName[i] << ", please enter 1 to roll the dice." << endl;
        cout << endl;
        int num1;
        cin >> num1;
        if (num1 != 1) {
          cout << "Invalid Entry. Please enter 1 to roll the dice." << endl;
        } else {
          check1 = false;
          int num2 = rollDice();
            
          cout << playerName[i] << " rolled a " << num2
               << ". You have been moved " << num2 << " spots forward." << endl;
          cout << endl;
          position[i] = ll.move(num2, position[i], balance[i]);
          int num3 = checkifOwned(position[i], playerName[i], balance[i], playerName, balance, loop);
          if (num3 == 2) {
            if (balance[i] <= 0) {
              cout << "You have no more money! Game Over for you, "
                   << playerName[i] << "." << endl;
              cout << endl;
              int j;
              for (j = i; j < players - 1; j++) {
                balance[j] = balance[j + 1];
                position[j] = position[j + 1];
                playerName[j] = playerName[j + 1];
                loop--;
                stuff = true;
              }
            }
          }
        }
      }
    check1 = true;
    if(stuff){
      break;
    }
    }
  }

  cout << playerName[0] << " is the winner. Congratulations!" << endl;

  return 0;
}