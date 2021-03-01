#include "funcc.h"
#include "windows.h"

MYSQL* conn;
string userId_global = "";

void createConnection()
{
	conn = mysql_init(NULL);
	mysql_real_connect(conn, "localhost", "halel", "140196", "bot_db", 3306, NULL, 0);
}

void closeConnection() {
	mysql_close(conn);
}

//---------------------Function for the queries----------------------------//

MYSQL_RES* executeQuery(string query, MYSQL* con) {
	const char* s = query.c_str();
	mysql_query(con, s);
	MYSQL_RES* res = mysql_store_result(con);
	return res;
}

//------------------Displays the information from the DB------------------//

void selectQuery(MYSQL_RES* res) {
	int num_fields = mysql_num_fields(res);
	MYSQL_ROW row = mysql_fetch_row(res);
	if (row != NULL) {
		num_fields = mysql_num_fields(res);
		int i = 0;
		do {
			for (i = 0; i < num_fields; i++)
			{
				if(row[i] != NULL) {
					cout << row[i] << "\t";
				}
				else {
					continue;
				}
			}
			cout << endl;
		} while ((row = mysql_fetch_row(res)));
		mysql_free_result(res);
	}
}

//--------------Navigation function - incorrect input-----------------------//

void SelectionFromTheList()
{
	cout << "Choose number from the list and click Enter!";
}

//------------------------------Customer-functions--------------------------------//

