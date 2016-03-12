/************************************************************
*                                                           *
*   Copyright (C) Steven Frost 2016. All Rights Reserved.   *
*                                                           *
************************************************************/

#pragma once

extern bool AssertEnableFastFail;

#if FEATURE_ASSERTS_ENABLED

#ifndef FAST_FAIL_FATAL_APP_EXIT
#define FAST_FAIL_FATAL_APP_EXIT 7
#endif // FAST_FAIL_FATAL_APP_EXIT

#define Assert(x) (!!(x) || (AssertEnableFastFail ? __fastfail(FAST_FAIL_FATAL_APP_EXIT) : __debugbreak(), 0))
#define AssertExpr(x, e) (!!(x) || (AssertEnableFastFail ? __fastfail(FAST_FAIL_FATAL_APP_EXIT) : __debugbreak(), 0))

#else // FEATURE_ASSERTS_ENABLED

#define Assert(x) 
#define AssertExpr(x, e) 

#endif // FEATURE_ASSERTS_ENABLED
