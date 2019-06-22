#ifndef _I_PARSER_HH_
#define _I_PARSER_HH_
#include<string>
#include<vector>
#include<cstdint>
class i_parser {
public:
	i_parser() {}
	virtual ~i_parser() {}
	virtual std::string<uint8_t> parse(const std::string& source) = 0;
};
#endif
