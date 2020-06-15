/****
AESCryptor.h

Klasse zum AES-Kodieren und Dekodieren von std::string
Schluessel wird auf Datei gespeichert und von Datei gelesen

(c) Kristina Schädler 2017, 2019
****/

#ifndef AESCRYPTOR_H
#define AESCRYPTOR_H

#include <string>
#include <aes.h>
#include <ccm.h>

class AESCryptor
{
    public:
        AESCryptor(const char* keypath);
        static void GenerateSaveKeys(const char* keypath);
        std::string Encode(std::string);
        std::string Decode(std::string);
    protected:
        std::string keys;
    private:
};

#endif // AESCRYPTOR_H
