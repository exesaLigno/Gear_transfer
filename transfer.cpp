#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <assert.h>
#include "gear.hpp"


int parseArguments(int arg_count, const char*** arg_vector);
int printHelp();
long file_size (FILE* file);


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
	
	if (settings::by_ip)
	    current_gear = Gear(settings
	
	current_gear.createConnection();
		
	
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


int printHelp()
{
	printf("Help page\n");
	settings::pass = 1;
	return 0;
}


long file_size (FILE* file)
{
    fseek (file, 0, SEEK_END);
    long file_size = ftell (file);
    rewind (file);

    return file_size;
}





//end;

