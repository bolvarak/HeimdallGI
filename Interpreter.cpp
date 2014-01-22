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
		this->ReloadCore();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool Interpreter::Process(QString strSource, QString strOperation) {
		// Fire the signal
		emit this->Status(Processing);

		return true;
	}

	void Interpreter::ReloadCore() {
		// Read the HGML backend core file
		QFile qfHGML(":/Configuration/HGML.json");
		// Open the HGML core file
		qfHGML.open(QIODevice::ReadOnly|QIODevice::Text);
		// Define the JSON container
		QJsonDocument qjdHGMLCore = QJsonDocument::fromJson(qfHGML.readAll());
		// Close the file
		qfHGML.close();
		// Store the core engine
		this->mCore               = qjdHGMLCore.toVariant().toMap();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
