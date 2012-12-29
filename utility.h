/*****************************************************************************
*
*  This file is part of the AVR Annoyance project. The project is
*  distributed at:
*  https://github.com/maximecb/AVR-Annoyance
*
*  Copyright (c) 2012, Maxime Chevalier-Boisvert. All rights reserved.
*
*  This software is licensed under the following license (Modified BSD
*  License):
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are
*  met:
*   1. Redistributions of source code must retain the above copyright
*      notice, this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright
*      notice, this list of conditions and the following disclaimer in the
*      documentation and/or other materials provided with the distribution.
*   3. The name of the author may not be used to endorse or promote
*      products derived from this software without specific prior written
*      permission.
*
*  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
*  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
*  NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
*  NOT LIMITED TO PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
*  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*****************************************************************************/

#ifndef _UTILITY_H_
#define _UTILITY_H_

// Output pin handling macro
#define MAKE_OUTPUT(IO_NAME, P_LTR, PIN_NO, NUM_BITS)                   \
inline void IO_NAME(uint8_t val)                                        \
{                                                                       \
    uint8_t NMASK = (uint8_t)(                                          \
        ~((0xFF >> (8-NUM_BITS)) << PIN_NO)                             \
    );                                                                  \
                                                                        \
    PORT##P_LTR = (PORT##P_LTR & NMASK) | (val << PIN_NO);              \
}                                                                       \
inline void INIT_##IO_NAME()                                            \
{                                                                       \
    uint8_t MASK = (uint8_t)(                                           \
        ((0xFF >> (8-NUM_BITS)) << PIN_NO)                              \
    );                                                                  \
                                                                        \
    DDR##P_LTR = DDR##P_LTR | MASK;                                     \
    IO_NAME(0);                                                         \
}

// Input pin handling macro
#define MAKE_INPUT(IO_NAME, P_LTR, PIN_NO, NUM_BITS)                    \
inline uint8_t IO_NAME()                                                \
{                                                                       \
    uint8_t MASK = (uint8_t)(                                           \
        ((0xFF >> (8-NUM_BITS)) << PIN_NO)                              \
    );                                                                  \
                                                                        \
    uint8_t val = (PIN##P_LTR & MASK) >> PIN_NO;                        \
    return val;                                                         \
}                                                                       \
inline void INIT_##IO_NAME()                                            \
{                                                                       \
    uint8_t NMASK = (uint8_t)(                                          \
        ~((0xFF >> (8-NUM_BITS)) << PIN_NO)                             \
    );                                                                  \
                                                                        \
    DDR##P_LTR = DDR##P_LTR & NMASK;                                    \
}

#endif // #ifndef _UTILITY_H_
