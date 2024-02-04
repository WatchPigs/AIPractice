#include "Utils.h"

vector<string> split(const string& s, const char& seperator)
{
	vector<string> ans;
	istringstream stream(s);
	string word;
	while (getline(stream, word, seperator)) {
		ans.push_back(word);
	}
	return ans;
}