void UserExist(MYSQL* con)
{
	stringstream buf;
	string first_name = "";
	string last_name = "";
	string pass = "";

	cout << "Please enter your first name:\t";
	cin >> first_name;
	cout << "Please enter your last name:\t";
	cin >> last_name;
	cout << "Please enter your password:\t";
	cin >> pass;

	buf << "SELECT u.first_name, u.last_name, u.password FROM bot_db.users u where u.first_name = '" + first_name + "' and u.last_name = '" + last_name + "' and u.password = '" + pass + "'";
	string str = buf.str();

	const char* s = str.c_str();
	mysql_query(con, s);
	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row = mysql_fetch_row(res);
	if (row != NULL) {
		cout << "User logged in";
		Sleep(2000);
		string q1 = "SELECT id_user FROM bot_db.users u where first_name = '" + first_name + "' and u.last_name = '" + last_name + "' and u.password = '" + pass + "'";
		MYSQL_RES* re = executeQuery(q1, con);
		if (re != NULL) {
			MYSQL_ROW row = mysql_fetch_row(re);
			if (row != NULL) {
				userId_global = row[0];
			}
			else {
				return;
			}
		}
		else {
			return;
		}
	}
	else {
		cout << "No user found!!\n";
		Sleep(1500);
		UserExist(con);
	}
}
void recommendations(MYSQL* con) {

	string query = "SELECT cosher, allergies, vegetarian from users where id_user =" + userId_global + ";";
	MYSQL_RES* res = executeQuery(query, con);
	if (res != NULL) {
		MYSQL_ROW row = mysql_fetch_row(res);
		if (row != NULL) {
			int cosher = atoi(row[0]);
			int vegetarian = atoi(row[2]);
			if (strcmp(row[1],"0")==0)
			{
				if (strcmp(row[0], "1") == 0 && strcmp(row[2], "1") == 0)
				{
					string query = "SELECT Restaurant, food from restaurant r inner join dish_restaurant dr on r.ID = dr.restaurant_id inner join dish d on d.id = dr.dish_id where cosher = '1' and vegetarian = '1';";
					MYSQL_RES* res = executeQuery(query, con);
					if (res != NULL) {
						selectQuery(res);
					}
					else {
						cout << "No dishes available\n\n";
					}
				}
				else if (strcmp(row[0], "1") == 0 && strcmp(row[2], "0") == 0)
				{
					string query = "SELECT Restaurant, food from restaurant r inner join dish_restaurant dr on r.ID = dr.restaurant_id inner join dish d on d.id = dr.dish_id where cosher = '1';";
					MYSQL_RES* res = executeQuery(query, con);
					if (res != NULL) {
						selectQuery(res);
					}
					else {
						cout << "No dishes available\n\n";
					}
				}
				else if (strcmp(row[0], "0") == 0 && strcmp(row[2], "1") == 0)
				{
					string query = "SELECT Restaurant, food from restaurant r inner join dish_restaurant dr on r.ID = dr.restaurant_id inner join dish d on d.id = dr.dish_id where vegetarian = '1';";
					MYSQL_RES* res = executeQuery(query, con);
					if (res != NULL) {
						selectQuery(res);
					}
					else {
						cout << "No dishes available\n\n";
					}
				}
			}
			else
			{
				string query = "select * from allergies where id_user =" + userId_global + ";";
				MYSQL_RES * res = executeQuery(query, con);
				if (res != NULL) {
					MYSQL_ROW row = mysql_fetch_row(res);
					if (row != NULL) {
						int lactose = atoi(row[1]);
						int g6pd = atoi(row[2]);
						int	nuts = atoi(row[3]);
						int	gluten = atoi(row[4]);
						string strWhere = "WHERE 1=1 ";
						if (g6pd == 1) { strWhere += " AND g6pd=0 "; }
						if (lactose == 1) { strWhere += " AND lactose=0 "; }
						if (nuts == 1) { strWhere += " AND nuts=0 "; }
						if (gluten == 1) { strWhere += " AND gluten=0 "; }
						if (cosher == 1) { strWhere += " AND cosher=1 "; }
						if (vegetarian == 1) { strWhere += " AND vegetarian=1 "; }
						query = "SELECT Restaurant, food from restaurant r inner join dish_restaurant dr on r.ID = dr.restaurant_id inner join dish d on d.id = dr.dish_id " + strWhere;
						MYSQL_RES* res2 = executeQuery(query, con);
						if (res2 != NULL) {
							selectQuery(res2);
						}
						else {
							cout << "No dishes available\n\n";
						}
					}
				}
			}
		}
		else {
			return;
		}
	}
	else {
		cout << "No dishes available\n\n";
	}

}
void allDishes(MYSQL* con) {
	string query = "SELECT dish_id, Restaurant, food from restaurant r inner join dish_restaurant dr on r.ID = dr.restaurant_id inner join dish d on d.id = dr.dish_id order by dish_id;";
	MYSQL_RES* res = executeQuery(query, con);
	if (res != NULL) {
		selectQuery(res);
	}
	else {
		cout << "No dishes available\n\n";
	}
}
void newOrder(MYSQL* con) {
	cin.ignore();
	string Confirmation, nameDish, nameRestaurant, credit, adress, phone;
	cout << "Write down the name of the dish you would like to order: ";
	getline(cin, nameDish);
	cout << "Write down the name of the restaurant from which you would like to order the dish: ";
	getline(cin, nameRestaurant);

	string query = "SELECT Restaurant , food from restaurant r inner join dish_restaurant dr on r.ID = dr.restaurant_id inner join dish d on d.id = dr.dish_id where Restaurant = '" + nameRestaurant + "' and food ='" + nameDish + "';";
	MYSQL_RES* res = executeQuery(query, con);
	if (res != NULL) {
		MYSQL_ROW row = mysql_fetch_row(res);
		if (row != NULL) {
			cout << "The dish exists\n\n";
			query = "select credit from users where id_user = '" + userId_global + "'";
			MYSQL_RES* res1 = executeQuery(query, con);
			if (res1 != NULL) {
				MYSQL_ROW row = mysql_fetch_row(res1);
				if (row[0] != NULL && strlen(row[0]) > 0) {
					cout << "The card number that appears in the system is: " << row[0] << "\n";
					cout << "To confirm press 1, press any key to change: ";
					cin >> Confirmation;
					if (Confirmation != "1")
					{
						goto update1;
					}
				}
				else
				{
				update1:
					cin.ignore();
					cout << "Please enter credit number: ";
					getline(cin, credit);
					query = "update users set credit = '" + credit + "'where id_user ='" + userId_global + "'";
					executeQuery(query, con);
				}
			}
			else
			{
				return;
			}

			query = "select adress from users where id_user ='" + userId_global + "'";
			MYSQL_RES* res2 = executeQuery(query, con);
			if (res2 != NULL) {
				MYSQL_ROW row = mysql_fetch_row(res2);
				if (row[0] != NULL && strlen(row[0]) > 0) {
					cout << "The address that appears in the system is: " << row[0] << "\n";
					cout << "To confirm press 1, press any key to change: ";
					cin >> Confirmation;
					if (Confirmation != "1")
					{
						goto update2;
					}
				}
				else
				{
				update2:
					cin.ignore();
					cout << "Enter your new address: ";
					getline(cin, adress);
					query = "update users set adress = '" + adress + "'where id_user ='" + userId_global + "'";
					executeQuery(query, con);
				}
			}
			else
			{
				return;
			}

			query = "select phone from users where id_user ='" + userId_global + "'";
			MYSQL_RES* res3 = executeQuery(query, con);
			if (res3 != NULL) {
				MYSQL_ROW row = mysql_fetch_row(res3);
				if (row[0] != NULL && strlen(row[0]) > 0) {
					cout << "The phone number that appears in the system is: " << row[0] << "\n";
					cout << "To confirm press 1, press any key to change: ";
					cin >> Confirmation;
					if (Confirmation != "1")
					{
						goto update3;
					}
				}
				else
				{
				update3:
					cin.ignore();
					cout << "Enter your phone number: ";
					getline(cin, phone);
					query = "update users set phone = '" + phone + "'where id_user ='" + userId_global + "'";
					executeQuery(query, con);
				}
			}
			else
			{
				return;
			}
			
		}
		else {
			cout << "No dishes available!!\n";
			newOrder(con);
		}
	}
	else
	{
		return;
	}

	string dishID, rerestaurantID, dish_restaurantID;
	int orderID;

	query = "SELECT max(ID_order) FROM bot_db.orders;";
	MYSQL_RES* res4 = executeQuery(query, con);
	query = "SELECT dish_id from restaurant r inner join dish_restaurant dr on r.ID = dr.restaurant_id inner join dish d on d.id = dr.dish_id where Restaurant = '" + nameRestaurant + "' and food ='" + nameDish + "';";
	MYSQL_RES* res5 = executeQuery(query, con);
	query = "SELECT restaurant_id from restaurant r inner join dish_restaurant dr on r.ID = dr.restaurant_id inner join dish d on d.id = dr.dish_id where Restaurant = '" + nameRestaurant + "' and food = '" + nameDish + "';";
	MYSQL_RES* res6 = executeQuery(query, con);
	if (res4 != NULL && res5 != NULL && res6 != NULL) {
		MYSQL_ROW row4 = mysql_fetch_row(res4);
		MYSQL_ROW row5 = mysql_fetch_row(res5);
		MYSQL_ROW row6 = mysql_fetch_row(res6);
		if (row4 != NULL && row5 != NULL && row6 != NULL) {
			orderID = stoi(row4[0]) + 1;
			dishID = row5[0];
			rerestaurantID = row6[0];
			query = "SELECT id FROM bot_db.dish_restaurant where dish_id = '" + dishID + "' and restaurant_id = '" + rerestaurantID + "'";
			MYSQL_RES* res7 = executeQuery(query, con);
			if (res7 != NULL)
			{
				MYSQL_ROW row7 = mysql_fetch_row(res7);
				if (row7 != NULL)
				{
					dish_restaurantID = row7[0];
				}
			}
		}
		else {
			return;
		}
	}
	else {
		return;
	}

	string q = "INSERT INTO bot_db.orders (`ID_order`, `id_user`, `dish_restaurant_id`, `date`, `status`) VALUES ('" + to_string(orderID) + "', '" + userId_global + "', '" + dish_restaurantID + "', current_timestamp(), 'Ordered');";
	executeQuery(q, con);
	cout << "The order was successfully placed!";
	Sleep(2000);
}
void orderStatus(MYSQL* con)
{
	cin.ignore();
	string nameDish, nameRestaurant;
	cout << "Enter dish name: ";
	getline(cin, nameDish);
	cout << "Enter the name of the restaurant from which you ordered: ";
	getline(cin, nameRestaurant);

	string query1 = "SELECT Restaurant , food from restaurant r inner join dish_restaurant dr on r.ID = dr.restaurant_id inner join dish d on d.id = dr.dish_id where Restaurant = '" + nameRestaurant + "' and food ='" + nameDish + "';";
	MYSQL_RES* res1 = executeQuery(query1, con);
	if (res1 != NULL) {
		MYSQL_ROW row1 = mysql_fetch_row(res1);
		if (row1 != NULL) {
			cout << "The dish exists\n\n";
			string query = "SELECT status from orders o inner join dish_restaurant dr on o.dish_restaurant_id = dr.id inner join dish d on dr.dish_id = d.id inner join restaurant r on dr.restaurant_id = r.ID where id_user =" + userId_global + " and food = '" + nameDish + "' and Restaurant = '" + nameRestaurant + "';";
			MYSQL_RES* res = executeQuery(query, con);
			if (res != NULL) {
				MYSQL_ROW row = mysql_fetch_row(res);
				if (row != NULL) {
					cout << row[0];
				}
				else
				{
					cout << "There is no such order\n\n";
				}
			}
			else {
				cout << "There is no such order\n";
			}
		}
		else {
			cout << "Restaurant name or dish name doesn't exists!!\n";
			orderStatus(con);
		}
	}
	else {
		cout << "Restaurant name or dish name doesn't exists!!\n";
	}
}

