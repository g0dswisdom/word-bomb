#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <map>

std::map<char, unsigned int> keys{
	{'a', 0x41},
	{'b', 0x42},
	{'c', 0x43},
	{'d', 0x44},
	{'e', 0x45},
	{'f', 0x46},
	{'g', 0x47},
	{'h', 0x48},
	{'i', 0x49},
	{'j', 0x4A},
	{'k', 0x4B},
	{'l', 0x4C},
	{'m', 0x4D},
	{'n', 0x4E},
	{'o', 0x4F},
	{'p', 0x50},
	{'q', 0x51},
	{'r', 0x52},
	{'s', 0x53},
	{'t', 0x54},
	{'u', 0x55},
	{'v', 0x56},
	{'w', 0x57},
	{'x', 0x58},
	{'y', 0x59},
	{'z', 0x5A},
	{'-', VK_OEM_MINUS},
};

std::vector<std::string> words;

void keyPress(WORD key) {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	/* key press */
	ip.ki.wVk = key;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	/* key release */
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

int main()
{
	std::srand(std::time(nullptr));
	SetConsoleTitleA("Word Bomb");
	std::ifstream file("words.txt");

	HWND hwnd = FindWindowA(NULL, "Roblox");
	if (hwnd == INVALID_HANDLE_VALUE) {
		std::cout << "Roblox Window not found\n";
	}

	std::cout << "Reading words..\n";

	/* read all words and put them into the words list */
	std::string word;
	while (std::getline(file, word)) {
		words.push_back(word);
	}

	while (true) {
		std::cout << "Enter your prompt: ";
		std::string input;
		std::getline(std::cin, input);

		std::vector<std::string> matches;
		matches.clear();

		/* find words that contain the input/prompt */
		for (std::string word : words) {
			if (word.contains(input)) {
				matches.push_back(word);
			}
		}

		std::string selected = matches[std::rand() % matches.size()];
		SetForegroundWindow(hwnd);

		/* press keys and then enter */
		for (char c : selected) {
			c = tolower(c);
			if (keys.find(c) != keys.end()) {
				keyPress(keys[c]);
				Sleep(100);
				keyPress(0x0D);
			}
		}
	}

	//matches.clear();
}