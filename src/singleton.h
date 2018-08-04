#ifndef SINGLETON_H
#define SINGLETON_H

template <class SingletonClass>
class Singleton{
public:
    static SingletonClass * instance(){
        static SingletonClass instance;
        return &instance;
    }
    SingletonClass* operator ->() { return instance(); }
    const SingletonClass* operator ->() const { return instance(); }
private:
    Singleton(){}
    ~Singleton(){}
};

#endif // SINGLETON_H
