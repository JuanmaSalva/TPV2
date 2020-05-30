#include <iostream>

#include "StarWars.h"
#include "Networking.h"

using namespace std;



void server(int port) {
	Networking net;
	net.server(port);
}

void client(char* host, int port, char* name) {
	try {
		StarWars g(host, port, name);
		g.start();
	}
	catch (std::string & e) { // catch errors thrown as strings
		cerr << e << endl;
	}
	catch (const std::exception & e) { // catch other exceptions
		cerr << e.what();
	}
	catch (...) {
		cerr << "Caught and exception of unknown type ..";
	}

}


int main(int argc, char** argv) {
	if (argc == 3 && strcmp(argv[1], "server") == 0) {
		server(atoi(argv[2])); // start in server mode
		
	}
	else if ((argc == 5 || argc == 4) && strcmp(argv[1], "client") == 0) {
		if (argc == 4) { //si no pone un nombre
			char name[] = "Anonymous";
			client(argv[2], atoi(argv[3]),name); // start in client mode
		}
		else if (strlen(argv[4]) > 10) throw;
		else  client(argv[2], atoi(argv[3]), argv[4]); // start in client mode
	}
	else {
		cout << "Usage: " << endl;
		cout << "  " << argv[0] << " client host port " << endl;
		cout << "  " << argv[0] << " server port " << endl;
		cout << endl;
		cout << "Example:" << endl;
		cout << "  " << argv[0] << " server 2000" << endl;
		cout << "  " << argv[0] << " client localhost 2000" << endl;
	}

	return 0;
}
