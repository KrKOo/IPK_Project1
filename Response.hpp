#include <string>

class Response
{
private:
	std::string body;
	std::string code;
	std::string text;
	void generateBody();

public:
	Response(std::string code, std::string text = "");
	void setCode(std::string code);
	void setText(std::string text);
	const char *getBody();
	size_t length();
};
