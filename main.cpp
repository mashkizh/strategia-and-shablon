#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include "stek.h"

using namespace std;

// Реализация паттерна "Стратегия"
enum class FeedingStrategyEnum : int
{
  Predator,
  Herbivore,
  FilterFeeder,
  None
};
class FeedingStrategy {
public:
  virtual ~FeedingStrategy() {}
  virtual void Feed() = 0;
};

class PredatorStrategy : public FeedingStrategy {
  void Feed() { cout << "Hunting other fish..."; }
};

class HerbivoreStrategy : public FeedingStrategy {
  void Feed() { cout << "Eating algae and plants..."; }
};

class FilterFeederStrategy : public FeedingStrategy {
  void Feed() { cout << "Filtering plankton from water..."; }
};
// Фабричный метод для создания стратегий
FeedingStrategy* CreateFeedingStrategy(FeedingStrategyEnum strategy)
{
  switch(strategy) {
    case FeedingStrategyEnum::Predator: return new PredatorStrategy;
    case FeedingStrategyEnum::Herbivore: return new HerbivoreStrategy;
    case FeedingStrategyEnum::FilterFeeder: return new FilterFeederStrategy;
    default: return nullptr;
  }
}

class Fish // Родительский (базовый) класс "рыбы"
{
private: // "Закрытые" компоненты (не доступны в унаследованных классах)
    string name;
    double length;
    double weight;
    FeedingStrategy* feedingStrategy;
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

    //стратегия
    void SetFeedingStrategy(FeedingStrategy* strategy)
    {
        if(feedingStrategy != nullptr) delete feedingStrategy;
        feedingStrategy = strategy;
    }

    void PerformFeeding()
    {
        if(feedingStrategy == nullptr)
            {
            cout << "No feeding strategy set!";
            return;
            }
        feedingStrategy->Feed();
    }
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
    if(feedingStrategy != nullptr) delete feedingStrategy;
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
    SetFeedingStrategy(CreateFeedingStrategy(FeedingStrategyEnum::Predator));
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
    SetFeedingStrategy(CreateFeedingStrategy(FeedingStrategyEnum::Predator));
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
    SetFeedingStrategy(CreateFeedingStrategy(FeedingStrategyEnum::Herbivore));
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

int main()
{
    setlocale(LC_ALL, "Russian");
    wcout<<L"Создание массива рыб"<<endl;
    cout << endl;
    ArrayClass<Fish*> fishArray;
    for(size_t i=0; i<6; i++) {
        int fish_num = rand()%3+1;
        FishType fish_type = static_cast<FishType>(fish_num);
        Fish *newFish = CreateFish(fish_type);
        fishArray.Add(newFish);
    }
    cout << "\n=== Feeding Strategies ===\n";
    for(size_t i=0; i<fishArray.Size(); i++) {
        Fish* fish = fishArray.GetElement(i);
        cout << fish->getName() << ": ";
        fish->PerformFeeding();
        cout << endl;
    }
    for(size_t i=0; i<fishArray.Size(); i++)
        {
        delete fishArray.GetElement(i);
        }



    return 0;
}
