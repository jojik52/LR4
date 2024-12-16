/**
 * @file
 * @author Бусыгин Г. С.
 * @version 1.0
 * @date 14.12.2024
 * @brief Заголовочный файл для модуля tableCipher
 */

#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <locale>
#include <codecvt>
#include <iostream>
#include <sstream>

using namespace std;

/**
 * @brief Класс для шифрования и дешифрования методом табличного шифра
 * @details Ключ устанавливается в конструкторе. Методы encrypt и decrypt предназначены для шифрования и дешифрования текста соответственно.
 */
class tableCipher
{
private:
    int key; ///< Ключ шифрования
    wstring ABC = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
                  L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя"
                  L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                  L"abcdefghijklmnopqrstuvwxyz"
                  L"0123456789 !?.,-#\n\r\t"; ///< Допустимые символы

public:
    tableCipher() = delete; ///< Удаленный конструктор по умолчанию
    /**
     * @brief Конструктор с ключом
     * @param key Ключ шифрования
     * @throw CipherError если ключ меньше 2
     */
    tableCipher(int key);

    /**
     * @brief Зашифровывание текста
     * @param open_text Открытый текст
     * @return Зашифрованный текст
     * @throw CipherError если текст некорректен
     */
    wstring encrypt(wstring &open_text);

    /**
     * @brief Дешифровывание текста
     * @param secret_text Зашифрованный текст
     * @return Расшифрованный текст
     * @throw CipherError если текст некорректен
     */
    wstring decrypt(wstring &secret_text);

    /**
     * @brief Валидация текста
     * @param text Текст для валидации
     * @throw CipherError если текст некорректен
     */
    inline void validateText(wstring &text);

    /**
     * @brief Валидация открытого и зашифрованного текста
     * @param open_text Открытый текст
     * @param secret_text Зашифрованный текст
     * @throw CipherError если тексты некорректны
     */
    inline void validateText(wstring &open_text, wstring &secret_text);

    /**
     * @brief Валидация ключа
     * @param key Ключ
     * @param text Текст
     * @throw CipherError если ключ некорректного размера
     */
    inline void validateKey(int &key, wstring &text);
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
