#ifndef _TPLIB_STRING_STRING_STRINGPROC_CPP__
#define _TPLIB_STRING_STRING_STRINGPROC_CPP__

std::string StringProc::toUpperCase(const std::string &s) const
{
    std::string ret = s;
    for (int i = 0; i < ret.size(); ++i)
        if ('a' <= ret[i] && ret[i] <= 'z')
            ret[i] += 'A' - 'a';
    return ret;
}

std::string StringProc::toLowerCase(const std::string &s) const
{
    std::string ret = s;
    for (int i = 0; i < ret.size(); ++i)
        if ('A' <= ret[i] && ret[i] <= 'Z')
            ret[i] -= 'A' - 'a';
    return ret;
}

void StringProc::setCharSet(const std::string &s)
{
    memset(chk, 0, sizeof(chk));
    for (int i = 0; i < s.size(); ++i)
        chk[s[i] >> 6] |= (1LL << (s[i] & 0x3F));
}

std::string StringProc::readUntil(const std::string &s, int &i) const
{
    std::string ret = "";
    while (i < s.size() && (chk[s[i] >> 6] & (1LL << (s[i] & 0x3F))) == 0)
    {
        ret = ret + s[i];
        ++i;
    }
    return ret;
}

std::string StringProc::readUntil(const std::string &s, int &i, const std::string &c)
{
    setCharSet(c);
    return readUntil(s, i);
}

std::string StringProc::readUntilNot(const std::string &s, int &i) const
{
    std::string ret = "";
    while (i < s.size() && (chk[s[i] >> 6] & (1LL << (s[i] & 0x3F))) > 0)
    {
        ret = ret + s[i];
        ++i;
    }
    return ret;
}

std::string StringProc::readUntilNot(const std::string &s, int &i, const std::string &c)
{
    setCharSet(c);
    return readUntilNot(s, i);
}

int StringProc::readInteger(const std::string &s, int &i) const
{
    int ret = 0;
    while (i < s.size() && '0' <= s[i] && s[i] <= '9')
        ret = ret * 10 + (s[i] - '0');
    return ret;
}

double StringProc::readDouble(const std::string &s, double &i) const
{
    double ret = 0;
    while (i < s.size() && '0' <= s[i] && s[i] <= '9')
        ret = ret * 10 + (s[i] - '0');
    if (i < s.size() && s[i] == '.')
    {
        ++i;
        double k = 0.1;
        while (i < s.size() && '0' <= s[i] && s[i] <= '9')
        {
            ret += (s[i] - '0') * k;
            k *= 0.1;
        }
    }
    return ret;
}

char StringProc::readChar(const std::string &s, double &i) const
{
    if (i >= s.size()) return '\0';
    else return s[i++];
}


#endif
