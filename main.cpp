#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include "stek.h"

using namespace std;

// Реализация паттерна "Стратегия"
class Fish // Родительский (базовый) класс "рыбы"
{
private: // "Закрытые" компоненты (не доступны в унаследованных классах)
    string name;
    double length;
    double weight;
protected: // "Защищенные" компоненты (доступны в унаследованных классах, но не доступны внешнему наблюдателю)
    bool yadovitaya;

public: // "Открытые" компоненты, определяющие интерфейс класса

    Fish(string name, double length, double weight); // Конструктор
    virtual ~Fish(); // Деструктор (объявлен виртуальным, чтобы обеспечить корректное уничтожение унаследованных классов)

    // Функция с реализацией
    string getName() const { return name; }
    double getLength() const { return length; }
    double getWeight() const { return weight; }

    // Абстрактная функция
    virtual void eat() = 0;
    virtual string reproduce() const {return "1";}
    virtual string swim() const {return "1";}
};

// Реализация конструктора
Fish::Fish(string name, double length, double weight) :
    name(name), length(length), weight(weight), yadovitaya(false)
{
    cout << "Creating fish..." << endl;
}

// Реализация деструктора
Fish::~Fish()
{
    cout << "Deleting fish..." << endl;
}

class Losos : public Fish // Класс-наследник
{
private:
    string sreda;
public:
    Losos(string name, double length, double weight, string sreda);
    ~Losos();

    string getSreda() const { return sreda; }

    // Переопределение функции в унаследованном классе
    string swim() const override; //override - нужно для переопределения виртуальных функций. Без этого выдавало ошибку
    string reproduce() const override;
    void eat() override;
};

// Реализация конструктора
Losos::Losos(string name, double length, double weight, string sreda) : Fish("Losos", length, weight), sreda(sreda) //
{
    yadovitaya = false;

    cout << "Creating losos ..." << endl;
}

// Реализация деструктора
Losos::~Losos()
{
    cout << "Deleting losos..." << endl;
}

string Losos::swim() const
{
    return Fish::getName() + "is swimming";
}
string Losos::reproduce() const
{
    return Fish::getName() + "can reproduce from spring to autumn";
}

void Losos::eat()
{
    cout <<"Yadovitaya" << yadovitaya << "You can eat losos..." << endl;
}

class Shark : public Fish
{
private:
    string attack_type;
public:
    Shark(string name, double length, double weight, string attack_type);
    ~Shark();

    string getAttackType() const { return attack_type; }
    string swim() const override;
    string reproduce() const override;

    void eat() override;
};

Shark::Shark(string name, double length, double weight, string attack_type) : Fish("Shark", length, weight),  attack_type(attack_type) //
{
    yadovitaya = false;
    cout << "Creating shark..." << endl;
}

Shark::~Shark()
{
    cout << "Deleting shark..." << endl;
}
string Shark::swim() const
{
    return Fish::getName() + " is swimming";
}
string Shark::reproduce() const
{
    return Fish::getName() + " can reproduce from june to july";
}

void Shark::eat()
{
    cout << " It is very strange idea..." << endl;
}


class Fugu : public Fish
{
private:
    string colour;
public:
    Fugu(string name, double length, double weight, string colour);
    ~Fugu();

    string getColour() const { return colour; }
    string swim() const override;
    string reproduce() const override;

    void eat() override;
};

Fugu::Fugu(string name, double length, double weight, string colour) : Fish("Fugu", length, weight),  colour(colour) //
{
    yadovitaya = true;
    cout << "Creating Fugu..." << endl;
}

Fugu::~Fugu()
{
    cout << "Deleting Fugu..." << endl;
}
string Fugu::swim() const
{
    return Fish::getName() + " is swimming";
}
string Fugu::reproduce() const
{
    return Fish::getName() + " can reproduce from june to july";
}

void Fugu::eat()
{
    cout <<"Yadovitaya" << yadovitaya << " You can't eat fugu..." << endl;
}
enum class FishType : int
{
    Losos = 1,
    Shark = 2,
    Fugu = 3,

    Undefined = 0 // На всякий случай
};

Fish *CreateFish(FishType type)
{
    Fish *newFish = nullptr;

    if(type == FishType::Losos)
    {
        newFish = new Losos("Samlmon", rand()%100+1, 5000.0, "River");
    }
    else if(type == FishType::Shark)
    {
        newFish = new Shark ("Jaws", rand()%100+1, 15000.0, "Aggressive");
    }
    else if(type == FishType::Fugu)
    {
        newFish = new Fugu ("Fugu Chan", rand()%100+1, 150000.0, "Brown");
    }

    return newFish;
}

void swimmingAll(Iterator<Fish*> *it)
{
    for(it->First(); !it->IsDone(); it->Next())
    {
        Fish *currentFish = it->GetCurrent();
        cout<<currentFish->swim()<<endl;
    }
}
// Декоратор итератора для выделения рыб по длине

class FishLenghtDecorator : public IteratorDecorator<class Fish*>
{
private:
    double TargetLenght;

public:
    FishLenghtDecorator(Iterator<Fish*> *it, double Lenght)
    : IteratorDecorator<Fish*>(it), TargetLenght(Lenght) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->getLength() < TargetLenght)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->getLength() < TargetLenght);
    }
};
// Декоратор итератора для выделения имени рыб

