///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Router.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Globals //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Router* Router::mInstance = NULL;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Singleton ////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Router* Router::Instance(bool bReset) {
		// Check for an existing instance
		if ((mInstance == NULL) || (bReset == true)) {
			// Create a new instance
			mInstance = new Router();
		}
		// Return the instance
		return mInstance;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Constructor //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Router::Router(QObject* qoParent, CGI* objRequest) : QObject(qoParent) {
		// Check for a request object
		if (objRequest != NULL) {
			// Set the request object into the instance
			this->SetRequest(objRequest);
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool Router::ReverseMatchPath(QString strPattern, QString strPath, QVariantMap &qvmParameters) {
		// Split the pattern
		QStringList qslPattern = strPattern.split('/');
		// Split the path
		QStringList qslPath    = strPath.split('/');
		// Make sure the lists match in size
		if (qslPath.size() != qslPattern.size()) {
			// There is no possibility of a match
			return false;
		}
		// Define the pattern parameter pattern
		QRegularExpression qrePatternParameter("^[:[a-zA-Z0-9_-]+]$");
		// Loop through the pattern
		for (int intPart = 0; intPart < qslPattern.size(); ++intPart) {
			// Grab the matches
			QRegularExpressionMatch qremPatternPart = qrePatternParameter.match(qslPattern.at(intPart));
			// Check for an exact match
			if (qslPattern[intPart] == qslPath[intPart]) {
				// Continue to the next iteration
				continue;
			} else if (qremPatternPart.hasMatch() && QRegularExpression("^[a-zA-Z0-9_-]+$").match(qslPath.at(intPart)).hasMatch()) {
				// Define the variable name
				QString strName  = qremPatternPart.capturedTexts().at(0);
				// Remove the unwanted characters
				strName.replace("[", "").replace(":", "").replace("]", "");
				// Define the value
				QString strValue = qslPath.at(intPart);
				// Add the parameter to the map
				qvmParameters.insert(strName, strValue);
			} else {
				// Something doesn't match
				return false;
			}
		}
		// We're done
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Public Methods ///////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Router* Router::AddRoute(QString strPath, QObject* objController, QByteArray qbaMethod) {
		// Assert the Controller
		Q_ASSERT(objController);
		// Assert the View Method
		Q_ASSERT(qbaMethod.constData());
		// Define a success notifier
		bool bSuccess                    = true;
		// Load the controller's meta data
		const QMetaObject* qmoController = objController->metaObject();
		// Loop through the methods
		for (int intMethod = qmoController->methodOffset(); intMethod < qmoController->methodCount(); ++intMethod) {
			// Check the method
			if (qmoController->method(intMethod).name() == qbaMethod) {
				// Load the argument types
				const QList<QByteArray> qlArgumentTypes = qmoController->method(intMethod).parameterTypes();
				// Make sure we have the right number of arguments
				if (qlArgumentTypes.isEmpty() || (qlArgumentTypes.size() < 2)) {
					// Send the error
					qDebug() << "[WARN]\tThe view method '" << qbaMethod << "' must accept at least two arguments.";
					// There was an error
					bSuccess = false;
				}
				// Make sure the first argument is HeimdallGI::CGI
				if ((qlArgumentTypes[0] != "HeimdallGI::CGI*")) {
					// Send the error
					qDebug() << "[WARN]\tThe view method '" << qbaMethod << "' should have its first argument as the type HeimdallGI::CGI. (" << qlArgumentTypes[0] << ")";
					// There was an error
					bSuccess = false;
				}
				// Make sure the second argument is HeimdallGI::View
				if ((qlArgumentTypes[1] != "HeimdallGI::View*&")) {
					// Send the error
					qDebug() << "[WARN]\tThe view method '" << qbaMethod << "' should have its second argument as the type HeimdallGI::View. (" << qlArgumentTypes[1] << ")";
					// There was an error
					bSuccess = false;
				}
			}
			// Check for success
			if (bSuccess == true) {
				// Define the route map
				Route structRoute;
				// Set the path
				structRoute.setPath(strPath);
				// Set the controller
				structRoute.setController(objController);
				// Set the View Method
				structRoute.setViewMethod(qbaMethod);
				// Add the route to the instance
				this->mRoutes.append(structRoute);
			}
			// We're done
			return this;
		}
		// Return the instance
		return this;
	}

	View* Router::Execute(CGI* objRequest, QString strPath) {
		// Traverse the routes
		for (int intRoute = 0; intRoute < this->mRoutes.size(); ++intRoute) {
			// Define the parameter map
			QVariantMap qvmParameters;
			// Set the route into the structure
			Route structRoute = this->mRoutes.at(intRoute);
			// Check for a match
			if (structRoute.getController() && this->ReverseMatchPath(structRoute.getPath(), strPath, qvmParameters)) {
				// Traverse the parameters map
				for (QVariantMap::const_iterator itrParameters = qvmParameters.begin(); itrParameters != qvmParameters.end(); ++itrParameters) {
					// Add the parameter to the CGI request
					objRequest->AddParameter(itrParameters.key(), itrParameters.value().toString());
				}
				// Define the response
				View* viewResponse = new HeimdallGI::View;
				// Define the invoke argument list
				QList<QGenericArgument> qlArguments;
				// Add the firs argument (HeimdallGI::CGI*)
				qlArguments << Q_ARG(HeimdallGI::CGI*, objRequest);
				// Add the second argument (HeimdallGI::View*)
				qlArguments << Q_ARG(HeimdallGI::View*&, viewResponse);
				// Provide filler arguments, if need be
				while (qlArguments.size() < 10) {
					// Add the filler argument
					qlArguments << QGenericArgument();
				}
				// Invoke the controller and view
				if (!QMetaObject::invokeMethod(structRoute.getController(), structRoute.getViewMethod(), Qt::DirectConnection, qlArguments[0], qlArguments[1], qlArguments[2], qlArguments[3], qlArguments[4], qlArguments[5], qlArguments[6], qlArguments[7], qlArguments[8], qlArguments[9]) || !viewResponse) {
					// Send the error
					qDebug() << "Unable to load the view.  (HeimdallGI::Router Line 157)";
				}
				// Setup the template
				Template::Instance()
						->Process(viewResponse);
				// Return the response
				return viewResponse->SetTemplate(Template::Instance()->GetTemplate());
			}
		}
		// Return an empty response
		return 0;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setters //////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Router* Router::SetRequest(CGI* objRequest) {
		// Set the request object into the instance
		this->mRequest = objRequest;
		// Return the instance
		return this;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
