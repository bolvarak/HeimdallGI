///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HEIMDALLGI_REQUEST_H
#define HEIMDALLGI_REQUEST_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "HeimdallGI"
#include "QObject"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// HeimdallGI::Request Class Definition /////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class Request : public QObject
	{
		/**
		 * @paragraph Ensure this class is recognized by Qt
		 */
		Q_OBJECT

		/**
		 * @paragraph Ensure this class is recognized as a meta type
		 */
		Q_DECLARE_METATYPE(HeimdallGI::Request)

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	protected:

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This contains the singleton instance of this class
		 * @brief HeimdallGI::Request::mInstance
		 * @var HeimdallGI::Request*
		 */
		static Request* mInstance;

		/**
		 * @paragraph This property contains the block file to be loaded
		 * @brief HeimdallGI::Request::mBlock
		 * @var QString
		 */
		QString mBlock;

		/**
		 * @paragraph This property contains the instance of the CGI request
		 * @brief HeimdallGI::Request::mCgi
		 * @var HeimdallGI::Cgi
		 */
		CGI* mCgi;

		/**
		 * @paragraph This property contains the controller to load
		 * @brief mController
		 * @var QString
		 */
		QString mController;

		/**
		 * @paragraph This property contains the cookies from the CGI
		 * @brief HeimdallGI::Request::mCookies
		 * @var QVariantMap
		 */
		QVariantMap mCookies;

		/**
		 * @paragraph This property contains the GET variables from CGI
		 * @brief HeimdallGI::Request::mGetParameters
		 * @var QVariantMap
		 */
		QVariantMap mGetParameters;

		/**
		 * @paragraph This property contains the POST variables from CGI
		 * @brief HeimdallGI::Request::mPostParameters
		 * @var QVariantMap
		 */
		QVariantMap mPostParameters;

		/**
		 * @paragraph This property contains the SEO friendly GET variables
		 * @brief HeimdallGI::Request::mQueryParameters
		 * @var QVariantMap
		 */
		QVariantMap mQueryParameters;

		/**
		 * @paragraph This property contains the ENV variables from the request
		 * @brief HeimdallGI::Request::mServer
		 * @var QVariantMap
		 */
		QVariantMap mServer;

		/**
		 * @paragraph This property contains the sessions for this request
		 * @brief HeimdallGI::Request::mSessions
		 * @var QVariantMap
		 */
		QVariantMap mSessions;

		/**
		 * @paragraph This property contains the REQUEST_URI
		 * @brief HeimdallGI::Request::mRequest
		 * @var QString
		 */
		QString mRequest;

		/**
		 * @paragraph This property contains the base URI for the request
		 * @brief HeimdallGI::Request::mBaseUri
		 * @var QString
		 */
		QString mBaseUri;

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method determines the view block to load
		 * @brief HeimdallGI::Request::ProcessBlock()
		 * @return HeimdallGI::Request* this
		 */
		Request* ProcessBlock();

		/**
		 * @paragraph This method determines the controller class to load
		 * @brief HeimdallGI::Request::ProcessController()
		 * @return HeimdallGI::Request* this
		 */
		Request* ProcessController();

		/**
		 * @paragraph This method reads the cookies from the CGI request
		 * @brief HeimdallGI::Request::ProcessCookies()
		 * @return HeimdallGI::Request* this
		 */
		Request* ProcessCookies();

		/**
		 * @paragraph This method processes the GET parameters from the CGI request
		 * @brief HeimdallGI::Request::ProcessGetParameters()
		 * @return HeimdallGI::Request* this
		 */
		Request* ProcessGetParameters();

		/**
		 * @paragraph This method processes the POST parameters from the CGI request
		 * @brief HeimdallGI::Request::ProcessPostParameters()
		 * @return HeimdallGI::Request* this
		 */
		Request* ProcessPostParameters();

		/**
		 * @paragraph This method processes the SEO-Friendly query parameters from the REQUEST_URI
		 * @brief HeimdallGI::Request::ProcessQueryParameters()
		 * @return HeimdallGI::Request* this
		 */
		Request* ProcessQueryParameters();

		/**
		 * @paragraph This method processes the REQUEST_URI
		 * @brief HeimdallGI::Request::ProcessRequest()
		 * @return HeimdallGI::Request* this
		 */
		Request* ProcessRequest();

		/**
		 * @paragraph This method processes the server variables from the ENV
		 * @brief HeimdallGI::Request::ProcessServer()
		 * @return HeimdallGI::Request* this
		 */
		Request* ProcessServer();

		/**
		 * @paragraph This method processes the sessions from the request
		 * @brief HeimdallGI::Request::ProcessSessions()
		 * @return HeimdallGI::Request* this
		 */
		Request* ProcessSessions();

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public:

		///////////////////////////////////////////////////////////////////////
		/// Singleton ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method maintains access to the singleton instance of this class
		 * @brief HeimdallGI::Request::Instance()
		 * @param bool bReset [false]
		 * @return HeimdallGI::Request* HeimdallGI::Request::mInstance
		 */
		static Request* Instance(bool bReset = false);

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets up the class
		 * @brief HeimdallGI::Request::Request()
		 * @param QObject* qoParent [0]
		 */
		explicit Request(QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////


		void ConvertToTrueType(QString strValue, QString strKey, QVariantMap &qvmPlaceholder);

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////



		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////


	};
} // namespace HeimdallGI

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End //////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // HEIMDALLGI_REQUEST_H
