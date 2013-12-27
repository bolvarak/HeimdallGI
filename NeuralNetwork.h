///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Definitions //////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef HEIMDALLGI_NEURALNETWORK_H
#define HEIMDALLGI_NEURALNETWORK_H

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Headers //////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "QDebug"
#include "QList"
#include "QMap"
#include "QtMath"
#include "QObject"
#include "QVariant"
#include "QVector"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace HeimdallGI {

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Structures ///////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @paragraph This structure defines an Axon which is a connection between neurons, or in this case, Neurons
	 * @brief HeimdallGI::Axon
	 */
	struct Axon {

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the key for the source Neuron
		 * @brief HeimdallGI::Axon::mFrom
		 * @var QVector<int>
		 */
		QVector<int> mSource;

		/**
		 * @paragraph This property contains the key for the target Neuron
		 * @brief HeimdallGI::Axon::mTo
		 * @var QVector<int>
		 */
		QVector<int> mTarget;

		/**
		 * @paragraph This property contains the type of connection it is, or what types of layers this connection is traversing
		 * @brief HeimdallGI::Axon::mType
		 */
		int mType;

		/**
		 * @paragraph This property contains the weight or bias of the connection
		 * @brief HeimdallGI::Axon::mWeight
		 * @var double
		 */
		float mWeight;

		///////////////////////////////////////////////////////////////////////
		/// Constructors /////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constructor sets up an empty connection between neurons
		 * @brief HeimdallGI::Axon
		 * @return HeimdallGI::Axon
		 */
		Axon() {}

		/**
		 * @paragraph This constructor fully sets up a connection between neurons
		 * @brief HeimdallGI::Axon
		 * @param int intSourceLayer
		 * @param int intSourceNeuron
		 * @param int intTargetLayer
		 * @param int intTargetNeuron
		 * @param int intLayerType
		 * @param float fltWeight [0.0]
		 * @return HeimdallGI::Axon
		 */
		Axon(int intSourceLayer, int intSourceNeuron, int intTargetLayer, int intTargetNeuron, int intLayerType, float fltWeight = 0.0) {
			// Set the source
			setSource(intSourceLayer, intSourceNeuron);
			// Set the target
			setTarget(intTargetLayer, intTargetNeuron);
			// Set the layer type
			setType(intLayerType);
			// Set the weight
			setWeight(fltWeight);
		}

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the source from the connection
		 * @brief HeimdallGI::Axon::getSource()
		 * @return QVector<int> HeimdallGI::Axon::mSource
		 */
		QVector<int> getSource() {
			// Return the index of the source neuron
			return mSource;
		}

		/**
		 * @paragraph This method returns the target from the connection
		 * @brief HeimdallGI::Axon::getTarget()
		 * @return QVector<int> HeimdallGI::Axon::mTarget
		 */
		QVector<int> getTarget() {
			// Return the connection target
			return mTarget;
		}

		/**
		 * @paragraph This method returns the type from the connection
		 * @brief HeimdallGI::Axon::getType()
		 * @return int HeimdallGI::Axon::mType
		 */
		int getType() {
			// Return the connection type
			return mType;
		}

		/**
		 * @paragraph This method returns the weight from the connection
		 * @brief HeimdallGI::Axon::getWeight()
		 * @return float HeimdallGI::Axon::mWeight
		 */
		float getWeight() {
			// Return the connection weight
			return mWeight;
		}

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the source neuron coordinates into the connection
		 * @brief HeimdallGI::Axon::setSource()
		 * @param int intLayer
		 * @param int intNeuron
		 * @return void
		 */
		void setSource(int intLayer, int intNeuron) {
			// Make sure the source is clear
			mSource.clear();
			// Set the source Layer
			mSource.append(intLayer);
			// Set the source Neuron
			mSource.append(intNeuron);
		}

		/**
		 * @paragraph This method sets the target neuron coordinates into the connection
		 * @brief HeimdallGI::Axon::setTarget()
		 * @param int intLayer
		 * @param int intNeuron
		 * @return void
		 */
		void setTarget(int intLayer, int intNeuron) {
			// Make sure the target is clear
			mTarget.clear();
			// Set the target Layer
			mTarget.append(intLayer);
			// Set the target Neuron
			mTarget.append(intNeuron);
		}

		/**
		 * @paragraph This method sets the connection type into the connection
		 * @brief HeimdallGI::Axon::setType()
		 * @param int intType
		 * @return void
		 */
		void setType(int intType) {
			// Set the type into the connection
			mType = intType;
		}

		/**
		 * @paragraph This method sets the weight into the connection
		 * @brief HeimdallGI::Axon::setWeight()
		 * @param floar fltWeight
		 * @return void
		 */
		void setWeight(float fltWeight) {
			// Set the weight into the connection
			mWeight = fltWeight;
		}
	};

	/**
	 * @paragraph This structure defines a Neuron which is an artificial neuron
	 * @brief HeimdallGI::Neuron
	 */
	struct Neuron {

		///////////////////////////////////////////////////////////////////////
		/// Properties ///////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This property contains the acvtivation after firing
		 * @brief HeimdallGI::Neuron::mActivation
		 * @var int
		 */
		int mActivation;

		/**
		 * @paragraph This property contains the input
		 * @brief QList<QVariant>
		 */
		float mInput;

		/**
		 * @paragraph This property contains the weight
		 * @brief HeimdallGI::Neuron::mWeights
		 * @var QList<QVariant>
		 */
		float mWeight;

		///////////////////////////////////////////////////////////////////////
		/// Constructors /////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constructor sets up an empty neuron
		 * @brief HeimdallGI::Neuron
		 * @return HeimdallGI::Neuron
		 */
		Neuron() {}

		/**
		 * @paragraph This constructor sets up the structure with inputs
		 * @brief HeimdallGI::Neuron
		 * @param float fltInput
		 * @param float fltMinMax [0.5]
		 * @return HeimdallGI::Neuron
		 */
		Neuron(float fltInput, float fltWeight) {
			// Seed the random number generator
			srand((unsigned int) time(NULL));
			// Set the input
			mInput  = fltInput;
			// Set the weight
			mWeight = fltWeight;
		}

		///////////////////////////////////////////////////////////////////////
		/// Getters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method returns the Neuron's activation
		 * @brief HeimdallGI::Neuron::getActivation()
		 * @return int HeimdallGI::Neuron::mActivation
		 */
		int getActivation() {
			// Return the activation
			return mActivation;
		}

		/**
		 * @paragraph This method returns the input from the neuron
		 * @brief HeimdallGI::Neuron::getInput()
		 * @return float HeimdallGI::Neuron::mInput
		 */
		float getInput() {
			// Return the input from the neuron
			return mInput;
		}

		/**
		 * @paragraph This method returns the weight from the neuron
		 * @brief HeimdallGI::Neuron::getWeight()
		 * @return float HeimdallGI::Neuron::mWeight
		 */
		float getWeight() {
			// Return the weight from the neuron
			return mWeight;
		}

		///////////////////////////////////////////////////////////////////////
		/// Setters //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method sets the activation of the Neuron
		 * @brief HeimdallGI::Neuron::setActivation()
		 * @param int intActive
		 * @return void
		 */
		void setActivation(int intActive) {
			// Set the activation
			mActivation = intActive;
		}

		/**
		 * @paragraph This method sets the input of the Neuron
		 * @brief HeimdallGI::Neuron::setInput()
		 * @param float fltInput
		 * @return void
		 */
		void setInput(float fltInput) {
			// Set the input
			mInput = fltInput;
		}

		/**
		 * @paragraph This method sets the weight of the Neuron
		 * @brief setWeight
		 * @param fltWeight
		 */
		void setWeight(float fltWeight) {
			// Set the weight
			mWeight = fltWeight;
		}

	///////////////////////////////////////////////////////////////////////////
	/// End HeimdallGI::Neuron Structure /////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	};

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// HeimdallGI::NeuralNetwork Class Definition ///////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	class NeuralNetwork : public QObject
	{
		/**
		 * Ensure this class is recognized by Qt
		 */
		Q_OBJECT

	///////////////////////////////////////////////////////////////////////////
	/// Protected Methods & Properties ///////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	protected:

		/**
		 * @paragraph This property contains the singleton instance of this class
		 * @brief HeimdallGI::NeuralNetwork::mInstance
		 * @var HeimdallGI::NeuralNetwork*
		 */
		static NeuralNetwork* mInstance;

		/**
		 * @paragraph This property contains the axons between the Neurons
		 * @brief HeimdallGI::NeuralNetwork::mConnections
		 * @var QList<HeimdallGI::Axon>
		 */
		QList<Axon> mConnections;

		/**
		 * @paragraph This property contains the Neurons for the hidden layers
		 * @brief HeimdallGI::NeuralNetwork::mHiddenNeurons
		 * @var QList< QList<HeimdallGI::Neuron> >
		 */
		QMap<int, QList<Neuron> > mHiddenNeurons;

		/**
		 * @paragraph This property contains the Neurons for the input layers
		 * @brief HeimdallGI::NeuralNetwork::mInputNeurons
		 * @var QList< QList<HeimdallGI::Neuron> >
		 */
		QMap<int, QList<Neuron> > mInputNeurons;

		/**
		 * @paragraph This property contains the Neurons for the output layers
		 * @brief HeimdallGI::NeuralNetwork::mOutputNeurons
		 * @var QList< QList<Neuron> >
		 */
		QMap<int, QList<Neuron> > mOutputNeurons;

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method adds a new Neuron to the input layer defined by intIndex
		 * @brief HeimdallGI::NeuralNetwork::AppendNeuronToInputLayer()
		 * @param HeimdallGI::Neuron netNeuron
		 * @param int intIndex
		 */
		void AppendNeuronToInputLayer(Neuron &netNeuron, int intIndex);

		/**
		 * @paragraph This method adds a new Neuron to the hidden layer defined by intIndex
		 * @brief HeimdallGI::NeuralNetwork::AppendNeuronToHiddenLayer()
		 * @param HeimdallGI::Neuron netNeuron
		 * @param int intIndex
		 */
		void AppendNeuronToHiddenLayer(Neuron &netNeuron, int intIndex);

		/**
		 * @paragraph This method adds a new Neuron to the output layer defined by intIndex
		 * @brief HeimdallGI::NeuralNetwork::AppendNeuronToOutputLayer()
		 * @param HeimdallGI::Neuron netNeuron
		 * @param int intIndex
		 * @return void
		 */
		void AppendNeuronToOutputLayer(Neuron &netNeuron, int intIndex);

	///////////////////////////////////////////////////////////////////////////
	/// Public Methods & Properties //////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

	public:

		///////////////////////////////////////////////////////////////////////
		/// Constants ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This constant contains the identifier for the hidden layer(s)
		 * @brief HeimdallGI::NeuralNetwork::HiddenLayer
		 * @var int
		 */
		static int HiddenLayer;

		/**
		 * @paragraph This constant contains the identifier for the input layer(s)
		 * @brief HeimdallGI::NeuralNetwork::InputLayer
		 * @var int
		 */
		static int InputLayer;

		/**
		 * @paragraph This constant contains the identifier for the output layer(s)
		 * @brief HeimdallGI::NeuralNetwork::OutputLayer
		 * @var int
		 */
		static int OutputLayer;


		/**
		 * @paragraph This constant contains the identifier for axons between hidden Neurons
		 * @brief HeimdallGI::NeuralNetwork::HiddenToHiddenLayer
		 * @var int
		 */
		static int HiddenToHiddenLayer;

		/**
		 * @paragraph This constant contains the identifier for axons between hidden and input Neurons
		 * @brief HeimdallGI::NeuralNetwork::HiddenToInputLayer
		 * @var int
		 */
		static int HiddenToInputLayer;

		/**
		 * @paragraph This constant contains the identifier for axons between hidden and output Neurons
		 * @brief HeimdallGI::NeuralNetwork::HiddenToOutputLayer
		 * @var int
		 */
		static int HiddenToOutputLayer;

		/**
		 * @paragraph This constant contains the identifier for axons between input and hidden Neurons
		 * @brief HeimdallGI::NeuralNetwork::InputToHiddenLayer
		 * @var int
		 */
		static int InputToHiddenLayer;

		/**
		 * @paragraph This constant contains the identifier for axons between input Neurons
		 * @brief HeimdallGI::NeuralNetwork::InputToInputLayer
		 * @var int
		 */
		static int InputToInputLayer;

		/**
		 * @paragraph This constant contains the identifier for axons between input and output Neurons
		 * @brief HeimdallGI::NeuralNetwork::InputToOutputLayer
		 * @var int
		 */
		static int InputToOutputLayer;

		/**
		 * @paragraph This constant contains the identifier for axons between output and hidden Neurons
		 * @brief HeimdallGI::NeuralNetwork::OutputToHiddenLayer
		 * @var int
		 */
		static int OutputToHiddenLayer;

		/**
		 * @paragraph This constant contains the identifier for axons between output and input Neurons
		 * @brief HeimdallGI::NeuralNetwork::OutputToInputLayer
		 * @var int
		 */
		static int OutputToInputLayer;

		/**
		 * @paragraph This constant contains the identifier for axons between output Neurons
		 * @brief HeimdallGI::NeuralNetwork::OutputToOutputLayer
		 * @var int
		 */
		static int OutputToOutputLayer;

		///////////////////////////////////////////////////////////////////////
		/// Singleton ////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method maintains access to the singleton instance of this class
		 * @brief HeimdallGI::NeuralNetwork::Instance()
		 * @param bool bReset [false]
		 * @return HeimdallGI::NeuralNetwork* HeimdallGI::NeuralNetwork::mInstance
		 */
		static NeuralNetwork* Instance(bool bReset = false);

		///////////////////////////////////////////////////////////////////////
		/// Constructor //////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		explicit NeuralNetwork(QObject* qoParent = 0);

		///////////////////////////////////////////////////////////////////////
		/// Static ///////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method generates the new delta weight adjustment for the perceptron method
		 * @brief HeimdallGI::NeuralNetwork::DeltaWeight()
		 * @param int intError
		 * @param float fltInput
		 * @param float fltWeight
		 * @return float
		 */
		static float DeltaWeight(int intError, float fltInput, float fltWeight);

		/**
		 * @paragraph This method returns a random boolean value
		 * @brief HeimdallGI::NeuralNetwork::RandomBoolean()
		 * @return bool
		 */
		static bool RandomBoolean();

		/**
		 * @paragraph This method generates a random integer between the range
		 * @brief HeimdallGI::NeuralNetwork::RandomInteger()
		 * @param int intMiniumum
		 * @param int intMaximum
		 * @return int
		 */
		static int RandomInteger(int intMiniumum, int intMaximum);

		/**
		 * @paragraph This method randomly generates a weight for the inputs of a Neuron
		 * @brief HeimdallGI::NeuralNetwork::RandomWeight()
		 * @param float fltMinMax [0.5]
		 * @return float
		 */
		static float RandomWeight(float fltMinMax = 0.5);

		/**
		 * @paragraph This method runs a sigmoid curve on a value
		 * @brief HeimdallGI::NeuralNetwork::Sigmoid()
		 * @param float fltX
		 * @return float
		 */
		static float Sigmoid(float fltX);

		///////////////////////////////////////////////////////////////////////
		/// Methods //////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////

		/**
		 * @paragraph This method adds a connection between percetrons
		 * @brief HeimdallGI::NeuralNetwork::AddConnection()
		 * @param int intSourceLayer
		 * @param int intSourceNeuron
		 * @param int intTargetLayer
		 * @param int intTargetNeuron
		 * @param float fltWeigth [-2.0]
		 * @return HeimdallGI::NeuralNetwork* HeimdallGI::NeuralNetwork::mInstance
		 */
		NeuralNetwork* AddConnection(int intSourceLayer, int intSourceNeuron, int intTargetLayer, int intTargetNeuron, float fltWeight = -2.0);

		/**
		 * @paragraph This method adds a Neuron to a layer
		 * @brief HeimdallGI::NeuralNetwork::AddNeuron()
		 * @param float fltInput
		 * @param float fltWeight
		 * @param int intLayer
		 * @param int intIndex [0]
		 * @return HeimdallGI::NeuralNetwork* HeimdallGI::NeuralNetwork::mInstance
		 */
		NeuralNetwork* AddNeuron(float fltInput, float fltWeight, int intLayer, int intIndex = 0);

		/**
		 * @paragraph This method automatically sets up the connections between Neurons
		 * @brief HeimdallGI::NeuralNetwork::AutoConnect()
		 * @return HeimdallGI::NeuralNetwork* HeimdallGI::NeuralNetwork::mInstance
		 */
		NeuralNetwork* AutoConnect();

		///////////////////////////////////////////////////////////////////////
		/// Network Execution Methods ////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////


		int Activate(float fltOutput);

		/**
		 * @paragraph This method executes a Perceptron Feed-Forward neural network
		 * @brief HeimdallGI::NeuralNetwork::FeedForward()
		 * @return QVector<int>
		 */
		QVector<int> FeedForward();

		/**
		 * @paragraph This method sets up and executes a Perceptron Feed-Forward neural network
		 * @brief HeimdallGI::NeuralNetwork::FeedForward()
		 * @param QVector<float> vecInputs
		 * @return QVector<int>
		 */
		QVector<int> FeedForward(QVector<float> vecInputs);

		/**
		 * @paragraph This method sets up and executes a Perceptron Feed-Forward neural network
		 * @brief HeimdallGI::NeuralNetwork::FeedForward()
		 * @param int intNumberOfInputs
		 * @param float fltInput1, fltInput2, ...
		 * @return QVector<int>
		 */
		QVector<int> FeedForward(int intNumberOfInputs, ...);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// End HeimdallGI::NeuralNetwork Class Definition ///////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Namespace ////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// End Definitions //////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