void orderHistory(MYSQL* con) 
{ 
	string query = "SELECT date, Restaurant, food from orders o inner join dish_restaurant dr on o.dish_restaurant_id = dr.id inner join dish d on dr.dish_id = d.id inner join restaurant r on dr.restaurant_id = r.ID where id_user =" + userId_global + ";";
	MYSQL_RES* res = executeQuery(query, con);
	if (res != NULL) {
		selectQuery(res);
	}
	else {
		cout << "You have no previous orders\n\n";
	}
}
void newUser(MYSQL* con)
{
	cin.ignore();
	string first_name, last_name, pass, cosher, allergies, vegetarian, lactose, G6PD, nuts, gluten;
	cout << "First name:\t";
	getline(cin, first_name);
	cout << "\nLast Name:\t";
	getline(cin, last_name);
	cout << "\npassword:\t";
	getline(cin, pass);

	system("CLS");
	cout << "Answer the following questions: '1' = yes, '0' = no";
	cout << "\nDo you eat cosher?\t";
	getline(cin, cosher);
	cout << "\nDo you have allergies?\t";
	getline(cin, allergies);
	cout << "\nAre you vegetarian?\t";
	getline(cin, vegetarian);
	int idUser = stoi(mysql_fetch_row(executeQuery("SELECT max(id_user) FROM bot_db.users;", con))[0]) + 1;
	userId_global = to_string(idUser);
	string q2 = "INSERT INTO bot_db.users (`id_user`, `first_name`, `last_name`, `password`, `adress`, `phone`, `credit`, `cosher` , `allergies`, `vegetarian`) VALUES ('"+ to_string(idUser)+"' , '"+first_name+"' , '"+last_name+"', '"+pass+"', NULL, NULL, NULL, '" + cosher + "', '" + allergies + "', '" + vegetarian + "')";
	executeQuery(q2, con);
	cout << "Customer created in database";
	Sleep(2000);

	if (allergies == "1"){
		system("CLS");
		cout << "Answer the following questions: '1' = yes, '0' = no";
		cout << "\nDo you have lactose intolerance?\t";
		getline(cin, lactose);
		cout << "\nDo you have G6PD?\t";
		getline(cin, G6PD);
		cout << "\nDo you have sensitivity to nuts?\t";
		getline(cin, nuts);
		cout << "\nDo you have gluten sensitivity?\t";
		getline(cin, gluten);		

		string q2 = "Insert into allergies VALUES('" + to_string(idUser) + "', '" + lactose + "' , '" + G6PD + "', '" + nuts + "', '" + gluten + "');";
		executeQuery(q2, con);
		cout << "Customer created in database";
		Sleep(2000);
	}
}
void DeletingUser(MYSQL* con)
{
	string query = "Delete from orders where id_user = '" + userId_global + "';";
	executeQuery(query, con);
	string query2 = "Delete from allergies where id_user = '" + userId_global + "';";
	executeQuery(query2, con);
	string query1 = "Delete from users where id_user = '" + userId_global + "';";
	executeQuery(query1, con);
	cout << "The user and all his orders have been deleted from the system!";
	Sleep(2000);

}

