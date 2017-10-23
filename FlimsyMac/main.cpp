#include<windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <Winreg.h>
#include <ctime>

int main() {
	HKEY key = NULL;
	LPCTSTR subkey = "SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e972-e325-11ce-bfc1-08002be10318}\\0001";	//change this to whereever your internet adaptor is located
	if (!RegOpenKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, KEY_SET_VALUE, &key)) std::cout << "Opened Key!\n" << std::endl;
	else {
		std::cout << "Couldn't open key! Aborting.\n" << std::endl;
		system("pause");
		exit(0);
	}

	//generate random mac
	char mac[13];
	static const char alphanum[] =
		"0123456789"
		"ABCDEF";

	srand(time(0));
	for (int i = 0; i < 12; ++i) {
		mac[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
	}
	mac[12] = 0;

	//set mac
	if (!RegSetValueEx(key, "NetworkAddress", 0, REG_SZ, (LPBYTE)mac, strlen(mac) + 1)) std::cout << "Success! Your new MAC is " << mac << "!" << std::endl << "It will be set next time the adaptor is restarted." << std::endl;
	else std::cout << "Couldn't set key!" << std::endl;
	system("pause");
	return 0;
}