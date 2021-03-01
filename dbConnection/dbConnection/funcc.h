#include <iostream>
#include <sstream>
#include <windows.h>
#include <mysql.h>
#include <stdlib.h>

using namespace std;

void Navigationfunc();
void createConnection();
void closeConnection();
MYSQL_RES* executeQuery(string query, MYSQL* con);
void selectQuery(MYSQL_RES* res);

void UserExist(MYSQL* con);
void recommendations(MYSQL* con);
void allDishes(MYSQL* con);
void newOrder(MYSQL* con);
void orderStatus(MYSQL* con);
void orderHistory(MYSQL* con);
void newUser(MYSQL* con);
void DeletingUser(MYSQL* con);


void allStores(MYSQL* con);
void addRestaurant(MYSQL* con);
void deleteRestaurant(MYSQL* con);
void addingDose(MYSQL* con);
void DeletingDose(MYSQL* con);
void CommonDish(MYSQL* con);
void CommonRestaurant(MYSQL* con);