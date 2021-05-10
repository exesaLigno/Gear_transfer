#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <map>
#include <cstring>
#include <assert.h>
#include "gear.hpp"


#define DEBUG_MODE

#ifdef DEBUG_MODE
	#define DEBUG if(1)
#else
	#define DEBUG if(0)
#endif


RET_CODE parseArguments(int arg_count, const char*** arg_vector);
int printHelp();                            // N/C
int exportDevice(const char name[], const char ip[]);   // N/I
char* importDevice(const char name[]);
char* findByMac(const char mac[]);
char* readFile(const char file_name[]);
long fileSize(FILE* file);


enum class RET_CODE : unsigned short int
{
	SUCCESS,
	INVALID_INPUT,
	COUNT_OF_ERRORS
};


enum class MODE : unsigned short int
{
	SEARCH,
	TRANSFER_TO_GEAR,
	TRANSFER_FROM_GEAR,
	COUNT_OF_MODES
};

namespace settings
{
	MODE mode = NULL;
	char* mac;
	char** initial_files;
	char* initial_path;
	char* target_path;
};




int main(int argc, const char* argv[])
{
	if(argc >= 2)
		parseArguments(argc, &argv);
	else
		printHelp();
	
	return 0;
}


#define arg (*arg_vector)[counter]
RET_CODE parseArguments(int arg_count, const char*** arg_vector)
{
	for(int counter = 1; counter < arg_count; counter++)
	{
		if (counter >= arg_count)
			return RET_CODE::INVALID_INPUT;

		if (!strcmp(arg, "--find") or !strcmp(arg, "-f"))
		{
			std::cout << "finding device" << std::endl;
			settings::mode = MODE::SEARCH;
			counter++;
			printf("%d\n", arg);
		}
			
		else if (!strcmp(arg, "--get") or !strcmp(arg, "-g"))
			std::cout << "getting files from gear" << std::endl;
			
		else if (!strcmp(arg, "--initial-path") or !strcmp(arg, "--i"))
			std::cout << "given initial path" << std::endl;
			
		else if (!strcmp(arg, "--target-path") or !strcmp(arg, "--t"))
			std::cout << "given target path" << std::endl;
		
		else if (!strcmp(arg, "--help") or !strcmp(arg, "-h") or !strcmp(arg, "--usage"))
			printHelp();
		
		else
			std::cout << "че дурак блять а " << arg << std::endl;
	}
	return RET_CODE::SUCCESS;
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


char* readFile(const char file_name[])
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

