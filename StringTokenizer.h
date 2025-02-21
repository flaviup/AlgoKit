

#ifndef __STRINGTOKENIZER_H__
#define __STRINGTOKENIZER_H__

#include <string>
#include <vector>

std::vector<std::string> StrTok(const std::string& str, const std::string& separators = " ,;\t\n\r", bool includeEmpty = false) {
	std::vector<std::string> tokens;
	
	if (str.empty()) {
		return tokens;
	}

	if (separators.empty()) {
		if (!str.empty() || includeEmpty) {
			tokens.push_back(str);
		}
		return tokens;
	}
	std::string::size_type pos = 0, tmp = 0;
	std::string substr;
	
	if (separators.find(str[0]) != std::string::npos ) {
		if (includeEmpty) {
			tokens.push_back("");
		}
		++pos;
	}

	while (pos < str.length()) {
		tmp = str.substr(pos).find_first_of(separators);
		
		if (tmp == std::string::npos) {
			substr = str.substr(pos);
			
			if (!substr.empty() || includeEmpty) {
				tokens.push_back(substr);
			}
			pos = str.length();
		} else {
			tmp += pos;
			substr = str.substr(pos, tmp - pos);
			pos = tmp + 1;
		
			if (!substr.empty() || includeEmpty) {
				tokens.push_back(substr);
			}
		}
	}

	if (separators.find(str[str.length() - 1]) != std::string::npos && includeEmpty) {
		tokens.push_back("");
	}
	return tokens;
}

#endif // __STRINGTOKENIZER_H__
