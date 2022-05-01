//
// Created by Robbie on 2021/3/30.
//

#include "Common.h"

#ifdef DOTNET_BUILD
#include <time.h>
#endif

#ifdef ANDROID_BUILD
#include <unistd.h>
#endif
#include <sstream>
#include <iomanip>
#include <regex>

#ifdef ANDROID_BUILD
bool Common::isFileExist(const char* file) {
    return (access(file, F_OK) != -1);
}
#endif

bool Common::isInvalidString(std::string& data) {
    return false;
}

std::string Common::trim(std::string& data) {
    std::string result = "";

    if (data.empty()) {
        return data;
    }

    // 去除尾部换行回车
    std::string whitespaces(" \t\r\n");
    size_t posBegin = data.find_first_not_of(whitespaces);
    size_t posEnd = data.find_last_not_of(whitespaces);
    if (posBegin != std::string::npos && posEnd != std::string::npos) {
        result = data.substr(posBegin, posEnd - posBegin + 1);
    }

    return result;
}

void Common::splitHex(const std::string& s, std::vector<std::string>& sv) {
    if (s.empty()) {
        return;
    }

    sv.clear();
    std::regex express(":[0-9A-F]+");
    std::regex_iterator<std::string::const_iterator> begin(s.cbegin(), s.cend(), express);
    for (auto iter = begin; iter != std::sregex_iterator(); iter++) {
        //        sv.push_back(iter->str());
    }

    return;
}

void Common::splitS19(const std::string& s, std::vector<std::string>& sv) {
    if (s.empty()) {
        return;
    }

    sv.clear();
    std::regex express("[S|s]([0|1|2|3|4|5|6|7|8|9][0-9A-F]+)?");
    std::regex_iterator<std::string::const_iterator> begin(s.cbegin(), s.cend(), express);
    for (auto iter = begin; iter != std::sregex_iterator(); iter++) {
        sv.push_back(iter->str());
    }

    return;
}

#ifdef ANDROID_BUILD
uint64_t Common::getTimestamp() {
    timeval tv;
    gettimeofday(&tv, nullptr);

    return static_cast<uint64_t>(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
#endif

uint8_t Common::calcHexCrc(const char* data, size_t len) {
    uint8_t crcValue = 0;

    for (int idx = 0; idx < len; ++idx) {
        crcValue += static_cast<uint8_t>(data[idx]);
    }
    return static_cast<uint8_t>(~crcValue + 1);
}

uint8_t Common::calcSreCrc(const char* data, size_t len) {
    uint8_t crcValue = 0;

    for (int idx = 0; idx < len; ++idx) {
        crcValue += static_cast<uint8_t>(data[idx]);
    }
    return static_cast<uint8_t>(~crcValue);
}

std::string Common::bytesToHexStr(std::string& bytes, bool lower) {
    return bytesToHexStr(bytes.data(), bytes.size());
}

std::string Common::bytesToHexStr(const char* bytes, size_t len, bool lower) {
    char characters[] = "0123456789ABCDEF";

    if (lower)
    {
        memcpy_s((void*)characters, sizeof(characters), "0123456789abcdef", 16);
    }

    // Zeroes out the buffer unnecessarily, can't be avoided for std::string.
    std::string ret(len * 2, 0);

    // Hack... Against the rules but avoids copying the whole buffer.
    char* buf = const_cast<char*>(ret.data());

    for (size_t idx = 0; idx < len; idx++)
    {
        *buf++ = characters[(bytes[idx] >> 4) & 0x0F];
        *buf++ = characters[(bytes[idx] >> 0) & 0x0F];
    }
    return ret;
}

std::string Common::hexStrToBytes(std::string& hexStr) {
    return hexStrToBytes(hexStr.data(), hexStr.length());
}

std::string Common::hexStrToBytes(const char* bytes, size_t len) {
    std::string result = "";

    if (len % 2 == 0) {
        for (size_t i = 0; i < len; i += 2)
        {
            uint8_t c1 = static_cast<uint8_t>(bytes[i]);
            uint8_t c2 = static_cast<uint8_t>(bytes[i + 1]);
            uint8_t c3 = (charToInt(c1) << 4) | charToInt(c2);
            result.push_back(c3);
        }
    }

    return result;
}

uint8_t Common::charToInt(uint8_t ch) {
    if (ch >= 0x30 && ch <= 0x39) {
        return static_cast<uint8_t>(ch - 0x30);
    }
    else if (ch >= 0x41 && ch <= 0x46) {
        return static_cast<uint8_t>(ch - 0x37);
    }
    else if (ch >= 0x61 && ch <= 0x66) {
        return static_cast<uint8_t>(ch - 0x57);
    }

    throw "非法字符";
}

void Common::split(const std::string& s, std::vector<std::string>& sv, const char delim) {
    sv.clear();
    std::istringstream iss(s);
    std::string temp = "";

    while (std::getline(iss, temp, delim)) {
        if (temp.at(temp.length() - 1) == '\r') {
            //            temp.at(temp.length() - 1) = '\x00';
            temp = temp.substr(0, temp.size() - 1);
        }
        sv.emplace_back(std::move(temp));
    }

    return;
}

#ifdef ANDROID_BUILD
jstring Common::stringToJString(JNIEnv* env, std::string& str) {
    jclass strClass = env->FindClass("java/lang/String");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(str.size());
    env->SetByteArrayRegion(bytes, 0, str.size(), (jbyte*)(str.data()));
    jstring encoding = env->NewStringUTF("utf-8");
    return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}

jbyteArray Common::stringToJByteArray(JNIEnv* env, std::string& str) {
    jbyteArray array = env->NewByteArray(str.size());
    env->SetByteArrayRegion(array, 0, str.size(), (jbyte*)(str.data()));
    return array;
}

std::string Common::jByteArrayToString(JNIEnv* env, jbyteArray buf) {
    std::string result = "";

    jbyte* bytes = env->GetByteArrayElements(buf, 0);
    jsize bytesLen = env->GetArrayLength(buf);
    result.append((const char*)(bytes), (unsigned int)(bytesLen));
    env->ReleaseByteArrayElements(buf, bytes, 0);

    return result;
}
#endif

#ifdef DOTNET_BUILD
void Common::toStdString(System::String^ s, std::string& os)
{
    os.erase();
    const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
    os.append(chars, s->Length);
    Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void Common::toClrString(std::string& s, interior_ptr<System::String^> os)
{
    *os = gcnew String(s.data(), 0, s.size());
}
#endif
