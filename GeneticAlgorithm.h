///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HEIMDALLGI_GENETICALGORITHM_H
#define HEIMDALLGI_GENETICALGORITHM_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QObject"
#include "QVector"
#include "GeneticAlgorithmMap.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Structures ///////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	struct Genome {

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the genome's bits
		 * @brief HeimdallGI::Genome::mBits
		 * @var QVector<int>
		 */
		QVector<int> mBits;

		/**
		 * @paragraph This property contains the fitness of the genome
		 * @brief HeimdallGI::Genome::mFitness
		 * @var double
		 */
		double mFitness;

		///////////////////////////////////////////////////////////////////////
		/// Constructors /////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constructor simply initializes the genome's fitness
		 * @brief HeimdallGI::Genome()
		 * @return HeimdallGI::Genome
		 */
		Genome() : mFitness(0) {}

		/**
		 * @paragraph This constructor initializes the genome's fitness with a set number of bits
		 * @brief HeimdallGI::Genome()
		 * @param int intBits
		 * @return HeimdallGI::Genome
		 */
		Genome(int intBits) : mFitness(0) {
			// Loop to the bits
			for (int intBit = 0; intBit < intBits; ++intBit) {
				// Add a random bit
				this->mBits.push_back(rand() % (1 - 0 + 1) + 0);
			}
		}
	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// HeimdallGI::GeneticAlgorithm Class Definitiona ///////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class GeneticAlgorithm : public QObject
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
		 * @paragraph This property contains the singleton instance of this network
		 * @brief HeimdallGI::GeneticAlgorithm::mInstance
		 * @var HeimdallGI::GeneticAlgorithm*
		 */
		static GeneticAlgorithm* mInstance;

		/**
		 * @paragraph This property contains the best fitness score from the network
		 * @brief HeimdallGI::GeneticAlgorithm::mBestFitness
		 * @var double
		 */
		double mBestFitness;

		/**
		 * @paragraph This property contains the brain of the network
		 * @brief HeimdallGI::GeneticAlgorithm::mBrain
		 * @var HeimdallGI::GeneticAlgorithmMap
		 */
		GeneticAlgorithmMap mBrain;

		/**
		 * @paragraph This property tells the caller that the network is busy
		 * @brief HeimdallGI::GeneticAlgorithm::mBusy
		 * @var bool
		 */
		bool mBusy;

		/**
		 * @paragraph This property contains the chromosome length
		 * @brief HeimdallGI::GeneticAlgorithm::mChromosomeLength
		 * @var int
		 */
		int mChromosomeLength;

		/**
		 * @paragraph This property contains the crossover rate
		 * @brief HeimdallGI::GeneticAlgorithm::mCrossoverRate
		 * @var double
		 */
		double mCrossoverRate;

		/**
		 * @paragraph This property contains the fittest gene
		 * @brief HeimdallGI::GeneticAlgorithm::mFittestGene
		 * @var int
		 */
		int mFittestGene;

		/**
		 * @paragraph This property contains the gene length
		 * @brief HeimdallGI::GeneticAlgorithm::mGeneLength
		 * @var int
		 */
		int mGeneLength;

		/**
		 * @paragraph This property contains the current generation or iteration of the network
		 * @brief HeimdallGI::GeneticAlgorithm::mGeneration
		 * @var int
		 */
		int mGeneration;

		/**
		 * @paragraph This property contains the genomes for the network
		 * @brief HeimdallGI::GeneticAlgorithm::mGenomes
		 * @var QVector<HeimdallGI::Genome>
		 */
		QVector<Genome> mGenomes;

		/**
		 * @paragraph This property contains the map to test the network with
		 * @brief HeimdallGI::GeneticAlgorithm::mMap
		 * @var HeimdallGI::GeneticAlgorithmMap
		 */
		GeneticAlgorithmMap mMap;

		/**
		 * @paragraph This property contains the mutation rate of the genes
		 * @brief HeimdallGI::GeneticAlgorithm::mMutationRate
		 * @var double
		 */
		double mMutationRate;

		/**
		 * @paragraph This property contains the population of the network
		 * @brief HeimdallGI::GeneticAlgorithm::mPopulation
		 * @var int
		 */
		int mPopulation;

		/**
		 * @paragraph This property contains the total fitness of the network
		 * @brief HeimdallGI::GeneticAlgorithm::mTotalFitness
		 * @var double
		 */
		double mTotalFitness;

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////


		int BinaryToInteger(QVector<int> &qviBinary);


		void Crossover(QVector<int> &qviMaternal, QVector<int> &qviPaternal, QVector<int> &qviOffspringAlpha, QVector<int> &qviOffspringBeta);


		QVector<int> Decode(QVector<int> &qviEncodedBits);


		void Mutate(QVector<int> &qviBits);


		Genome& Selection();


		void UpdateFitnessScores();

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public:

		///////////////////////////////////////////////////////////////////////
		/// Constants ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constant contains the boolean network status for a busy network
		 * @brief HeimdallGI::GeneticAlgorithm::NetowrkStarted
		 * @var bool [true]
		 */
		static bool NetowrkStarted;

		/**
		 * @paragraph This constant contains the boolean network status for a resting network
		 * @brief HeimdallGI::GeneticAlgorithm::NetworkStopped
		 * @var bool [false]
		 */
		static bool NetworkStopped;

		///////////////////////////////////////////////////////////////////////
		/// Singleton ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method maintains access to the singleton instance of the network
		 * @brief HeimdallGI::GeneticAlgorithm::Instance()
		 * @param bool bReset [false]
		 * @return HeimdallGI::GeneticAlgorithm* HeimdallGI::GeneticAlgorithm::mInstance
		 */
		static GeneticAlgorithm* Instance(bool bReset = false);

		///////////////////////////////////////////////////////////////////////
		/// Contstructor /////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph The constructor simply sets up the class
		 * @brief HeimdallGI::GeneticAlgorithm::GeneticAlgorithm()
		 * @param QObject* qoParent [0]
		 * @return HeimdallGI::GeneticAlgorithm* HeimdallGI::GeneticAlgorithm::mInstance
		 */
		explicit GeneticAlgorithm(QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method epochs the generation of the network
		 * @brief HeimdallGI::GeneticAlgorithm::Epoch()
		 * @return void
		 */
		void Epoch();

		/**
		 * @paragraph This method executes the network
		 * @brief HeimdallGI::GeneticAlgorithm::Execute()
		 * @return void
		 */
		void Execute();

		/**
		 * @paragraph This method initializes the population of the network
		 * @brief HeimdallGI::GeneticAlgorithm::InitializePopulation()
		 * @return void
		 */
		void InitializePopulation();


		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the fittest genome
		 * @brief HeimdallGI::GeneticAlgorithm::GetFittest()
		 * @return int HeimdallGI::GeneticAlgorithm::mFittestGene
		 */
		int GetFittest();

		/**
		 * @paragraph This method returns the current generation
		 * @brief HeimdallGI::GeneticAlgorithm::GetGeneration()
		 * @return int
		 */
		int GetGeneration();

		/**
		 * @paragraph This method returns the status of the network
		 * @brief HeimdallGI::GeneticAlgorithm::GetStatus()
		 * @return bool HeimdallGI::GeneticAlgorithm::mBusy
		 */
		bool GetStatus();

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the number of bits into the instance
		 * @brief HeimdallGI::GeneticAlgorithm::SetBits()
		 * @param int intNumberOfBits
		 * @return HeimdallGI::GeneticAlgorithm* HeimdallGI::GeneticAlgorithm::mInstance
		 */
		GeneticAlgorithm* SetBits(int intNumberOfBits);

		/**
		 * @paragraph This method sets the crossover rate into the network
		 * @brief HeimdallGI::GeneticAlgorithm::SetCrossoverRate()
		 * @param double dblCrossoverRate
		 * @return HeimdallGI::GeneticAlgorithm* HeimdallGI::GeneticAlgorithm::mInstance
		 */
		GeneticAlgorithm* SetCrossoverRate(double dblCrossoverRate);

		/**
		 * @paragraph This method sets the gene length into the network
		 * @brief HeimdallGI::GeneticAlgorithm::SetGeneLength()
		 * @param int intGeneLength
		 * @return HeimdallGI::GeneticAlgorithm* HeimdallGI::GeneticAlgorithm::mInstance
		 */
		GeneticAlgorithm* SetGeneLength(int intGeneLength);

		/**
		 * @paragraph This method sets the mutation rate into the network
		 * @brief HeimdallGI::GeneticAlgorithm::SetMutationRate()
		 * @param double dblMutationRate
		 * @return HeimdallGI::GeneticAlgorithm* HeimdallGI::GeneticAlgorithm::mInstance
		 */
		GeneticAlgorithm* SetMutationRate(double dblMutationRate);

		/**
		 * @paragraph This method sets the population size into the network
		 * @brief HeimdallGI::GeneticAlgorithm::SetPopulation()
		 * @param int intPopulationSize
		 * @return HeimdallGI::GeneticAlgorithm* HeimdallGI::GeneticAlgorithm::mInstance
		 */
		GeneticAlgorithm* SetPopulation(int intPopulationSize);

		/**
		 * @paragraph This method sets the status of the network into the instance
		 * @brief HeimdallGI::GeneticAlgorithm::SetStatus()
		 * @param bool bStatus
		 * @return HeimdallGI::GeneticAlgorithm* HeimdallGI::GeneticAlgorithm::mInstance
		 */
		GeneticAlgorithm* SetStatus(bool bStatus);

	///////////////////////////////////////////////////////////////////////////
	/// Signals //////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	signals:

		/**
		 * @paragraph This signal fires each time the network status changes
		 * @brief HeimdallGI::GeneticAlgorithm::StatusChanged()
		 * @param bool bBusy
		 * @return void
		 */
		void StatusChanged(bool bBusy);

		/**
		 * @paragraph This signal fires when the fitness score is updated
		 * @brief HeimdallGI::GeneticAlgorithm::FitnessScoresUpdated()
		 * @param int intFittest
		 * @param double dblBestFitness
		 * @param double dblTotalFitness
		 * @return void
		 */
		void FitnessScoresUpdated(int intFittest, double dblBestFitness, double dblTotalFitness);

		/**
		 * @paragraph This signal fires when a new epoch occurs
		 * @brief HeimdallGI::GeneticAlgorithm::NewEpoch()
		 * @param int intGeneration
		 * @param QVector<HeimdallGI::Genome> qvgGenomes
		 */
		void NewEpoch(int intGeneration, QVector<Genome> qvgGenomes);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// End HeimdallGI::GeneticAlgorithm Class Definition ////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace HeimdallGI

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Definitions //////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // HEIMDALLGI_GENETICALGORITHM_H
