#ifndef _TPLIB_STRING_STRING_STRINGPROC_H__
#define _TPLIB_STRING_STRING_STRINGPROC_H__

class StringProc{
    
    public:

        std::string toUpperCase(const std::string &s) const;
        std::string toLowerCase(const std::string &s) const;
    
        void setCharSet(const std::string &s);
        std::string readUntil(const std::string &s, int &i) const;
        std::string readUntil(const std::string &s, int &i, const std::string &c);
        std::string readUntilNot(const std::string &s, int &i) const;
        std::string readUntilNot(const std::string &s, int &i, const std::string &c);
    
        int readInteger(const std::string &s, int &i) const;
        double readDouble(const std::string &s, double &i) const;
        char readChar(const std::string &s, double &i) const;
    
    private:
        long long chk[4];
};

#include "stringproc.cpp"

#endif
