//
// Created by baoduong on 17/10/2017.
//

#pragma once

#include <string>
#include <iostream>
#include <cmath>
using namespace std;
const string ERR_EXPONENTIAL_OF_DIVIDE_OPERATOR_MUST_BE_AN_INTEGER = "ERR EXPONENTIAL OF DIVIDE OPERATOR MUST BE AN INTEGER";
const string ERR_INVALID_BEGINING_OF_A_NUMBER = "INVALID BEGINING OF A NUMBER";
const string ERR_DETECTED_MULTIPLE_COMMAS_IN_DECIMAL_NUMBER = "DETECTED MULTIPLE COMMAS IN DECIMAL NUMBER";
const string ERR_DIVIDED_BY_ZERO = "DIVIDED BY ZERO";
const string ERR_NA_VALUE = "NA: 0 ^ 0";
const int PRECISION = 150;
class BigReal {
    string m_digits;
    int m_sign;
    int m_exponential;
    int operator[](int i) const { // from .
        return m_exponential - i >= 0 && m_exponential - i < m_digits.length() ?
                m_digits[m_exponential - i] - 48 : 0;
    }
    void trim() {
        while (m_digits.length() - 1 > PRECISION)
            m_digits.erase(m_digits.length() - 1, 1);
        while (m_digits.length() > 1 && m_digits[0] == '0') {
            m_digits.erase(0, 1);
            m_exponential--;
        }
        while (m_digits.length() > 1 && m_digits.back() == '0')
            m_digits.erase(m_digits.length() - 1, 1);
        if (m_digits == "0" && m_sign < 0) {
            m_sign = 1;
            m_exponential = 0;
        }
    }
    int getLength() const {
        return m_digits.length();
    }
public:
    void standardPrint(int pcs) {
        if (this->isInt()) {
            cout << *this;
            return;
        }
        string s = "";
        if (m_sign < 0)
            s = "-";
        int i;
        if (m_exponential < 0)
            s += "0";
        for (i = m_exponential; i >= 0; i--)
            s += char((*this)[i] + 48);
        s += '.';
        for (int i = -1; i >= -pcs; i--)
            s += char((*this)[i] + 48);
        while (s.size() > 1 && s.back() == '0')
            s.erase(s.length() - 1, 1);
        cout << s;
    }
    BigReal(int sign, string digits, int exponential) {
        m_sign = sign;
        m_digits = digits;
        m_exponential = exponential;
    }
    BigReal(long long c = 0) {
        m_sign = 1;
        m_exponential = 0;
        if (c < 0) {
            m_sign = -1;
            c = -c;
        }
        do {
            m_digits = char(c % 10 + 48) + m_digits;
            c /= 10;
        } while (c);
        m_exponential = this->getLength() - 1;
    }
    long long toInt() const {
        long long res = 0;
        for (int i = m_exponential; i >=0; i--)
            res = res * 10 + (*this)[i];
        return res * m_sign;
    }
    string toIntStr() const {
        string s = "";
        for (int i = m_exponential; i >= 0; i--)
            s += char((*this)[i] + 48);
        while (s.length() > 1 && s[0] == '0')
            s.erase(0, 1);
        if (m_sign < 0)
            s = "-" + s;
        return s;
    }
    // assume s only contains 0-9, -+ and .
    BigReal(string s) { // ex: "123.1", "0.001"
        if (s[0] == '.' || (!(s[0] >= '0' && s[0] <= '9') && s[0] != '-'))
            throw ERR_INVALID_BEGINING_OF_A_NUMBER;

        for (int i = 0; i < s.length(); i++)
        string tmp = s;
        if (s[0] == '-') {
            m_sign = -1;
            s = s.substr(1);
        }
        else
            m_sign = 1;
        m_exponential = -1;
        for (int i = 0, comma = 0; i < s.length(); i++) {
            if (s[i] == '.') {
                if (comma)
                    throw ERR_DETECTED_MULTIPLE_COMMAS_IN_DECIMAL_NUMBER;
                comma = 1;
            }
            else
                m_digits += s[i];
            m_exponential += !comma;
        }
        this->trim();
    }
    BigReal(const BigReal& p) {
        m_sign = p.m_sign;
        m_digits = p.m_digits;
        m_exponential = p.m_exponential;
    }

    friend ostream& operator<<(ostream& os, const BigReal& p) {
        if (p.isInt())//
            os << p.toIntStr();
        else {
            if (p.m_sign < 0)
                os << "-";
            os << p.m_digits[0];
            if (p.getLength() > 1)
                os << "." << p.m_digits.substr(1);
            os << "e" << p.m_exponential;
        }
        return os;
    }
    const BigReal operator-() const {
        return BigReal(-m_sign, m_digits, m_exponential);
    }
    bool isInt() const {
        return m_exponential >= 0 && m_digits.length() - 1 <= m_exponential;
    }
    bool operator<(const BigReal& p) const {
        if (m_sign != p.m_sign)
            return m_sign < p.m_sign;
        if (m_exponential != p.m_exponential)
            return m_sign > 0 && m_exponential < p.m_exponential;
        for (int i = m_exponential; i >= 0; i--)
            if ((*this)[i] != p[i])
                return m_sign > 0 && (*this)[i] < p[i];
        return false;
    }
    bool operator>(const BigReal& p) const {
        if (m_sign != p.m_sign)
            return m_sign > p.m_sign;
        if (m_exponential != p.m_exponential)
            return m_sign > 0 && m_exponential > p.m_exponential;
        for (int i = m_exponential; i >= 0; i--)
            if ((*this)[i] != p[i])
                return m_sign > 0 && (*this)[i] > p[i];
        return false;
    }
    bool operator==(const BigReal& p) const {
        return m_sign == p.m_sign && m_digits == p.m_digits && m_exponential == p.m_exponential;
    }
    bool operator<=(const BigReal& p) const {
        return *this == p || *this < p;
    }
    bool operator>=(const BigReal& p) const {
        return *this == p || *this > p;
    }
    bool isNeg() const {
        return m_sign < 0;
    }
    BigReal absolute() const {
        return BigReal(1, m_digits, m_exponential);
    }

