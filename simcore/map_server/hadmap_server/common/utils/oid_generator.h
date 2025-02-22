// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#pragma once
#include <string>

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/string_generator.hpp>

#include "common/third/gutil/macros.h"
#include "common/utils/spin_lock.h"

namespace tad {
namespace sim {

// Generates a unique 32byte id, based on uuid v4.
// This class is thread safe
class ObjectIdGenerator {
 public:
  ObjectIdGenerator() {}
  ~ObjectIdGenerator() {}

  // Generates and returns a new UUID.
  std::string Next();

  // Validates an existing UUID and converts it into the format used
  // (that is, 16 hexadecimal bytes without any dashes).
  // bool Canonicalize(const std::string& input, std::string* output) const;

 private:
  DISALLOW_COPY_AND_ASSIGN(ObjectIdGenerator);

  std::string NextWithoutBoost();

  typedef SpinLock LockType;

  // Protects 'oid_generator_'.
  LockType oid_lock_;

  // Generates new UUIDs.
  boost::uuids::random_generator oid_generator_;
};

}  // namespace sim
}  // namespace tad
