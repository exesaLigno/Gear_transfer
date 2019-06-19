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
	int fileTransferToGear(char initial_file_path[], char target_file_path[]); // Not implemented
	int fileTransferFromGear(char initial_file_path[], char target_file_path[]); // Not implemented
	~Gear();
};



Gear::Gear(char adress[])
{
    strcpy(deviceAdress, adress);
    strcat(deviceAdress, ":");
	strcat(deviceAdress, "26101");
}

Gear::~Gear()
{}

int Gear::createConnection()
{
	char command[34] = "adb connect ";
	strcat(command, deviceAdress);
	//execl("/usr/bin/fish/", "adb", "connect", deviceAdress, NULL);
	system(command);
	return 0;
}

int Gear::refuseConnection()
{
    char command[37] = "adb disconnect ";
	strcat(command, deviceAdress);
	system(command);
	return 0;
}

int Gear::fileTransferToGear(char initial[], char target[] = "")
{
    return 0;
}
