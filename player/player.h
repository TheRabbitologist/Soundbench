/*
	This file is part of Soundbench.

	Soundbench is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Soundbench is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Soundbench.  If not, see <http://www.gnu.org/licenses/>.

	Copyright 2012  Amaya S.
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "midichain.h"
#include "midifio/midifio.h"
#include "util/sfwriter.h"

#include "frontend/rtmidi.h"
#include "frontend/jackmidi.h"

#include "playerenums.h"

#include <deque>
#include <cstdio>
#include <thread>

#include <QListWidget>

namespace sb {

	class Player : public QObject {
		Q_OBJECT

	std::vector<std::string> tracklist; //DO NOT MOVE DOWN.
	public:
		explicit Player(Synth* syn);
		~Player();

		bool loadTrack(uint16_t track);
		std::vector<std::string> getPorts();
		size_t getCurrentPort();
		bool setVirtualPort(bool vport);

		inline const decltype(tracklist)& getTracks() {
			return tracklist;
		}

		inline void close() {
			reed->close();
			first->chainDestroy();
		}
		inline bool isOpen() {
			return reed->isOpen();
		}
		inline bool empty() {
			return first->returnNext() == nullptr;
		}
		inline void setFile(std::string thefile) {
			fi = thefile;
		}
		inline bool setTempo(int tmp) {
			return reed->setTempo(tmp);
		}
		inline int getTempo() {
			return reed->getTempo();
		}
		inline void setPort(size_t porter) {
			if(midin != nullptr)
				midin->setPort(porter);
		}
		inline bool isRtAvailable() {
			return midin != nullptr;
		}

		void startPlay();
		void stopPlay();
		void startRt();
		void stopRt();
		void startRec();
		void stopRec();

		void initfrontend(Synth* syn);

	signals:
		void progressed(int gression);
		void donePlaying();
		void updatedTrackList();

	public slots:
		void writeFile();
		bool loadFile();

	private slots:
		void cleanThread() {
			if (playthread == nullptr)
				return;
			playthread->join();
			delete playthread;
			playthread = nullptr;
		}

	private:
		std::deque<midi::nodes::MIDIEventNode> nodes;
		std::map<FrontendType,bool> supported_apis;
		time_t midiclocklen;
		std::string fi;
		bool playing;

		midi::MidiFIO* reed;
		midi::nodes::PlayerStartNode* first;
		SoundFileWriter* wri;
		MidiFrontend* midin;
		FrontendType fetype;
		std::thread* playthread;

		static void playChain(Player*);
	};
}

#endif // PLAYER_H
