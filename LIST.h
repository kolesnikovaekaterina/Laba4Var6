#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <iostream>

using namespace std;

template<typename T>

class List
{
protected:
    struct Element{
        Element* prev;
        Element* next;
        T data;
    };
    Element *Current;
    Element *First;
public:
    List()
    {
        First = nullptr;
        Current = nullptr;
    }
    List(T const data)
    {
        First = new Element();
        First->data = data;
        First->prev = First;
        First->next = First;
        Current = First;
    }
    List(List const &List)
    {
        if(List->First == nullptr)
        {
            First = nullptr;
            Current = nullptr;
            return;
        }
        List->Current=List->First;
        First = new Element();
        First->data = List->Current->data;
        First->prev = First;
        First->next = First;
        Current = First;
        List->Current=List->Current->next;
        while(List->Current != List->First)
        {
            this->insert(List->Current->data);
            List->Current=List->Current->next;
        }
        Current = First;
    }

    unsigned int const size()
    {
        if(First == nullptr)
            return 0;
        unsigned int counter = 0;
        Element *time = First;
        do
        {
            ++counter;
            time = time->next;
        }while(time != First);
        return counter;
    }
    bool const isEmpty() const
    {
        if(First == nullptr)
            return true;
        return false;
    }
    bool const isContains(T const data) const
    {
        if(First == nullptr)
            return false;
        Element *time = First;
        do
        {
            if(time->data == data)
                return true;
            time = time->next;
        }while(time != First);
        return false;
    }

    T const getCurrent()
    {
        return Current->data;
    }
    bool const shiftRight()
    {
        if(First == nullptr)
            return false;
        Current = Current->next;
        return true;
    }
    bool const shiftLeft()
    {
        if(First == nullptr)
            return false;
        Current = Current->prev;
        return true;
    }
    void clear()
    {
        Current = First;
        while(Current != nullptr)
        {
            if(Current == Current->prev)
            {
                delete Current;
                First = nullptr;
                Current = nullptr;
                return;
            }
            Element *time = Current;
            Current->prev->next = Current->next;
            Current->next->prev = Current->prev;
            Current = Current->next;
            delete time;
        }
    }

    bool const deleteAtPos(unsigned int position)
    {
        if((First == nullptr)||(position < 1))
            return false;
        Element *tmpCurrent = Current;
        Current = First;
        while(position > 1)
        {
            Current = Current->next;
            if(Current == First)
            {
                Current = tmpCurrent;
                return false;
            }
            --position;
        }
        if(tmpCurrent == Current)
            tmpCurrent  = tmpCurrent->next;
        deleteCur();
        if(tmpCurrent != nullptr)
            Current = tmpCurrent;
        else
            Current = First;
        return true;
    }
    bool const deleteCur()
    {
        if(Current == nullptr)
            return false;
        if(Current == Current->next)
        {
            delete Current;
            Current = nullptr;
            First = nullptr;
            cout<<"\n\t||element deleted||\t";
            return true;
        }
        Current->prev->next=Current->next;
        Current->next->prev=Current->prev;
        Element *time = Current;
        if(Current == First)
            First = First->next;
        Current = Current->next;
        delete[] time;
        time = nullptr;
        return true;
    }
    bool const delet(T const data)
    {
        if(First == nullptr)
            return false;
        unsigned counter = 0;
        Current = First;
        do
        {
            if(Current->data == data)
            {
                deleteCur();
                ++counter;
            }else{
                Current = Current->next;
            }
        }while((Current != First)&&(Current != nullptr));
        Current = First;
        if(counter == 0)
            return false;
        return true;
    }

    bool const insert(T const data)
    {
        if(First == nullptr)
        {
            First = new Element();
            Current = First;
            Current->data = data;
            Current->prev = First;
            Current->next = First;
            return true;
        }
        Element *time = new Element();
        time->data = data;
        time->prev = Current;
        time->next = Current->next;
        Current->next->prev = time;
        Current->next = time;
        Current = Current->next;
        return true;
    }
    bool const insertAtPos(T const data, unsigned int position)
    {
        if(position < 1)
            return false;
        if((First == nullptr)&&(position != 1))
            return false;
        if((First == nullptr)&&(position == 1))
        {
            First = new Element();
            First->data = data;
            First->prev = First;
            First->next = First;
            Current = First;
            return true;
        }
        if(position == 1)
        {
            Element *time = new Element();
            time->data = data;
            time->prev = First->prev;
            First->prev->next = time;
            time->next = First;
            First->prev = time;
            First = time;
            Current = time;
            return true;
        }
        Current = First;
        while(position>2)
        {
            --position;
            Current = Current->next;
            if(Current == First)
                return false;
        }
        Element *time = new Element();
        time->data = data;
        time->prev = Current;
        time->next = Current->next;
        Current->next->prev = time;
        Current->next = time;
        Current = time;
        return true;
    }

    void print()
    {
        if(First == nullptr)
        {
            cout<<"No";
            return;
        }
        Element *time = First;
        do
        {
            std::cout<<time->data<<"\t";
            time = time->next;
        }while(time != First);
    }
    List& operator = (List const &List)
    {
        if(List->First == nullptr)
        {
            First = nullptr;
            Current = nullptr;
            return *this;
        }
        List->Current=List->First;
        First = new Element();
        Current = First;
        do
        {
            Current->data = List->Current->data;
            Current->prev = List->Current->prev;
            Current->next = List->Current->next;
            List->Current = List->Current->next;
        }while(List->Current != List->First);
        return *this;
    }

    ~List()
    {
        First->prev->next = nullptr;
        while(Current != nullptr)
        {
            Current = First;
            First = First->next;
            delete Current;
            Current = nullptr;
        }
    }
};
#endif // LIST_H_INCLUDED
