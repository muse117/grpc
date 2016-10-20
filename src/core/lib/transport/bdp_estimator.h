/*
 *
 * Copyright 2016, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef GRPC_CORE_LIB_TRANSPORT_BDP_ESTIMATOR_H
#define GRPC_CORE_LIB_TRANSPORT_BDP_ESTIMATOR_H

#include <stdbool.h>
#include <stdint.h>

#define GRPC_BDP_SAMPLES 16
#define GRPC_BDP_MIN_SAMPLES_FOR_ESTIMATE 3

typedef struct grpc_bdp_estimator {
  uint8_t num_samples;
  uint8_t first_sample_idx;
  bool sampling;
  int64_t samples[GRPC_BDP_SAMPLES];
} grpc_bdp_estimator;

void grpc_bdp_estimator_init(grpc_bdp_estimator *estimator);
void grpc_bdp_estimator_destroy(grpc_bdp_estimator *estimator);

// Returns true if a reasonable estimate could be obtained
bool grpc_bdp_estimator_get_estimate(grpc_bdp_estimator *estimator,
                                     int64_t *estimate);
// Returns true if the user should start a ping
bool grpc_bdp_estimator_add_incoming_bytes(grpc_bdp_estimator *estimator,
                                           int64_t num_bytes);
// Note that a ping is starting
void grpc_bdp_estimator_start_ping(grpc_bdp_estimator *estimator);
// Completes a previously started ping
void grpc_bdp_estimator_complete_ping(grpc_bdp_estimator *estimator);

#endif
