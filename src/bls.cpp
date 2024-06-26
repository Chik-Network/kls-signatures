// Copyright 2020 Chik Network Inc

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "bls.hpp"

#if BLSALLOC_SODIUM
#include "sodium.h"
#endif

namespace bls {

const size_t BLS::MESSAGE_HASH_LEN;

bool BLSInitResult = BLS::Init();

Util::SecureAllocCallback Util::secureAllocCallback;
Util::SecureFreeCallback Util::secureFreeCallback;

bool BLS::Init()
{
#if BLSALLOC_SODIUM
    if (sodium_init() < 0) {
        throw std::runtime_error("libsodium init failed");
    }
    SetSecureAllocator(sodium_malloc, sodium_free);
#else
    SetSecureAllocator(malloc, free);
#endif

    return true;
}

void BLS::SetSecureAllocator(
    Util::SecureAllocCallback allocCb,
    Util::SecureFreeCallback freeCb)
{
    Util::secureAllocCallback = allocCb;
    Util::secureFreeCallback = freeCb;
}

}  // end namespace bls
