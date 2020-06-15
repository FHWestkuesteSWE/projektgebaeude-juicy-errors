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
    FileSource( keypath, true, new HexDecoder( new StringSink( keys ) ) );

}

/*
Erzeugt Schluessel und speichert ihn in Datei keypath
*/
void AESCryptor::GenerateSaveKeys(const char* keypath){
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
std::string AESCryptor::Encode(std::string s){
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
std::string AESCryptor::Decode(std::string hex){

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
