///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Template.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Globals //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Template* Template::mInstance = NULL;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constants ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString Template::Footer      = "footer";
	QString Template::Header      = "header";

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Singleton ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Template* Template::Instance(bool bReset) {
		// Check for an existing instance or a reset notification
		if ((mInstance == NULL) || (bReset == true)) {
			// Create a new instance
			mInstance = new Template;
		}
		// Return the instance
		return mInstance;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Template::Template(QObject* qoParent) : QObject(qoParent) {
		// Default the template read failure to false
		this->mTemplateReadFailure = false;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void Template::determineTemplatePath(QString strTemplate) {
		// Reset the template
		strTemplate = (strTemplate.isEmpty() ? this->mView->getTemplate() : strTemplate);
		// Check to see if this is a resource template
		if (strTemplate.at(0) == ':') {
			// Set the template file
			this->mTemplateFile = strTemplate;
			// Log the path
			this->mLog->Add("TemplatePath", this->mTemplateFile);
			// We're done
			return;
		}
		// Determine if the template has a file extension
		if (strTemplate.contains(Configuration::Get("Environment.templateExtension").toString().prepend(".")) == false) {
			// Append the file extension
			strTemplate.append(".").append(Configuration::Get("Environment.templateExtension").toString());
		}
		// Create the replacements map
		QMap<QString, QString> qmsReplacements;
		// Load the file path
		QString strTemplatePath = Configuration::Get("Paths.templatePath").toString();
		// Check the last character of the template path for a directory separator
		if (strTemplatePath.at(strTemplatePath.size() - 1) != '/') {
			// Append a directory separator
			strTemplatePath.append("/");
		}
		// Combine the paths and set them into the instance
		this->mTemplateFile = QDir::toNativeSeparators(strTemplatePath.append(strTemplate));
		// Log the path
		this->mLog->Add("TemplatePath", this->mTemplateFile);
	}

	void Template::doAssignments(QString &strLine) {
		// Define the pattern
		QRegularExpression qreAssignment("<%\\s*?\\$([a-zA-Z0-9_-]+)\\s*?\\=\\s*?(\"|')(.*)(\"|')\\s*?%>", QRegularExpression::DotMatchesEverythingOption|QRegularExpression::CaseInsensitiveOption);
		// Check for matches and replace them
		while (qreAssignment.match(strLine).hasMatch()) {
			this->mView->setPageValue(qreAssignment.match(strLine).captured(1), qreAssignment.match(strLine).captured(3).replace("\\\"", "\"").replace("\\'", "'"));
			// Replace the line
			strLine.replace(qreAssignment.match(strLine).captured(0), "");
		}
	}

	void Template::doComments(QString &strLine) {
		// Define the patters
		QRegularExpression qreComment("<%(\\-|\\*){2}\\s*?(.*)\\s*?(\\-|\\*){2}%>", QRegularExpression::DotMatchesEverythingOption|QRegularExpression::CaseInsensitiveOption);
		// Check for matches and replace them
		while (qreComment.match(strLine).hasMatch()) {
			// Remove the comment from the view
			strLine.replace(qreComment.match(strLine).captured(0), "");
		}
	}

	void Template::doConditional(QString &strLine) {
		// Create the complex pattern
		QRegularExpression qreConditional("<%\\s*?if\\s*?\\(\\$*?([a-zA-Z0-9_-]+)\\s*?(eq|neq|==|!=|<>)\\s*?\"*?'*?(\\$*?.*)\"*?'*?\\s*?\\)\\s*%>(.*?)<%\\s*?else\\s*?%>(.*?)<%\\s*?endif\\s*?%>", QRegularExpression::DotMatchesEverythingOption|QRegularExpression::CaseInsensitiveOption|QRegularExpression::MultilineOption);
		// Check for matches and replace them
		while (qreConditional.match(strLine).hasMatch()) {
			// Localize the page value
			QString strPageValue  = qreConditional.match(strLine).captured(1);
			// Localize the operator
			QString strOperator   = qreConditional.match(strLine).captured(2);
			// Localize the operand
			QString strOperand    = qreConditional.match(strLine).captured(3).replace(QRegularExpression("^\\s*?(\"|')"), "").replace(QRegularExpression("(\"|')\\s*?$"), "");
			// Grab the truth value
			QString strTruthValue = qreConditional.match(strLine).captured(4);
			// Grab the false value
			QString strFalseValue = qreConditional.match(strLine).captured(5);
			// Instantiate the template class
			Template* tplConditional = new Template;
			// Run the condition
			if (this->isTrue(strPageValue, strOperator, strOperand) == true) {
				// Make the replacement
				strLine.replace(qreConditional.match(strLine).captured(0), tplConditional->setRequest(this->mRequest)->setLogger(this->mLog)->processString(strTruthValue, this->mView)->getTemplate());
			} else {
				// Make the replacement
				strLine.replace(qreConditional.match(strLine).captured(0), tplConditional->setRequest(this->mRequest)->setLogger(this->mLog)->processString(strFalseValue, this->mView)->getTemplate());
			}
		}
		// Reset the pattern to a simple pattern
		qreConditional.setPattern("<%\\s*?if\\s*?\\(\\$*?([a-zA-Z0-9_-]+)\\s*?(eq|neq|==|!=|<>)\\s*?\"*?'*?(\\$*?.*)\"*?'*?\\s*?\\)\\s*%>(.*?)<%\\s*?endif\\s*?%>");
		// Check for matches and replace them
		while (qreConditional.match(strLine).hasMatch()) {
			// Localize the page value
			QString strPageValue  = qreConditional.match(strLine).captured(1);
			// Localize the operator
			QString strOperator   = qreConditional.match(strLine).captured(2);
			// Localize the operand
			QString strOperand    = qreConditional.match(strLine).captured(3).replace(QRegularExpression("^\\s*?(\"|')"), "").replace(QRegularExpression("(\"|')\\s*?$"), "");
			// Localize the truth value
			QString strTruthValue = qreConditional.match(strLine).captured(4);
			// Run the condition
			if (this->isTrue(strPageValue, strOperator, strOperand) == true) {
				// Instantiate the template class
				Template* tplConditional = new Template;
				// Make the replacement
				strLine.replace(qreConditional.match(strLine).captured(0), tplConditional->setRequest(this->mRequest)->setLogger(this->mLog)->processString(strTruthValue, this->mView)->getTemplate());
			} else {
				// Make the replacement
				strLine.replace(qreConditional.match(strLine).captured(0), "");
			}
		}
	}

	void Template::doForEach(QString &strLine) {
		// Create the pattern
		QRegularExpression qreForEach("<%\\s*?foreach\\s*?\\((\\$[a-zA-Z0-9_-]+)\\s+?as\\s+?(\\$[a-zA-Z0-9_-]+)\\)\\s*?%>(.*?)(<%\\s*?endforeach\\s*?%>)", QRegularExpression::DotMatchesEverythingOption|QRegularExpression::CaseInsensitiveOption);
		// Grab the matches
		// Check for matches and replace them
		while (qreForEach.match(strLine).hasMatch()) {
			// Check for a close to the foreach loop
			if (qreForEach.match(strLine).captured(4).isEmpty() || qreForEach.match(strLine).captured(4).isNull()) {
				// There is an error, make the replacement
				strLine.replace(qreForEach.match(strLine).captured(0), "ERROR:  No \"endforeach\" specified for loop.");
			}
			// Grab the page value name
			QString strPageValue = qreForEach.match(strLine).captured(1).replace("$", "");
			// Grab the temproary variable name
			QString strVariable  = qreForEach.match(strLine).captured(2).replace("$", "");
			// Check to see if the page value is a list
			if (!this->mView->getPageValue(strPageValue).canConvert(QMetaType::QVariantList)) {
				// There is an error, make the replacement
				strLine.replace(qreForEach.match(strLine).captured(0), QString("ERROR:  Variable \"$%1\" is not a list.").arg(strVariable));
			}
			// Create the data placeholder
			QString strForEach;
			// Check for an empty loop
			if (this->mView->getPageValue(strPageValue).toList().isEmpty() == false) {
				// Loop over the page value
				for (int intIteration = 0; intIteration < this->mView->getPageValue(strPageValue).toList().size(); ++intIteration) {
					// Set the page value
					this->mView->setPageValue(strVariable, this->mView->getPageValue(strPageValue).toList().at(intIteration));
					// Instantiate the template class
					Template* tplForEach = new Template;
					// Process the string
					strForEach.append(tplForEach->setRequest(this->mRequest)->setLogger(this->mLog)->processString(qreForEach.match(strLine).captured(3), this->mView)->getTemplate());
				}
			}
			// Make the replacement
			strLine.replace(qreForEach.match(strLine).captured(0), strForEach);
		}
	}

	void Template::doInclusion(QString &strLine) {
		// Define the pattern
		QRegularExpression qreInclude("<%\\s*?include\\s*?\\(\\s*?\"([a-zA-Z0-9\\/\\_-]+\\.[a-zA-Z]{3,5})\"\\s*?\\)\\s*?%>", QRegularExpression::DotMatchesEverythingOption);
		// Check for matches and replace them
		while (qreInclude.match(strLine).hasMatch()) {
			// Instantiate the template
			Template* tplInclude = new Template;
			// Process the template
			tplInclude->setRequest(this->mRequest)->setLogger(this->mLog)->process(this->mView, qreInclude.match(strLine).captured(1));
			// Reset the line
			strLine.replace(qreInclude.match(strLine).captured(0), tplInclude->getTemplate());
		}
	}

	void Template::doJSON(QString &strLine) {
		// Define the pattern
		QRegularExpression qreJSON("<%\\s*?getJson\\((\\$[a-zA-Z0-9-_]+)\\)\\s*?%>", QRegularExpression::DotMatchesEverythingOption);
		// Check for matches and replace them
		while (qreJSON.match(strLine).hasMatch()) {
			// Check for a full scope
			if (qreJSON.match(strLine).captured(1).toLower() == "$this") {
				// Create the JSON object
				QJsonObject qjoSubstitution;
				// Create the JSON document
				QJsonDocument qjdSubstitution;
				// Iterate over the page values
				for (QVariantMap::const_iterator itrValue = this->mView->getPageValues().constBegin(); itrValue != this->mView->getPageValues().constEnd(); ++itrValue) {
					// Add the value to the JSON object
					qjoSubstitution.insert(itrValue.key(), QJsonValue(itrValue.value().toString()));
				}
				// Set the JSON object into the document
				qjdSubstitution.setObject(qjoSubstitution);
				// Make the replacement
				strLine.replace(qreJSON.match(strLine).captured(0), qjdSubstitution.toJson(QJsonDocument::Compact));
			} else {
				// Create the JSON object
				QJsonObject qjoSubstitution;
				// Create the JSON document
				QJsonDocument qjdSubstitution;
				// Add the variable
				qjoSubstitution.insert(qreJSON.match(strLine).captured(1), QJsonValue(this->mView->getPageValue(qreJSON.match(strLine).captured(1).replace("$", "")).toString()));
				// Set the object into the document
				qjdSubstitution.setObject(qjoSubstitution);
				// Set an empty JSON object
				strLine.replace(qreJSON.match(strLine).captured(0), qjdSubstitution.toJson(QJsonDocument::Compact));
			}
		}
		// Define the multiple argument pattern
		qreJSON.setPattern("<%\\s*?getJson\\((\\$[a-zA-Z0-9-_]+\\s*?,*?\\s*?)+\\)\\s*?%>");
		// Check for matches and Replace them
		while (qreJSON.match(strLine).hasMatch()) {
			// Localize the match
			QString strMatch = qreJSON.match(strLine).captured(0)
							   .replace(QRegularExpression("^<%\\s*?getJson\\("), "") // Remove the opening of the tag and function call
							   .replace(QRegularExpression("\\)\\s*?%>$"), "")        // Remove the closing of the tag and function call
							   .replace("$", "")                                      // Remove the variable notation
							   .replace(QRegularExpression("\\s*?"), "");             // Remove the spaces
			// Localize and split the arguments
			QStringList qslSubstitutions = strMatch.split(QRegularExpression(","));
			// Create the JSON object
			QJsonObject qjoSubstitutions;
			// Create the JSON document
			QJsonDocument qjdSubstitutions;
			// Iterate over the list
			for (int intSubstitution = 0; intSubstitution < qslSubstitutions.size(); ++intSubstitution) {
				// Add the value to the object
				qjoSubstitutions.insert(qslSubstitutions.at(intSubstitution), QJsonValue(this->mView->getPageValue(qslSubstitutions.at(intSubstitution)).toString()));
			}
			// Set the object into the document
			qjdSubstitutions.setObject(qjoSubstitutions);
			// Make the replacement
			strLine.replace(qreJSON.match(strLine).captured(0), qjdSubstitutions.toJson(QJsonDocument::Compact));
		}
	}

	void Template::doMetaTags(QString &strLine) {
		// Define the pattern
		QRegularExpression qreMetaTags("<%\\s*?getMetaTags\\(\\)\\s*?%>", QRegularExpression::DotMatchesEverythingOption|QRegularExpression::CaseInsensitiveOption);
		// Check for matches and replace them
		while (qreMetaTags.match(strLine).hasMatch()) {
			// Replace the styles
			strLine.replace(qreMetaTags.match(strLine).captured(0), this->mView->getMetaTags());
		}
	}

	void Template::doScripts(QString &strLine) {
		// Define the pattern
		QRegularExpression qreScripts("<%\\s*?getScripts\\(\"(footer|header)\"\\)\\s*?%>", QRegularExpression::DotMatchesEverythingOption|QRegularExpression::CaseInsensitiveOption);
		// Check for matches and replace them
		while (qreScripts.match(strLine).hasMatch()) {
			// Check for header/footer
			if (qreScripts.match(strLine).captured(1).toLower() == Template::Header) {
				// Replace with header scripts
				strLine.replace(qreScripts.match(strLine).captured(0), this->mView->getScripts(true));
			} else {
				// Replace with footer scripts
				strLine.replace(qreScripts.match(strLine).captured(0), this->mView->getScripts(false));
			}
		}
	}

	void Template::doStyles(QString &strLine) {
		// Define the patter
		QRegularExpression qreStyles("<%\\s*?getStyles\\(\\)\\s*?%>", QRegularExpression::DotMatchesEverythingOption|QRegularExpression::CaseInsensitiveOption);
		// Check for matches and replace them
		while (qreStyles.match(strLine).hasMatch()) {
			// Replace the styles
			strLine.replace(qreStyles.match(strLine).captured(0), this->mView->getStyles());
		}
	}

	void Template::doSubstitution(QString &strLine) {
		// Define the pattern
		QRegularExpression qreSubstitution("<%=\\s*?\\$([a-zA-Z0-9_-]+)->([a-zA-Z0-9_-]+)\\s*?%>", QRegularExpression::DotMatchesEverythingOption);
		// Check for matches and replace them
		while (qreSubstitution.match(strLine).hasMatch()) {
			// Make sure the parent can convert
			if (this->mView->getPageValue(qreSubstitution.match(strLine).captured(1)).canConvert(QMetaType::QVariantMap)) {
				// Localize the parent
				QMap<QString, QVariant> qvmSubstitution = this->mView->getPageValue(qreSubstitution.match(strLine).captured(1)).toMap();
				// Check for the child
				if (qvmSubstitution.contains(qreSubstitution.match(strLine).captured(2))) {
					// Make the replacement
					strLine.replace(qreSubstitution.match(strLine).captured(0), qvmSubstitution.value(qreSubstitution.match(strLine).captured(2)).toString());
				} else {
					// Set the warning
					strLine.replace(qreSubstitution.match(strLine).captured(0), QString("WARNING:  Variable \"$%1\" has no property:  %2").arg(qreSubstitution.match(strLine).captured(1), qreSubstitution.match(strLine).captured(2)));
				}
			} else {
				// Set the variable with the warning
				strLine.replace(qreSubstitution.match(strLine).captured(0), QString("WARNING:  Variable \"$%1\" is undefined!").arg(qreSubstitution.match(strLine).captured(1)));
			}
		}
		// Reset the pattern to a plain variable
		qreSubstitution.setPattern("<%=\\s*?\\$([a-zA-Z0-9_-]+)\\s*?%>");
		// Check for matches and replace them
		while (qreSubstitution.match(strLine).hasMatch()) {
			// Grab the variable
			QString strSubstitution = this->mView->getPageValue(qreSubstitution.match(strLine).captured(1)).toString();
			//
			// Chec kfor a null variable
			if (strSubstitution.isNull()) {
				// Set the variable with the warning
				strSubstitution = QString("WARNING:  Variable \"%1\" is undefined!").arg(qreSubstitution.match(strLine).captured(1).prepend("$"));
			}
			// Reset the line
			strLine = strLine.replace(qreSubstitution.match(strLine).captured(0), strSubstitution);
		}
	}

	bool Template::isBoolean(QString strVariable) {
		// Create the pattern
		QRegularExpression qreBooleanTest("^(false|true)$", QRegularExpression::DotMatchesEverythingOption|QRegularExpression::CaseInsensitiveOption);
		// Check for matches
		if (qreBooleanTest.match(strVariable).hasMatch()) {
			// This is a boolean
			return true;
		}
		// This is not a boolean
		return false;
	}

	bool Template::isFloat(QString strVariable) {
		// Create the pattern
		QRegularExpression qreFloatTest("^([0-9]+\\.[0-9]+)$", QRegularExpression::DotMatchesEverythingOption|QRegularExpression::CaseInsensitiveOption);
		// Check for matches
		if (qreFloatTest.match(strVariable).hasMatch()) {
			// This is a float
			return true;
		}
		// This is not a float
		return false;
	}

	bool Template::isInteger(QString strVariable) {
		// Create the pattern
		QRegularExpression qreIntegerTest("^([0-9]+)$", QRegularExpression::DotMatchesEverythingOption|QRegularExpression::CaseInsensitiveOption);
		// Check for matches
		if (qreIntegerTest.match(strVariable).hasMatch()) {
			// This is an integer
			return true;
		}
		// This is not an integer
		return false;
	}

	bool Template::isNumeric(QString strVariable) {
		// Create the pattern
		QRegularExpression qreNumericTest("^[0-9]+\\.?[0-9]+?$", QRegularExpression::DotMatchesEverythingOption|QRegularExpression::CaseInsensitiveOption);
		// Check for matches
		if (qreNumericTest.match(strVariable).hasMatch()) {
			// This is numeric
			return true;
		}
		// This is not numeric
		return false;
	}

	bool Template::isTrue(QString strPageValue, QString strOperator, QString strOperand) {
		// Check for a variable notation
		if (strOperand.at(0) == '$') {
			// Reset the operand to the page value
			strOperand = this->mView->getPageValue(strOperand.replace("$", "")).toString();
		}
		// Check the operand for the undefined keyword
		if ((strOperand.toLower() == "undef") || (strOperand.toLower() == "undefined")) {
			// Check to see if the page value exists
			if (this->mView->getPageValue(strPageValue).isNull()) {
				// The page value is not defined
				return ((strOperator == "eq" || strOperator == "==") ? true : false);
			}
			// The page value is defined
			return ((strOperator == "eq" || strOperator == "==") ? false : true);
		}
		// Determine the operator
		if ((strOperator == "eq") || (strOperator == "==")) {             // Equality
			// Run the condition
			if (this->mView->getPageValue(strPageValue).toString() == strOperand) {
				// Match
				return true;
			} else {
				// No match
				return false;
			}
		} else if ((strOperator == "gt") || (strOperator == ">")) {       // Greater Than
			// Convert the type to Float
			if (this->mView->getPageValue(strPageValue).canConvert(QMetaType::Float)) {
				// Run the condition
				if (this->mView->getPageValue(strPageValue).toFloat() > strOperand.toFloat()) {
					// Match
					return true;
				} else {
					// No match
					return false;
				}
			} else if (this->mView->getPageValue(strPageValue).canConvert(QMetaType::Int)) {
				// Run the condition
				if (this->mView->getPageValue(strPageValue).toInt() > strOperand.toInt()) {
					// Match
					return true;
				} else {
					// No match
					return false;
				}
			} else {
				// No match or conversion available
				return false;
			}
		} else if ((strOperator == "gte") || (strOperator == ">=")) { // Greater Than or Equal To
			// Convert the type to Float
			if (this->mView->getPageValue(strPageValue).canConvert(QMetaType::Float)) {
				// Run the condition
				if (this->mView->getPageValue(strPageValue).toFloat() >= strOperand.toFloat()) {
					// Match
					return true;
				} else {
					// No match
					return false;
				}
			} else if (this->mView->getPageValue(strPageValue).canConvert(QMetaType::Int)) {
				// Run the condition
				if (this->mView->getPageValue(strPageValue).toInt() >= strOperand.toInt()) {
					// Match
					return true;
				} else {
					// No match
					return false;
				}
			} else {
				// No match or conversion available
				return false;
			}
		} else if ((strOperator == "lt") || (strOperator == "<")) {   // Less Than
			// Convert the type to Float
			if (this->mView->getPageValue(strPageValue).canConvert(QMetaType::Float)) {
				// Run the condition
				if (this->mView->getPageValue(strPageValue).toFloat() < strOperand.toFloat()) {
					// Match
					return true;
				} else {
					// No match
					return false;
				}
			} else if (this->mView->getPageValue(strPageValue).canConvert(QMetaType::Int)) {
				// Run the condition
				if (this->mView->getPageValue(strPageValue).toInt() < strOperand.toInt()) {
					// Match
					return true;
				} else {
					// No match
					return false;
				}
			} else {
				// No match or conversion available
				return false;
			}
		} else if ((strOperator == "lte") || (strOperator == "<=")) { // Less Than or Equal To
			// Convert the type to Float
			if (this->mView->getPageValue(strPageValue).canConvert(QMetaType::Float)) {
				// Run the condition
				if (this->mView->getPageValue(strPageValue).toFloat() <= strOperand.toFloat()) {
					// Match
					return true;
				} else {
					// No match
					return false;
				}
			} else if (this->mView->getPageValue(strPageValue).canConvert(QMetaType::Int)) {
				// Run the condition
				if (this->mView->getPageValue(strPageValue).toInt() <= strOperand.toInt()) {
					// Match
					return true;
				} else {
					// No match
					return false;
				}
			} else {
				// No match or conversion available
				return false;
			}
		} else if ((strOperator == "neq") || (strOperator == "<>") || (strOperator == "!=")) { // Non-Equality
			// Run the condition
			if (this->mView->getPageValue(strPageValue).toString() != strOperand) {
				// Match
				return true;
			} else {
				// No match
				return false;
			}
		} else {
			// Return false by default
			return false;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Template* Template::process(View* objView, QString strTemplate) {
		// Check for a provided view
		if (objView) {
			// Set the view into the instance
			this->mView = objView;
		}
		// Determine the template path
		this->determineTemplatePath(strTemplate);
		// Define our handle
		QFile qfTemplate(this->mTemplateFile);
		// Try to open the file
		if (!qfTemplate.open(QFile::ReadOnly|QFile::Text)) {
			// Execute the route
			QMetaObject::invokeMethod(new ErrorController, "ServerFault", Qt::AutoConnection, Q_ARG(CGI*&, this->mRequest), Q_ARG(View*&, objView), Q_ARG(QString, QString("Unable to load view file:  %1").arg(this->mTemplateFile)));
			// Set the template file
			this->mTemplateFile = objView->getTemplate();
			// Process the error route
			qfTemplate.setFileName(this->mTemplateFile);
			// Open the file
			qfTemplate.open(QFile::ReadOnly|QFile::Text);
		}
		// Create the file stream
		QTextStream qtsTemplate(&qfTemplate);
		// Read the file line-by-line
		while (!qtsTemplate.atEnd()) {
			// Grab the line
			QString strLine = qtsTemplate.readLine();
			// Append the line to the instance
			this->mTemplate.append(strLine.append("\n"));
		}
		// Process variable assignments
		this->doAssignments(this->mTemplate);
		// Process comments
		this->doComments(this->mTemplate);
		// Process inclusions
		this->doInclusion(this->mTemplate);
		// Process foreach loops
		this->doForEach(this->mTemplate);
		// Process conditionals
		this->doConditional(this->mTemplate);
		// Process JSON requests
		this->doJSON(this->mTemplate);
		// Process the meta tags
		this->doMetaTags(this->mTemplate);
		// Process the scripts
		this->doScripts(this->mTemplate);
		// Process the styles
		this->doStyles(this->mTemplate);
		// Process the substitutions
		this->doSubstitution(this->mTemplate);
		// We're done
		return this;
	}

	Template* Template::processString(QString strTemplate, View* objView) {
		// Check for a view
		if (objView) {
			// Set the view into the instance
			this->mView = objView;
		}
		// Set the template into the instance
		this->mTemplate = strTemplate;
		// Process variable assignments
		this->doAssignments(this->mTemplate);
		// Process comments
		this->doComments(this->mTemplate);
		// Process inclusions
		this->doInclusion(this->mTemplate);
		// Process foreach loops
		this->doForEach(this->mTemplate);
		// Process conditionals
		this->doConditional(this->mTemplate);
		// Process JSON requests
		this->doJSON(this->mTemplate);
		// Process the meta tags
		this->doMetaTags(this->mTemplate);
		// Process the scripts
		this->doScripts(this->mTemplate);
		// Process the styles
		this->doStyles(this->mTemplate);
		// Process the substitutions
		this->doSubstitution(this->mTemplate);
		// Return the instance
		return this;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString Template::getTemplate() {
		// Return the processed template from the instance
		return this->mTemplate;
	}

	bool Template::getTemplateReadStatus() {
		// Return the template read failure flag
		return this->mTemplateReadFailure;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setters //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Template* Template::setLogger(Log* &objLogger) {
		// Set the logger object into the instance
		this->mLog = objLogger;
		// Return the instance
		return this;
	}

	Template* Template::setRequest(CGI* objRequest) {
		// Set the request object into the instance
		this->mRequest = objRequest;
		// Return the instance
		return this;
	}

	Template* Template::setView(View* objView) {
		// Set the view object into the instance
		this->mView = objView;
		// Return the instance
		return this;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace HeimdallGI
