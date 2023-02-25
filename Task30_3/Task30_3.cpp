#include <iostream>
#include <vector>
#include<string>
#include <cpr/cpr.h>

void getRequest(std::vector<std::pair<std::string,std::string>> &args)
{
	std::string req = "http://httpbin.org/get?";
	for (int i = 0; i < args.size(); i++)
	{
		req += args[i].first + "=" + args[i].second + "&";
	}
	cpr::Response r = cpr::Get(cpr::Url(req));
	std::cout << r.text << std::endl;
	std::cout << "status code " << r.status_code << std::endl;
}

void postRequest(std::vector<std::pair<std::string, std::string>>& inArgs)
{
	std::vector<cpr::Pair> args;
	int index = 0;
	for (auto it = inArgs.begin(); it != inArgs.end(); ++it,index++)
	{
		cpr::Pair arg(inArgs[index].first, inArgs[index].second);
		args.push_back(arg);
	}
	cpr::Response r = cpr::Post(cpr::Url("http://httpbin.org/post"),
		              cpr::Payload(args.begin(), args.end()));
	std::cout << r.text << std::endl;
	std::cout << "status code " << r.status_code << std::endl;
}

int main()
{
	std::vector<std::pair<std::string, std::string>> args;
	std::string keys, val;
	std::cout << "Input arguments : ";
	std::getline(std::cin, keys);
	while (keys!="get"&& keys!="post")
	{
		std::cout << "Input value : ";
		std::getline(std::cin, val);
		args.push_back({keys, val});
		std::cout << "Input arguments : ";
		std::getline(std::cin, keys);
	}
	if (keys == "get")
	{
		getRequest(args);
	}
	if (keys == "post")
	{
		postRequest(args);
	}
}
