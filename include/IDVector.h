#ifndef IDVECTOR_H
#define IDVECTOR_H
#include <cstddef>
#include <iterator>
#include <strings.h>
#include <utility>
#include <vector>
#pragma once

template<typename T>
class IDVector
{
    private:
        std::vector<T> m_container;
        int counterID;
    private:

    public:
        using iterator = typename std::vector<T>::iterator;
        using const_iterator = typename std::vector<T>::const_iterator;

    public:
        IDVector( ) : counterID{ 0 } {}

        template<typename... Args>
        T& emplaceBack( Args&&... args )
        {
            T& returnValue = m_container.emplace_back(counterID, std::forward<Args>(args)...);
            counterID ++;
            return returnValue;
        }

        void reserve( int value )
        {
            m_container.reserve(value);
        }

        void deleteElementById( int& id )
        {
            for(auto it = m_container.begin(); it != m_container.end(); ++it)
            {
                if(it->ID == id)
                {
                    m_container.erase(it);
                    break;
                }
            }
        }

        std::size_t size( )
        {
            return m_container.size();
        }

        T& operator[]( std::size_t index )
        {
            return m_container[index];
        }

        int findIndexById( int id )
        {
            for(std::size_t i = 0; i < m_container.size(); ++i)
            {
                if(m_container[i].ID == id)
                {
                    return static_cast<int>(i);
                }
            }
            return -1;
        }

        T& getById( int id )
        {
            int index = findIndexById(id);
            if(index != -1)
            {
                return m_container[static_cast<std::size_t>(index)];
            }
            throw std::out_of_range("ELEMENT WITH ID NOT FOUND");
        }

        void clear( )
        {
            m_container.clear();
        }

        iterator erase( iterator pos )
        {
            return m_container.erase(pos);
        }



        // ranged for loops
        iterator begin( )
        {
            return m_container.begin();
        }
        iterator end( ) {
            return m_container.end();
        }

        const_iterator begin( ) const {
            return m_container.begin();
        }

        const_iterator end( ) const {
            return m_container.end();
        }

        const_iterator cbegin( ) const {
            return m_container.cbegin();
        }

        const_iterator cend( ) const {
            return m_container.cend();
        }

};

#endif
