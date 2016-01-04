///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "AES.h"

///////////////////////////////////////////////////////////////////////////////
/// HeimdallGI Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI
{
	///////////////////////////////////////////////////////////////////////////
	/// Cryptography Namespace ///////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	namespace Cryptography
	{
		///////////////////////////////////////////////////////////////////////
		/// Public Static Methods ////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		QVariant AES::decrypt(QString strHash, int intRecursion)
		{
			// Convert the hash
			strHash = QString(QByteArray::fromBase64(strHash.toLatin1()));
			// Split the hash
			QStringList qslParts = strHash.split("]::[");
			// Make sure we have three parts
			if (qslParts.size() != 3) {
				// We're done
				qFatal(QString("Hash is invalid!").toLatin1().data());
			}
			// Initialize the underlying engine
			QCA::Initializer qciInit;
			// Set the key
			QCA::SymmetricKey cskKey(qslParts.at(1).toLatin1());
			// Check to see if we can use AES256-CBC
			if (!QCA::isSupported("aes256-cbc-pkcs7")) {
				// We're done
				qFatal(QString("AES256-CBC Not Supported!").toLatin1().data());
			}
			// Set the initialization vector
			QCA::InitializationVector civVector(qslParts.at(2).toLatin1());
			// Create the cipher
			QCA::Cipher qccCipher("aes256", QCA::Cipher::CBC, QCA::Cipher::DefaultPadding, QCA::Decode, cskKey, civVector);
			// Localize the cipher text
			QCA::SecureArray qsaCipherText(qslParts.at(0).toLatin1());
			// Iterate to recursion
			for (int intIterator = 0; intIterator < intRecursion; ++intIterator) {
				// Decrypt the data
				qsaCipherText = qccCipher.update(qsaCipherText);
				// Make sure we're good to go
				if (!qccCipher.ok()) {
					// We're done
					qFatal(QString("[Iteration %1]:  Unable to decrypt cipher text!").arg(intIterator + 1).toLatin1().data());
				}
			}
			// Finalize the hash
			qsaCipherText = qccCipher.final();
			// Make sure everything went according to plan
			if (!qccCipher.ok()) {
				// We're done
				qFatal(QString("Plain Text finalization failed!").toLatin1().data());
			}
			// We're done
			return QVariant(qsaCipherText.toByteArray());
		}

		QString AES::encrypt(QVariant mixData, int intRecursion)
		{
			// Initialize the underlying engine
			QCA::Initializer qciInit;
			// Convert the data
			QCA::SecureArray qsaSource = mixData.toByteArray().data();
			// Check to see if we can use AES256-CBC
			if (!QCA::isSupported("aes256-cbc-pkcs7")) {
				// We're done
				qFatal(QString("AES256-CBC Not Supported!").toLatin1().data());
			}
			// Create the symmetry key
			QCA::SymmetricKey cskKey(32);
			// Create the initialization vector
			QCA::InitializationVector civVetor(32);
			// Create the cipher
			QCA::Cipher qccCipher("aes256", QCA::Cipher::CBC, QCA::Cipher::DefaultPadding, QCA::Encode, cskKey, civVetor);
			// Create the hash placeholder
			QCA::SecureArray csaHash;
			// Iterate to recursion
			for (int intIterator = 0; intIterator < intRecursion; ++intIterator) {
				// Encrypt the data
				csaHash = qccCipher.update(qsaSource);
				// Check to see if the encryption succeeded
				if (!qccCipher.ok()) {
					// We're done
					qFatal(QString("[Iteration %1]:  Unable to encrypt source data!").arg(intIterator + 1).toLatin1().data());
				}
			}
			// Grab the final hash
			csaHash = qccCipher.final();
			// Make sure everything went according to plan
			if (!qccCipher.ok()) {
				// We're done
				qFatal(QString("Hash finalization failed!").toLatin1().data());
			}
			// Return the hash
			return QString(QString("%1]::[%2]::[%3").arg(QString::fromLatin1(csaHash.toByteArray()), QString::fromLatin1(cskKey.toByteArray()), QString::fromLatin1(civVetor.toByteArray()).toLatin1().toBase64()));
		}

	///////////////////////////////////////////////////////////////////////////
	/// End Cryptography Namespace ///////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	}

///////////////////////////////////////////////////////////////////////////////
/// End HeimdallGI Namespace /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

}
