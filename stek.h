#ifndef STEK_H_INCLUDED
#define STEK_H_INCLUDED
#include <vector>
#include <vector>
#include <iostream>

using namespace std;


const size_t MaxSize = 100;
template<typename T> // T - подставляемый тип данных (элемент контейнера)
class Iterator
{
protected:
    Iterator() {}

public:
    virtual ~Iterator() {}
    virtual void First() = 0; // Спозиционироваться на начале контейнера
    virtual void Next() = 0;  // Перейти к следующему элементу
    virtual bool IsDone() const = 0;  // Проверить, достигнут ли конец
    virtual T GetCurrent() const = 0; // Получить текущий элемент
};
template<typename T> // Объявление шаблонного класса, T - тип хранимых данных
class Iterable // Абстрактный базовый класс для всех контейнеров
{
public:
    virtual Iterator<T>* GetIterator() = 0; // функция для получения итератора
    virtual ~Iterable() {} // деструктор
};
// Шаблонный класс "Массив"
template<typename T>
class ArrayIterator : public Iterator<T>
{
private:

    const T *ArrayContainer; // Указатель на массив
    size_t Pos; // Текущее положение в массиве
    size_t Size; // Размер массива

public:
    ArrayIterator(T *container, size_t size)
    : ArrayContainer(container), Pos(0), Size(size) {}

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= Size); }
    T GetCurrent() const override { return ArrayContainer[Pos]; }
};

template <typename T>
class ArrayClass : public Iterable<T>
{
private:

    T Items[MaxSize];
    size_t ArraySize;

public:

    void Add(T newObject) { Items[ArraySize++] = newObject; }
    size_t Size() const { return ArraySize; }
    /* Первый вариант получения элемента по индексу (перегрузка оператора [])
    T operator[](size_t index) const { return Items[index]; }*/
    // Второй вариант получения элемента по индексу
    T GetElement(size_t index) const { return Items[index]; }

    class Iterator<T> *GetIterator() override // Переопределение функции GetIterator
    {
        return new ArrayIterator<T>(Items, ArraySize);
    }
    ArrayClass() : ArraySize(0) {}
};
/*template<typename T>
class VectorIterator : public Iterator<T>
{
private:
    const VectorClass<T> *VectorContainer;
    size_t Pos;
public:
    VectorIterator(VectorClass<T> *container)
    : VectorContainer(container), Pos(0) {}

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= VectorContainer->Size()); }
    T GetCurrent() const override { return VectorContainer->GetElement(Pos); }
};*/

template <typename T>
class VectorClass : public Iterable<T>
{
private:
    vector<T> Items;
public:
    size_t Size() const { return Items.size(); }
    void Push(T newObject) {Items.push_back(newObject);}
    T First() {return Items.front();}
    T Back() {return Items.back();}
    T GetElement(size_t index) const {return Items[index];}
    template <typename U>
    class VectorIterator : public Iterator<U>
    {
    private:
        const VectorClass<U> *VectorContainer;
        size_t Pos;
    public:
    VectorIterator(VectorClass<U> *container)
    : VectorContainer(container), Pos(0) {}

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= VectorContainer->Size()); }
    T GetCurrent() const override { return VectorContainer->GetElement(Pos); }
};
    //GetIterator для Vectora
    class Iterator<T> *GetIterator() override // Переопределение функции GetIterator
    {
        return new VectorIterator<T>(this);
    }
};
// Шаблонный класс, реализующий паттерн "Итератор"
// (класс абстрактный, так как содержит функции без реализации)


// Реализация паттерна "Итератор",
// предназначенная для обхода массива



// Декоратор для итератора (пустой)

template<typename T>
class IteratorDecorator : public Iterator<T>
{
protected:
    Iterator<T> *It;

public:
    IteratorDecorator(Iterator<T> *it) : It(it) {}
    virtual ~IteratorDecorator() { delete It; }
    virtual void First() { It->First(); }
    virtual void Next() { It->Next(); }
    virtual bool IsDone() const { return It->IsDone(); }
    virtual T GetCurrent() const { return It->GetCurrent(); }
};
template<typename T>
class ConstIteratorAdapter : public Iterator<T>
{
protected:
     const VectorClass<T> *Container; // Указатель на контейнер VectorClass (чтобы сразу определить тип)
     size_t current_index;

public:
    ConstIteratorAdapter(const VectorClass<T> *container)
    :  Container(container), current_index(0)
    {
    }

    virtual ~ConstIteratorAdapter() {}
    virtual void First() { current_index = 0; }
    virtual void Next() { current_index++; }
    virtual bool IsDone() const { return (current_index == Container->Size()); }
    virtual T GetCurrent() const { return Container->GetElement(current_index);  }
};
#endif // STEK_H_INCLUDED
