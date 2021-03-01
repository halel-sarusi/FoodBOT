#include "funcc.h"
#include "dbConnection.h"

using namespace std;


int main()
{
	createConnection();
	Navigationfunc();
	closeConnection();

	system("PAUSE");
	return 0;
}


