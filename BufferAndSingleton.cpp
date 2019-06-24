#include <iostream>
#include <map>

class Singleton;
static std::map<int, Singleton*> map = std::map<int,Singleton*>();

class Singleton
{
public:
    static Singleton* getInstance(void){
        m_Singleton = map[m_SingletonCount];
        if(m_Singleton == nullptr){
            m_Singleton = new Singleton;
            map[m_SingletonCount] = m_Singleton;
        }
        m_SingletonCount++;
        if(m_SingletonCount > NUM_MAX) m_SingletonCount = 1;

        return m_Singleton;
    }
private:
    Singleton (){
        m_Singleton = nullptr;
    };
    static Singleton* m_Singleton;
    static int m_SingletonCount;
	const static int NUM_MAX = 5;
};
Singleton* Singleton::m_Singleton = nullptr;
int Singleton::m_SingletonCount = 1;

int main(int argc, char *argv[])
{
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    Singleton *p3 = Singleton::getInstance();
    Singleton *p4 = Singleton::getInstance();
    Singleton *p5 = Singleton::getInstance();

    Singleton *s1 = Singleton::getInstance();
    Singleton *s2 = Singleton::getInstance();
    Singleton *s3 = Singleton::getInstance();
    Singleton *s4 = Singleton::getInstance();
    Singleton *s5 = Singleton::getInstance();
    
    std::cout << p1 << "\t";
    std::cout << p2 << "\t";
    std::cout << p3 << "\t";
    std::cout << p4 << "\t";
    std::cout << p5 << std::endl;

    std::cout << s1 << "\t";
    std::cout << s2 << "\t";
    std::cout << s3 << "\t";
    std::cout << s4 << "\t";
    std::cout << s5 << std::endl;
    
    return 0;
}
