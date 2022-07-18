/**
 * \file envelope-dl.h
 */
#ifndef ENVELOPE_DL_H
#define ENVELOPE_DL_H
#include "envelope.h" // for envelope_t
                      /**
                       * An envelope in the DL format.
                       */
class envelope_dl_t : public envelope_t
{
public: /**
         14 * Constructs a new envelope in the DL format.
         15 * Initializes its height to "220" and width to "110".
         16 */
  envelope_dl_t();
};
#endif