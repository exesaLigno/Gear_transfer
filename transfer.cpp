#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <assert.h>
#include "gear.hpp"


int parseArguments(int arg_count, const char*** arg_vector);
int printHelp();                            // N/C
int exportDevice(char name[], char ip[]);   // N/I
char* importDevice(char name[]);            // N/I
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
	//else if (settings::by_name) strcpy(ip, importDevice(settings::name));
	else
	{
	    printf("Arguments Error. Type \"transfer --help\" to see help\n");
	    return 0;
	}
	    
    
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
		if(!strcmp(arg, "--name") or !strcmp(arg, "-n"))
		{
			strcpy(settings::name, (*arg_vector)[++counter]);
			settings::by_name = 1;
	    }
		
		else if(!strcmp(arg, "--set-name") or !strcmp(arg, "-sn"))
		{
			strcpy(settings::name, (*arg_vector)[++counter]);
			settings::save = 1;
		}
		
		else if(!strcmp(arg, "--mac") or !strcmp(arg, "-m"))
		{
			strcpy(settings::mac, (*arg_vector)[++counter]);
			settings::by_mac = 1;
		}
		
		else if(!strcmp(arg, "--ip") or !strcmp(arg, "-i"))
		{
			strcpy(settings::ip, (*arg_vector)[++counter]);
			settings::by_ip = 1;
		}
		
		else if(!strcmp(arg, "--help") or !strcmp(arg, "-h"))
			printHelp();
		
		else
			printf("undefined parameter: %s\n", arg);
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
        return "n/f";
    
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

int printHelp()
{
	printf("Help page\n");
	return 0;
}


char* readFile(char file_name[])
{
    FILE* file = fopen(file_name, "r");
    long file_length = fileSize(file);

    char* text = (char*) calloc (sizeof (char), file_length + 1);
    fread (text, sizeof (char), file_length, file);
    
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

