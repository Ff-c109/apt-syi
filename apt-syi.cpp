#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

string pkg_list = "";

bool data_sync() {
	auto retv = system("apt update");
	return retv == 0 ? true : false;
}

void** install(bool fix_missing) {
	void** retv = new void*[2];
	retv[0] = new bool*;
	*((bool*)(retv[0])) = new bool;
	auto set_retv = [=] (bool val, const char* msg) mutable {
		*( (bool*)(retv[0]) ) = val;
		retv[1] = new char[strlen(msg + 2)];
		strcpy( ((char*)(retv[1])), msg );
	};

	system("apt clean");
	string command_download = "apt install --download-only";
	command_download += pkg_list;
	auto d_retv = system(command_download.c_str());
	if(d_retv != 0) {
		if(fix_missing) {
			command_download = "apt install --download-only --fix-missing";
			command_download += pkg_list;
			d_retv = system(command_download.c_str());
			if(d_retv != 0) {
				set_retv(false, "Fail: Fetching Fail.");
				return retv;
			}
		}
		else{
			set_retv(false, "Fail: Fetching Fail.");
			return retv;
		}
	}
	auto i_retv = system("dpkg --install /var/cache/apt/archives/*.deb");
	if(i_retv != 0) {
		set_retv(false, "Fail: dpkg-install fail.");
		return retv;
	}
	system("apt clean");
	set_retv(true, "done.");
	return retv;
}

void** fixbroken(bool force, char** argv) {
	void** retv = new void*[2];
	retv[0] = new bool;
	auto setRetv = [=] (bool stat, const char* msg) mutable {
		*((bool*)(retv[0])) = stat;
		retv[1] = new char[strlen(msg) + 2];
		strcpy( ((char*)(retv[1])), msg );
	};

	system("apt clean");
	auto d_retv = system("apt --fix-broken --download-only install");
	if(d_retv != 0) {
		setRetv(false, "Failed: Fetching Faild");
		return retv;
	}
	string cmd_c = argv[0];
	cmd_c += " --continue";
	string cmd_cf = argv[0];
	cmd_cf += " --continue --force";
	auto f_retv = force ? system(cmd_cf.c_str()) : system(cmd_c.c_str());
	if(f_retv != 0) {
		setRetv(false, "Faild: fix error");
		return retv;
	}
	setRetv(true, "");
	return retv;
}

int main(int argc, char** argv) {
	if(argc == 1) {
		cout << "apt-syi [--fix-missing] [pkg0] [pkg1] [pkg2] ..." << "\r\n"
			<< "Install pkgs which is already downloaded: " << "\r\n"
			<< "      apt-syi --continue" << "\r\n"
			<< "Force Install downloaded pkgs: " << "\r\n"
			<< "      apt-syi --continue --force" << "\r\n"
			<< "Fix install: " << "\r\n"
			<< "      apt-syi --fix-broken [--force]" << "\r\n";
		return 0;
	}
	if(argv[0][0] != '/') {
		cout << "Error: Must use absolute path." << "\r\n";
		return -1;
	}
	if(argc >= 2 ? strcmp(argv[1], "--fix-broken") == 0 : false) {
		auto fix_retv = fixbroken(argc >= 3 ? strcmp(argv[2], "--force") == 0 : false, argv);
		cout << ((char*)(fix_retv[1])) << "\r\n";
		return *((bool*)(fix_retv[0])) ? 0 : -1;
	}
	if(argc >= 2 ? strcmp(argv[1], "--continue") == 0 : false || argc >= 3 ? strcmp(argv[2], "--continue") == 0 : false) {
		if(argc >= 3 ? strcmp(argv[2], "--force") == 0 : false || argc >= 3 ? strcmp(argv[1], "--force") == 0 : false) {
			cout << "This will forcibly install all packages which is in the cache (Nomally it is the unfinished part in the last installation)" << "\r\n"
			       	<< "Note: The -- force option is very dangerous, and it may cause a very serious impact on the system." << "\r\n"
				<< "We do not recommend you to use it. It is recommended to try \"apt install - f\"." << "\r\n"
				<< "Do you still want to continue? [ Yes (Y) / Exit (N) / Execute \"apt install -f\" (F) ] ";
			char ans = 'N';
			cin >> ans;
			while(getchar() != '\n') true;
			if(ans == 'Y') {
				cout << "\r\n\r\n";
				cout << "!!!!!!!!!" << "\r\n";
				cout << "[!!! DANGER !!!] We hope you understand the meaning of the operation which you are currently carrying out and have a full understanding of the consequences." << "\r\n";
				cout << "[!!! DANGER !!!] Enter the following text to confirm execution" << "\r\n";
				cout << "\r\n" << "Confirm Force Installation" << "\r\n";
				cout << "!!!!!!!!!" << "\r\n" << "\r\n";
				cout << ": ";
				char* confirm_text = new char[strlen("Confirm Force Installation") + 1];
				for(int i = 0; (confirm_text[i] = getchar()) != '\n'; i++) true;
				confirm_text[strlen("Confirm Force Installation")] = '\0';
				if(strcmp(confirm_text, "Confirm Force Installation") != 0) {
					cout << "\r\n" << "Installation Canceled. " << confirm_text << "\r\n";
					return 0;
				}
				cout << "\r\n" << "[!!! DANGER !!!] Execute Force Installation" << "\r\n\r\n";
				return system("dpkg --force-all --install /var/cache/apt/archives/*.deb");
			}
			else if(ans == 'N') {
				return 1;
			}
			else if(ans == 'F') {
				return system("apt install -f");
			}
			else {
				return -1;
			}
		}
		else {
			cout << "Install all the package which is in the cache." << "\r\n";
			cout << "Continue? [Y/n]";
			char confirm = getchar();
			if(confirm != '\n') while(getchar() != '\n') true;
			if(confirm == '\n' || confirm == 'Y' || confirm == 'y') {
				return system("dpkg --install /var/cache/apt/archives/*.deb");
			}
			else {
				cout << "Canceled." << "\r\n";
				return 1;
			}
		}
	}

	for(int i = (strcmp(argv[1], "--fix-missing") == 0 ? 2 : 1); i < argc; i++) { pkg_list += " "; pkg_list += argv[i]; }
	bool dsync_retv = data_sync();
	auto install_retv = install(strcmp(argv[1], "--fix-missing") == 0 ? true : false);
	if(*((bool*)(install_retv[0]))) {
		cout << "Installation completed successfully." << "\r\n";
	}
	else {
		cout << ((char*)(install_retv[1])) << "\r\n";
		return -1;
	}
}
