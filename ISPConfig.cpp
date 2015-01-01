///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "ISPConfig.h"

///////////////////////////////////////////////////////////////////////////////
/// HeimdallGI Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////
	/// Globals //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	ISPConfig* mInstance = NULL;

	///////////////////////////////////////////////////////////////////////////
	/// Singleton ////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	ISPConfig* ISPConfig::Instance(bool blnReset) {
		// Check for an existing instance or a reset flag
		if ((mInstance == NULL) || (blnReset == true)) {
			// Create a new instance
			mInstance = new ISPConfig;
		}
		// Return the instance
		return mInstance;
	}

	///////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	ISPConfig::ISPConfig(QObject *qoParent) : QObject(qoParent) {
		// Connect the response signal
		connect(&mConnection, SIGNAL(finished(QNetworkReply*)), this, SLOT(getJsonResponse(QNetworkReply*)));
		// Default the error flag
		this->mErrorFlag       = false;
		// Default the error message
		this->mErrorMessage    = QString::null;
		// Default the secure transport flag
		this->mSecureTransport = false;
	}

	///////////////////////////////////////////////////////////////////////////
	/// Destructor ///////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	ISPConfig::~ISPConfig() {}

	///////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	void ISPConfig::makeRequest(QString strMethod, QVariantMap qvmArguments) {
		// Reset the error state
		this->mErrorFlag    = false;
		this->mErrorMessage = QString::null;
		// Define the URL
		QUrl urlEndpoint(Configuration::Get("ispConfig.endpoint").toString());
		// Create the query string
		QUrlQuery qryEndpoint;
		// Add the method to the query
		qryEndpoint.addQueryItem("method", QString::fromLatin1(QUrl::toPercentEncoding(strMethod)));
		// Create the request
		QNetworkRequest qnrRequest(urlEndpoint);
		// Make the request
		this->mConnection.post(qnrRequest, this->mapToQuery(qvmArguments));
	}

	QByteArray ISPConfig::mapToQuery(QVariantMap qvmParameters) {
		// Create the parameter placeholder
		QStringList qslParams;
		// Iterate over the parameters
		for (QVariantMap::const_iterator itrParameter = qvmParameters.constBegin(); itrParameter != qvmParameters.constEnd(); ++itrParameter) {
			// Add the parameter
			qslParams.append(QString("%1=%2").arg(QString::fromLatin1(QUrl::toPercentEncoding(itrParameter.key())), QString::fromLatin1(QUrl::toPercentEncoding(itrParameter.value().toString()))));
		}
		// We're done
		return qslParams.join("&").toLatin1();
	}

	void ISPConfig::processLoginResponse() {
		// Define the sessionID
		QString strSessionID = this->mResponse.value("response").toString();
		// Clear the response
		this->mResponse.remove("response");
		// Set the session ID
		this->mResponse.insert("sessionID", strSessionID);
		// Set the logged in status
		this->mResponse.insert("loggedIn",  true);
		// We're done
		return;
	}

	void ISPConfig::processLogoutResponse() {
		// Set the logout status
		this->mResponse.insert("loggedOut", this->mResponse.value("response").toBool());
		// Clear the response
		this->mResponse.remove("response");
		// We're done
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	/// Protected Slots //////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	void ISPConfig::getJsonResponse(QNetworkReply* qnrResponse) {
		// Check for an error
		if (qnrResponse->error() != QNetworkReply::NoError) {
			// A network error has occurred, fire the signal
			emit this->networkError(qnrResponse->error(), qnrResponse->errorString());
			// We're done
			return;
		}
		// Decode the response
		QJsonDocument qjdResponse = QJsonDocument::fromJson(qnrResponse->readAll());
		// Store the response
		this->mResponse           = qjdResponse.object().toVariantMap();
		// Check for an API error
		if (this->mResponse.contains("error") && (this->mResponse.value("success").toBool() == false)) {
			// An API error has occurred, fire the signal
			emit this->apiError(this->mResponse.value("code").toString(), this->mResponse.value("error").toString());
			// We're done
			return;
		}
		// Determine the method
		switch(this->mCurrentMethod) {
			// Login
			case JsonMethod::Login  : return this->processLoginResponse();  break;
			// Logout
			case JsonMethod::Logout : return this->processLogoutResponse(); break;
		}
		// Fire the ready signal
		emit responseReady(this->mResponse);
		// We're done
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	void ISPConfig::endSession(QString strSessionID) {
		// Create the parameter map
		QVariantMap qvmArguments;
		// Add the session_id
		qvmArguments.insert("session_id", strSessionID);
		// Make the request
		this->makeRequest("logout", qvmArguments);
		// We're done
		return;
	}

	void ISPConfig::startSession() {
		// Create the parameter map
		QVariantMap qvmArguments;
		// Add the username
		qvmArguments.insert("username", Configuration::Get("ispConfig.userName").toString());
		// Add the password
		qvmArguments.insert("password", Configuration::Get("ispConfig.passWord").toString());
		// Make the request
		this->makeRequest("login", qvmArguments);
		// We're done
		return;
	}

///////////////////////////////////////////////////////////////////////////////
/// End HeimdallGI Namespace /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

}

