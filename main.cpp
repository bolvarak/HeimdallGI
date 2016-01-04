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
	QByteArray strHash = HeimdallGI::Cryptography::AES::encrypt("itsMe123!!!#");
	// Output the encryption
	std::cout << std::endl << std::endl << "[Encrypting itsMe123!!!#]:  " << strHash.data() << std::endl << std::endl;
	// Output the decryption
	std::cout << std::endl << std::endl << "[Decrypting]:  " << HeimdallGI::Cryptography::AES::decrypt(strHash).toByteArray().data() << std::endl << std::endl;
	// We're done
	return 0;
}