#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <assert.h>
#include "gear.hpp"


int parseArguments(int arg_count, const char*** arg_vector);
int printHelp();                            // N/C
int exportDevice(char name[], char ip[]);   // N/I
char* importDevice(char name[]);
char* findByMac(char mac[]);
char* readFile(char file_name[]);
long fileSize(FILE* file);


namespace settings
{
    char name[20] = "";
    char mac[17] = "";
    char ip[15] = "";
    bool by_name = 0;
    bool by_mac = 0;
    bool by_ip = 0;
    bool save = 0;
}




int main(int argc, const char* argv[])
{
	if(argc >= 2)
		parseArguments(argc, &argv);
	else
		printHelp();
		
    char ip[15] = "";
	
	if (settings::by_ip) strcpy(ip, settings::ip);
	else if (settings::by_mac) strcpy(ip, findByMac(settings::mac));
	else if (settings::by_name) strcpy(ip, importDevice(settings::name));
	else
	{
	    std::cout << "Arguments Error. Type \"transfer --help\" to see help" << std::endl;
	    return 0;
	}
	
	if(settings::save and not settings::by_name and strcmp(ip, ""))
	    exportDevice(settings::name, ip);
	    
    
    printf("ip: \"%s\"\n", ip);
	
	//current_gear.createConnection();
		
	
	//Gear s3("s3", "192.168.1.143", "26101", "00:00:00:00:00:00");
	
	return 0;
}


#define arg (*arg_vector)[counter]
int parseArguments(int arg_count, const char*** arg_vector)
{
	for(int counter = 1; counter < arg_count; counter++)
	{		
		if (!strcmp(arg, "--find") or !strcmp(arg, "-f"))
			std::cout << "finding device" << std::endl;
		
		else if (!strcmp(arg, "--help") or !strcmp(arg, "-h") or !strcmp(arg, "--usage"))
			printHelp();
		
		else
			std::cout << "undefined parameter: " << arg << std::endl;
	}
	return 0;
}
#undef arg


char* findByMac(char mac[])
{
    char command[33] = "./findmac.sh ";
    strcat(command, mac);
    system(command);

    char* result = readFile("finded.conf");
    int length = strlen(result);
    
    if(length == 0)
        return "";
    
    char* ip = (char*) calloc (sizeof(char), 15);
    int ind = 0;    
    bool writing = 0;
    
    for(int counter = 0; counter < length; counter++)
    {
        if (result[counter] == '(')
            writing = 1;
        else if (result[counter] == ')')
            writing = 0;
        else if (writing)
        {
            ip[ind] = result[counter];
            ind++;
        }
    }
    
    return ip;
}


char* importDevice(char required_name[])
{
    char* list = readFile("devices.conf");
    int length = strlen(list);
    bool name_flag = 1;
    bool ip_flag = 0;
    bool founded = 0;
    char current_name[20] = "";
    char current_ip[20] = "";
    int ind = 0;
    
    char* ip = (char*) calloc (sizeof(char), 15);
    
    for(int counter = 0; counter < length; counter++)
    {
        if(list[counter] == ' ')
        {
            name_flag = 0;
            ip_flag = 1;
            ind = 0;
        }
        else if(list[counter] == '\n')
        {
            if(!strcmp(current_name, required_name))
                strcpy(ip, current_ip);
            name_flag = 1;
            ip_flag = 0;
            for(ind = 0; ind < 20; ind++)
            {
                current_name[ind] = 0;
                current_ip[ind] = 0;
            }
            ind = 0;
        }
        else if(name_flag)
        {
            current_name[ind] = list[counter];
            ind++;
        }
        else if(ip_flag)
        {
            current_ip[ind] = list[counter];
            ind++;
        }
    }
    
    return ip;
}


int exportDevice(char name[], char ip[])
{
    FILE* database = fopen("devices.conf", "a+");
    fprintf(database, "%s %s\n", name, ip);
    fclose(database);
    return 0;
}


int printHelp()
{
	printf("Help page\n");
	return 0;
}


char* readFile(char file_name[])
{
    FILE* file = fopen(file_name, "r");
    char* text = "";
    if (file)
    {
        long file_length = fileSize(file);
        text = (char*) calloc (sizeof (char), file_length + 1);
        fread (text, sizeof (char), file_length, file);
        fclose(file);
    }
    return text;
}


long fileSize (FILE* file)
{
    fseek (file, 0, SEEK_END);
    long file_size = ftell (file);
    rewind (file);

    return file_size;
}





//end;

