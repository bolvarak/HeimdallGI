///////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#ifndef HEIMDALLGI_MAXMIND_H
#define HEIMDALLGI_MAXMIND_H

///////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "QHostAddress"
#include "QMetaType"
#include "QObject"
#include "QString"
#include "GeoIP.h"
#include "GeoIPCity.h"

///////////////////////////////////////////////////////////////////////////////
/// HeimdallGI Namespace /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////
	/// HeimdallGI::MaxMind Class Definition /////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	class MaxMind : public QObject
	{
			/**
			 * Ensure this class is recognized by Qt
			 */
			Q_OBJECT

		///////////////////////////////////////////////////////////////////////
		/// Protected Methods & Properties ///////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		protected:

			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains the singleton instance of this class
			 * @brief HeimdallGI::MaxMind::mInstance
			 * @var HeimdallGI::MaxMind*
			 */
			static MaxMind* mInstance;


			GeoIP

		///////////////////////////////////////////////////////////////////////
		/// Public Methods & Properties //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////////
			/// Singleton ////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method maintains access to the singleton instance of this class
			 * @brief HeimdallGI::MaxMind::Instance()
			 * @param bool blnReset [false]
			 * @return HeimdallGI::MaxMind* HeimdallGI::MaxMind::mInstance
			 */
			static MaxMind* Instance(bool blnReset = false);


			///////////////////////////////////////////////////////////////////
			/// Constructor //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			explicit MaxMind(QObject* qoParent = 0);

			///////////////////////////////////////////////////////////////////
			/// Destructor ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			~MaxMind();

	///////////////////////////////////////////////////////////////////////////
	/// End HeimdallGI::MaxMind Class Definition /////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	};

///////////////////////////////////////////////////////////////////////////////
/// End HeimdallGI Namespace /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

}

///////////////////////////////////////////////////////////////////////////////
/// End Definitions //////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#endif
