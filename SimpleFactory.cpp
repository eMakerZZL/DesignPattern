#include <iostream>
#include <string>
#include <map>

typedef void* (*Constructor)();

class CObjectFactory
{
public:
    static void registerClass(std::string className,Constructor constructor)
    {
        constructors()[className] = constructor;
    }

    static void* creatObject(const std::string &className){
        Constructor constructor = NULL;

        if(constructors().find(className) != constructors().end())
            constructor = constructors().find(className)->second;

        if(constructor == NULL) return NULL;

        return (*constructor)();
    }
private:
    inline static std::map<std::string,Constructor>& constructors(){
        static std::map<std::string,Constructor> instance;
        return instance;
    }
};

#define REG_CLASS(class_name) \
class class_name##Helper  \
{ \
public: \
    class_name##Helper (){ \
        CObjectFactory::registerClass(#class_name,class_name##Helper::createObjFunc); \
    }; \
 \
    static void* createObjFunc(){ \
        return new class_name; \
    } \
}; \
class_name##Helper class_name##helper;

class Api
{
public:
	virtual void test(std::string s) = 0;
protected:
	Api() {};
};

class ImplOne : public Api
{
public:
    void test(std::string s){
        std::cout << s << "Run ImplOne" << std::endl;
    }
};


class ImplTwo : public Api
{
public:
    void test(std::string s){
        std::cout << s << "Run ImplTwo" << std::endl;
    }
};

class AutoFactory
{
public:
    static Api* createApi(){
        Api* pApi = nullptr;

        pApi = static_cast<Api*>(CObjectFactory::creatObject("ImplTwo"));

        return pApi;
    }
};

REG_CLASS(ImplOne)
REG_CLASS(ImplTwo)

int main(int argc, char *argv[])
{
    Api* pApi = AutoFactory::createApi();
    pApi->test("Dy");

    return 0;
}

