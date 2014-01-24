///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Interpreter.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Globals //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Interpreter* Interpreter::mInstance    = NULL;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constants ////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString Interpreter::HGMLNotation      = "<%(.*?)%>";

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Singleton ////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Interpreter* Interpreter::Instance(bool bReset) {
		// Check for an existing instance or a reset flag
		if ((mInstance == NULL) || (bReset == true)) {
			// Instantiate the class
			mInstance = new Interpreter;
		}
		// Return the instance
		return mInstance;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Interpreter::Interpreter(QObject* qoParent) : QObject(qoParent) {
		// Reload the HGML Engine
		this->ReloadEngine();
		// Add the Functions interpreter
		this->AddInterpretationClass(QString("HeimdallGI::Interpretation::Functions"), new HeimdallGI::Interpretation::Functions);
		// Fire the initialization signal
		emit this->Initialization(*this);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool Interpreter::Process(QString strSource, QString strOperation) {
		// Fire the signal
		emit this->Status(Processing);
		// We're done
		return true;
	}

	void Interpreter::ReloadEngine() {
		// Read the HGML backend core file
		QFile qfHGML(":/Configuration/HGML.json");
		// Open the HGML core file
		qfHGML.open(QIODevice::ReadOnly|QIODevice::Text);
		// Define the JSON container
		QJsonDocument qjdHGMLCore           = QJsonDocument::fromJson(qfHGML.readAll());
		// Close the file
		qfHGML.close();
		// Store the core engine
		this->mCore                         = qjdHGMLCore.toVariant().toMap();
		// Localize the functions
		QMap<QString, QVariant> qmFunctions = qjdHGMLCore.toVariant().toMap().value("Interpreter").toMap().value("Functions").toMap();
		// Iterate over the functions
		for (QMap<QString, QVariant>::const_iterator itrFunction = qmFunctions.constBegin(); itrFunction != qmFunctions.constEnd(); ++itrFunction) {
			// Create the arguments placeholder
			QList<InterpretedFunctionArgument> qlArguments;
			// Iterate over the arguments
			for (int intArgument = 0; intArgument != itrFunction.value().toMap().value("Arguments").toList().size(); ++itrFunction) {
				// Localize the argument
				QMap<QString, QVariant> qmArgument = itrFunction.value().toMap().value("Arguments").toList().at(intArgument).toMap();
				// Create the structure
				InterpretedFunctionArgument ifaArgument(
					qmArgument.value("Name").toString(),
					qmArgument.value("Type").toString(),
					qmArgument.value("Required").toBool(),
					qmArgument.value("Default", QVariant("undefined"))
				);
				// Add the argument to the list
				qlArguments.append(ifaArgument);
			}
			// Create the structure
			InterpretedFunction ifnFunction(
				itrFunction.key(),
				qlArguments,
				itrFunction.value().toMap().value("Expression").toString(),
				itrFunction.value().toMap().value("Class").toString(),
				itrFunction.value().toMap().value("Method").toString(),
				itrFunction.value().toMap().value("Returns").toStringList()
			);
			// Add the function to the instance
			this->AddFunction(ifnFunction);
		}
	}

	void Interpreter::SanityCheckDuplicateFunctions(QString strName) {
		// Iterate over the funcitons
		for (int intFunction = 0; intFunction < this->mInterpretationFunctions.size(); ++intFunction) {
			// Localize the funciton
			InterpretedFunction ifnFunction = this->mInterpretationFunctions.at(intFunction);
			// Check the name
			if (ifnFunction.getName().toUpper() == strName.toUpper()) {
				// Remove the function
				this->mInterpretationFunctions.removeAt(intFunction);
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Interpreter* Interpreter::AddFunction(InterpretedFunction ifnFunction) {
		// Run the sanity check
		this->SanityCheckDuplicateFunctions(ifnFunction.getName());
		// Append the function to the list
		this->mInterpretationFunctions.append(ifnFunction);
		// Return the instance
		return this;
	}

	Interpreter* Interpreter::AddFunction(QString strName, QList<InterpretedFunctionArgument> qlArguments, QString strClass, QString strMethod, QString strExpression, QStringList qslReturns) {
		// Run the sanity check
		this->SanityCheckDuplicateFunctions(strName);
		// Create the structure
		InterpretedFunction ifnFunction;
		// Set the name
		ifnFunction.setName(strName);
		// Set the arguments
		ifnFunction.setArguments(qlArguments);
		// Set the class
		ifnFunction.setClass(strClass);
		// Set the method
		ifnFunction.setMethod(strMethod);
		// Set the expression
		ifnFunction.setExpression(strExpression);
		// Set the return types
		ifnFunction.setReturnTypes(qslReturns);
		// Append the function to the instance
		this->mInterpretationFunctions.append(ifnFunction);
		// Return the instance
		return this;
	}

	Interpreter* Interpreter::AddFunction(QString strName, QList<QVariantMap> qlArguments, QString strClass, QString strMethod, QString strExpression, QStringList qslReturns) {
		// Run the sanity check
		this->SanityCheckDuplicateFunctions(strName);
		// Create the structure
		InterpretedFunction ifnFunction;
		// Set the name
		ifnFunction.setName(strName);
		// Set the arguments
		ifnFunction.setArguments(qlArguments);
		// Set the class
		ifnFunction.setClass(strClass);
		// Set the method
		ifnFunction.setMethod(strMethod);
		// Set the expression
		ifnFunction.setExpression(strExpression);
		// Set the return types
		ifnFunction.setReturnTypes(qslReturns);
		// Append the function to the instance
		this->mInterpretationFunctions.append(ifnFunction);
		// Return the instance
		return this;
	}

	Interpreter* Interpreter::AddInterpretationClass(QString strName, QObject* hgiInterpreterInstance) {
		// Add the class to the instance
		this->mInterpretationClasses.insert(strName, hgiInterpreterInstance);
		// Return the instance
		return this;
	}

	Interpreter* Interpreter::Execute() {
		// Setup the expression
		QRegularExpression qreInterpret(this->mMarkupNotation.isEmpty() ? Interpreter::HGMLNotation : this->mMarkupNotation);
		// Check for matches
		if (qreInterpret.match(this->mSource).hasMatch() == false) {
			// Fire the signals
			emit this->Status(Finished);
			// We're done
			return this;
		}
		// Iterate over the matches
		while (qreInterpret.match(this->mSource).hasMatch()) {
			// Check for success
			if (this->Process(qreInterpret.match(this->mSource).captured(0), qreInterpret.match(this->mSource).captured(1)) == false) {
				// Fire the signals
				emit this->Exception(this->mLastExpception);
				emit this->Status(Failure);
				// Break out of the loop
				break;
			}
		}
		// Return the instance
		return this;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString Interpreter::GetInterpretation() {
		// Return the interpreted source
		return this->mSource;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setters //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Interpreter* Interpreter::SetLogger(Log* &hgiLogger) {
		// Set the logger into the instance
		this->mLogger = hgiLogger;
		// Return the instance
		return this;
	}

	Interpreter* Interpreter::SetMarkupNotation(QString strExpression) {
		// Create an expression placeholder
		QRegularExpression qreTest;
		// Set the pattern
		qreTest.setPattern(strExpression);
		// Validate the expression
		if (qreTest.isValid() == true) {
			// Set the HGML expression into the instance
			this->mMarkupNotation = strExpression;
		}
		// Return the instance
		return this;
	}

	Interpreter* Interpreter::SetSource(QString strSource) {
		// Set the source into the instance
		this->mSource = strSource;
		// Return the instance
		return this;
	}

	Interpreter* Interpreter::SetView(View* &hgiResponse) {
		// Set the view object into the instance
		this->mView = hgiResponse;
		// Return the instance
		return this;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
