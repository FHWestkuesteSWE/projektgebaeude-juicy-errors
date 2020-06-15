/****
AESCryptor.h

Klasse zum AES-Kodieren und Dekodieren von std::string
Schluessel wird auf Datei gespeichert und von Datei gelesen

(c) Kristina Schädler 2017, 2019
extended by juicy errors 2020
****/

#ifndef AESCRYPTOR_H
#define AESCRYPTOR_H

#include <string>
#include <aes.h>
#include <ccm.h>

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string>

class AESCryptor
{
    public:
        AESCryptor(const char* keypath);
        static void GenerateSaveKeys(const char* keypath);
        std::string Encode(std::string);
        std::string Decode(std::string);

        // added helper functions
        int decryptFile ( const char * filename );
        int encryptFile ( const char * filename );

    protected:
        std::string keys;
    private:
};

#endif // AESCRYPTOR_H
