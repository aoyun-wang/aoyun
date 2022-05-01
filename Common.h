#pragma once
//
// Created by Robbie on 2021/3/30.
//

#ifndef INTELHEX_COMMON_H
#define INTELHEX_COMMON_H

#ifdef ANDROID_BUILD
#include <jni.h>
#endif
#include <string>
#include <vector>
#include <iostream>

#ifdef DOTNET_BUILD
#include <msclr\marshal_cppstd.h>
using namespace System;
using namespace System::Runtime::InteropServices;
#endif

#include <winsock.h>
#pragma comment(lib, "ws2_32.lib")


class Common {
public:
    static bool isInvalidString(std::string& data);
#ifdef ANDROID_BUILD
    static bool isFileExist(const char* file);
    static uint64_t getTimestamp();
#endif

    static std::string trim(std::string& data);
    static void splitHex(const std::string& s, std::vector<std::string>& sv);
    static void splitS19(const std::string& s, std::vector<std::string>& sv);
    static void split(const std::string& s, std::vector<std::string>& sv, const char delim = '\n');

    static uint8_t calcHexCrc(const char* data, size_t len);
    static uint8_t calcSreCrc(const char* data, size_t len);

    static std::string bytesToHexStr(std::string& bytes, bool lower = false);
    static std::string bytesToHexStr(const char* bytes, size_t len, bool lower = false);
    static std::string hexStrToBytes(std::string& hexStr);
    static std::string hexStrToBytes(const char* bytes, size_t len);

#ifdef DOTNET_BUILD
    static void toStdString(System::String^ s, std::string& os);
    static void toClrString(std::string& s, interior_ptr<System::String^> os);
#endif
#ifdef ANDROID_BUILD
    static jstring stringToJString(JNIEnv* env, std::string& str);
    static jbyteArray stringToJByteArray(JNIEnv* env, std::string& str);
    static std::string jByteArrayToString(JNIEnv* env, jbyteArray buf);
#endif

private:
    static uint8_t charToInt(uint8_t ch);
};


#endif //INTELHEX_COMMON_H
