#include "tableCipher.h"

// Конструктор
tableCipher::tableCipher(int key)
{
    if (key < 2)
        throw CipherError("Ключ некорректного размера");
    this->key = key;
}

wstring tableCipher::encrypt(wstring &open_text)
{
    validateText(open_text);
    validateKey(key, open_text);
    int length = open_text.length();
    int strings = (length + key - 1) / key;
    wchar_t **table = new wchar_t *[strings];
    for (int i = 0; i < strings; i++)
        table[i] = new wchar_t[key]();
    for (int i = 0; i < strings; i++)
        for (int j = 0; j < key; j++)
        {
            if (i * key + j < length)
                table[i][j] = open_text[i * key + j];
            else
                table[i][j] = L' ';
        }
    wstring result;
    result.reserve(strings * key);
    for (int j = 0; j < key; j++)
        for (int i = 0; i < strings; i++)
            result += table[i][j];
    for (int i = 0; i < strings; i++)
        delete[] table[i];
    delete[] table;
    return result;
}

// Удалить пробелы в начале и в конце
wstring trim(const wstring &str)
{
    auto wsfront = find_if_not(str.begin(), str.end(), [](wchar_t c)
                               { return iswspace(c); });
    auto wsback = find_if_not(str.rbegin(), str.rend(), [](wchar_t c)
                              { return iswspace(c); })
                      .base();
    return (wsback <= wsfront ? wstring() : wstring(wsfront, wsback));
}

wstring tableCipher::decrypt(wstring &secret_text)
{
    validateText(secret_text);
    validateKey(key, secret_text);
    int length = secret_text.length();
    int strings = (length + key - 1) / key;
    wchar_t **table = new wchar_t *[strings];
    for (int i = 0; i < strings; i++)
        table[i] = new wchar_t[key]();
    for (int j = 0; j < key; j++)
        for (int i = 0; i < strings; i++)
        {
            if (j * strings + i < length)
                table[i][j] = secret_text[j * strings + i];
            else
                table[i][j] = L' ';
        }
    wstring result;
    result.reserve(strings * key);
    for (int i = 0; i < strings; i++)
        for (int j = 0; j < key; j++)
            result += table[i][j];
    for (int i = 0; i < strings; i++)
        delete[] table[i];
    delete[] table;
    return trim(result);
}

inline void tableCipher::validateText(wstring &text)
{
    if (text.empty())
        throw CipherError("Отсутствует текст!");
    for (wchar_t wc : text)
    {
        if (ABC.find(wc) != wstring::npos)
            continue;
        wstringstream wss;
        wss << L"Текст содержит недопустимый символ: " << wc;
        wstring_convert<codecvt_utf8<wchar_t>> conv;
        throw CipherError(conv.to_bytes(wss.str()));
    }
}

inline void tableCipher::validateText(wstring &open_text, wstring &secret_text)
{
    if (open_text.empty() && secret_text.empty())
        throw CipherError("Отсутствует текст!");
    if (!(open_text.empty() || secret_text.empty()) && secret_text.size() != open_text.size())
        wcerr << L"Предупреждение: размер открытого текста не соответствует размеру шифрованного текста" << endl;

    validateText(open_text);   // Проверка первого текста
    validateText(secret_text); // Проверка второго текста
}

inline void tableCipher::validateKey(int &key, wstring &text)
{
    if (key < 2 || key > static_cast<int>(text.size()))
        throw CipherError("Ключ некорректного размера");
}
