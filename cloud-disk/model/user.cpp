
#include <json/json.h>
#include "user.h"

User::User()
{

}

User::~User()
{

}

User User::Parse(const string &json)
{
   Json::Value root;
   Json::Reader reader;
   reader.parse(json,root);
   if(root ==Json::Value::nullRef)
   {
       std::cout<<"root is null"<<std::endl;
       return User();
   }
  Json::Value emps= root["employees"];

  if(emps.isArray())
  {
    Json::Value::ArrayIndex size= emps.size();
    std::cout<<"arr size "<<size<<std::endl;
    Json::Value::iterator it=emps.begin();
    for(it;it!=emps.end();++it)
    {
       Json::Value fname=(*it)["firstName"];
        Json::Value sname=(*it)["lastName"];
       std::cout<<fname.asString()<<" "<<sname.asString()<<std::endl;
    }
  }
}

#include <vector>
#include <map>
#include <functional>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
  std::string json=R"({
                   "employees": [
                   { "firstName":"Bill" , "lastName":"Gates" },
                   { "firstName":"George" , "lastName":"Bush" },
                   { "firstName":"Thomas" , "lastName":"Carter" }
                   ]
                   })";
  User user=User::Parse(json);

    return 0;
}
