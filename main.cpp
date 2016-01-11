#include "iostream"
#include "QtCore/QByteArray"
#include "QtCore/QString"
#include "QtCore/QVariant"
#include "Cryptography/AES.h"
#include "Pool/Database.h"
#include "Abstract/PgModel.h"

int main(int intArguments, char **chrArguments)
{
	// Encrypt some data
	QByteArray strHash = HeimdallGI::Cryptography::AES::recursiveEncrypt("itsMe123!!!#", 100, false);
	// Output the encryption
	std::cout << std::endl << std::endl << "[Encrypting itsMe123!!!#]:  " << strHash.data() << std::endl << std::endl;
	// Output the decryption
	std::cout << std::endl << std::endl << "[Decrypting]:  " << HeimdallGI::Cryptography::AES::recursiveDecrypt(strHash, 100, false).toByteArray().data() << std::endl << std::endl;
	// We're done
	return 0;
}