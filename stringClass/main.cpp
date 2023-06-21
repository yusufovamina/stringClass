#include <iostream>
#include <cstring>
#include<conio.h>
using namespace std;

class String {
private:
    char* data;
    int length;
    int capacity;

public:
    String() : data(nullptr), length(0), capacity(15) {}
    
    //copy constr

    String(const String& str) : data(nullptr), length(str.length), capacity(15) {
        if (str.length >= capacity) {
            capacity = capacity+15 + (str.length - capacity);
        }
        data = new char[capacity];
        strncpy_s(data, capacity, str.data, length);
    }
    String(const string& str) : data(nullptr), length(str.length()), capacity(15) {
        if (str.length() >= capacity) {
            capacity = capacity + 15 + (str.length() - capacity);
        }
        data = new char[capacity];
        strncpy_s(data, capacity, str.data(), length);
    }
    //move constr
    String(String&& str) : data(str.data), length(str.length), capacity(str.capacity) {
        str.data = nullptr;
        str.length = 0;
        str.capacity = 0;
    }

    String(const char* str) : data(nullptr), length(0), capacity(15) {
        length = strlen(str);
      
        if (length >= capacity) {
            capacity = capacity +15 + (length - capacity);
        }
        data = new char[capacity];
        strncpy_s(data, capacity, str, length);
    }

    String(int size, char symbol) : data(nullptr), length(size), capacity(15) {
        if (size >= capacity) {
            capacity = capacity +15 + (size - capacity);
        }
        data = new char[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = symbol;
        }
        data[size] = '\0';
    }

    ~String() {
        delete[] data;
    }

    int size() const {
        return length;
    }

    int capac() const {
        return capacity;
    }

    void clear() {
        delete[] data;
        data = nullptr;
        length = 0;
        capacity = 0;
    }

    char at(int index) const {
        if (index >= 0 && index < length) {
            return data[index];
        }
        
    }

#pragma region insertfunction
    void insert(char symb) {
        if (length + 1 >= capacity) {
            int newCapacity = capacity + 15;
            char* newData = new char[newCapacity];
            strncpy_s(newData, newCapacity, data, length);
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        data[length] = symb;
        length++;
        data[length] = '\0';
    }


    String insert(char symb, int index) {
        if (index < 0 || index > length) {
            cout << "Index is out of range" << endl;
        }

        int newLength = length + 1;
        int newCapacity = newLength + 15;
        char* newData = new char[newCapacity];

        strncpy_s(newData, newCapacity, data, index);
        newData[index]= symb;
        strncpy_s(newData + index + 1, newCapacity - index - 1, data + index, length - index + 1);

        String result;
        result.data = newData;
        result.length =newLength;
        result.capacity = newCapacity;

        return result;
    }

    String insert(char symb, int index,int count) {
        if (index < 0 || index > length) {
            cout << "Index is out of range" << endl;
        }

        int newLength = length + 1;
        int newCapacity = newLength + 15;
        char* newData = new char[newCapacity];

strncpy_s(newData, newCapacity, data, index);
    for (int i = 0; i < count; i++) {
        newData[index + i] = symb;
    }
    strncpy_s(newData + index + count, newCapacity - index - count, data + index, length - index + 1);
        String result;
        result.data = newData;
        result.length = newLength;
        result.capacity = newCapacity;

        return result;
    }

    void insert(int index, const char* substr) {
        if (index < 0 || index > length) {
            cout << "Index out of range" << endl;
        }

        int substrLength = strlen(substr);
        int newLength = length + substrLength;
        int newCapacity = newLength + 15;
        char* newData = new char[newCapacity];

        strncpy_s(newData, newCapacity, data, index);
        strncpy_s(newData + index, newCapacity - index, substr, substrLength);
        strncpy_s(newData + index + substrLength, newCapacity - index - substrLength, data + index, length - index + 1);

        delete[] data;
        data = newData;
        length = newLength;
        capacity = newCapacity;
    }
    
    void insert(int index, const string& substr) {
        if (index < 0 || index > length) {
            cout << "Index out of range" << endl;
        }

        int substrLength = substr.length();
        int newLength = length + substrLength;
        int newCapacity = newLength + 15;
        char* newData = new char[newCapacity];

        strncpy_s(newData, newCapacity, data, index);
        substr.copy(newData + index, substrLength);
        strncpy_s(newData + index + substrLength, newCapacity - index - substrLength, data + index, length - index + 1);

        delete[] data;
        data = newData;
        length = newLength;
        capacity = newCapacity;
    }

#pragma endregion
    int find(const String& substr) const {
        if (substr.length > length) {
            return -1;
        }

        for (int i = 0; i <= length - substr.length; i++) {
            bool found = true;
            for (int j = 0; j < substr.length; j++) {
                if (data[i + j] != substr.data[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return i;
            }
        }

        return -1;
    }

    int rfind(const String& substr) const {
        if (substr.length > length) {
            return -1;
        }

        for (int i = length - substr.length; i >= 0; i--) {
            bool found = true;
            for (int j = 0; j < substr.length; j++) {
                if (data[i + j] != substr.data[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return i;
            }
        } return -1;
    }

#pragma region operatorOverloading


   friend String operator+(const String& str1, const String& str2) {
       
        String result;
        result.length = str1.length + str2.length;
       if (result.length > result.capacity) {
            result.capacity = result.capacity + 15 + (result.length - result.capacity);
        }
        result.data = new char[result.capacity];
        strncpy_s(result.data, result.capacity , str1.data, str1.length);
        strncpy_s(result.data + str1.length, result.capacity - str1.length, str2.data, str2.length);
        result.data[result.length] = '\0';
        return result;
    }

   String& operator+=(const string& str) {
       insert(length, str);
       return *this;
   }



    char& operator[](int index) {
        if (index >= 0 && index < length) {
            return data[index];
        }
    }

    bool operator>(const String& str) const {
        return strcmp(data, str.data) > 0;
    }

    bool operator<(const String& str) const {
        return strcmp(data, str.data) < 0;
    }

    bool operator>=(const String& str) const {
        return strcmp(data, str.data) >= 0;
    }

    bool operator<=(const String& str) const {
        return strcmp(data, str.data) <= 0;
    }

    bool operator==(const String& str) const {
        return strcmp(data, str.data) == 0;
    }
    bool operator!=(const String& str) const {
        return !(strcmp(data, str.data) == 0);
    }

    String& operator=(const String& str) {
        if (this == &str) {
            return *this;
        }

        delete[] data;
        length = str.length;
        capacity = str.capacity;
        data = new char[capacity];
        strncpy_s(data, capacity , str.data, length);
        return *this;
    }

    String& operator=(const char* str) {
        delete[] data;
        length = strlen(str);
        if (length >= capacity) {
            capacity = capacity + 15 + (length - capacity);
        }
        data = new char[capacity + 1];
        strncpy_s(data, capacity + 1, str, length);
        return *this;
    }

    friend ostream& operator<<(ostream& output, const String& str) {
        output << str.data;
        return output;
    }

    friend istream& operator>>(istream& input, String& str) {
        string temp;
        input >> temp;
       str=temp;
        return input;
    }
#pragma endregion
};



int main() {
    String str1("Hello world");
        String str2;
        String str3("zzzz");
       // cout << str1[3];
        //cout << (str3 != str2);
        string a = "asassassssss"; 
        //str3.insert(1, a);
        // cout << str3.capac();
        cin >> str2;
        cout << str2 << "  " << str2.capac();
        str3 += "BCBCBC";
       // cout << str3  << endl;

}