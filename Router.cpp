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
			this->setRequest(objRequest);
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Protected Methods ////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool Router::reverseMatchPath(QString strPattern, QString strPath, QVariantMap &qvmParameters) {
		// Log the path and pattern
		this->mLog->Add(strPath, strPattern);
		// Check for a direct match
		if (strPath == strPattern) {
			// We're done
			return true;
		}
		// Check the path
		if (strPath.endsWith('/'))    { strPath.chop(1);    }
		// Check the pattern
		if (strPattern.endsWith('/')) { strPattern.chop(1); }
		// Split the pattern
		QStringList qslPattern = strPattern.split('/');
		// Split the path
		QStringList qslPath    = strPath.split('/');
		// Check the path
		if (qslPath.at(0).isEmpty())    { qslPath.removeFirst();    }
		// Check the pattern
		if (qslPattern.at(0).isEmpty()) { qslPattern.removeFirst(); }
		// Make sure the lists match in size
		if (qslPath.size() != qslPattern.size()) {
			// There is no possibility of a match
			return false;
		}
		// Define the pattern parameter pattern
		QRegularExpression qrePatternParameter("\\[:[a-zA-Z0-9_-]+\\]");
		// Loop through the pattern
		for (int intPart = 0; intPart < qslPattern.size(); ++intPart) {
			// Grab the matches
			QRegularExpressionMatch qremPatternPart = qrePatternParameter.match(qslPattern.at(intPart));
			// Check for an exact match
			if (qslPattern[intPart] == qslPath[intPart]) {
				// Continue to the next iteration
				continue;
			} else if (qremPatternPart.hasMatch() && QRegularExpression("[a-zA-Z0-9_-]+").match(qslPath.at(intPart)).hasMatch()) {
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

	Router* Router::addRoute(QString strPath, Abstract::Endpoint* objController, QByteArray qbaMethod) {
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
					this->mLog->Add("WARN", QString("The view method '%1' must accept at least two argument.").arg(QString(qbaMethod)));
					// There was an error
					bSuccess = false;
				}
				// Make sure the first argument is HeimdallGI::CGI
				if ((qlArgumentTypes[0] != "HeimdallGI::CGI*&")) {
					// Send the error
					this->mLog->Add("WARN", QString("The view method '%1' should have its first argument as the type HeimdallGI::CGI*&.  (%2)").arg(QString(qbaMethod), QString(qlArgumentTypes.at(0))));
					// There was an error
					bSuccess = false;
				}
				// Make sure the second argument is HeimdallGI::View
				if ((qlArgumentTypes[1] != "HeimdallGI::View*&")) {
					// Send the error
					this->mLog->Add("WARN", QString("The view method '%1' should have its second argument as the type HeimdallGI::View*&.  (%2)").arg(QString(qbaMethod), QString(qlArgumentTypes.at(1))));
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

	View* Router::execute(CGI* &objRequest, QString strPath) {
		// Check for a path
		if (strPath.isEmpty()) {
			// Set the path to the REQUEST_URI
			strPath = objRequest->getRequestHeader("REQUEST_URI").replace(QString("?%1").arg(objRequest->getRequestHeader("QUERY_STRING")), "").replace(this->mBaseURI, "");
		}
		this->mLog->Add("InitialPath", strPath);
		// Check the last character for a slash
		if ((strPath.at(strPath.size() - 1) == '/') && (strPath != "/")) {
			// Remove the last character
			strPath.chop(1);
		}
		// Log the path
		this->mLog->Add("Path", strPath);
		// Define the response
		View* viewResponse = new HeimdallGI::View;
		// Traverse the routes
		for (int intRoute = 0; intRoute < this->mRoutes.size(); ++intRoute) {
			// Define the parameter map
			QVariantMap qvmParameters;
			// Set the route into the structure
			Route structRoute = this->mRoutes.at(intRoute);
			// Log the route
			this->mLog
					->Add(QString("Controller %1").arg(QString::number(intRoute + 1)), QString(structRoute.getController()->metaObject()->className()))
					->Add(QString("View %1").arg(QString::number(intRoute + 1)), structRoute.getViewMethod())
					->Add(QString("Route Path %1").arg(QString::number(intRoute + 1)), structRoute.getPath());
			// Check for a match
			if (structRoute.getController() && this->reverseMatchPath(structRoute.getPath(), strPath, qvmParameters) == true) {
				// Log the match
				this->mLog->Add("ReverseMatch", "SUCCESS");
				// Traverse the parameters map
				for (QVariantMap::const_iterator itrParameters = qvmParameters.begin(); itrParameters != qvmParameters.end(); ++itrParameters) {
					// Add the parameter to the CGI request
					objRequest->addParameter(itrParameters.key(), itrParameters.value().toString());
				}
				// Define the invoke argument list
				QList<QGenericArgument> qlArguments;
				// Add the firs argument (HeimdallGI::CGI*)
				qlArguments << Q_ARG(HeimdallGI::CGI*&, objRequest);
				// Add the second argument (HeimdallGI::View*)
				qlArguments << Q_ARG(HeimdallGI::View*&, viewResponse);
				// Provide filler arguments, if need be
				while (qlArguments.size() < 10) {
					// Add the filler argument
					qlArguments << QGenericArgument();
				}
				// Invoke the controller and view
				if (!QMetaObject::invokeMethod(structRoute.getController(), structRoute.getViewMethod(), Qt::AutoConnection, qlArguments[0], qlArguments[1], qlArguments[2], qlArguments[3], qlArguments[4], qlArguments[5], qlArguments[6], qlArguments[7], qlArguments[8], qlArguments[9]) || !viewResponse) {
					// Reset the view response
					viewResponse = new View;
					// Send the error to the log
					this->mLog->Add("ERROR", "Unable to load the view.  (HeimdallGI::Router Line 157)");
					// Execute a server fault
					QMetaObject::invokeMethod(new ErrorController, "ServerFault", Qt::AutoConnection, Q_ARG(CGI*&, objRequest), Q_ARG(View*&, viewResponse), Q_ARG(QString, QString("Unable to process view method:  ").append(structRoute.getViewMethod())));
				}
				// Check the view for file processing
				if ((viewResponse->getViewStatus() == true) && (viewResponse->getTemplate().isEmpty() == false)) {
					// Check for a layout
					if (viewResponse->getLayout().isEmpty() == false) {
						// Instantiate the route template
						Template* tplRoute = new Template;
						// Instantiate the view template
						Template* tplView  = new Template;
						// Process and set the body
						viewResponse->setPageValue("__body__", tplView->setLogger(this->mLog)->setRequest(objRequest)->process(viewResponse)->getTemplate());
						// Process the layout
						tplRoute
							->setLogger(this->mLog)
							->setRequest(objRequest)
							->process(viewResponse, viewResponse->getLayout());
						// Set the template
						viewResponse->setTemplate(tplRoute->getTemplate());
					} else {
						// Instantiate the template
						Template* tplRoute = new Template;
						// Setup the template
						tplRoute
							->setLogger(this->mLog)
							->setRequest(objRequest)
							->process(viewResponse);
						// Set the template into the view
						viewResponse->setTemplate(tplRoute->getTemplate());
					}
				} else {
					// Reset the view response
					viewResponse = new View;
					// If we get down to this point, execute the error controller
					if (!QMetaObject::invokeMethod(new ErrorController, "NotFound", Qt::AutoConnection, Q_ARG(CGI*&, objRequest), Q_ARG(View*&, viewResponse))) {
						// Execute a server fault
						QMetaObject::invokeMethod(new ErrorController, "ServerFault", Qt::AutoConnection, Q_ARG(CGI*&, objRequest), Q_ARG(View*&, viewResponse), Q_ARG(QString, "Unable to execute HeimdallGI::ErrorController::NotFound()"));
					}
					// Instantiat the template
					Template* tplError = new Template;
					// Setup the template
					tplError
						->setLogger(this->mLog)
						->setRequest(objRequest)
						->process(viewResponse);
					// Return the response
					return viewResponse->setTemplate(tplError->getTemplate());
				}
				// Return the view
				return viewResponse;
			}
		}
		// Log the match fail
		this->mLog->Add("ReverseMatch", "FAIL");
		// Reset the view response
		viewResponse = new View;
		// Log
		this->mLog->Add("404", "EXECUTING");
		// If we get down to this point, execute the error controller
		if (!QMetaObject::invokeMethod(new ErrorController, "NotFound", Qt::DirectConnection, Q_ARG(CGI*&, objRequest), Q_ARG(View*&, viewResponse))) {
			// Execute a server fault
			QMetaObject::invokeMethod(new ErrorController, "ServerFault", Qt::DirectConnection, Q_ARG(CGI*&, objRequest), Q_ARG(View*&, viewResponse), Q_ARG(QString, "Unable to execute HeimdallGI::ErrorController::NotFound()"));
		}
		// Log
		this->mLog->Add("404", "SUCCESS");
		// Instantiate the template
		Template* tplError = new Template;
		// Setup the template
		tplError
			->setLogger(this->mLog)
			->setRequest(objRequest)
			->process(viewResponse);
		// Return the response
		return viewResponse->setTemplate(tplError->getTemplate());
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getters //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	QString Router::getBaseURI() {
		// Return the baseURI from the instance
		return this->mBaseURI;
	}

	QList<Route> Router::getRoutes() {
		// Return the routes
		return this->mRoutes;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setters //////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Router* Router::setBaseURI(QString strBaseURI) {
		// Check the last character of the URI
		if (strBaseURI.at(strBaseURI.size() - 1) == '/') {
			// Reset the URI
			strBaseURI = strBaseURI.remove((strBaseURI.size()), 1);
		}
		// Set the baseURI into the instance
		this->mBaseURI = strBaseURI;
		// We're done
		return this;
	}

	Router* Router::setLogger(Log *&objLogger) {
		// Set the logger into the instance
		this->mLog = objLogger;
		// Return the instance
		return this;
	}

	Router* Router::setRequest(CGI* &objRequest) {
		// Set the request object into the instance
		this->mRequest = objRequest;
		// Return the instance
		return this;
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
