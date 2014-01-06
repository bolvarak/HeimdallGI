///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HeimdallGI_CGI_H
#define HeimdallGI_CGI_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QByteArray"
#include "QDebug"
#include "QMap"
#include "QObject"
#include "QString"
#include "QStringList"
#include "QUrl"
#include "QVariant"
#include "QVariantMap"
#include "iostream"
#include "string"
#include "Log.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// HeimdallGI Namespace /////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Structures ///////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct StackEntry {

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the filename
		 * @brief HeimdallGI::StackEntry::mFile
		 * @var QString
		 */
		QString mFile;

		/**
		 * @paragraph This property contains the line number
		 * @brief HeimdallGI::StackEntry::mLineNumber
		 * @var int
		 */
		int mLineNumber;

		/**
		 * @paragraph This property contains the snippet or call
		 * @brief HeimdallGI::StackEntry::mSnippet
		 */
		QString mSnippet;

		///////////////////////////////////////////////////////////////////////
		/// Constructors /////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constructor initializes and sets up a StackEntry
		 * @brief HeimdallGI::StackEntry::StackEntry()
		 * @param QString strFile
		 * @param int intLine
		 * @param QString strSnippet
		 */
		StackEntry(QString strFile, int intLine, QString strSnippet) {
			// Set the file
			mFile       = strFile;
			// Set the line number
			mLineNumber = intLine;
			// Set the snippet
			mSnippet    = strSnippet;
		}

		/**
		 * @paragraph This constructor simply initializes a StackEntry
		 * @brief HeimdallGI::StackEntry::StackEntry()
		 */
		StackEntry() {}

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the file name
		 * @brief HeimdallGI::StackEntry::getFile()
		 * @return QString HeimdallGI::StackEntry::mFile
		 */
		QString getFile() {
			// Return the filename
			return mFile;
		}

		/**
		 * @paragraph This method returns the line number
		 * @brief HeimdallGI::StackEntry::getLine()
		 * @return int HeimdallGI::StackEntry::mLineNumber
		 */
		int getLine() {
			// Return the line number
			return mLineNumber;
		}

		/**
		 * @paragraph This method returns the snippet
		 * @brief HeimdallGI::StackEntry::getSnippet()
		 * @return QString HeimdallGI::StackEntry::mSnippet
		 */
		QString getSnippet() {
			// Return the snippet
			return mSnippet;
		}

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////




	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Cgi Class Definition /////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This class handles the interaction between the web browser and the application
	 * @brief HeimdallGI::CGI
	 */
	class CGI : public QObject {
			/**
			 * Ensure this class is recognized by Qt
			 */
			Q_OBJECT

			///////////////////////////////////////////////////////////////////////////
			/// Protected Methods & Properties ///////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////

	protected:

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the singleton instance of this class
		 * @brief CGI::mInstance
		 * @var CGI*
		 */
		static CGI* mInstance;

		/**
		 * @paragraph This property contains the response content
		 * @brief CGI::mContent
		 * @var QString
		 */
		QString mContent;

		/**
		 * @paragraph This property contains the response content type
		 * @brief HeimdallGI::CGI::mContentType
		 * @var QString
		 */
		QString mContentType;

		/**
		 * @paragraph This property contains the HTTP cookies
		 * @brief CGI::mCookies
		 * @var QMap<QString, QString>
		 */
		QMap<QString, QString> mCookies;

		/**
		 * @paragraph This property contains the GET data
		 * @brief CGI::mGetParameters
		 * @var QMap<QString, QString>
		 */
		QMap<QString, QString> mGetParameters;

		/**
		 * @paragraph This property contains the POST data
		 * @brief CGI::mPostParameters
		 * @var QMap<QString, QString>
		 */
		QMap<QString, QString> mPostParameters;

		/**
		 * @paragraph This property contains the request headers from the client
		 * @brief CGI::mRequestHeaders
		 * @var QMap<QString, QString>
		 */
		QMap<QString, QString> mRequestHeaders;

		/**
		 * @paragraph This property contains the response headers to send to the client
		 * @brief CGI::mResponseHeaders
		 * @var QMap<QString, QString>
		 */
		QMap<QString, QString> mResponseHeaders;

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method processes the HTTP_COOKIE from the header
		 * @brief CGI::ProcessCookies()
		 * @return CGI* CGI::mInstance
		 */
		CGI* ProcessCookies();

		/**
		 * @paragraph This method processes the QUERY_STRING from the header
		 * @brief CGI::ProcessGet()
		 * @return CGI* CGI::mInstance
		 */
		CGI* ProcessGet();

		/**
		 * @paragraph This method processes the request headers into the instance
		 * @brief CGI::ProcessHeaders()
		 * @return CGI* CGI::mInstance
		 */
		CGI* ProcessHeaders();

		/**
		 * @paragraph This method processes the POST data into the instance
		 * @brief CGI::ProcessPost()
		 * @return CGI* CGI::mInstance
		 */
		CGI* ProcessPost();

		/**
		 * @paragraph This method writes the content to the browser/socket/stream
		 * @brief CGI::SendContent()
		 * @return CGI* CGI::mInstance
		 */
		CGI* SendContent();

		/**
		 * @paragraph This method writes the response headers to the browser/socket/stream
		 * @brief CGI::SendHeaders()
		 * @param QString strContentType [NULL]
		 * @return CGI* CGI::mInstance
		 */
		CGI* SendHeaders(QString strContentType = NULL);

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public:

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the header type for GIF
		 * @brief CGI::ContentImageGIF
		 * @var QString
		 */
		static QString ContentImageGIF;

		/**
		 * @paragraph This property contains the header type for JPEG
		 * @brief CGI::ContentImageJPEG
		 * @var QString
		 */
		static QString ContentImageJPEG;

		/**
		 * @paragraph This property contains the header type for JPG
		 * @brief CGI::ContentImageJPG
		 * @var QString
		 */
		static QString ContentImageJPG;

		/**
		 * @paragraph This property contains the header type for PNG
		 * @brief CGI::ContentImagePNG
		 * @var QString
		 */
		static QString ContentImagePNG;

		/**
		 * @paragraph Thie property contains the header type for SVG
		 * @brief CGI::ContentImageSVG
		 * @var QString
		 */
		static QString ContentImageSVG;

		/**
		 * @paragraph This property contains the header type for TIFF
		 * @brief CGI::ContentImageTIFF
		 * @var QString
		 */
		static QString ContentImageTIFF;

		/**
		 * @paragraph This property contins the header type for FONT
		 * @brief CGI::ContentFont
		 * @var QString
		 */
		static QString ContentFont;

		/**
		 * @paragraph This property contains the header type for EOT
		 * @brief CGI::ContentFontEOT
		 * @var QString
		 */
		static QString ContentFontEOT;

		/**
		 * @paragraph This property contains the header type for OTF
		 * @brief CGI::ContentFontOTF
		 * @var QString
		 */
		static QString ContentFontOTF;

		/**
		 * @paragraph This property contains the header type for TTF
		 * @brief CGI::ContentFontTTF
		 * @var QString
		 */
		static QString ContentFontTTF;

		/**
		 * @paragraph This property contains the header type for WOFF
		 * @brief CGI::ContentFontWOFF
		 * @var QString
		 */
		static QString ContentFontWOFF;

		/**
		 * @paragraph This property contains the header type for ECMAS
		 * @brief CGI::ContentScriptECMAS
		 * @var QString
		 */
		static QString ContentScriptECMAS;

		/**
		 * @paragraph This property contains the header type for VB
		 * @brief CGI::ContentScriptVB
		 * @var QString
		 */
		static QString ContentScriptVB;

		/**
		 * @paragraph This property contains the header type for CSS
		 * @brief CGI::ContentTypeCSS
		 * @var QString
		 */
		static QString ContentTypeCSS;

		/**
		 * @paragraph This property contain the header type for HTML
		 * @brief CGI::ContentTypeHTML
		 * @var QString
		 */
		static QString ContentTypeHTML;

		/**
		 * @paragraph This property contains the header type for JS
		 * @brief CGI::ContentTypeJS
		 * @var QString
		 */
		static QString ContentTypeJS;

		/**
		 * @paragraph This property contains the header type for JSON
		 * @brief CGI::ContentTypeJSON
		 * @var QString
		 */
		static QString ContentTypeJSON;

		/**
		 * @paragraph This property contains the header type for TXT
		 * @brief CGI::ContentTypeText
		 * @var QString
		 */
		static QString ContentTypeText;

		/**
		 * @paragraph This property contains the header type for XML
		 * @brief CGI::ContentTypeXML
		 * @var QString
		 */
		static QString ContentTypeXML;

		/**
		 * @paragraph This property contains the COMSPEC header name
		 * @brief CGI::HeaderComSpec
		 * @var QString
		 */
		static QString HeaderComSpec;

		/**
		 * @paragraph This property contains the DOCUMENT_ROOT header name
		 * @brief CGI::HeaderDocumentRoot
		 * @var QString
		 */
		static QString HeaderDocumentRoot;

		/**
		 * @paragraph This proeprty contains the GATEWAY_INTERFACE header name
		 * @brief CGI::HeaderGatewayInterface
		 * @var QString
		 */
		static QString HeaderGatewayInterface;

		/**
		 * @paragraph This property contains the HTTP_ACCEPT header name
		 * @brief CGI::HeaderHttpAccept
		 * @var QString
		 */
		static QString HeaderHttpAccept;

		/**
		 * @paragraph This property contains the HTTP_ACCEPT_ENCODING header name
		 * @brief CGI::HeaderHttpAcceptEncoding
		 * @var QString
		 */
		static QString HeaderHttpAcceptEncoding;

		/**
		 * @paragraph This property contains the HTTP_ACCEPT_LANGUAGE header
		 * @brief CGI::HeaderHttpAcceptLanguage
		 * @var QString
		 */
		static QString HeaderHttpAcceptLanguage;

		/**
		 * @paragraph This property contains the HTTP_CONNECTION header name
		 * @brief CGI::HeaderHttpConnection
		 * @var QString
		 */
		static QString HeaderHttpConnection;

		/**
		 * @paragraph This property contains the HTTP_COOKIE header name
		 * @brief CGI::HeaderHttpCookie
		 * @var QString
		 */
		static QString HeaderHttpCookie;

		/**
		 * @paragraph This property contains the HTTP_HOST header name
		 * @brief CGI::HeaderHttpHost
		 * @var QString
		 */
		static QString HeaderHttpHost;

		/**
		 * @paragraph This property contains the HTTP_USER_AGENT header name
		 * @brief CGI::HeaderHttpUserAgent
		 * @var QString
		 */
		static QString HeaderHttpUserAgent;

		/**
		 * @paragraph This property contains the PATH header name
		 * @brief CGI::HeaderPath
		 */
		static QString HeaderPath;

		/**
		 * @paragraph This property contains the QUERY_STRING header name
		 * @brief CGI::eaderQueryString
		 * @var QString
		 */
		static QString HeaderQueryString;

		/**
		 * @paragraph This property contains the REMOTE_ADDR header name
		 * @brief CGI::HeaderRemoteAddress
		 * @var QString
		 */
		static QString HeaderRemoteAddress;

		/**
		 * @paragraph This property contain the REMOTE_PORT header name
		 * @brief CGI::HeaderRemotePort
		 * @var QString
		 */
		static QString HeaderRemotePort;

		/**
		 * @paragraph This property contains the REQUEST_METHOD header name
		 * @brief CGI::HeaderRequestMethod
		 * @var QString
		 */
		static QString HeaderRequestMethod;

		/**
		 * @paragraph This property contains the REQUEST_URI header name
		 * @brief CGI::HeaderRequestUri
		 * @var QString
		 */
		static QString HeaderRequestUri;

		/**
		 * @paragraph This paragraph contains the SCRIPT_FILENAME header name
		 * @brief CGI::HeaderScriptFilename
		 * @var QString
		 */
		static QString HeaderScriptFilename;

		/**
		 * @paragraph This property contains the SCRIPT_NAME header namr
		 * @brief CGI::HeaderScriptName
		 * @var QString
		 */
		static QString HeaderScriptName;

		/**
		 * @paragraph This property contains the SERVER_ADDR header name
		 * @brief CGI::HeaderServerAddress
		 * @var QString
		 */
		static QString HeaderServerAddress;

		/**
		 * @paragraph This property contians the SERVER_ADMIN header name
		 * @brief CGI::HeaderServerAdministrator
		 * @var QString
		 */
		static QString HeaderServerAdministrator;

		/**
		 * @paragraph This property contains the SERVER_NAME header name
		 * @brief CGI::HeaderServerName
		 * @var QString
		 */
		static QString HeaderServerName;

		/**
		 * @paragraph This property contains the SERVER_PORT header name
		 * @brief CGI::HeaderServerPort
		 * @var QString
		 */
		static QString HeaderServerPort;

		/**
		 * @paragraph This property contains the SERVER_PROTOCOL header name
		 * @brief CGI::HeaderServerProtocol
		 * @var QString
		 */
		static QString HeaderServerProtocol;

		/**
		 * @paragraph This property contains the SERVER_SIGNATURE header name
		 * @brief CGI::HeaderServerSignature
		 * @var QString
		 */
		static QString HeaderServerSignature;

		/**
		 * @paragraph This property contains the SERVER_SOFTWARE header name
		 * @brief CGI::HeaderServerSoftware
		 * @var QString
		 */
		static QString HeaderServerSoftware;

		/**
		 * @paragraph This constant contains the 200 OK header
		 * @brief CGI::HeaderStatusOK
		 * @var QString
		 */
		static QString HeaderStatusOK;

		/**
		 * @paragraph This property contains the DELETE data request method name
		 * @brief CGI::MethodDelete
		 * @var QString
		 */
		static QString MethodDelete;

		/**
		 * @paragraph This property contains the GET data request method name
		 * @brief CGI::MethodGet
		 * @var QString
		 */
		static QString MethodGet;

		/**
		 * @paragraph This property contains the HEAD data request method name
		 * @brief CGI::MethodHead
		 * @var QString
		 */
		static QString MethodHead;

		/**
		 * @paragraph This property contains the POST data request method name
		 * @brief CGI::MethodPost
		 * @var QString
		 */
		static QString MethodPost;

		/**
		 * @paragraph This property contains the PUT data request method name
		 * @brief CGI::MethodPut
		 * @var QString
		 */
		static QString MethodPut;

		///////////////////////////////////////////////////////////////////////
		/// Singleton ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method maintains access to the singleton instance of this class
		 * @brief CGI::Instance()
		 * @param bool bReset [false]
		 * @param QObject* qoParent [0]
		 * @return CGI* CGI::mInstance
		 */
		static CGI* Instance(bool bReset = false, QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constructor autmatically parses the HTTP headers and data
		 * @brief CGI::CGI()
		 * @param QObject* qoParent [0]
		 */
		explicit CGI(QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method is a helper for the router to add parameters from URL routes
		 * @brief HeimdallGI::CGI::AddParameter()
		 * @param QString strName
		 * @param QString strValue
		 * @return HeimdallGI::CGI* HeimdallGI::CGI::mInstance
		 */
		CGI* AddParameter(QString strName, QString strValue);

		/**
		 * @paragraph This method adds a response header to the instance
		 * @brief CGI::AddResponseHeader()
		 * @param QString strName
		 * @param QString strValue
		 * @return CGI* CGI::mInstance
		 */
		CGI* AddResponseHeader(QString strName, QString strValue);

		/**
		 * @paragraph This method decodes a query string into a query map
		 * @brief CGI::DecodeQuery()
		 * @param QString strQuery
		 * @param QString strPairSeparator ["&"]
		 * @return QMap<QString, QString>
		 */
		QMap<QString, QString> DecodeQuery(QString strQuery, QString strPairSeparator = "&");

		/**
		 * @paragraph This method encodes a query map into a query string
		 * @brief CGI::EncodeQuery()
		 * @param QMap<QString, QString> qmQuery
		 * @param QString strPairGlue ["&"]
		 * @return QString
		 */
		QString EncodeQuery(QMap<QString, QString> qmQuery, QString strPairGlue = "&");

		/**
		 * @paragraph This method encodes a query variant map into a query string
		 * @brief CGI::EncodeQuery()
		 * @param QVariantMap qvmQuery
		 * @param QString strPairGlue ["&"]
		 * @return QString
		 */
		QString EncodeQuery(QVariantMap qvmQuery, QString strPairGlue = "&");

		/**
		 * @paragraph This method writes the HTTP response to the browser/socket
		 * @brief CGI::WriteResponse()
		 * @param QString strContentType [NULL]
		 * @return void
		 */
		void WriteResponse(QString strContentType = NULL);

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the current response content in the instance
		 * @brief CGI::GetContent()
		 * @return QString CGI::mContent
		 */
		QString GetContent();

		/**
		 * @paragraph This method returns a cookie from the instance if one exists
		 * @brief CGI::GetCookie()
		 * @param QString strName
		 * @return QString
		 */
		QString GetCookie(QString strName);

		/**
		 * @paragraph This method returns the current cookie map in the instance
		 * @brief CGI::GetCookies()
		 * @return QMap<QString, QString> CGI::mCookies
		 */
		QMap<QString, QString> GetCookies();

		/**
		 * @paragraph This method returns a GET/POST parameter from the instance if one exists
		 * @brief CGI::GetParam()
		 * @param QString strName
		 * @return QString
		 */
		QString GetParam(QString strName);

		/**
		 * @paragraph This method returns the current POST map from the instance
		 * @brief CGI::GetPostData()
		 * @return QMap<QString, QString> CGI::mPostParameters
		 */
		QMap<QString, QString> GetPostData();

		/**
		 * @paragraph This method returns the current GET map from the instance
		 * @brief CGI::GetQueryData()
		 * @return QMap<QString, QString> CGI::mGetParameters
		 */
		QMap<QString, QString> GetQueryData();

		/**
		 * @paragraph This method returns a request header from the instance if one exists
		 * @brief CGI::GetRequestHeader()
		 * @param QString strName
		 * @return QString
		 */
		QString GetRequestHeader(QString strName);

		/**
		 * @paragraph This method returns the current request header map in the instance
		 * @brief CGI::GetRequestHeaders()
		 * @return QMap<QString, QString> CGI::mRequestHeaders
		 */
		QMap<QString, QString> GetRequestHeaders();

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the response content into the instance
		 * @brief CGI::SetContent()
		 * @param QString strContent
		 * @return CGI* CGI::mInstance
		 */
		CGI* SetContent(QString strContent);

		/**
		 * @paragraph This method sets the content type header into the instance
		 * @brief CGI::SetContentType()
		 * @param QString strContentType
		 * @return CGI* CGI::mInstance
		 */
		CGI* SetContentType(QString strContentType = CGI::ContentTypeHTML);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// End Class Definition /////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

#endif // HeimdallGI_CGI_H
