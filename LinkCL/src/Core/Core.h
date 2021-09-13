#ifndef LINKCL_CORE_H
#define LINKCL_CORE_H

#define LINKCL_PLATFORM_WINDOWS 0
#define LINKCL_PLATFORM_MACOS 1
#define LINKCL_PLATFORM_LINUX 3
#define LINKCL_PLATFORM_ANDROID 4


#if (defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__))

#ifdef LINKCL_PLATFORM
#error "Platform is already defined and cannot be defined twice."
#endif

#define LINKCL_PLATFORM LINKCL_PLATFORM_WINDOWS
#define LINKCL_WINDOWS

#endif


#if ((defined(macintosh) || defined(Macintosh) || defined(__APPLE__) || defined(__MACH__)) && !defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__))

#ifdef LINKCL_PLATFORM
#error "Platform is already defined and cannot be defined twice."
#endif

#define LINKCL_PLATFORM LINKCL_PLATFORM_MACOS
#define LINKCL_MACOS

#endif


#if (defined(__linux__) || defined(linux) || defined(__linux))

#ifdef LINKCL_PLATFORM
#error "Platform is already defined and cannot be defined twice."
#endif

#define LINKCL_PLATFORM LINKCL_PLATFORM_LINUX
#define LINKCL_LINUX

#endif


#if (defined(__ANDROID__))

#ifdef LINKCL_PLATFORM
#error "Platform is already defined and cannot be defined twice."
#endif

#define LINKCL_PLATFORM LINKCL_PLATFORM_ANDROID
#define LINKCL_ANDROID

#endif


#define LINKCL_NORMAL 0;
#define LINKCL_WRAPPER 1;


#define LINKCL_LINK_SUCCESS 1;
#define LINKCL_LINK_FAILURE 0;


#define LINKCL_PUBLIC_API __attribute__((visibility("default")))

#define LINKCL_PRIVATE_API __attribute__((visibility("hidden")))

#define LINKCL_NOEXCEPT noexcept

#endif