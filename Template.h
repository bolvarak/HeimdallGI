///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HEIMDALLGI_TEMPLATE_H
#define HEIMDALLGI_TEMPLATE_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QBuffer"
#include "QFile"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonValue"
#include "QObject"
#include "QRegularExpression"
#include "QRegularExpressionMatch"
#include "QString"
#include "QtXml/QDomDocument"
#include "QtXml/QDomElement"
#include "QtXml/QDomText"
#include "Configuration.h"
#include "Log.h"
#include "View.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// HeimdallGI::Template Class Definition ////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class Template : public QObject
	{
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
		 * @brief HeimdallGI::Template::mInstance
		 * @var HeimdallGI::Template*
		 */
		static Template* mInstance;

		/**
		 * @paragraph This property contains the list of substitutions
		 * @brief HeimdallGI::Template::mSubstitutions
		 * @var QVariantMap
		 */
		QVariantMap mSubstitutions;

		/**
		 * @paragraph This property contains the view file path
		 * @brief HeimdallGI::Template::mTemplateFile
		 */
		QString mTemplateFile;

		/**
		 * @paragraph This property contains the unprocessed template file
		 * @brief HeimdallGI::Template::mTemplate
		 * @var QString
		 */
		QString mTemplate;

		/**
		 * @paragraph This property contains the processed view
		 * @brief HeimdallGI::Template::mView
		 * @var HeimdallGI::View*
		 */
		View* mView;

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method processes all of the in-view variable assignments
		 * @brief HeimdallGI::Template::DoAssignments()
		 * @param QString strLine
		 * @return void
		 */
		void DoAssignments(QString &strLine);

		/**
		 * @paragraph This method replaces view comments
		 * @brief HeimdallGI::Template::DoComments()
		 * @param QString strLine
		 * @return void
		 */
		void DoComments(QString &strLine);

		/**
		 * @paragraph This method processes a conditional statement
		 * @brief HeimdallGI::Template::DoConditional()
		 * @param QString strLine
		 * @return void
		 */
		void DoConditional(QString &strLine);

		/**
		 * @paragraph This method processes a foreach loop
		 * @brief HeimdallGI::Template::DoForEach()
		 * @param QString strLine
		 * @return void
		 */
		void DoForEach(QString &strLine);

		/**
		 * @paragraph This method processes the inclusions for a line
		 * @brief HeimdallGI::Template::DoInclusion()
		 * @param QString &strLine
		 * @return void
		 */
		void DoInclusion(QString &strLine);

		/**
		 * @paragraph This method converts data to JSON
		 * @brief HeimdallGI::Template::DoJSON()
		 * @param QString strLine
		 * @return void
		 */
		void DoJSON(QString &strLine);

		/**
		 * @paragraph This method processes the meta tags for the view
		 * @brief HeimdallGI::Template::DoMetaTags()
		 * @param QString strLine
		 * @return void
		 */
		void DoMetaTags(QString &strLine);

		/**
		 * @paragraph This method processes the scripts for the view
		 * @brief HeimdallGI::Template::DoScripts()
		 * @param QString strLine
		 * @return void
		 */
		void DoScripts(QString &strLine);

		/**
		 * @paragraph This method processes the the styles for the view
		 * @brief HeimdallGI::Template::DoStyles()
		 * @param QString strLine
		 * @return void
		 */
		void DoStyles(QString &strLine);

		/**
		 * @paragraph This method processes the substitutions for a line
		 * @brief HeimdallGI::Template::DoSubstitution()
		 * @param QString &strLine
		 * @return void
		 */
		void DoSubstitution(QString &strLine);

		/**
		 * @paragraph This method determines if a variable is boolean
		 * @brief HeimdallGI::Template::IsBoolean()
		 * @param QString strVariable
		 * @return bool
		 */
		bool IsBoolean(QString strVariable);

		/**
		 * @paragraph This method determines if a variable is a floating point
		 * @brief HeimdallGI::Template::IsFloat()
		 * @param QString strVariable
		 * @return bool
		 */
		bool IsFloat(QString strVariable);

		/**
		 * @paragraph This method determines if a variable is an integer
		 * @brief HeimdallGI::Template::IsInteger()
		 * @param QString strVariable
		 * @return bool
		 */
		bool IsInteger(QString strVariable);

		/**
		 * @paragraph This method determines if a variable is numeric
		 * @brief HeimdallGI::Template::IsNumeric()
		 * @param QString strVariable
		 * @return bool
		 */
		bool IsNumeric(QString strVariable);

		/**
		 * @paragraph This method processes a template conditional
		 * @brief HeimdallGI::Template::IsTrue()
		 * @param QString strPageValue
		 * @param QString strOperator
		 * @param QString strOperand
		 * @return bool
		 */
		bool IsTrue(QString strPageValue, QString strOperator, QString strOperand);

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public:

		///////////////////////////////////////////////////////////////////////
		/// Constants ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constant defines the footer keyword for scripts
		 * @brief HeimdallGI::Template::Footer
		 * @var QString
		 */
		static QString Footer;

		/**
		 * @paragraph This constant defines the header keyword for scripts
		 * @brief HeimdallGI::Template::Header
		 * @var QString
		 */
		static QString Header;

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		explicit Template(QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Singleton ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method maintains access to the singleton instance of this class
		 * @brief HeimdallGI::Template::Instance()
		 * @param bool bReset [false]
		 * @return HeimdallGI::Template* HeimdallGI::Template::mInstance
		 */
		static Template* Instance(bool bReset = false);

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method starts the processing of a template file
		 * @brief HeimdallGI::Template::Process()
		 * @param HeimdallGI::View* objView [0]
		 * @param QString strTemplate [NULL]
		 * @return HeimdallGI::Template* HeimdallGI::Template::mInstance
		 */
		Template* Process(View* objView = 0, QString strTemplate = NULL);

		/**
		 * @paragraph This method processes a string instead of a template
		 * @brief HeimdallGI::Template::ProcessString()
		 * @param QString strTemplate
		 * @param HeimdallGI::View* objView [0]
		 * @return HeimdallGI::Template* HeimdallGI::Template::mInstance
		 */
		Template* ProcessString(QString strTemplate, View* objView = 0);

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the processed template from the instance
		 * @brief HeimdallGI::Template::GetTemplate()
		 * @return QString HeimdallGI::Template::mTemplate
		 */
		QString GetTemplate();

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the view object into the instance
		 * @brief HeimdallGI::Template::SetView()
		 * @param HeimdallGI::View* objView
		 * @return HeimdallGI::Template* HeimdallGI::Template::mInstance
		 */
		Template* SetView(View* objView);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// End HeimdallGI::Template Class Definition ////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End HeimdallGI::Template Header //////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // HEIMDALLGI_TEMPLATE_H
