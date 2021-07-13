#pragma once

#include <vector>

// https://stackoverflow.com/a/868894/12586927
class InputParser {
public:
	InputParser(int &argc, char **argv) {
		for (int i = 1; i < argc; ++i)
			this->tokens.push_back(std::string(argv[i]));
	}
	/// @author iain
	const std::string& getCmdOption(const std::string &option) const {
		std::vector<std::string>::const_iterator itr;
		itr = std::find(this->tokens.begin(), this->tokens.end(), option);
		if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
			return *itr;
		}
		static const std::string empty_string("");
		return empty_string;
	}
	/// @author iain
	bool cmdOptionExists(const std::string &option) const {
		return std::find(this->tokens.begin(), this->tokens.end(), option)
			!= this->tokens.end();
	}

	const std::string& getNthNonOption(int n) const {
		int found = 0;
		for (auto const& token: this->tokens)
			if (strcmp(token.substr(0, 1).c_str(), "-") != 0)
				if (n == found++)
					return token;
		static const std::string empty_string("");
		return empty_string;
	}

	const int getNonOptionCount() const {
		int found = 0;
		for (auto const& token : this->tokens)
			if (strcmp(token.substr(0, 1).c_str(), "-") != 0)
				found++;
		return found;
	}
private:
	std::vector <std::string> tokens;
};
