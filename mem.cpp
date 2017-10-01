/**
Copyright (c) 2017, Philip Deegan.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

    * Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the following disclaimer
in the documentation and/or other materials provided with the
distribution.
    * Neither the name of Philip Deegan nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// will seg fault if the stack limit is too low
// *nix systems check "ulimit -s"

#include "kul/proc.hpp"

#define MAX_SIZE 123456789

volatile uint64_t no_op = 0;

int main(int argc, char* argv[]){

    KOUT(NON) << "Runtime test for show memory usage for different types of arrays"; 


    const uint64_t size(MAX_SIZE);

    KOUT(NON) << "RAM in KB: "  << kul::this_proc::physicalMemory();
    {
        uint64_t ar[size];
        for(uint64_t i = 0; i < size; i++){
            ar[i] = i;
            no_op = ar[i];
        }
        KOUT(NON) << "RAM in KB: "  << kul::this_proc::physicalMemory();
    }
    kul::this_thread::sleep(11);

    KOUT(NON) << "RAM in KB: "  << kul::this_proc::physicalMemory();
    {
        std::array<uint64_t, size> ar;
        for(uint64_t i = 0; i < size; i++){
            ar[i] = i;
            no_op = ar[i];
        }
        KOUT(NON) << "RAM in KB: "  << kul::this_proc::physicalMemory();
    }
    kul::this_thread::sleep(11);

    KOUT(NON) << "RAM in KB: "  << kul::this_proc::physicalMemory();
    {
        uint64_t* ar = new uint64_t[size];
        for(uint64_t i = 0; i < size; i++){
            ar[i] = i;
            no_op = ar[i];
        }
        KOUT(NON) << "RAM in KB: "  << kul::this_proc::physicalMemory();
        delete[] ar;
    }
    kul::this_thread::sleep(11);

    KOUT(NON) << "RAM in KB: "  << kul::this_proc::physicalMemory();
    {
        std::vector<uint64_t> ar;
        for(uint64_t i = 0; i < size; i++){
            ar.push_back(i);
            no_op = ar[i];
        }
        KOUT(NON) << "RAM in KB: "  << kul::this_proc::physicalMemory();
    }
}
