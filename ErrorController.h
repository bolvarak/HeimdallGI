///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HEIMDALLGI_ERRORCONTROLLER_H
#define HEIMDALLGI_ERRORCONTROLLER_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QObject"
#include "Base.h"
#include "Configuration.h"
#include "CGI.h"
#include "Log.h"
#include "View.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// HeimdallGI::ErrorController Class Definition /////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class ErrorController : public QObject
	{

		/**
		 * Ensure this class is recognized by Qt
		 */
		Q_OBJECT

	///////////////////////////////////////////////////////////////////////////
	/// Protected Methods & Properties ///////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	protected:

		/**
		 * @paragraph This property contains the singleton instance of this class
		 * @brief HeimdallGI::ErrorController::mInstance
		 * @var HeimdallGI::ErrorController*
		 */
		static ErrorController* mInstance;

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public:

		///////////////////////////////////////////////////////////////////////
		/// Singleton ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method maintains access to the singleton instance of this class
		 * @brief HeimdallGI::ErrorController::Instance()
		 * @param bool bReset [false]
		 * @return HeimdallGI::ErrorController* HeimdallGI::ErrorController::mInstance
		 */
		static ErrorController* Instance(bool bReset = false);

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		explicit ErrorController(QObject* qoParent = 0);

	///////////////////////////////////////////////////////////////////////
	/// View Methods /////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////

	public slots:
		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method prettyfies the 404 errors
		 * @brief HeimdallGI::ErrorController::NotFound()
		 * @param HeimdallGI::CGI* &objRequest
		 * @param HeimdallGI::View* &objResponse
		 * @return void
		 */
		void NotFound(CGI*& objRequest, View*& objResponse);

		/**
		 * @paragraph This method prettyfies the 505 error
		 * @brief HeimdallGI::ErrorController::ServerFault()
		 * @param HeimdallGI::CGI* &objRequest
		 * @param HeimdallGI::View* &objResponse
		 * @param QString strMessage
		 * @return void
		 */
		void ServerFault(CGI*& objRequest, View*& objResponse, QString strMessage);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// End HeimdallGI::ErrorController Class Definition /////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Definitions //////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
