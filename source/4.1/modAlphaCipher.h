/**
 * @file
 * @brief Заголовочный файл для модуля modAlphaCipher
 * @details Содержит реализацию класса для шифрования методом Гронсфельда.
 * @version 1.0
 * @date 14.12.2024
 * @author Бусыгин Г. С.
 */

#pragma once
#include <vector>
#include <string>
#include <map>
#include <stdexcept>

using namespace std;

/**
 * @brief Класс для шифрования и дешифрования методом Гронсфельда
 * @details Ключ устанавливается в конструкторе. Методы encrypt и decrypt предназначены для шифрования и дешифрования текста соответственно.
 */
class modAlphaCipher
{
private:
    const wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; ///< Алфавит
    map<wchar_t, int> alphaNum; ///< Соответствие букв и индексов
    vector<int> key; ///< Ключ шифрования

    /**
     * @brief Преобразование строки в вектор индексов
     * @param s Строка для преобразования
     * @return Вектор индексов
     */
    vector<int> convert(const string &s);

    /**
     * @brief Преобразование вектора индексов в строку
     * @param v Вектор индексов
     * @return Строка
     */
    string convert(const vector<int> &v);

    /**
     * @brief Проверка и получение валидного ключа
     * @param s Строка ключа
     * @return Валидный ключ
     * @throw CipherError если ключ некорректен
     */
    string getValidKey(const string &s);

    /**
     * @brief Проверка и получение валидного открытого текста
     * @param s Открытый текст
     * @return Валидный открытый текст
     * @throw CipherError если текст некорректен
     */
    string getValidOpenText(const string &s);

    /**
     * @brief Проверка и получение валидного зашифрованного текста
     * @param s Зашифрованный текст
     * @return Валидный зашифрованный текст
     * @throw CipherError если текст некорректен
     */
    string getValidCipherText(const string &s);

public:
    modAlphaCipher() = delete; ///< Удаляем конструктор по умолчанию

    /**
     * @brief Конструктор с ключом
     * @param skey Ключ шифрования
     * @throw CipherError если ключ некорректен
     */
    explicit modAlphaCipher(const string &skey);

    /**
     * @brief Шифрование текста
     * @param open_text Открытый текст
     * @return Зашифрованный текст
     * @throw CipherError если текст некорректен
     */
    string encrypt(const string &open_text);

    /**
     * @brief Дешифрование текста
     * @param cipher_text Зашифрованный текст
     * @return Расшифрованный текст
     * @throw CipherError если текст некорректен
     */
    string decrypt(const string &cipher_text);
};

/**
 * @brief Класс для обработки ошибок шифрования
 */
class CipherError : public invalid_argument
{
public:
    /**
     * @brief Конструктор с сообщением об ошибке
     * @param what_arg Сообщение об ошибке
     */
    explicit CipherError(const string &what_arg) : invalid_argument(what_arg) {}

    /**
     * @brief Конструктор с сообщением об ошибке
     * @param what_arg Сообщение об ошибке
     */
    explicit CipherError(const char *what_arg) : invalid_argument(what_arg) {}
};
