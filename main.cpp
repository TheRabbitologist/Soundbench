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

#include "application.h"
#include "printhelp.h"

size_t sb::SampleRate;
sb::Synth* sb::midi::MIDIEventNode::synref;

int main(int argc, char *argv[])
{
    if (argc == 2) {
        std::string arg = argv[1];
        if (arg == "--version" || arg == "-v") {
            std::cout << "Version: " << SBVERSION << '\n';
            std::cout << "Series: " << SBVERSION_SERIES << '\n';
            return 0;
        }
        else if (arg == "--help" || arg == "-h") {
            printhelp();
            return 0;
        }
    }
    SoundbenchApp a(argc, argv);
    a.newSoundbench(SoundbenchApp::Default);
    std::cerr << "Soundbench loaded.\n";
    return a.run();
}

