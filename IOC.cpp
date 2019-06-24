#include <iostream>
#include <memory>
#include <functional>
#include <map>

template <typename T>
class IocContainer
{
public:
	IocContainer(void) {};
	virtual ~IocContainer() {};

    template <typename Drived>
    void RegisterType(std::string strKey){
        std::function<T* ()> function = [] {return new Drived();};

        RegisterType(strKey,function);
	};

    T* Resolve(std::string strKey){
        if(m_Createmap.find(strKey) == m_Createmap.end()) return nullptr;

        std::function<T* ()> function = m_Createmap[strKey];

        return function();
	};

    std::shared_ptr<T> ResolveShared(std::string strKey){
        T* ptr = Resolve(strKey);

        return std::shared_ptr<T>(ptr);
	};
private:
    std::map<std::string,std::function<T* ()>> m_Createmap;

    void RegisterType(std::string strKey,std::function<T* ()> creator){
        if(m_Createmap.find(strKey) != m_Createmap.end()){
            throw std::invalid_argument("Already Has Key");
        }
        m_Createmap.emplace(strKey,creator);
	};
};

class ICar
{
public:
	virtual ~ICar() {};
    virtual void test() const = 0;
};

class Bus : public ICar
{
public:
    Bus (){};
    void test() const {
        std::cout << "Bus test" << std::endl;
	};
};

class Track : public ICar
{
public:
    Track (){};
    void test() const {
        std::cout << "Track test" << std::endl;
	};
};

int main(int argc, char *argv[])
{
    IocContainer<ICar> carIOC;

    carIOC.RegisterType<Bus>("Bus");
    carIOC.RegisterType<Track>("Track");

    std::shared_ptr<ICar> bus   = carIOC.ResolveShared("Bus");
    bus->test();

    std::shared_ptr<ICar> track = carIOC.ResolveShared("Track");
    track->test();

    return 0;
}
