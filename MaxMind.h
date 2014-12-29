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
	/// Structures ///////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////


	struct GeoRecord {

			///////////////////////////////////////////////////////////////////
			/// Properties ///////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This property contains the city of the IP address
			 * @brief HeimdallGI::GeoRecord::mCity
			 * @var QString
			 */
			QString mCity;

			/**
			 * @paragraph This property contains the ISO-3166-1-A2 country code of the IP address
			 * @brief HeimdallGI::GeoRecord::mContinentISO
			 * @var QString
			 */
			QString mContinentISO;

			/**
			 * @paragraph This property contains the country of the IP address
			 * @brief HeimdallGI::GeoRecord::mCountry
			 * @var QString
			 */
			QString mCountry;

			/**
			 * @paragraph This property contains the ISO-3166-1-A2 country code of the IP address
			 * @brief HeimdallGI::GeoRecord::mCountryISO
			 * @var QString
			 */
			QString mCountryISO;

			/**
			 * @paragraph This property contains the Internet Service Provider (ISP) of the IP address
			 * @brief HeimdallGI::GeoRecord::mISP
			 * @var QString
			 */
			QString mISP;

			/**
			 * @paragraph This property contains the latitude of the IP address
			 * @brief HeimdallGI::GeoRecord::mLatitude
			 * @var float
			 */
			float mLatitude;

			/**
			 * @paragraph This property contains the longitude of the IP address
			 * @brief HeimdallGI::GeoRecord::mLongitude
			 * @var float
			 */
			float mLongitude;

			/**
			 * @paragraph This property contains the region or stat of the IP address
			 * @brief HeimdallGI::GeoRecord::mRegion
			 * @var QString
			 */
			QString mRegion;

			/**
			 * @paragraph This property contains the time zone of the IP address
			 * @brief HeimdallGI::GeoRecord::mTimeZone
			 * @var QString
			 */
			QString mTimeZone;

			///////////////////////////////////////////////////////////////////
			/// Constructors /////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This constructor creates an empty HeimdallGI::GeoRecord
			 * @brief HeimdallGI::GeoRecord()
			 * @return HeimdallGI::GeoRecord
			 */
			GeoRecord() {}

			/**
			 * @paragraph This constructor builds a complete HeimdallGI::GeoRecord
			 * @brief HeimdallGI::GeoRecord()
			 * @param QString strCity
			 * @param QString strContinentISO
			 * @param QString strCountry
			 * @param QString strCountryISO
			 * @param QString strISP
			 * @param float intLatitude
			 * @param float intLongitude
			 * @param QString strRegion
			 * @param QString strTimeZone
			 * @return HeimdallGI::GeoRecord
			 */
			GeoRecord(
				QString strCity,
				QString strContinentISO,
				QString strCountry,
				QString strCountryISO,
				QString strISP,
				float intLatitude,
				float intLongitude,
				QString strRegion,
				QString strTimeZone
			) :
				mCity(strCity),
				mContinentISO(strContinentISO),
				mCountry(strCountry),
				mCountryISO(strCountryISO),
				mISP(strISP),
				mLatitude(intLatitude),
				mLongitude(intLongitude),
				mRegion(strRegion),
				mTimeZone(strTimeZone)
			{
				// Minimize memory usage
				mCity.squeeze();
				mContinentISO.squeeze();
				mCountry.squeeze();
				mCountryISO.squeeze();
				mISP.squeeze();
				mRegion.squeeze();
				mTimeZone.squeeze();
			}

			///////////////////////////////////////////////////////////////////
			/// Getters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method returns the IP's city
			 * @brief HeimdallGI::GeoRecord::getCity()
			 * @return QString HeimdallGI::GeoRecord::mCity
			 */
			QString getCity()         { return mCity;         }

			/**
			 * @paragraph This method returns the IP's continent ISO code
			 * @brief HeimdallGI::GeoRecord::getContinentISO()
			 * @return QString HeimdallGI::GeoRecord::mContinentISO
			 */
			QString getContinentISO() { return mContinentISO; }

			/**
			 * @paragraph This method returns the IP's country
			 * @brief HeimdallGI::GeoRecord::getCountry()
			 * @return QString HeimdallGI::GeoRecord::mCountry
			 */
			QString getCountry()      { return mCountry;      }

			/**
			 * @paragraph This method returns the IP's ISO country code
			 * @brief HeimdallGI::GeoRecord::getCountryISO()
			 * @return QString HeimdallGI::GeoRecord::mCountryISO
			 */
			QString getCountryISO()   { return mCountryISO;   }

			/**
			 * @paragraph This method returns the IP's ISP
			 * @brief HeimdallGI::GeoRecord::getISP()
			 * @return QString HeimdallGI::GeoRecord::mISP
			 */
			QString getISP()          { return mISP;          }

			/**
			 * @paragraph This method returns the IP's latitude
			 * @brief HeimdallGI::GeoRecord::getLatitude()
			 * @return float HeimdallGI::GeoRecord::mLatitude
			 */
			float getLatitude()       { return mLatitude;     }

			/**
			 * @paragraph This method returns the IP's longitude
			 * @brief HeimdallGI::GeoRecord::getLongitude()
			 * @return float HeimdallGI::GeoRecord::mLongitude
			 */
			float getLongitude()      { return mLongitude;    }

			/**
			 * @paragraph This method returns the IP's region/state
			 * @brief HeimdallGI::GeoRecord::getRegion()
			 * @return QString HeimdallGI::GeoRecord::mRegion
			 */
			QString getRegion()       { return mRegion;       }

			/**
			 * @paragraph This method returns the IP's timezone
			 * @brief HeimdallGI::GeoRecord::getTimeZone()
			 * @return QString HeimdallGI::GeoRecord::mTimeZone
			 */
			QString getTimeZone()     { return mTimeZone;     }

			///////////////////////////////////////////////////////////////////
			/// Setters //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method sets the IP's city
			 * @brief HeimdallGI::GeoRecord::setCity()
			 * @param QString strCity
			 * @return void
			 */
			void setCity(QString strCity)                 { mCity         = strCity;         mCity.squeeze();         }

			/**
			 * @paragraph This method sets the IP's continent ISO code
			 * @brief HeimdallGI::GeoRecord::setContinentISO()
			 * @param QString strContinentISO
			 * @return void
			 */
			void setContinentISO(QString strContinentISO) { mContinentISO = strContinentISO; mContinentISO.squeeze(); }

			/**
			 * @paragraph This method sets the IP's country
			 * @brief HeimdallGI::GeoRecord::setCountry()
			 * @param QString strCountry
			 * @return void
			 */
			void setCountry(QString strCountry)           { mCountry      = strCountry;      mCountry.squeeze();      }

			/**
			 * @paragraph This method sets the IP's country ISO code
			 * @brief HeimdallGI::GeoRecord::setCountryISO()
			 * @param QString strCountryISO
			 * @return void
			 */
			void setCountryISO(QString strCountryISO)     { mCountryISO   = strCountryISO;   mCountryISO.squeeze();   }

			/**
			 * @paragraph This method sets the IP's Internet Service Provider (ISP)
			 * @brief HeimdallGI::GeoRecord::setISP()
			 * @param QString strISP
			 * @return void
			 */
			void setISP(QString strISP)                   { mISP          = strISP;          mISP.squeeze();          }

			/**
			 * @paragraph This method sets the IP's latitude
			 * @brief HeimdallGI::GeoRecord::setLatitude()
			 * @param float intLatitude
			 * @return void
			 */
			void setLatitude(float intLatitude)           { mLatitude     = intLatitude;                              }

			/**
			 * @paragraph This method sets the IP's longitude
			 * @brief HeimdallGI::GeoRecord::setLongitude()
			 * @param float intLongitude
			 * @return void
			 */
			void setLongitude(float intLongitude)         { mLongitude    = intLongitude;                             }

			/**
			 * @paragraph This method sets the IP's region
			 * @brief HeimdallGI::GeoRecord::setRegion()
			 * @param QString strRegion
			 * @return void
			 */
			void setRegion(QString strRegion)             { mRegion       = strRegion;       mRegion.squeeze();       }

			/**
			 * @paragraph This method sets the IP's time zone
			 * @brief HeimdallGI::GeoRecord::setTimeZone()
			 * @param QString strTimeZone
			 * @return void
			 */
			void setTimeZone(QString strTimeZone)         { mTimeZone     = strTimeZone;     mTimeZone.squeeze();     }
	};

	/**
	 * Register the GeoRecord to allow testing
	 */
	// Q_DECLARE_METATYPE(HeimdallGI::GeoRecord)

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

			/**
			 * @paragraph This property contains the reference to our City Database
			 * @brief HeimdallGI::MaxMind::mCityDatabase
			 * @var GeoIP*
			 */
			GeoIP* mCityDatabase;

			/**
			 * @paragraph This property contains the reference to our ISP Database
			 * @brief HeimdallGI::MaxMind::mIspDatabase
			 * @var GeoIP*
			 */
			GeoIP* mIspDatabase;

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method closes a database
			 * @brief HeimdallGI::MaxMind::closeDB()
			 * @param GeoIP* gipDatabase
			 * @protected
			 * @return void
			 */
			void closeDB(GeoIP* gipDatabase);

			/**
			 * @paragraph This method determines if a database is open
			 * @brief HeimdallGI::MaxMind::dbIsOpen()
			 * @param GeoIP* const gipDatabase
			 * @protected
			 * @return bool
			 */
			bool dbIsOpen(GeoIP* gipDatabase);

			/**
			 * @paragraph This method returns the database type
			 * @brief HeimdallGI::MaxMind::dbType()
			 * @protected
			 * @return HeimdallGI::MaxMind::DatabaseType
			 */
			// DatabaseType dbType() const;

			/**
			 * @paragraph This method opens a database file
			 * @brief HeimdallGI::MaxMind::openDB()
			 * @param GeoIP** gipDatabase
			 * @param const QString strFileName
			 * @protected
			 * @return bool
			 */
			bool openDB(GeoIP** gipDatabase, const QString &strFileName);

		///////////////////////////////////////////////////////////////////////
		/// Public Methods & Properties //////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		public:

			///////////////////////////////////////////////////////////////////
			/// Enumerations /////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This enumeration contains the MaxMind database types relative to this interface
			 * @brief HeimdallGI::MaxMind::DatabaseType
			 * @var enum
			 */
			enum DatabaseType {
				ASN,
				City,
				Country,
				Domain,
				ISP,
				NetSpeed,
				Organization,
				Proxy,
				Region,
				Unknown = 0
			};

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

			///////////////////////////////////////////////////////////////////
			/// Methods //////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////

			/**
			 * @paragraph This method closes the connection stream to the databases
			 * @brief HeimdallGI::MaxMind::closeConnection()
			 * @return void
			 */
			void closeConnection();

			/**
			 * @paragraph This method searches for a record by the IPv4 or IPv6 address
			 * @brief HeimdallGI::MaxMind::findByAddress()
			 * @param const QHostAddress qhaIpAddress
			 * @return HeimdallGI::GeoRecord
			 */
			GeoRecord findByAddress(const QHostAddress &qhaIpAddress);

			/**
			 * @paragraph This method opens a connection stream to the MaxMind databases
			 * @brief HeimdallGI::MaxMind::openConnection()
			 * @param const QString strCityDatabasePath
			 * @param const QString strIspDatabasePath
			 * @return bool
			 */
			bool openConnection(const QString &strCityDatabasePath, const QString &strIspDatabasePath);


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