//------------------------------Restaurant-functions--------------------------------//

void allStores(MYSQL* con) 
{ 
	string query = "SELECT Restaurant FROM bot_db.restaurant;";
	MYSQL_RES* res = executeQuery(query, con);
	if (res != NULL) {
		selectQuery(res);
	}
	else {
		cout << "There are no restaurants in the system\n\n";
	}
}
void addingDose(MYSQL* con) 
{ 
	cin.ignore();
	string Restaurant_name, Restaurant_id, dish_name, vegetarian, lactose, G6PD, nuts, gluten;
	cout << "Name of the restaurant that you want to add a dish:\t";
	getline(cin, Restaurant_name);

	string query = "SELECT * from restaurant where Restaurant ='" + Restaurant_name + "';";
	MYSQL_RES* res = executeQuery(query, con);
	if (res != NULL) {
		MYSQL_ROW row = mysql_fetch_row(res);
		if (row != NULL) {
			cout << "The restaurant exists!";
			cin.ignore();
			cout << "Enter the dish name:\t";
			getline(cin, dish_name);
			cout << "For all the following questions about the dish, please enter '1' = yes, '0' = no : \n";
			cout << "\nIs the dish vegetarian?\t";
			getline(cin, vegetarian);
			cout << "\nDoes it contain lactose?\t";
			getline(cin, lactose);
			cout << "\nDoes in the dish have a sensitivity to G6PD?\t";
			getline(cin, G6PD);
			cout << "\nDoes it contain nuts?\t";
			getline(cin, nuts);
			cout << "\nDoes it contain gluten?\t";
			getline(cin, gluten);
			int dish_id = stoi(mysql_fetch_row(executeQuery("SELECT max(id) FROM bot_db.dish;", con))[0]) + 1;
			int dish_Restaurant_id = stoi(mysql_fetch_row(executeQuery("SELECT max(id) FROM bot_db.dish_restaurant;", con))[0]) + 1;
			string q = "Insert into dish VALUES('" + to_string(dish_id) + "', '" + dish_name + "' , '" + vegetarian + "', '" + lactose + "', '" + G6PD + "', '" + nuts + "', '" + gluten + "');";
			executeQuery(q, con);
			string query = "SELECT ID from restaurant where Restaurant ='" + Restaurant_name + "';";
			MYSQL_RES* res2 = executeQuery(query, con);
			if (res2 != NULL) {
				MYSQL_ROW row2 = mysql_fetch_row(res2);
				if (row2 != NULL)
				{
					Restaurant_id = row2[0];
					string q2 = "Insert into dish_restaurant VALUES('" + to_string(dish_Restaurant_id) + "', '" + to_string(dish_id) + "' , '" + Restaurant_id + "');";
					executeQuery(q2, con);
					cout << "\nThe dish was added to the requested restaurant!";
					Sleep(2000);
				}
			}
			else {
				cout << "There is a problem with the restaurant's data\n";
			}
		}
		else
		{
			cout << "No such restaurant was found\n\n";
			addingDose(con);
		}
	}
	else {
		cout << "No such restaurant was found\n";
		addingDose(con);
	}

}
void DeletingDose(MYSQL* con) 
{ 
	cin.ignore();
	string nameDish, nameRestaurant, dishID, RestaurantID;
	cout << "Write down the dish you want to delete: ";
	getline(cin, nameDish);
	cout << "Write down the name of the restaurant to which the dish belongs: ";
	getline(cin, nameRestaurant);

	string query = "SELECT id FROM dish where food ='" + nameDish + "';";
	MYSQL_RES* res = executeQuery(query, con);
	if (res != NULL) {
		MYSQL_ROW row = mysql_fetch_row(res);
		if (row != NULL) {
			dishID = row[0];
			string query = "SELECT ID from restaurant where Restaurant ='" + nameRestaurant + "';";
			MYSQL_RES* res2 = executeQuery(query, con);
			if (res2 != NULL) {
				MYSQL_ROW row2 = mysql_fetch_row(res2);
				if (row2 != NULL)
				{
					RestaurantID = row2[0];
					string q = "Delete from dish_restaurant where  dish_id = '" + dishID + "' and restaurant_id='" + RestaurantID +"';";
					executeQuery(q, con);
					string q1 = "Delete from dish where id = '" + dishID + "';";
					executeQuery(q1, con);
					cout << "\nThe dish has been deleted from the system!";
					Sleep(2000);
				}
			}
			else {
				cout << "The requested restaurant was not found";
			}
		}
		else
		{
			cout << "The requested dish was not found";
		}
	}
	else {
		cout << "The requested dish was not found";
	}
}
void CommonDish(MYSQL* con) 
{ 
	cin.ignore();
	string Restaurant_name, Restaurant_id;
	cout << "Write down the name of the restaurant where you would like to check out the most popular dish:\t";
	getline(cin, Restaurant_name);
	string query = "SELECT ID from restaurant where Restaurant ='" + Restaurant_name + "';";
	MYSQL_RES* res = executeQuery(query, con);
	if (res != NULL) {
		MYSQL_ROW row = mysql_fetch_row(res);
		if (row != NULL) {
			Restaurant_id = row[0];
			string query1 = "SELECT count(*) as cnt, food from orders o inner join dish_restaurant dr on o.dish_restaurant_id = dr.id inner join dish d on dr.dish_id = d.id inner join restaurant r on dr.restaurant_id = r.ID where restaurant_id ='" + Restaurant_id + "' group by dish_id order by count(*) Desc;";
			MYSQL_RES* res1 = executeQuery(query1, con);
			if (res1 != NULL && res1->row_count > 0) {
				cout << "The most popular dishes from the restaurant: (from large to small)\n";
				selectQuery(res1);
			}
			else {
				cout << "There are no reservations from this restaurant";
			}
		}
		else {
			cout << "Restaurant does not exist";
		}
	}
	else {
		cout << "Restaurant does not exist";
	}
}
void CommonRestaurant(MYSQL* con)
{
	string query = "SELECT  count(*), Restaurant as cnt from orders o inner join dish_restaurant dr on o.dish_restaurant_id = dr.id inner join restaurant r on dr.restaurant_id = r.ID group by restaurant_id order by count(*) Desc;";
	MYSQL_RES* res = executeQuery(query, con);
	if (res != NULL && res->row_count > 0) {
		cout << "The most popular restaurants in terms of reservations are: (arranged by number of orders)\n";
		selectQuery(res);
	}
	else {
		cout << "There are no orders in the system\n\n";
	}
}
void deleteRestaurant(MYSQL* con) 
{ 
	cin.ignore();
	int count;
	string Restaurant_name, RestaurantID, dishID;
	cout << "Write down the name of the restaurant you want to delete:\t";
	getline(cin, Restaurant_name);
	string query = "SELECT * from restaurant where Restaurant ='" + Restaurant_name + "';";
	MYSQL_RES* res = executeQuery(query, con);
	if (res != NULL) {
		MYSQL_ROW row = mysql_fetch_row(res);
		if (row != NULL) {
			RestaurantID = row[0];
			string query = "SELECT dish_id FROM dish_restaurant where restaurant_id = '" + RestaurantID + "';";
			MYSQL_RES* res1 = executeQuery(query, con);
			if (res1 != NULL)
			{
				MYSQL_ROW row1 = mysql_fetch_row(res1);
				if (row1 != NULL) {
					count = res1->row_count;
					while (count)
					{
						string query = "SELECT dish_id FROM dish_restaurant where restaurant_id = '" + RestaurantID + "';";
						MYSQL_RES* res2 = executeQuery(query, con);
						MYSQL_ROW row2 = mysql_fetch_row(res2);
						dishID = row2[0];
						string q1 = "Delete from dish_restaurant where  dish_id = '" + dishID + "' and restaurant_id='" + RestaurantID + "';";
						executeQuery(q1, con);
						string q = "Delete from dish where id = '" + dishID + "';";
						executeQuery(q, con);

						count--;
					}
				}
				string q = "Delete from restaurant where ID = '" + RestaurantID + "';";
				executeQuery(q, con);
				cout << "The restaurant and all its dishes have been deleted!";
			}
			else {
				cout << "\nRestaurant does not exist";
			}

		}
		else {
			cout << "\nRestaurant does not exist";
		}
	}
	else {
		cout << "\nRestaurant does not exist";
	}

}
void addRestaurant(MYSQL* con) 
{ 
	cin.ignore();
	string Restaurant_name, cosher;
	cout << "Write down the name of the restaurant:\t";
	getline(cin, Restaurant_name);
	cout << "Is the restaurant cosher? ('1' = yes, '0' = no):\t";
	getline(cin, cosher);
	int Restaurant_id = stoi(mysql_fetch_row(executeQuery("SELECT max(ID) FROM bot_db.restaurant;", con))[0]) + 1;

	string q2 = "Insert into restaurant VALUES('" + to_string(Restaurant_id) + "', '" + Restaurant_name + "' , '" + cosher + "');";
	executeQuery(q2, con);
	cout << "\nThe restaurant was successfully added";
	Sleep(2000);
}

