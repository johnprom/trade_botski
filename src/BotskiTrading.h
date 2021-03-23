#pragma once

#ifdef WIN32
  #define BotskiTrading_EXPORT __declspec(dllexport)
#else
  #define BotskiTrading_EXPORT
#endif

BotskiTrading_EXPORT void BotskiTrading();
