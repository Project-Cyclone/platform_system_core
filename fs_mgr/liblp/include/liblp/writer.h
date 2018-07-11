/*
 * Copyright (C) 2018 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LIBLP_WRITER_H
#define LIBLP_WRITER_H

#include "metadata_format.h"

namespace android {
namespace fs_mgr {

// Place an initial partition table on the device. This will overwrite the
// existing geometry, and should not be used for normal partition table
// updates. False can be returned if the geometry is incompatible with the
// block device or an I/O error occurs.
bool FlashPartitionTable(const std::string& block_device, const LpMetadata& metadata,
                         uint32_t slot_number);

// Update the partition table for a given metadata slot number. False is
// returned if an error occurs, which can include:
//  - Invalid slot number.
//  - I/O error.
//  - Corrupt or missing metadata geometry on disk.
//  - Incompatible geometry.
bool UpdatePartitionTable(const std::string& block_device, const LpMetadata& metadata,
                          uint32_t slot_number);

// These variants are for testing only. The path-based functions should be used
// for actual operation, so that open() is called with the correct flags.
bool FlashPartitionTable(int fd, const LpMetadata& metadata, uint32_t slot_number);
bool UpdatePartitionTable(int fd, const LpMetadata& metadata, uint32_t slot_number);

// Helper function to serialize geometry and metadata to a normal file, for
// flashing or debugging.
bool WriteToImageFile(const char* file, const LpMetadata& metadata);
bool WriteToImageFile(int fd, const LpMetadata& metadata);

}  // namespace fs_mgr
}  // namespace android

#endif /* LIBLP_WRITER_H */
