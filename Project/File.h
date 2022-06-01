#pragma once
#include <iostream>
#include <fstream>
#include "listProduct.h"
using namespace std;

template<typename T>
class File {
private:
    fstream file;
    string path; 
    string file_name;
    //  C:/Folder/    string file_name; //  text.txt    bool isBinary;
public:
    void ChangePath(string path)
    {
        this->path = path;
    }
    void ChangeFilename(string file_name)
    {
        this->file_name = file_name;
    }
    bool Save(T* object, uint32_t length = 0)
    {
        try {
            this->file.open(path + file_name, ios::out | ios::binary);
            if (!file.is_open())
            {
                throw;
            }
            else {
                if (length != 0)
                {
                    /*file.write((char*)length, sizeof(uint32_t));                    for (size_t i = 0; i < length; i++)                    {                        file.write((char*)&object[i], sizeof(object[i]));                    }*/
                }
                else {
                    T buf = *object;
                    file.write((char*)&buf, sizeof(buf));
                }
                file.close();
            }
            return true;
        }
        catch (const ifstream::failure& e)
        {
            cout << e.what() << endl;
            return false;
        }
    }
    bool Append(T* object)
    {
        try {
            this->file.open((path + file_name), ios::app | ios::binary);
            if (!file.is_open())
            {
                throw;
            }
            else {
                file.write((char*)&object, sizeof(T));
                file.close();
            }
            return true;
        }
        catch (const ifstream::failure& e)
        {
            cout << e.what() << endl;
            return false;
        }
    }
    bool Load(T*& object, uint32_t& length)
    {
        try {
            this->file.open((path + file_name), ios::in | ios::binary);
            if (!file.is_open())
            {
                throw;
            }
            else {
                file.read((char*)&length, sizeof(uint32_t));
                delete[]object;
                object = new T[length];
                for (size_t i = 0; i < length; i++)
                {
                    file.read((char*)&object[i], sizeof(T));
                }
                file.close();
                return true;
            }
        }
        catch (const ifstream::failure& e)
        {
            cout << e.what() << endl;
            return false;
        }
    }
    T* Load()
    {
        try {
            T* object = new T;
            this->file.open((path + file_name), ios::in | ios::binary);
            if (!file.is_open())
            {
                throw;
            }
            else {
                T buf;
                file.read((char*)&buf, sizeof(buf));
                *object = buf;
                file.close();
            }
            return object;
        }
        catch (const ifstream::failure& e)
        {
            cout << e.what() << endl;
            return nullptr;
        }
    }
    bool Clear()
    {
        try {
            this->file.open((path + file_name), ios::trunc | ios::binary);
            if (!file.is_open())
            {
                throw;
            }
            else {
                cout << "Clear!" << endl;
                file.close();
            }
            return true;
        }
        catch (const ifstream::failure& e)
        {
            cout << e.what() << endl;
            return false;
        }
    }
    File() = default;
    File(string path, string file_name)
    {
        ChangePath(path);
        ChangeFilename(file_name);
    }
};
