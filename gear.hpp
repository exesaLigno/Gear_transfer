#pragma once
#include <cstring>
#include <cstdlib>

/*	
 *
 *	implement createConnection with execl
 *
 *
 *
 */

class Gear
{
private:
	char deviceAdress[22] = "0.0.0.0:26101";
	
public:
	Gear(char adress[]);
	int createConnection();
	int refuseConnection();
	int fileTransferToGear(char initial_file_path[], const char target_file_path[]); // Not implemented
	int fileTransferFromGear(char initial_file_path[], const char target_file_path[]); // Not implemented
	~Gear();
};
