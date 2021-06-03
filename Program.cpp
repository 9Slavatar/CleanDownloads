#include <iostream>
#include <filesystem>
#include <windows.h>
#include <Lmcons.h>

using namespace std;


// Vars
string path = "";
vector<string> files = {};


void updateFiles() {
	files = {};
	for (const auto& entry : filesystem::directory_iterator(path)) {
		// Remove path
		string file = entry.path().u8string();
		file = file.substr(file.find("\\") + 1);
		// Add to vector filename
		files.push_back(file);
	}
}

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	// Get username
	char char_username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName((TCHAR*) char_username, &username_len);

	path = "C:/Users/" + (string) char_username + "/Downloads";

	// Create folders & arrays with extension
	filesystem::create_directory(path + "/Media");
	filesystem::create_directory(path + "/Archives");
	filesystem::create_directory(path + "/Documents");
	filesystem::create_directory(path + "/Programs");
	string media_ex[37] = {".ai", ".bmp", ".gif", ".ico", ".jpeg", ".jpg", 
						   ".ps", ".psd", ".tif", ".tiff", ".3g2", ".3gp", 
						   ".avi", ".flv", ".h264", ".m4v", ".swf", ".vob",
						   ".mkv", ".mov", ".mp4", ".mpg", ".mpeg", ".rm",
						   ".wmv", ".aif", ".cda", ".mid", ".midi", ".mpa",
						   ".ogg", ".wav", ".wma", ".wpl", ".mp3", ".svg",
						   ".png"};

	string archive_ex[9] = {".7z", ".arj", ".deb", ".pkg", ".rar", ".rpm",
							 ".tar.gz", ".z", ".zip"};

	string document_ex[17] = {".odp", ".pps", ".ppt", ".pptx", ".xls", ".ods",
							  ".xlsm", ".xlsx", ".doc", ".docx", ".odt", ".pdf",
							  ".rtf", ".tex", ".txt", ".wpd", ".csv"};

	string program_ex[11] = {".apk", ".bat", ".bin", ".cgi", ".pl", ".com",
							 ".exe", ".gadget", ".jar", ".msi", "wsf"};

	// Main loop
	int oldFilesSize = 0;
	while (true) {
		updateFiles();
		// Check on new files
		if (files.size() != oldFilesSize) {
			oldFilesSize = files.size();

			// Check again every files
			for (int i = 0; i < files.size(); i++) {
				int dot = files[i].find_last_of("."); // Get extension
				if (dot < 1) continue; // If folder then next element in vector
				string ex = files[i].substr(dot);

				// Sort files
				if (find(begin(media_ex), end(media_ex), ex) != end(media_ex)) 
					filesystem::rename(path + "/" + files[i], path + "/Media" + "/" + files[i]);
				else if (find(begin(archive_ex), end(archive_ex), ex) != end(archive_ex)) 
					filesystem::rename(path + "/" + files[i], path + "/Archives" + "/" + files[i]);
				else if (find(begin(document_ex), end(document_ex), ex) != end(document_ex)) 
					filesystem::rename(path + "/" + files[i], path + "/Documents" + "/" + files[i]);
				else if (find(begin(program_ex), end(program_ex), ex) != end(program_ex)) 
					filesystem::rename(path + "/" + files[i], path + "/Programs" + "/" + files[i]);
			}
		}
		Sleep(600000); // 10 min cooldown
	}
    return 0;
}
