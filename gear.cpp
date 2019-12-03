#include "gear.hpp"

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

int Gear::fileTransferToGear(char initial[], const char target[] = "")
{
    return 0;
}
