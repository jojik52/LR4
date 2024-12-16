#include "modAlphaCipher.h"
#include <locale>
#include <codecvt>

using namespace std;

locale loc("ru_RU.UTF-8");
wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;

modAlphaCipher::modAlphaCipher(const string &skey)
{
    for (unsigned i = 0; i < numAlpha.size(); i++)
        alphaNum[numAlpha[i]] = i;
    key = convert(getValidKey(skey));

    // проверка слабого ключа
    int n = 0;
    for (auto e : key)
    {
        if (e == 0)
            n++;
    }
    if (2 * n > key.size())
    {
        throw CipherError("Слабый ключ");
    }
}

string modAlphaCipher::encrypt(const string &open_text)
{
    vector<int> work = convert(getValidOpenText(open_text));
    for (unsigned i = 0; i < work.size(); i++)
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    return convert(work);
}

string modAlphaCipher::decrypt(const string &cipher_text)
{
    vector<int> work = convert(getValidCipherText(cipher_text));
    for (unsigned i = 0; i < work.size(); i++)
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    return convert(work);
}

inline vector<int> modAlphaCipher::convert(const string &s)
{
    wstring ws = codec.from_bytes(s);
    vector<int> result;
    for (auto c : ws)
    {
        if (alphaNum.find(c) != alphaNum.end())
        {
            result.push_back(alphaNum[c]);
        }
    }
    return result;
}

inline string modAlphaCipher::convert(const vector<int> &v)
{
    wstring ws;
    for (auto i : v)
    {
        if (i >= 0 && i < numAlpha.size())
        {
            ws.push_back(numAlpha[i]);
        }
    }
    return codec.to_bytes(ws);
}

inline string modAlphaCipher::getValidKey(const string &s)
{
    wstring ws = codec.from_bytes(s);
    if (ws.empty())
        throw CipherError("Пустой ключ");

    for (auto &c : ws)
    {
        if ((c < L'А' || c > L'Я') && (c < L'а' || c > L'я'))
            throw CipherError("Неверный ключ: " + s);
        if (c >= L'а' && c <= L'я')
            c -= 32; // Приведение к верхнему регистру
    }

    return codec.to_bytes(ws);
}

inline string modAlphaCipher::getValidOpenText(const string &s)
{
    wstring ws = codec.from_bytes(s);
    wstring tmp;

    for (auto c : ws)
    {
        if ((c >= L'А' && c <= L'Я') || (c >= L'а' && c <= L'я') || c == L'Ё' || c == L'ё')
        {
            if (c >= L'а' && c <= L'я')
                tmp.push_back(c -= 32); // Приведение к верхнему регистру
            else
                tmp.push_back(c);
        }
        else if (c == L' ')
        {
            tmp.push_back(c); // Разрешаем пробелы
        }
        else
        {
            throw CipherError("Недопустимый символ в тексте");
        }
    }

    if (tmp.empty())
        throw CipherError("Надо текст!");
    return codec.to_bytes(tmp);
}

inline string modAlphaCipher::getValidCipherText(const string &s)
{
    wstring ws = codec.from_bytes(s);
    if (ws.empty())
        throw CipherError("Empty cipher text");

    for (auto c : ws)
    {
        if ((c < L'А' || c > L'Я') && c != L'Ё')
            throw CipherError("Неверный зашифрованный текст " + s);
    }

    return codec.to_bytes(ws);
}
