// V8Unpack.cpp : Defines the entry point for the console application.
//

#include "V8File.h"
#include "version.h"
#include <iostream>

using namespace std;

void usage()
{
	cout << endl;
	cout << "V8Upack Version " << V8P_VERSION
         << " Copyright (c) " << V8P_RIGHT << endl;

	cout << endl;
	cout << "Unpack, pack, deflate and inflate 1C v8 file (*.cf)" << endl;
	cout << endl;
	cout << "V8UNPACK" << endl;
	cout << "  -U[NPACK]     in_filename.cf     out_dirname      [entry-name]" << endl;
	cout << "  -PA[CK]       in_dirname         out_filename.cf" << endl;
	cout << "  -I[NFLATE]    in_filename.data   out_filename" << endl;
	cout << "  -D[EFLATE]    in_filename        filename.data" << endl;
	cout << "  -E[XAMPLE]" << endl;
	cout << "  -BAT" << endl;
	cout << "  -P[ARSE]      in_filename        out_dirname" << endl;
	cout << "  -B[UILD]      in_dirname         out_filename" << endl;
	cout << "  -L[IST]       in_filename.cf     [list-in-file]" << endl;
	cout << "  -V[ERSION]" << endl;
}

void version()
{
	cout << V8P_VERSION << endl;
}

int main(int argc, char* argv[])
{

	string cur_mode;
	if (argc > 1)
		cur_mode = argv[1];

	string::iterator p = cur_mode.begin();

	for(;p != cur_mode.end(); ++p)
		*p = tolower(*p);

	int ret = 0;

	if (cur_mode == "-version" || cur_mode == "-v") {

		version();
		return 0;
	}


	if (cur_mode == "-inflate" || cur_mode == "-i" || cur_mode == "-und" || cur_mode == "-undeflate") {

		CV8File V8File;
		V8File.Inflate(std::string(argv[2]), std::string(argv[3]));
		return ret;
	}

	if (cur_mode == "-deflate" || cur_mode == "-d") {

		CV8File V8File;
		ret = V8File.Deflate(std::string(argv[2]), std::string(argv[3]));
		return ret;
	}


	if (cur_mode == "-unpack" || cur_mode == "-u" || cur_mode == "-unp") {

		CV8File V8File;
		string file_to_search;
		if (argc > 4) {
			file_to_search = argv[4];
		}
		ret = V8File.UnpackToFolder(std::string(argv[2]), std::string(argv[3]), file_to_search, true);
		return ret;
	}


	if (cur_mode == "-pack" || cur_mode == "-pa") {

		CV8File V8File;
		ret = V8File.PackFromFolder(argv[2], argv[3]);
		return ret;
	}

	if (cur_mode == "-parse" || cur_mode == "-p") {

		CV8File V8File;
		ret = V8File.Parse(argv[2], argv[3]);
		return ret;
	}

	if (cur_mode == "-list" || cur_mode == "-l") {
		if (argc > 2) {
			CV8File V8File;
			std::string root;
			if (argc == 4)
				root = argv[3];

			ret = V8File.ListFiles(argv[2], root);
			return ret;
		}
	}

	if (cur_mode == "-build" || cur_mode == "-b") {

		CV8File V8File;

		ret = V8File.BuildCfFile(argv[2], argv[3]);
		if (ret == SHOW_USAGE)
			usage();

		return ret;
	}


	if (cur_mode == "-bat") {

		cout << "if %1 == P GOTO PACK" << endl;
		cout << "if %1 == p GOTO PACK" << endl;
		cout << "" << endl;
		cout << "" << endl;
		cout << ":UNPACK" << endl;
		cout << "V8Unpack.exe -unpack      %2                              %2.unp" << endl;
		cout << "V8Unpack.exe -undeflate   %2.unp\\metadata.data            %2.unp\\metadata.data.und" << endl;
		cout << "V8Unpack.exe -unpack      %2.unp\\metadata.data.und        %2.unp\\metadata.unp" << endl;
		cout << "GOTO END" << endl;
		cout << "" << endl;
		cout << "" << endl;
		cout << ":PACK" << endl;
		cout << "V8Unpack.exe -pack        %2.unp\\metadata.unp            %2.unp\\metadata_new.data.und" << endl;
		cout << "V8Unpack.exe -deflate     %2.unp\\metadata_new.data.und   %2.unp\\metadata.data" << endl;
		cout << "V8Unpack.exe -pack        %2.unp                         %2.new.cf" << endl;
		cout << "" << endl;
		cout << "" << endl;
		cout << ":END" << endl;

		return ret;
	}

	if (cur_mode == "-example" || cur_mode == "-e") {

		cout << "" << endl;
		cout << "" << endl;
		cout << "UNPACK" << endl;
		cout << "V8Unpack.exe -unpack      1Cv8.cf                         1Cv8.unp" << endl;
		cout << "V8Unpack.exe -undeflate   1Cv8.unp\\metadata.data          1Cv8.unp\\metadata.data.und" << endl;
		cout << "V8Unpack.exe -unpack      1Cv8.unp\\metadata.data.und      1Cv8.unp\\metadata.unp" << endl;
		cout << "" << endl;
		cout << "" << endl;
		cout << "PACK" << endl;
		cout << "V8Unpack.exe -pack        1Cv8.unp\\metadata.unp           1Cv8.unp\\metadata_new.data.und" << endl;
		cout << "V8Unpack.exe -deflate     1Cv8.unp\\metadata_new.data.und  1Cv8.unp\\metadata.data" << endl;
		cout << "V8Unpack.exe -pack        1Cv8.und                        1Cv8_new.cf" << endl;
		cout << "" << endl;
		cout << "" << endl;

		return ret;
	}

	usage();
	return 1;
}
