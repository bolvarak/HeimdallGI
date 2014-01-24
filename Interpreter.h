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
#include "QMetaClassInfo"
#include "QMetaEnum"
#include "QMetaMethod"
#include "QMetaObject"
#include "QMetaProperty"
#include "QMetaType"
#include "QMetaTypeId"
#include "QMetaTypeId2"
#include "QMetaTypeIdQObject"
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
	/// Structures ///////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This structure builds an interpreted function for the interpreter
	 * @brief The InterpretedFunction struct
	 */
	struct InterpretedFunction {

		///////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the list of arguments for the function
		 * @brief HeimdallGI::InterpretedFunction::mArguments
		 * @var QList<HeimdallGI::InterpretedFunction>
		 */
		QList<InterpretedFunctionArgument> mArguments;

		/**
		 * @paragraph This property contains the class where the function lives
		 * @brief HeimdallGI::InterpretedFunction::mClass
		 * @var QString
		 */
		QString mClass;

		/**
		 * @paraagraph This property contains the match expression for the function
		 * @brief HeimdallGI::InterpretedFunction::mExpression
		 * @var QString
		 */
		QString mExpression;

		/**
		 * @paragraph This property contains the method of the function
		 * @brief HeimdallGI::InterpretedFunction::mMethod
		 * @var QString
		 */
		QString mMethod;

		/**
		 * @paragraph This property contains the name of the function
		 * @brief HeimdallGI::InterpretedFunction::mName
		 * @var QString
		 */
		QString mName;

		/**
		 * @paragraph This property contains a list of return types for the function
		 * @brief HeimdallGI::InterpretedFunction::mReturns
		 * @var QStringList
		 */
		QStringList mReturns;

		///////////////////////////////////////////////////////////////
		/// Constructors /////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constructor simply initializes the structure
		 * @brief HeimdallGI::InterpretedFunction::InterpretedFunction()
		 */
		InterpretedFunction() {}

		/**
		 * @paragraph This constructor initializes and sets up the function structure
		 * @brief HeimdallGI::InterpretedFunction::InterpretedFunction()
		 * @param QString strName
		 * @param QList<HeimdallGI::InterpretedFunctionArgument> qlArguments
		 * @param QString strExpression
		 * @param QString strClass
		 * @param QString strMethod
		 * @param QStringList qslReturns
		 */
		InterpretedFunction(QString strName, QList<InterpretedFunctionArgument> qlArguments, QString strExpression, QString strClass, QString strMethod, QStringList qslReturns) {
			// Set the name
			mName       = strName;
			// Set the arguments
			mArguments  = qlArguments;
			// Set the expressions
			mExpression = strExpression;
			// Set the class
			mClass      = strClass;
			// Set the method
			mMethod     = strMethod;
			// Set the return values
			mReturns    = qslReturns;
		}

		/**
		 * @paragraph This constructor initializes and sets up the function structure
		 * @brief HeimdallGI::InterpretedFunction::InterpretedFunction()
		 * @param QString strName
		 * @param QList<QVariantMap> qlArguments
		 * @param QString strExpression
		 * @param QString strClass
		 * @param QString strMethod
		 * @param QStringList qslReturns
		 */
		InterpretedFunction(QString strName, QList<QVariantMap> qlArguments, QString strExpression, QString strClass, QString strMethod, QStringList qslReturns) {
			// Set the name
			mName       = strName;
			// Set the expression
			mExpression = strExpression;
			// Set the class
			mClass      = strClass;
			// Set the method
			mMethod     = strMethod;
			// Set the return type
			mReturns    = qslReturns;
			// Iterate over the arguments
			for (int intArgument = 0; intArgument < qlArguments.size(); ++intArgument) {
				// Localize the argument map
				QVariantMap qvmArgument = qlArguments.at(intArgument);
				// Add the argument to the structure
				addArgument(qvmArgument.value("name").toString(), qvmArgument.value("type").toString(), qvmArgument.value("required").toBool(), qvmArgument.value("default"));
			}
		}

		///////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method adds an argument to the function structure
		 * @brief HeimdallGI::InterpretedFunction::addArgument()
		 * @param QString strName
		 * @param QString strType
		 * @param bool bRequired [true]
		 * @param QVariant qvDefault [undefined]
		 */
		void addArgument(QString strName, QString strType, bool bRequired = true, QVariant qvDefault = QVariant("undefined")) {
			// Create structure
			InterpretedFunctionArgument ifaArgument;
			// Set the name
			ifaArgument.setName(strName);
			// Set the type
			ifaArgument.setType(strType);
			// Set the requirement
			ifaArgument.setRequired(bRequired);
			// Set the default value
			ifaArgument.setDefault(qvDefault);
			// Add the argument the the instance
			mArguments.append(ifaArgument);
		}

		/**
		 * @paragraph This method adds a return type to the function structure
		 * @brief HeimdallGI::InterpretedFunction::addReturnType()
		 * @param QString strType
		 * @return void
		 */
		void addReturnType(QString strType) {
			// Append the return type to the instance
			mReturns.append(strType);
		}

		///////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the function arguments
		 * @brief HeimdallGI::InterpretedFunction::getArguments()
		 * @return QList<HeimdallGI::InterpretedFunctionArgument> HeimdallGI::InterpretedFunction::mArguments
		 */
		QList<InterpretedFunctionArgument> getArguments() {
			// Return the arguments
			return mArguments;
		}

		/**
		 * @paragraph This method returns the class name for the function processor
		 * @brief HeimdallGI::InterpretedFunction::getClass()
		 * @return QString HeimdallGI::InterpretedFunction::mClass
		 */
		QString getClass() {
			// Return the class name
			return mClass;
		}

		/**
		 * @paragraph This method returns the match expression for the function
		 * @brief HeimdallGI::InterpretedFunction::getExpression()
		 * @return QString HeimdallGI::InterpretedFunction::mExpression
		 */
		QString getExpression() {
			// Return the expression
			return mExpression;
		}

		/**
		 * @paragraph This method returns the method name for the function processor
		 * @brief HeimdallGI::InterpretedFunction::getMethod()
		 * @return QString HeimdallGI::InterpretedFunction::mMethod
		 */
		QString getMethod() {
			// Return the method
			return mMethod;
		}

		/**
		 * @paragraph This method returns the name of the function
		 * @brief HeimdallGI::InterpretedFunction::getName()
		 * @return QString HeimdallGI::InterpretedFunction::mName
		 */
		QString getName() {
			// Return the name
			return mName;
		}

		/**
		 * @paragraph This method returns the return types for the function
		 * @brief HeimdallGI::InterpretedFunction::getReturnTypes()
		 * @return QStringList HeimdallGI::InterpretedFunction::mReturns
		 */
		QStringList getReturnTypes() {
			// Return the return types
			return mReturns;
		}


		///////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the arguments into the instance
		 * @brief HeimdallGI::InterpretedFunction::setArguments()
		 * @param QList<HeimdallGI::InterpretedFunctionArgument> qlArguments
		 * @return void
		 */
		void setArguments(QList<InterpretedFunctionArgument> qlArguments) {
			// Set the arguments into the instance
			mArguments = qlArguments;
		}

		/**
		 * @paragraph This method sets the arguments into  the instance
		 * @overload HeimdallGI::InterpretedFunction::setArguments()
		 * @brief HeimdallGI::InterpretedFunction::setArguments()
		 * @param QList<QVariantMap> qlArguments
		 * @return void
		 */
		void setArguments(QList<QVariantMap> qlArguments) {
			// Clear the arguments
			mArguments.clear();
			// Iterate over the arguments
			for (int intArgument = 0; intArgument < qlArguments.size(); ++intArgument) {
				// Localize the argument map
				QVariantMap qvmArgument = qlArguments.at(intArgument);
				// Add the argument to the structure
				addArgument(qvmArgument.value("name").toString(), qvmArgument.value("type").toString(), qvmArgument.value("required").toBool(), qvmArgument.value("default"));
			}
		}

		/**
		 * @paragraph This method sets the class name into the instance
		 * @brief HeimdallGI::InterpretedFunction::setClass()
		 * @param QString strClass
		 * @return void
		 */
		void setClass(QString strClass) {
			// Set the class name
			mClass = strClass;
		}

		/**
		 * @paragraph This method sets the match expression into the instanece
		 * @brief HeimdallGI::InterpretedFunction::setExpression()
		 * @param QString strExpression
		 * @return void
		 */
		void setExpression(QString strExpression) {
			// Set the expression
			mExpression = strExpression;
		}

		/**
		 * @paragraph This method sets the method name into the instance
		 * @brief HeimdallGI::InterpretedFunction::setMethod()
		 * @param QString strMethod
		 * @return void
		 */
		void setMethod(QString strMethod) {
			mMethod = strMethod;
		}

		/**
		 * @paragraph This method sets the name of the function
		 * @brief HeimdallGI::InterpretedFunction::setName()
		 * @param QString strName
		 * @return void
		 */
		void setName(QString strName) {
			// Set the name of the function
			mName = strName;
		}

		/**
		 * @paragraph This method sets the return types into the instance
		 * @brief HeimdallGI::InterpretedFunction::setReturnTypes()
		 * @param QStringList qslReturnTypes
		 * @return void
		 */
		void setReturnTypes(QStringList qslReturnTypes) {
			// Set the return types
			mReturns = qslReturnTypes;
		}

	};

	/**
	 * @paragraph This structure builds an interpreted function argument for the interpreter
	 * @brief HeimdallGI::InterpretedFunctionArgument
	 */
	struct InterpretedFunctionArgument {

		///////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the default value for the argument
		 * @brief HeimdallGI::InterpretedFunctionArgument::mDefault
		 * @var QVariant
		 */
		QVariant mDefault;

		/**
		 * @paragraph This property contains the name of the argument
		 * @brief HeimdallGI::InterpretedFunctionArgument::mName
		 * @var QString
		 */
		QString mName;

		/**
		 * @paragraph This property contains the requirement of the argument
		 * @brief HeimdallGI::InterpretedFunctionArgument::mRequired
		 * @var bool
		 */
		bool mRequired;

		/**
		 * @paragraph This property contains the argument type
		 * @brief HeimdallGI::InterpretedFunctionArgument::mType
		 * @var QString
		 */
		QString mType;

		///////////////////////////////////////////////////////////////
		/// Constructors /////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constructor initializes the structure
		 * @brief HeimdallGI::InterpretedFunctionArgument::InterpretedFunctionArgument()
		 */
		InterpretedFunctionArgument() {}

		/**
		 * @paragraph This constructor initializes and sets up the structure
		 * @brief HeimdallGI::InterpretedFunctionArgument::InterpretedFunctionArgument()
		 * @param QString strName
		 * @param QString strType
		 * @param bool bRequired [true]
		 * @param QVariant qvDefault [undefined]
		 */
		InterpretedFunctionArgument(QString strName, QString strType, bool bRequired = true, QVariant qvDefault = QVariant("undefined")) {
			// Set the name
			mName     = strName;
			// Set the type
			mType     = strType;
			// Set the requirement
			mRequired = bRequired;
			// Set the default value
			mDefault  = qvDefault;
		}

		///////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the argument's default value
		 * @brief HeimdallGI::InterpretedFunctionArgument::getDefault()
		 * @return QVariant HeimdallGI::InterpretedFunctionArgument::mDefault
		 */
		Qvariant getDefault() {
			// Return the default value
			return mDefault;
		}

		/**
		 * @paragraph This method returns the argument's name
		 * @brief HeimdallGI::InterpretedFunctionArgument::getName()
		 * @return QString HeimdallGI::InterpretedFunctionArgument::mName
		 */
		QString getName() {
			// Return the variable name
			return mName;
		}

		/**
		 * @paragraph This method returns the argument's requirement
		 * @brief HeimdallGI::InterpretedFunctionArgument::getRequired()
		 * @return bool HeimdallGI::InterpretedFunctionArgument::mRequired
		 */
		bool getRequired() {
			// Return the requirement
			return mRequired;
		}

		/**
		 * @paragraph This method returns the argument's type
		 * @brief HeimdallGI::InterpretedFunctionArgument::getType()
		 * @return HeimdallGI::InterpretedFunctionArgument::mType
		 */
		QString getType() {
			// Return the type
			return mType;
		}

		///////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the argument's default value
		 * @brief HeimdallGI::InterpretedFunctionArgument::setDefault()
		 * @param QVariant qvDefault [undefined]
		 * @return void
		 */
		void setDefault(QVariant qvDefault = QVariant("undefined")) {
			// Set the default value
			mDefault = qvDefault;
		}

		/**
		 * @paragraph This method sets the argument's name
		 * @brief HeimdallGI::InterpretedFunctionArgument::setName()
		 * @param QString strName
		 * @return void
		 */
		void setName(QString strName) {
			// Set the name
			mName = strName;
		}

		/**
		 * @paragraph This method sets the argument's requirement
		 * @brief HeimdallGI::InterpretedFunctionArgument::setRequired()
		 * @param bool bRequired [true]
		 * @return void
		 */
		void setRequired(bool bRequired = true) {
			// Set the requirement
			mRequired = bRequired;
		}

		/**
		 * @paragraph This method sets the argument's type
		 * @brief HeimdallGI::InterpretedFunctionArgument::setType()
		 * @param QString strType
		 * @return void
		 */
		void setType(QString strType) {
			// Set the type
			mType = strType;
		}

	};

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
		 * @paragraph This method adds a new function to the instance
		 * @brief HeimdallGI::Interpreter::AddFunction()
		 * @param QString strName
		 * @param QList<HeimdallGI::InterpretedFunctionArgument> qlArguments
		 * @param QString strClass
		 * @param QString strExpression
		 * @param QString strMethod
		 * @param QStringList qslReturns
		 * @return HeimdallGI::Interpreter* HeimdallGI::Interpreter::mInstance
		 */
		Interpreter* AddFunction(QString strName, QList<InterpretedFunctionArgument> qlArguments, QString strClass, QString strExpression, QString strMethod, QStringList qslReturns);

		/**
		 * @paragraph This method adds a new function to the instance.
		 * @overload HeimdallGI::Interpreter::AddFunction()
		 * @brief HeimdallGI::Interpreter::AddFunction()
		 * @param QString strName
		 * @param QList<QVariantMap> qlArguments
		 * @param QString strClass
		 * @param QString strExpression
		 * @param QString strMethod
		 * @param QStringList qslReturns
		 * @return HeimdallGI::Interpreter* HeimdallGI::Interpreter::mInstance
		 */
		Interpreter* AddFunction(QString strName, QList<QVariantMap> qlArguments, QString strClass, QString strExpression, QString strMethod, QStringList qslReturns);

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
		 * @paragraph This signal fires whenever the interpreter starts
		 * @brief HeimdallGI::Interpreter::Initialization()
		 * @param HeimdallGI::Interpreter* &
		 */
		void Initialization(Interpreter* &);

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
