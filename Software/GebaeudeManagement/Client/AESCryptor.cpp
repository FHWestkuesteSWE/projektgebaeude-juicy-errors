/****
AESCryptor.cpp

(c) Kristina Schädler 2017, 2019
****/

#include "pch.h"
#include "AESCryptor.h"
#include <cryptlib.h>
#include <filters.h>
#include <files.h>
#include <osrng.h>
#include <aes.h>
#include <hex.h>
using namespace CryptoPP;
using namespace std;

/*
Schluessel wird von Datei keypath
*/
AESCryptor::AESCryptor(const char* keypath)
{
    struct stat info; 
    int ret = stat(keypath, &info);

    if (!ret) {
      // file exists
      FileSource( keypath, true, new HexDecoder( new StringSink( keys ) ) ); 
    }
    else {
      // file doesn't exist
      //CreateOrUseOther ()
      int choice = 0;
      do {
        std::cout << "\n----------------------------------------------------\n";
        std::cout << "Keyfile for encrypting log file does not exist.\n\n";
        std::cout << "(1)\tCreate '" << keypath << "'\n";
        std::cout << "(2)\tUse other key file\n";
        std::cout << "----------------------------------------------------\n";
        std::cout << "Choice: ";
        std::cin >> choice;
      } while (choice < 1 || choice > 2);

      if (choice == 1) {
        // generate key
        GenerateSaveKeys (keypath); 
        // load new key
        FileSource( keypath, true, new HexDecoder( new StringSink( keys ) ) ); 
      }
      else if (choice == 2) {
        char newkeypath[1024];
        std::cout << "\n----------------------------------------------------\n";
        std::cout << "Enter full path and file name of key:\n";
        std::cout << "----------------------------------------------------\n";
        std::cout << "> ";
        std::cin >> newkeypath; 

        ret = stat(keypath, &info);
        if (!ret) {
          // file exists
          std::cout << "\n----------------------------------------------------\n";
          std::cout << "Loading key file '" << newkeypath << "'...\n";
          std::cout << "----------------------------------------------------\n";
          // load key
          FileSource( newkeypath, true, new HexDecoder( new StringSink( keys ) ) ); 
        }
        else {
          // file does not exist
          std::cout << "\n----------------------------------------------------\n";
          std::cout << "Generating new key file '" << newkeypath << "'...\n";
          std::cout << "----------------------------------------------------\n";
          // generate key
          GenerateSaveKeys (newkeypath); 
          // load key 
          FileSource( newkeypath, true, new HexDecoder( new StringSink( keys ) ) ); 
        }
      } // end: choice == 2
    } // end: file doesn't exist
}

/*
Erzeugt Schluessel und speichert ihn in Datei keypath
*/
void AESCryptor::GenerateSaveKeys(const char* keypath)
{
    // Erzeuge zufälligen Schlüssel
    AutoSeededRandomPool prng;
    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock( key, key.size() );
    // Speichere Schlüssel hex-codiert in Datei
    HexEncoder encoder;
    encoder.Attach( new CryptoPP::FileSink( keypath ) );
    encoder.Put( key, key.size());
    encoder.MessageEnd(); 
}

/*
Gibt AES-kodierten string zurück
*/
std::string AESCryptor::Encode(std::string s)
{
  AutoSeededRandomPool prng;

  // Generate IV
  byte iv[AES::BLOCKSIZE];
  prng.GenerateBlock(iv, sizeof(iv));
    CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption e;
  e.SetKeyWithIV((const byte*)keys.data(), AES::DEFAULT_KEYLENGTH, iv);
    // Verschluesseln: "Filtere" s durch Verschlüsseler e und speichere Ergebnis in
    // encoded
    std::string encoded;
    StringSource source(s, true,
      new StreamTransformationFilter(e, // Behandle Block-Chiffre wie Stream
        new StringSink(encoded)
      )
    );

    // Speichere iv und verschüsselten String hexcodiert in hex
    std::string hex;
    HexEncoder encoder;
    encoder.Attach(new StringSink(hex));
  encoder.Put(iv, sizeof(iv));
  encoder.Put((const byte*)encoded.data(), encoded.size());
    encoder.MessageEnd();
    return hex;
}

/*
Gibt AES-dekodierten string zurück
*/
std::string AESCryptor::Decode(std::string hex)
{

    // Hex-decode
    std::string s;
    HexDecoder decoder;
    decoder.Attach( new StringSink( s ) );
    decoder.Put( (const byte*)hex.data(),hex.size()  );
    decoder.MessageEnd();

    // IV abtrennen
    std::string ivs=s.substr(0,AES::BLOCKSIZE);
  CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption d;
  d.SetKeyWithIV((const byte*)keys.data(), AES::DEFAULT_KEYLENGTH, (const byte*)ivs.data(), AES::BLOCKSIZE);

    // Entschluesseln
    std::string decoded;
    StringSource source(s.substr(AES::BLOCKSIZE), true,
      new StreamTransformationFilter(d, // Behandle Block-Chiffre wie Stream
        new StringSink(decoded)
      )
    );
  return decoded;
}


int AESCryptor::decryptFile ( const char * filename, char * logfile )
{
  std::ifstream encrFile ( filename ); // original encrypted log file
  std::stringstream encrLog; // encrypted file contents
  encrLog << encrFile.rdbuf();
  encrFile.close();

  std::stringstream clearLog; // clear file contents
  std::ofstream clearFile; // temporary clear text file
  clearFile.open( (TEMPFILE) ); 
  clearLog << Decode (encrLog.str()).c_str();
  clearFile << clearLog.rdbuf();
  clearFile.close();

  strcpy (logfile, TEMPFILE); // return file that can be written to

  return 0; 
}

int AESCryptor::encryptFile ( const char * filename )
{
  std::ifstream clearFile (TEMPFILE); // temporary clear text file
  std::stringstream clearLog; // clear file contents
  clearLog << clearFile.rdbuf();
  clearFile.close();

  std::stringstream encrLog; // encrypted file contents
  std::ofstream encrFile;
  encrFile.open ( filename ); // encrypted log file

  encrLog << Encode (clearLog.str()).c_str();
  encrFile << encrLog.rdbuf();
  encrFile.close(); 

  // delete clear log file
  remove (TEMPFILE);

  return 0; 
}

