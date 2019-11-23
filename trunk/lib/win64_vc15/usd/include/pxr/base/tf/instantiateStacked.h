//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifdef TF_INSTANTIATE_STACKED_H
#error This file may be included only once in a translation unit (.cpp file).
#endif

#define TF_INSTANTIATE_STACKED_H

#include "pxr/pxr.h"
#include "pxr/base/tf/stacked.h"

PXR_NAMESPACE_OPEN_SCOPE

#define TF_INSTANTIATE_STACKED(Derived)                \
    template <>                                        \
    std::atomic<typename Derived::Storage::Type*>      \
    Derived::Storage::value(nullptr)

#define TF_INSTANTIATE_DEFINED_STACKED(Derived)        \
    std::atomic<typename Derived::Storage::Type*>      \
    Derived::Storage::value(nullptr)

PXR_NAMESPACE_CLOSE_SCOPE