//------------------------Navigation - Main screen----------------------------//
void Navigationfunc()
{
	system("CLS");
	cout << "---------------User selection---------------\n";
	string choi = "1";
	while (choi != "q" && choi != "Q") {
		string choice = " ";

		cout << "1.Business owners\n";
		cout << "2.Customers\n";

		cin >> choice;
		system("CLS");

		if (choice == "1") {
			string pass = "";
		pass_again:
			cout << "Please enter a password:\t";
			cin >> pass;

			if (pass == "123456")
			{
				system("CLS");
				while (true) {
					string sub_choice = "";

					cout << " Enter 1 to view all existing restaurants.\n";
					cout << " Enter 2 to add / delete a dish from a restaurant.\n";
					cout << " Enter 3 to view the most popular dish of an existing restaurant.\n";
					cout << " Enter 4 to to view the most popular restaurant.\n";
					cout << " Enter 5 to delete a restaurant.\n";
					cout << " Enter 6 to add a restaurant.\n";

					cout << "Enter 10 to exit.\n";
					cin >> sub_choice;
					system("CLS");

					if (sub_choice == "1"){
						allStores(conn);
					}
					else if (sub_choice == "2")
					{
						while (true)
						{
							string functions = "";
							cout << "Enter 1 to add a dish.\n";
							cout << "Enter 2 to delete a dish.\n";
							cout << "Enter 10 to exit.\n";
							cin >> functions;
							system("CLS");
							if (functions == "1") { addingDose(conn); }
							else if (functions == "2") { DeletingDose(conn); }
							else if (functions == "10") { break; }
							else { SelectionFromTheList(); }
							cin.ignore();
							cin.ignore();
							system("CLS");
						}
					}
					else if (sub_choice == "3") {
						CommonDish(conn);
					}
					else if (sub_choice == "4") {
						CommonRestaurant(conn);
					}
					else if (sub_choice == "5") {
						deleteRestaurant(conn);
					}
					else if (sub_choice == "6") {
						addRestaurant(conn);
					}

					else if (sub_choice == "10") { break; }
					else { SelectionFromTheList(); }
					cin.ignore();
					cin.ignore();

					system("CLS");
				}
			}
			else
			{
				cout << "Incorrect password!\n";

				goto pass_again;
			}
		}
		else if (choice == "2") {
			while (true) {
				main:
				string sub_choice = "";
				cout << "1.User exist\n";
				cout << "2.New user\n";
				cout << "Enter 10 to exit.\n";

				cin >> sub_choice;
				system("CLS");
				if (sub_choice == "1")
				{
					UserExist(conn);
					while (true)
					{
						system("CLS");
						string functions = "";
						cout << "Enter 1 to view all the dishes offered from the system\n";
						cout << "Enter 2 to view all dishes\n";
						cout << "Enter 3 for a new order\n";
						cout << "Enter 4 to view order status\n";
						cout << "Enter 5 to view order history\n";
						cout << "Enter 6 to delete a user\n";

						cout << "Enter 10 to exit.\n";
						cin >> functions;
						system("CLS");
						if (functions == "1") { recommendations(conn); }
						else if (functions == "2") { allDishes(conn); }
						else if (functions == "3") { newOrder(conn); }
						else if (functions == "4") { orderStatus(conn); }
						else if (functions == "5") { orderHistory(conn); }
						else if (functions == "6") 
						{ 
							DeletingUser(conn);
							system("CLS");
							goto main; 		
						}
						else if (functions == "10") { break; }
						else { SelectionFromTheList(); }
						cin.ignore();
						cin.ignore();
						system("CLS");
					}
				}
				else if (sub_choice == "2")
				{
					newUser(conn);
					while (true)
					{
						system("CLS");
						string functions = "";
						cout << "Enter 1 to view all the dishes offered from the system\n";
						cout << "Enter 2 to view all dishes\n";
						cout << "Enter 3 for a new order\n";
						
						cout << "Enter 10 to exit.\n";
						cin >> functions;
						system("CLS");
						if (functions == "1") { recommendations(conn); }
						else if (functions == "2") { allDishes(conn); }
						else if (functions == "3") { newOrder(conn); }
						
						else if (functions == "10") { break; }
						else { SelectionFromTheList(); }
						cin.ignore();
						cin.ignore();
						system("CLS");
					}
				}
				
				else if (sub_choice == "10") { break; }
				else { SelectionFromTheList(); }
				cin.ignore();
				cin.ignore();
				system("CLS");
			}

		}
		else {
			choice = "Q";
		}
		system("CLS");

	}
}