    BigReal operator+(const BigReal& p) const {
        // this < 0 : this + p = p - |this| else = this - |p|
        if (this->isNeg() != p.isNeg())
            return *this - (-p);
        // now this and p have same sign
        //BigReal res(m_sign, "", m_exponential);
        int n = max(m_exponential, p.m_exponential);
        string s = "";
        int tmp = 0;
        for (int i = -PRECISION; i <= n; i++) {
            int d = tmp + (*this)[i] + p[i];
            tmp = d / 10;
            d %= 10;
            s = char(d + 48) + s;
        }
        if (tmp)
            s = "1" + s;
        BigReal res = BigReal(m_sign, s, s.length() - PRECISION - 1);
        res.trim();
        return res;
    }
    BigReal& operator+=(const BigReal& p) {
        *this = *this + p;
        return *this;
    }
    BigReal& operator++() {
        *this += 1;
        return *this;
    }
    BigReal operator++(int) {
        BigReal tmp = *this;
        ++*this;
        return tmp;
    }

    BigReal operator-(const BigReal& p) const {
        if (*this < p)
            return -(p - *this);

        // both negative, this - p = (-p) - (-this)
        if (this->isNeg() && p.isNeg())
            return p.absolute() - this->absolute();
        if (this->isNeg()) // p is posi, this - p = -(p - this)
            return -(p - *this);
        else
        if (p.isNeg())
            return *this + (-p);
        int n = max(0, max(m_exponential, p.m_exponential));
        string s = "";
        int tmp = 0;
        for (int i = -PRECISION; i <= n; i++) {
            int d = (*this)[i] - p[i] - tmp;
            if (d < 0) {
                d += 10;
                tmp = 1;
            }
            else
                tmp = 0;
            s = char(d + 48) + s;
        }
        BigReal res = BigReal(1, s, s.length() - PRECISION - 1);
        res.trim();
        return res;
    }
    BigReal& operator-=(const BigReal& p) {
        *this = *this - p;
        return *this;
    }
    BigReal& operator--() {
        *this -= 1;
        return *this;
    }
    BigReal operator--(int) {
        BigReal tmp = *this;
        --*this;
        return tmp;
    }

    BigReal operator*(const BigReal& p) const {
        int n = abs(m_exponential) + abs(p.m_exponential) + 1;
        string s = "";
        int tmp = 0;
        for (int i = -PRECISION; i <= n; i++) {
            int c = tmp;
            for (int j = -PRECISION; j <= n; j++)
                c += (*this)[j] * p[i - j];
            tmp = c / 10;
            c = c % 10;
            s = char(c + 48) + s;
        }
        BigReal res = BigReal(m_sign * p.m_sign, s, n);
        res.trim();
        return res;
    }
    BigReal& operator*=(const BigReal& p) {
        *this = *this * p;
        return *this;
    }

    BigReal operator/(const BigReal& p) const {
        if (p == 0)
            throw ERR_DIVIDED_BY_ZERO;
        int n = m_exponential - p.m_exponential;
        BigReal a(*this), b(p);
        a.m_sign = b.m_sign = 1;
        while (!b.isInt()) {
            a.m_exponential++;
            b.m_exponential++;
        }
        BigReal tmp = 0;
        string s = "";
        for (int i = a.m_exponential; i >= -PRECISION; i--) {
            tmp = tmp * 10 + a[i];
            int e = 0;
            while (tmp >= b && e < 9) {
                tmp -= b;
                e++;
            }
            s += char(e + 48);
        }
        BigReal res(m_sign * p.m_sign, s, a.m_exponential);
        res.trim();
        return res;
    }
    BigReal& operator/=(const BigReal& p) {
        *this = *this / p;
        return *this;
    }

    BigReal operator^(long long n) const {
        if (n < 0)
            return BigReal(1) / (*this ^ -n);
        if (n == 0) {
            if (*this == 0)
                throw ERR_NA_VALUE;
            return BigReal(1);
        }
        BigReal k = *this ^ (n >> 1);
        k = k * k;
        k.trim();
        if (n & 1)
            k *= *this;
        k.trim();
        return k;
    }
    BigReal operator^(const BigReal& p) const {
        if (!p.isInt())
            throw ERR_EXPONENTIAL_OF_DIVIDE_OPERATOR_MUST_BE_AN_INTEGER;
        return *this ^ p.toInt();
    }

};

