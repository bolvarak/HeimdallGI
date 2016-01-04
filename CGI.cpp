///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "CGI.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Globals //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CGI* CGI::mInstance                    = NULL;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constants ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString CGI::ContentImageGIF           = "image/gif";
	QString CGI::ContentImageJPEG          = "image/jpeg";
	QString CGI::ContentImageJPG           = "image/jpg";
	QString CGI::ContentImagePNG           = "image/png";
	QString CGI::ContentImageSVG           = "image/svg+xml";
	QString CGI::ContentImageTIFF          = "image/tiff";
	QString CGI::ContentFont               = "application/font";
	QString CGI::ContentFontEOT            = "application/vnd.ms-fontobject";
	QString CGI::ContentFontOTF            = "font/opentype";
	QString CGI::ContentFontTTF            = "font/ttf";
	QString CGI::ContentFontWOFF           = "font/woff";
	QString CGI::ContentScriptECMAS        = "text/ecmascript";
	QString CGI::ContentScriptVB           = "text/vbscript";
	QString CGI::ContentTypeCSS            = "text/css";
	QString CGI::ContentTypeHTML           = "text/html";
	QString CGI::ContentTypeJS             = "text/javascript";
	QString CGI::ContentTypeJSON           = "application/json";
	QString CGI::ContentTypeText           = "text/plain";
	QString CGI::ContentTypeXML            = "text/xml";
	QString CGI::HeaderComSpec             = "COMSPEC";
	QString CGI::HeaderDocumentRoot        = "DOCUMENT_ROOT";
	QString CGI::HeaderGatewayInterface    = "GATEWAY_INTERFACE";
	QString CGI::HeaderHttpAccept          = "HTTP_ACCEPT";
	QString CGI::HeaderHttpAcceptEncoding  = "HTTP_ACCEPT_ENCODING";
	QString CGI::HeaderHttpAcceptLanguage  = "HTTP_ACCEPT_LANGUAGE";
	QString CGI::HeaderHttpConnection      = "HTTP_CONNECTION";
	QString CGI::HeaderHttpCookie          = "HTTP_COOKIE";
	QString CGI::HeaderHttpHost            = "HTTP_HOST";
	QString CGI::HeaderHttpUserAgent       = "HTTP_USER_AGENT";
	QString CGI::HeaderPath                = "PATH";
	QString CGI::HeaderQueryString         = "QUERY_STRING";
	QString CGI::HeaderRemoteAddress       = "REMOTE_ADDR";
	QString CGI::HeaderRemotePort          = "REMOTE_PORT";
	QString CGI::HeaderRequestMethod       = "REQUEST_METHOD";
	QString CGI::HeaderRequestUri          = "REQUEST_URI";
	QString CGI::HeaderScriptFilename      = "SCRIPT_FILENAME";
	QString CGI::HeaderScriptName          = "SCRIPT_NAME";
	QString CGI::HeaderServerAddress       = "SERVER_ADDR";
	QString CGI::HeaderServerAdministrator = "SERVER_ADMIN";
	QString CGI::HeaderServerName          = "SERVER_NAME";
	QString CGI::HeaderServerPort          = "SERVER_PORT";
	QString CGI::HeaderServerProtocol      = "SERVER_PROTOCOL";
	QString CGI::HeaderServerSignature     = "SERVER_SIGNATURE";
	QString CGI::HeaderServerSoftware      = "SERVER_SOFTWARE";
	QString CGI::HeaderStatusOK            = "200 OK";
	QString CGI::MethodDelete              = "DELETE";
	QString CGI::MethodGet                 = "GET";
	QString CGI::MethodHead                = "HEAD";
	QString CGI::MethodPost                = "POST";
	QString CGI::MethodPut                 = "PUT";

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Singleton ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CGI* CGI::Instance(bool bReset, QObject* qoParent) {
	  // Check for an existing instance or a reset notification
		if ((mInstance == NULL) || (bReset == true)) {
			// Create a new instance
			mInstance = new CGI(qoParent);
		}
		// Return the instance
		return mInstance;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CGI::CGI(QObject* qoParent) : QObject(qoParent) {
		// Process the request and return
		this
			->processHeaders() // Headers
			->processCookies() // Cookies
			->processGet()     // Query String
			->processPost();   // POST data
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CGI* CGI::processCookies() {
		// Load the cookies
		QString strCookies = this->mRequestHeaders.value(CGI::HeaderHttpCookie);
		// Check for cookies
		if (!strCookies.isEmpty()) {
			// Set the cookies into the instance
			this->mCookies = this->decodeQuery(strCookies, ";");
		}
		// Return the instance
		return this;
	}

	CGI* CGI::processGet() {
		// Load the Query String
		QString strQuery = this->mRequestHeaders.value(CGI::HeaderQueryString);
		// Check for a query string
		if (!strQuery.isEmpty()) {
			// Set the GET variables into the instance
			this->mGetParameters = this->decodeQuery(strQuery);
		}
		// Return the instance
		return this;
	}

	CGI* CGI::processHeaders() {
		// Add the DOCUMENT_ROOT header
		this->mRequestHeaders.insert(CGI::HeaderDocumentRoot,        QString(qgetenv(CGI::HeaderDocumentRoot.toLatin1().data())));
		// Add the GATEWAY_INTERFACE header
		this->mRequestHeaders.insert(CGI::HeaderGatewayInterface,    QString(qgetenv(CGI::HeaderGatewayInterface.toLatin1().data())));
		// Add the HTTP_ACCEPT header
		this->mRequestHeaders.insert(CGI::HeaderHttpAccept,          QString(qgetenv(CGI::HeaderHttpAccept.toLatin1().data())));
		// Add the HTTP_ACCEPT_ENCODING header
		this->mRequestHeaders.insert(CGI::HeaderHttpAcceptEncoding,  QString(qgetenv(CGI::HeaderHttpAcceptEncoding.toLatin1().data())));
		// Add the HTTP_ACCEPT_LANGUAGE header
		this->mRequestHeaders.insert(CGI::HeaderHttpAcceptLanguage,  QString(qgetenv(CGI::HeaderHttpAcceptLanguage.toLatin1().data())));
		// Add the HTTP_CONNECTION header
		this->mRequestHeaders.insert(CGI::HeaderHttpConnection,      QString(qgetenv(CGI::HeaderHttpConnection.toLatin1().data())));
		// Add the HTTP_COOKIE header
		this->mRequestHeaders.insert(CGI::HeaderHttpCookie,          QString(qgetenv(CGI::HeaderHttpCookie.toLatin1().data())));
		// Add the HTTP_HOST header
		this->mRequestHeaders.insert(CGI::HeaderHttpHost,            QString(qgetenv(CGI::HeaderHttpHost.toLatin1().data())));
		// Add the HTTP_USER_AGENT header
		this->mRequestHeaders.insert(CGI::HeaderHttpUserAgent,       QString(qgetenv(CGI::HeaderHttpUserAgent.toLatin1().data())));
		// Add the PATH header
		this->mRequestHeaders.insert(CGI::HeaderPath,                QString(qgetenv(CGI::HeaderPath.toLatin1().data())));
		// Add the QUERY_STRING header
		this->mRequestHeaders.insert(CGI::HeaderQueryString,         QString(qgetenv(CGI::HeaderQueryString.toLatin1().data())));
		// Add the REMOTE_ADDR header
		this->mRequestHeaders.insert(CGI::HeaderRemoteAddress,       QString(getenv(CGI::HeaderRemoteAddress.toLatin1().data())));
		// Add the REMOTE_PORT header
		this->mRequestHeaders.insert(CGI::HeaderRemotePort,          QString(qgetenv(CGI::HeaderRemotePort.toLatin1().data())));
		// Add the REQUEST_METHOD header
		this->mRequestHeaders.insert(CGI::HeaderRequestMethod,       QString(qgetenv(CGI::HeaderRequestMethod.toUpper().toLatin1().data())));
		// Add the REQUEST_URI header
		this->mRequestHeaders.insert(CGI::HeaderRequestUri,          QString(qgetenv(CGI::HeaderRequestUri.toLatin1().data())));
		// Add the SCRIPT_FILENAME header
		this->mRequestHeaders.insert(CGI::HeaderScriptFilename,      QString(qgetenv(CGI::HeaderScriptFilename.toLatin1().data())));
		// Add the SCRIPT_NAME header
		this->mRequestHeaders.insert(CGI::HeaderScriptName,          QString(qgetenv(CGI::HeaderScriptName.toLatin1().data())));
		// Add the SERVER_ADDR header
		this->mRequestHeaders.insert(CGI::HeaderServerAddress,       QString(qgetenv(CGI::HeaderServerAddress.toLatin1().data())));
		// Add the SERVER_ADMIN header
		this->mRequestHeaders.insert(CGI::HeaderServerAdministrator, QString(qgetenv(CGI::HeaderServerAdministrator.toLatin1().data())));
		// Add the SERVER_NAME header
		this->mRequestHeaders.insert(CGI::HeaderServerName,          QString(qgetenv(CGI::HeaderServerName.toLatin1().data())));
		// Add the SERVER_PORT header
		this->mRequestHeaders.insert(CGI::HeaderServerPort,          QString(qgetenv(CGI::HeaderServerPort.toLatin1().data())));
		// Add the SERVER_PROTOCOL header
		this->mRequestHeaders.insert(CGI::HeaderServerProtocol,      QString(qgetenv(CGI::HeaderServerProtocol.toLatin1().data())));
		// Add the SERVER_SIGNATURE header
		this->mRequestHeaders.insert(CGI::HeaderServerSignature,     QString(qgetenv(CGI::HeaderServerSignature.toLatin1().data())));
		// Add the SERVER_SOFTWARE header
		this->mRequestHeaders.insert(CGI::HeaderServerSoftware,      QString(qgetenv(CGI::HeaderServerSoftware.toLatin1().data())));
		// Return the instance
		return this;
	}

	CGI* CGI::processPost() {
		// Make sure this is a POST request
		if (this->mRequestHeaders.value(CGI::HeaderRequestMethod).toUpper() == CGI::MethodPost) {
			// Create the post data placeholder
			std::string strPostData;
			// Loop throug the POST lines
			std::getline(std::cin, strPostData);
			// Make sure we don't have an empty POST set
			if (QString::fromStdString(strPostData).isEmpty()) {
				// We're done
				return this;
			}
			// Check for JSON
			if (this->isJson(QString::fromStdString(strPostData))) {
				// Create the JSON document
				// Set the error
				QJsonParseError* qjpError;
				// Try to decode the JSON
				QJsonDocument qjdData = QJsonDocument::fromJson(QString::fromStdString(strPostData).toLatin1(), qjpError);
				// Set the POST data
				this->mPostParameters = qjdData.toVariant().toMap();
			}  else {
				// Set the POST data into the instance
				this->mPostParameters = this->decodeQuery(QString::fromStdString(strPostData));
			}
		}
		// Return the instance
		return this;
	}

	CGI* CGI::sendContent() {
		// Write the content
		std::cout << this->mContent.toStdString().c_str() << std::endl;
		// Return the instance
		return this;
	}

	CGI* CGI::sendHeaders(QString strContentType) {
		// Add the OK header
		this->addResponseHeader("Status", CGI::HeaderStatusOK);
		// Set the content type
		this->addResponseHeader("Content-Type", (strContentType.isEmpty() ? this->mContentType : strContentType));
		// Add the content length header
		this->addResponseHeader("Content-Length", QString::number(this->mContent.length()));
		// Iterate over the headers
		for (QMap<QString, QString>::const_iterator itrHeaders = (this->mResponseHeaders.end() - 1); itrHeaders != 0; --itrHeaders) {
			// Print the header
			std::cout << itrHeaders.key().toStdString().c_str() << ": " << itrHeaders.value().toStdString().c_str() << "\r\n";
		}
		// Iterate over the cookies
		for (int intCookie = 0; intCookie < this->mNewCookies.size(); ++intCookie) {
			// Localize the cookie
			Cookie structNewCookie = this->mNewCookies.at(intCookie);
			// Send the cookie to the browser
			std::cout << structNewCookie.toHeaderValue().toStdString().c_str() << "\r\n";
		}
		// Send an extra newline
		std::cout << "\r\n";
		// Return the instance
		return this;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CGI* CGI::addCookie(QString strName, QString strValue, QDateTime qdtExpiration, QString strDomain, QString strPath, bool bHttpOnly, bool bSecure) {
		// Iterate over the existing new cookies
		for (int intCookie = 0; intCookie < this->mNewCookies.size(); ++intCookie) {
			// Localize the cookie
			Cookie structNewCookie = this->mNewCookies.at(intCookie);
			// Check the name
			if (structNewCookie.getName() == strName) {
				// Delete the cookie
				this->mNewCookies.removeAt(intCookie);
				// We're done
				break;
			}
		}
		// Create the new structure
		Cookie structNewCookie(strName, strValue, qdtExpiration, strDomain, strPath, bHttpOnly, bSecure);
		// Add the cookie to the instance
		this->mNewCookies.append(structNewCookie);
		// Return the instance
		return this;
	}

	CGI* CGI::addParameter(QString strName, QString strValue) {
		// Add the value to the GET parameters
		this->mGetParameters.insert(strName, QUrl::fromPercentEncoding(strValue.replace("+", " ").toLatin1()));
		// Return the instance
		return this;
	}

	/**
	 * @paragraph This method sets a response header into the instance
	 * @brief CGI::AddResponseHeader()
	 * @param QString strName
	 * @param QString strValue
	 * @return CGI* CGI::mInstance
	 */
	CGI* CGI::addResponseHeader(QString strName, QString strValue) {
		// Set the response header into the instance
		this->mResponseHeaders.insert(strName, strValue);
		// Return the instance
		return this;
	}

	CGI* CGI::addStackEntry(QString strFilename, int intLineNumber, QString strSnippet) {
		// Create the stack entry structure
		StackEntry structStackEntry(strFilename, intLineNumber, strSnippet);
		// Add the entry to the instance
		this->mCallStack.append(structStackEntry);
		// Return the instance
		return this;
	}

	CGI* CGI::appendToContent(QString strContent) {
		// Append the content
		this->mContent.append(strContent);
		// We're done
		return this;
	}

	QVariantMap CGI::decodeQuery(QString strQuery, QString strPairSeparator) {
		// Create the map placeholder
		QVariantMap qvmQuery;
		// Split the parameters
		QStringList qslParameters = strQuery.split(strPairSeparator);
		// Loop through the parameters
		foreach (QString strPair, qslParameters) {
			// Split the key/value pair
			QStringList qslPair = strPair.split("=");
			// Set the pair into the map
			qvmQuery.insert(QUrl::fromPercentEncoding(qslPair.at(0).toLatin1()).replace("+", " "), QUrl::fromPercentEncoding(qslPair.at(1).toLatin1()).replace("+", " "));
		}
		// Return the map
		return qvmQuery;
	}

	CGI* CGI::deleteCookie(QString strName, bool &bSuccess) {
		// Iterate over the new cookies
		for (int intCookie = 0; intCookie < this->mNewCookies.size(); ++intCookie) {
			// Localize the structure
			Cookie structCookie = this->mNewCookies.at(intCookie);
			// Check the name of the cookie
			if (structCookie.getName() == strName) {
				// Delete the cookie
				this->mNewCookies.removeAt(intCookie);
				// Set the success boolean
				bSuccess = true;
				// We're done
				return this;
			}
		}
		// Check the cookie map
		if (this->mCookies.contains(strName)) {
			// Remove the cookie from the map
			if (this->mCookies.remove(strName) > 0) {
				// Create the date time object
				QDateTime qdtExpiration;
				// Set the timestamp
				qdtExpiration.setTime_t(0);
				// Add the cookie to the new cookies to be deleted
				this->addCookie(strName, "", qdtExpiration);
				// Set the success boolean
				bSuccess = true;
				// We're done
				return this;
			}
		}
		// Set the success boolean
		bSuccess = false;
		// Return the instance
		return this;
	}

	QString CGI::encodeQuery(QMap<QString, QString> qmQuery, QString strPairGlue) {
		// Create the query placeholder
		QStringList qslQuery;
		// Loop through the parameters
		foreach (QString strKey, qmQuery) {
			// Create the pair list
			QStringList qslPair;
			// Add the key
			qslPair.append(QString(QUrl::toPercentEncoding(strKey)).replace(" ", "+"));
			// Add the value
			qslPair.append(QString(QUrl::toPercentEncoding(qmQuery.value(strKey))).replace(" ", "+"));
			// Append the pair to the query string
			qslQuery.append(qslPair.join("="));
		}
		// Return the query string
		return qslQuery.join(strPairGlue);
	}

	QString CGI::encodeQuery(QVariantMap qvmQuery, QString strPairGlue) {
		// Create the query placeholder
		QStringList qslQuery;
		// Loop through the parameters
		foreach (QString strKey, qvmQuery.keys()) {
			// Create the pair list
			QStringList qslPair;
			// Add the keyt
			qslPair.append(QString(QUrl::toPercentEncoding(strKey)).replace(" ", "+"));
			// Add the valie
			qslPair.append(QString(QUrl::toPercentEncoding(qvmQuery.value(strKey).toString())).replace(" ", "+"));
			// Append the pair to the query string
			qslQuery.append(qslPair.join("="));
		}
		// Return the query string
		return qslQuery.join(strPairGlue);
	}

	void CGI::writeResponse(QString strContentType) {
		// Write the data to the requester
		this
			->sendHeaders(strContentType) // Headers
			->sendContent();              // Content
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Determinants /////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool CGI::isJson(QString strData){
		// Set the error
		QJsonParseError* qjpError;
		// Try to decode the JSON
		QJsonDocument qjdTest = QJsonDocument::fromJson(strData.toLatin1(), qjpError);
		if (qjpError->errorString().isEmpty()) {
			// We're done
			return true;
		}
		// We're done
		return false;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString CGI::getContent() {
		// Return the content from the instance
		return this->mContent;
	}

	QVariant CGI::getCookie(QString strName) {
		// Check for the cookie
		if (this->mCookies.contains(strName)) {
			// Return the cookie
			return this->mCookies.value(strName);
		}
		// Elsewise, return null
		return QVariant(QString::null);
	}

	QVariantMap CGI::getCookies() {
		// Return the current cookie map
		return this->mCookies;
	}

	QVariant CGI::getParam(QString strName) {
		// Check for the parameter in POST
		if (this->mPostParameters.contains(strName)) {
			// Return the POST parameter
			return this->mPostParameters.value(strName);
		}
		// Check for the parameter in GET
		if (this->mGetParameters.contains(strName)) {
			// Return the GET parameter
			return this->mGetParameters.value(strName);
		}
		// Elsewise, return null
		return QVariant(QString::null);
	}

	QVariantMap CGI::getPostData() {
		// Return the POST data
		return this->mPostParameters;
	}

	QVariantMap CGI::getQueryData() {
		// Return the GET data
		return this->mGetParameters;
	}

	QString CGI::getRequestHeader(QString strName) {
		// Check to see if the request header exists
		if (this->mRequestHeaders.contains(strName)) {
			// Return the request header
			return this->mRequestHeaders.value(strName);
		}
		// Elsewise, return null
		return NULL;
	}

	QMap<QString, QString> CGI::getRequestHeaders() {
		// Return the response headers
		return this->mRequestHeaders;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setters //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CGI* CGI::setContent(QString strContent) {
		// Set the contnt into the instance
		this->mContent = strContent;
		// Return the instane
		return this;
	}

	CGI* CGI::setContentType(QString strContentType) {
		// Set the content type into the instance
		this->mContentType = strContentType;
		// Return the instance
		return this;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
