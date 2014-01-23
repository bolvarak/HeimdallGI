///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef HEIMDALLGI_INTERPRETER_H
#define HEIMDALLGI_INTERPRETER_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QFile"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonParseError"
#include "QJsonValue"
#include "QJsonValueRef"
#include "QList"
#include "QMap"
#include "QObject"
#include "QRegularExpression"
#include "QRegularExpressionMatch"
#include "QSettings"
#include "QString"
#include "QStringList"
#include "QVariant"
#include "QVariantMap"
#include "Configuration.h"
#include "Log.h"
#include "View.h"
#include "Interpreter/Functions.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// HeimdallGI::Interpreter Class Definition /////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class Interpreter : public QObject
	{

		/**
		 * Ensure this class is recognized by Qt
		 */
		Q_OBJECT


	///////////////////////////////////////////////////////////////////////
	/// Protected Methods & Properties ///////////////////////////////////
	/////////////////////////////////////////////////////////////////////

	protected:

		///////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the singleton instance of this class
		 * @brief HeimdallGI::Interpreter::mInstance
		 * @var HeimdallGI::Interpreter*
		 */
		static Interpreter* mInstance;

		/**
		 * @paragraph This property contains the HGML backend core
		 * @brief HeimdallGI::Interpreter::mCore
		 * @var QVariantMap
		 */
		QMap<QString, QVariant> mCore;

		/**
		 * @paragraph This property contains a map of interpretation classes for extensibility
		 * @brief HeimdallGI::Interpreter::mInterpretationClasses
		 * @var QMap<QString, QObject*>
		 */
		QMap<QString, QObject*> mInterpretationClasses;

		/**
		 * @paragraph This property contains the last exception that occurred
		 * @brief HeimdallGI::Interpreter::mLastExpception
		 * @var int
		 */
		int mLastExpception;

		/**
		 * @paragraph This property contains the instance of the system logger
		 * @brief HeimdallGI::Interpreter::mLogger
		 * @var HeimdallGI::Log*
		 */
		Log* mLogger;

		/**
		 * @paragraph This property contains the HGML notation expression
		 * @brief HeimdallGI::Interpreter::mMarkupNotation
		 * @var QString
		 */
		QString mMarkupNotation;

		/**
		 * @paragraph This property contains the source HGML being interpreted
		 * @brief HeimdallGI::Interpreter::mTemplate
		 * @var QString
		 */
		QString mSource;

		/**
		 * @paragraph This property contains the instance of the current view
		 * @brief HeimdallGI::Interpreter::mView
		 * @var HeimdallGI::View*
		 */
		View* mView;

		///////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method begins the processing of the source
		 * @brief HeimdallGI::Interpreter::Process()
		 * @param QString strSource
		 * @param QString strOperation
		 * @return bool
		 */
		bool Process(QString strSource, QString strOperation);

		/**
		 * @paragraph This method refreshes the HGML core backend into the instance
		 * @brief HeimdallGI::Interpreter::ReloadEngine()
		 * @return void
		 */
		void ReloadEngine();

	///////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////
	/////////////////////////////////////////////////////////////////////

	public:

		///////////////////////////////////////////////////////////////
		/// Enumerations /////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This enumeration contains the interpreter's exception codes
		 * @brief HeimdallGI::Interpreter::Exception
		 * @var enum
		 */
		enum Exception {
			SyntaxError
		};

		/**
		 * @paragraph This enumeration contains the interpreter's status codes
		 * @brief HeimdallGI::Interpreter::Status
		 * @var enum
		 */
		enum Status {
			Failure,    // The interpretation failed
			Finished,   // The interpretation has finished
			Processing, // The interpreter is running
			Successful  // The interpretation succeeded
		};

		///////////////////////////////////////////////////////////////
		/// Constants ////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constant defines the HGML notation expression
		 * @brief HeimdallGI::Interpreter::HGMLNotation
		 * @var QString
		 */
		static QString HGMLNotation;

		///////////////////////////////////////////////////////////////
		/// Singleton ////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method maintains access to the singleton instance of this class
		 * @brief HeimdallGI::Interpreter::Instance()
		 * @param bool bReset [false]
		 * @return HeimdallGI::Interpreter* HeimdallGI::Interpreter::mInstance
		 */
		static Interpreter* Instance(bool bReset = false);

		///////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		explicit Interpreter(QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method adds an interpretation class to the instance
		 * @brief HeimdallGI::Interpreter::AddInterpretationClass()
		 * @param QString strName
		 * @param QObject* hgiInterpreterInstance
		 * @return HeimdallGI::Interpreter* HeimdallGI::Interpreter::mInstance
		 */
		Interpreter* AddInterpretationClass(QString strName, QObject* hgiInterpreterInstance);

		/**
		 * @paragraph This method executes the interpretation of an HGML file
		 * @brief HeimdallGI::Interpreter::Execute()
		 * @return HeimdallGI::Interpreter* HeimdallGI::Interpreter::mInstance
		 */
		Interpreter* Execute();

		/**
		 * @paragraph This method reads an HGML file and stores it in the instance
		 * @brief HeimdallGI::Interpreter::Load()
		 * @param QString strFileName
		 * @return HeimdallGI::Interpreter* HeimdallGI::Interpreter::mInstance
		 */
		Interpreter* Load(QString strFileName);

		///////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the interpreted source
		 * @brief HeimdallGI::Interpreter::GetInterpretation()
		 * @return QString HeimdallGI::Interpreter::mSource
		 */
		QString GetInterpretation();

		///////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the system logger instance into this class
		 * @brief HeimdallGI::Interpreter::SetLogger()
		 * @param HeimdallGI::Log* hgiLogger
		 * @return HeimdallGI::Interpreter* HeimdallGI::Interpreter::mInstance
		 */
		Interpreter* SetLogger(Log* &hgiLogger);

		/**
		 * @paragraph This method sets a custom HGML notation expression into the instance
		 * @brief HeimdallGI::Interpreter::SetMarkupNotation()
		 * @param QString strExpression
		 * @return HeimdallGI::Interpreter* HeimdallGI::Interpreter::mInstance
		 */
		Interpreter* SetMarkupNotation(QString strExpression);

		/**
		 * @paragraph This method sets the HGML source into the instance
		 * @brief HeimdallGI::Interpreter::SetSource()
		 * @param QString strSource
		 * @return HeimdallGI::Interpreter* HeimdallGI::Interpreter::mInstance
		 */
		Interpreter* SetSource(QString strSource);

		/**
		 * @paragraph This method sets the view object into the instance
		 * @brief HeimdallGI::Interpreter::SetView()
		 * @param HeimdallGI::View* &hgiResponse
		 * @return HeimdallGI::Interpreter* HeimdallGI::Interpreter::mInstance
		 */
		Interpreter* SetView(View* &hgiResponse);


	///////////////////////////////////////////////////////////////////////
	/// Signals //////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////

	signals:

		/**
		 * @paragraph This signal fires when an exception occurs
		 * @brief HeimdallGI::Interpreter::Exception()
		 * @param int
		 * @return void
		 */
		void Exception(int);

		/**
		 * @paragraph This signal fires each time the status changes
		 * @brief HeimdallGI::Interpreter::Status()
		 * @param int
		 * @return void
		 */
		void Status(int);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// End HeimdallGI::Interpreter Class Definition /////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Definitions //////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
