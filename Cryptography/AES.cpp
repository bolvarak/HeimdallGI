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

		QVariant AES::decrypt(QByteArray strHash, bool blnFromBase64)
		{
			// Check to see if we need to decode the hash
			if (blnFromBase64) {
				// Convert the hash
				strHash = QByteArray::fromBase64(strHash);
			}
			// Initialize the underlying engine
			QCA::Initializer qciInit;
			// Set the key
			QCA::SymmetricKey cskKey(QByteArray::fromBase64(HeimdallGI::Configuration::Get("crypto.key").toByteArray()));
			// Check to see if we can use AES256-CBC
			if (!QCA::isSupported("aes256-cbc-pkcs7")) {
				// We're done
				qFatal(QString("AES256-CBC Not Supported!").toLatin1().data());
			}
			// Set the initialization vector
			QCA::InitializationVector civVector(strHash.left(32));
			// Create the cipher
			QCA::Cipher qccCipher("aes256", QCA::Cipher::CBC, QCA::Cipher::DefaultPadding, QCA::Decode, cskKey, civVector);
			// Localize the cipher text
			QCA::SecureArray qsaCipherText(strHash.remove(0, 32));
			// Decrypt the data
			qsaCipherText = qccCipher.process(qsaCipherText);
			// Make sure we're good to go
			if (!qccCipher.ok()) {
				// We're done
				qFatal(QString("[ERROR]:  Unable to decrypt cipher text!").toLatin1().data());
			}
			// We're done
			return QVariant(qsaCipherText.toByteArray());
		}

		QByteArray AES::encrypt(QVariant mixData, bool blnToBase64)
		{
			// Initialize the underlying engine
			QCA::Initializer qciInit;
			// Convert the data
			QCA::SecureArray qsaSource(mixData.toByteArray());
			// Check to see if we can use AES256-CBC
			if (!QCA::isSupported("aes256-cbc-pkcs7")) {
				// We're done
				qFatal(QString("AES256-CBC Not Supported!").toLatin1().data());
			}
			// Create the symmetry key
			QCA::SymmetricKey cskKey(QByteArray::fromBase64(HeimdallGI::Configuration::Get("crypto.key").toByteArray()));
			// Create the initialization vector
			QCA::InitializationVector civVetor(32);
			// Create the cipher
			QCA::Cipher qccCipher("aes256", QCA::Cipher::CBC, QCA::Cipher::DefaultPadding, QCA::Encode, cskKey, civVetor);
			// Create the hash placeholder
			QCA::SecureArray csaHash;
			// Encrypt the data
			csaHash = qccCipher.process(qsaSource);
			// Check to see if the encryption succeeded
			if (!qccCipher.ok()) {
				// We're done
				qFatal(QString("[ERROR]:  Unable to encrypt source data!").toLatin1().data());
			}
			// Determine the return data
			if (blnToBase64) {
				// Return the hash
				return csaHash.toByteArray().prepend(civVetor.toByteArray()).toBase64();
			}
			// Return the hash
			return csaHash.toByteArray().prepend(civVetor.toByteArray());
		}

		QVariant AES::recursiveDecrypt(QByteArray strHash, int64_t intRecursion, bool blnFromBase64)
		{
			// Check the recursion
			if (intRecursion == 1) {
				// Simply return the single pass decryption
				return decrypt(strHash, blnFromBase64);
			}
			// Check the decoding flag
			if (blnFromBase64) {
				// Reset the hash
				strHash = QByteArray::fromBase64(strHash);
			}
			// Iterate to recursion
			for (int intIterator = 0; intIterator < intRecursion; ++intIterator) {
				// Reset the hash
				strHash = decrypt(strHash, false).toByteArray();
			}
			// Return the decrypted data
			return QVariant(strHash);
		}

		QByteArray AES::recursiveEncrypt(QVariant mixData, int64_t intRecursion, bool blnToBase64)
		{
			// Check the recursion
			if (intRecursion == 1) {
				// Simply return the single pass encryption
				return encrypt(mixData, blnToBase64);
			}
			// Iterate to recursion
			for (int intIterator = 0; intIterator < intRecursion; ++intIterator) {
				// Encrypt the data
				mixData = encrypt(mixData, false);
			}
			// Check the encoding flag
			if (blnToBase64) {
				// Return the encoded hash
				return mixData.toByteArray().toBase64();
			}
			// Return the raw hash
			return mixData.toByteArray();
		}

	///////////////////////////////////////////////////////////////////////////
	/// End Cryptography Namespace ///////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	}

///////////////////////////////////////////////////////////////////////////////
/// End HeimdallGI Namespace /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

}