class FishNameDecorator : public IteratorDecorator<class Fish*>
{
private:
    string TargetName;

public:
    FishNameDecorator(Iterator<Fish*> *it, string name)
    : IteratorDecorator<Fish*>(it), TargetName(name) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->getName() == TargetName)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->getName() == TargetName);
    }
};
// Декоратор итератора для выделения имени рыб

class FishWeightDecorator : public IteratorDecorator<class Fish*>
{
private:
    double TargetWeight;

public:
    FishWeightDecorator(Iterator<Fish*> *it, double weight)
    : IteratorDecorator<Fish*>(it), TargetWeight(weight) {}

    void First()
    {
        It->First();
        while(!It->IsDone() && It->GetCurrent()->getWeight() < TargetWeight)
        {
            It->Next();
        }
    }

    void Next()
    {
        do
        {
            It->Next();

        } while(!It->IsDone() && It->GetCurrent()->getWeight() < TargetWeight);
    }
};
int main()
{
    setlocale(LC_ALL, "Russian");
    /*wcout << L"Какую рыбу создать (1 - лосось, 2 - акула, 3 - фугу)?" << endl;
    FishType type = FishType::Undefined;
    int ii;
    cin >> ii;
    type = static_cast<FishType>(ii);*/


    /*Fish* salmon = new Losos("Sam", 70.0, 5000.0, "River"); //если проводить ассоциацию со структурой (посмотрела, что так можно)
    Fish* shark = new Shark("Jaws", 500.0, 150000.0, "Aggressive");
    Fish* fugu = new Fugu("Fugu Chan", 500.0, 150000.0, "Brown");
    vector<Fish*> aquarium;

    aquarium.push_back(salmon); //по моему мнению, так проще обработать (чтобы места меньше заняло)
    aquarium.push_back(fugu);
    aquarium.push_back(shark);

    cout << endl;
    for (Fish* fish : aquarium) {
        cout << "Swim: " << fish->swim() << endl;
        cout << "Eat: " ;
        fish->eat();
        cout << "Reproduce: " << fish->reproduce() << endl;
        cout << endl;
    }
    Fish *newFish2 = CreateFish(type);
    newFish2->eat();
    delete newFish2;*/
    cout << endl;
    wcout<<L"Создание массива рыб"<<endl;
    cout << endl;
    ArrayClass<Fish*> fishArray;
    for(size_t i=0; i<6; i++)
    {
        int fish_num = rand()%3+1; // Число от 1 до 3 (случайный фрукт)
        FishType fish_type = static_cast<FishType>(fish_num);
        Fish *newFish = CreateFish(fish_type);
        fishArray.Add(newFish);
    }

    wcout<< endl << L"Создание вектора рыб"<<endl;
    VectorClass<Fish*> fishVector;
    for(size_t i=0; i<3; i++)
    {
        int fish_num = rand()%3+1; // Число от 1 до 3
        FishType fish_type = static_cast<FishType>(fish_num);
        Fish *newFish = CreateFish(fish_type);
        fishVector.Push(newFish);
    }
    cout << endl;
    /*wcout << L"Плавание рыб, которые оказались в массиве" << endl;
    Iterator<Fish*> *it1 = new  ArrayIterator<Fish*>(&fishArray);
    swimmingAll(it1);
    cout << endl;
    wcout << L"Плавание рыб, которые оказались в векторе" << endl;
    Iterator<Fish*> *it2 = new  VectorIterator<Fish*>(&fishVector);
    swimmingAll(it2);
    delete it1;
    delete it2;
    cout << endl << endl;*/
    /* Обход всех коротких рыб
    cout << endl << "Swimming all short using iterator:" << endl;
    Iterator<Fish*> *shortIt = new FishLenghtDecorator(fishArray.GetIterator(), 75);
    swimmingAll(shortIt);
    delete shortIt;

    // Обход всех рыб по имени Samlmon
    wcout << endl << L"Swimming all Sam рыб using iterator:" << endl;
    Iterator<Fish*> *nameIt = new FishNameDecorator(fishVector.GetIterator(), "Samlmon");
    swimmingAll(nameIt);
    delete nameIt;

      // Обход всех рыб по весу
    wcout << endl << L"Swimming all weight using iterator:" << endl;
    Iterator<Fish*> *weihtIt = new FishWeightDecorator(fishArray.GetIterator(), 10000);
    swimmingAll(weihtIt);
    delete weihtIt;

    cout << endl << "Swimming using adapted iterator (another container):" << endl;
    Iterator<Fish*> *adaptedIt = new ConstIteratorAdapter<Fish*>(&fishVector);
    Iterator<Fish*> *adaptedShortIt = new FishLenghtDecorator(new FishNameDecorator(adaptedIt, "Samlmon"), 75);
    swimmingAll(adaptedShortIt);
    delete adaptedShortIt;

    //
    //delete salmon;
    //delete shark;
    //delete fugu;*/




    return 0;
}
