/**
 * Copyright (c) 2019 Kylart <kylart.dev@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */ 
#ifndef BINDINGS_TORRENT_SRC_BIND_H_
#define BINDINGS_TORRENT_SRC_BIND_H_

#include <napi.h>

#include "client_session.h"
#include "version.h"

namespace Torrent {

void SetUp(Napi::Env env, Napi::Object exports);

}  // namespace Torrent

#endif  // BINDINGS_TORRENT_SRC_BIND_H_
