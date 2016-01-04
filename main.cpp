#include "iostream"
#include "QtCore/QByteArray"
#include "QtCore/QString"
#include "QtCore/QVariant"
#include "Pool/Database.h"
#include "Abstract/PgModel.h"

int main(int intArguments, char **chrArguments)
{
	// Add the connection to the database pool
	HeimdallGI::Pool::Database::add("QPSQL", "localhost", 5432, "someDatabase", "someUser", "somePass", "someDatabaseConnection");
	// Create a new model
	HeimdallGI::Abstract::PgModel* modDB = new HeimdallGI::Abstract::PgModel();
	// Set the database connection
	modDB->setConnection(HeimdallGI::Pool::Database::get("ArchCP"));
	// Encrypt the data
	QString strEncryption = modDB->encrypt("itsMe123!!!#", "fubar", 25);
	// Output the UUID
	std::cout << std::endl << std::endl << "[UUID]:  " << modDB->uuid().toByteArray().constData() << std::endl << std::endl;
	// Output the encryption
	std::cout << std::endl << std::endl << "[Encrypting itsMe123!!!#]:  " << strEncryption.toLatin1().data() << std::endl << std::endl;
	// Output the decryption
	std::cout << std::endl << std::endl << "[Decrypting]:  " << modDB->decrypt(strEncryption, "fubar", 25).toByteArray().data() << std::endl << std::endl;
	// We're done
	return 0;
}