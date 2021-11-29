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

#include "mkn/kul/proc.hpp"
#include "mkn/kul/time.hpp"

static const constexpr uint64_t MAX_SIZE = 123456789;
#define LOOP     100

volatile uint64_t no_op = 0;

void Cpy(uint64_t i){
    no_op = i;
}
void constCpy(const uint64_t i){
    no_op = i;
}

void constRef(const uint64_t& i){
    no_op = i;
}
void nonconstRef(uint64_t& i){
    no_op = i;
}
void constconstPtr(const uint64_t* const i){
    no_op = *i;
}
void const1Ptr(uint64_t* const i){
    no_op = *i;
}
void const2Ptr(const uint64_t* i){
    no_op = *i;
}
void constconstPtrRef(const uint64_t*const &i){
    no_op = *i;
}
void const1PtrRef(uint64_t * const &i){
    no_op = *i;
}
void const2PtrRef(const uint64_t*& i){
    no_op = *i;
}

int main(int argc, char* argv[]){

    KOUT(NON) << "Runtime test for to different paramter passing techniques";

    // CPY
    {
        auto now = mkn::kul::Now::NANOS();
        for(uint64_t j = 0; j < LOOP; j++)
            for(uint64_t i = 0; i < MAX_SIZE; i++)
                Cpy(i);
        auto then = mkn::kul::Now::NANOS();
        KOUT(NON) <<  ((then - now) / LOOP / 1000000) << "(ms) : uint64_t";
    }

    //constCpy
    {
        auto now = mkn::kul::Now::NANOS();
        for(uint64_t j = 0; j < LOOP; j++)
            for(uint64_t i = 0; i < MAX_SIZE; i++)
                constCpy(i);
        auto then = mkn::kul::Now::NANOS();
        KOUT(NON) <<  ((then - now) / LOOP / 1000000) << "(ms) : const uint64_t";
    }

    //constRef
    {
        auto now = mkn::kul::Now::NANOS();
        for(uint64_t j = 0; j < LOOP; j++)
            for(uint64_t i = 0; i < MAX_SIZE; i++)
                constRef(i);
        auto then = mkn::kul::Now::NANOS();
        KOUT(NON) <<  ((then - now) / LOOP / 1000000) << "(ms) : const uint64_t&";
    }

    //nonconstRef
    {
        auto now = mkn::kul::Now::NANOS();
        for(uint64_t j = 0; j < LOOP; j++)
            for(uint64_t i = 0; i < MAX_SIZE; i++)
                nonconstRef(i);
        auto then = mkn::kul::Now::NANOS();
        KOUT(NON) <<  ((then - now) / LOOP / 1000000) << "(ms) : uint64_t&";
    }

    //constconstPtr
    {
        auto now = mkn::kul::Now::NANOS();
        for(uint64_t j = 0; j < LOOP; j++)
            for(uint64_t i = 0; i < MAX_SIZE; i++)
                constconstPtr(&i);
        auto then = mkn::kul::Now::NANOS();
        KOUT(NON) <<  ((then - now) / LOOP / 1000000) << "(ms) : const uint64_t* const";
    }

    //const1Ptr
    {
        auto now = mkn::kul::Now::NANOS();
        for(uint64_t j = 0; j < LOOP; j++)
            for(uint64_t i = 0; i < MAX_SIZE; i++)
                const1Ptr(&i);
        auto then = mkn::kul::Now::NANOS();
        KOUT(NON) <<  ((then - now) / LOOP / 1000000) << "(ms) : uint64_t* const ";
    }

    //const2Ptr
    {
        auto now = mkn::kul::Now::NANOS();
        for(uint64_t j = 0; j < LOOP; j++)
            for(uint64_t i = 0; i < MAX_SIZE; i++)
                const2Ptr(&i);
        auto then = mkn::kul::Now::NANOS();
        KOUT(NON) <<  ((then - now) / LOOP / 1000000) << "(ms) : const uint64_t* ";
    }

    //constconstPtrRef
    {
        auto now = mkn::kul::Now::NANOS();
        for(uint64_t j = 0; j < LOOP; j++)
            for(uint64_t i = 0; i < MAX_SIZE; i++)
                constconstPtrRef(&i);
        auto then = mkn::kul::Now::NANOS();
        KOUT(NON) <<  ((then - now) / LOOP / 1000000) << "(ms) : const uint64_t * const & ";
    }

    //const1PtrRef
    {
        auto now = mkn::kul::Now::NANOS();
        for(uint64_t j = 0; j < LOOP; j++)
            for(uint64_t i = 0; i < MAX_SIZE; i++)
                const1PtrRef(&i);
        auto then = mkn::kul::Now::NANOS();
        KOUT(NON) <<  ((then - now) / LOOP / 1000000) << "(ms) : uint64_t * const & ";
    }

    // const2PtrRef
    // Requires local ptr
    {
        auto now = mkn::kul::Now::NANOS();
        for(uint64_t j = 0; j < LOOP; j++)
            for(uint64_t i = 0; i < MAX_SIZE; i++){
                const uint64_t * i1 = &i;
                const2PtrRef(i1);
            }
        auto then = mkn::kul::Now::NANOS();
        KOUT(NON) <<  ((then - now) / LOOP / 1000000) << "(ms) : const uint64_t*& ";
    }


}
