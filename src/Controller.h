#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Thread.h"
#include "Lock.h"
#include "SoundModel.h"

#include <queue>
#include <string>
#include <iostream>

 /**
 *Controls interaction between input and output stages of the hurdy gurdy.
 *
 */

namespace SYNTHPI {
namespace audio{

class Controller: public Thread{

 protected:
	/**
	 *An item on the noteQueue.
	 */
	class QueueItem{
	public:
		//True if the
		bool noteOff;
		int note;

		/**
		 *Creates a new item and initialises its variables.
		 */
		QueueItem(bool noteOff, int note){
			this->noteOff = noteOff;
			this->note = note;
		}

	};
	

  //Locks for signalling of changes in keyboard or pedal input.
  Lock outputLock;

  //SoundModel itself.
  SoundModel *playout;

  //Variable for storing the current status of playout.
  bool isPlaying;

  //Stores whether or not the pedal has triggered a broadcast.
  bool pedalTriggered;

  //Buffers notes sent by keyboard.  Notes are stored in instantiations of type QueueItem.
  std::queue<QueueItem> noteQueue;

  //Lock for accessing the noteQueue.
  Lock queueLock;

  
  float volume;
  float wavemix_val;

  int bank_number;
  
 public:

  /**
   *Creates a new controller object.
   *
   *@param playout Soundmodel to which controller passes signals.
   *
   */
  Controller(SoundModel *playout); 

  /**
   *Called when a controller object is destroyed.
   */
  ~Controller();


   /**
   *Called by keyboard interface whenever a key event happens.
   *
   *Stores notes in the noteQueue while waiting for processor time.
   *
   *@param noteOff is a boolean which is true if the event is turning a note off.
   *@param note indicates which note to turn off.
   */
  void keyEvent(bool noteOff, int note);
  
  void updateVolume(unsigned int parameter);

  void updateWavemix(unsigned int parameter);


  void updateBank(unsigned int parameter);

  /**
   *Starts the running of playout
   */
  virtual void run();


};

}
}
#endif /* CONTROLLER_H */
