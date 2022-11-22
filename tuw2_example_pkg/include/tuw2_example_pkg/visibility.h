// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TUW2_EXAMPLE_PKG__VISIBILITY_H_
#define TUW2_EXAMPLE_PKG__VISIBILITY_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__

  #ifdef __GNUC__
    #define TUW2_EXAMPLE_PACKAGE_EXPORT __attribute__ ((dllexport))
    #define TUW2_EXAMPLE_PACKAGE_IMPORT __attribute__ ((dllimport))
  #else
    #define TUW2_EXAMPLE_PACKAGE_EXPORT __declspec(dllexport)
    #define TUW2_EXAMPLE_PACKAGE_IMPORT __declspec(dllimport)
  #endif

  #ifdef TUW2_EXAMPLE_PACKAGE_DLL
    #define TUW2_EXAMPLE_PACKAGE_PUBLIC TUW2_EXAMPLE_PACKAGE_EXPORT
  #else
    #define TUW2_EXAMPLE_PACKAGE_PUBLIC TUW2_EXAMPLE_PACKAGE_IMPORT
  #endif

  #define TUW2_EXAMPLE_PACKAGE_PUBLIC_TYPE TUW2_EXAMPLE_PACKAGE_PUBLIC

  #define TUW2_EXAMPLE_PACKAGE_LOCAL

#else

  #define TUW2_EXAMPLE_PACKAGE_EXPORT __attribute__ ((visibility("default")))
  #define TUW2_EXAMPLE_PACKAGE_IMPORT

  #if __GNUC__ >= 4
    #define TUW2_EXAMPLE_PACKAGE_PUBLIC __attribute__ ((visibility("default")))
    #define TUW2_EXAMPLE_PACKAGE_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define TUW2_EXAMPLE_PACKAGE_PUBLIC
    #define TUW2_EXAMPLE_PACKAGE_LOCAL
  #endif

  #define TUW2_EXAMPLE_PACKAGE_PUBLIC_TYPE
#endif

#ifdef __cplusplus
}
#endif

#endif  // TUW2_EXAMPLE_PKG__VISIBILITY_H_
