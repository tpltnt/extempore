/*
 * Copyright (c) 2011, Andrew Sorensen
 *
 * All rights reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * Neither the name of the authors nor other contributors may be used to endorse
 * or promote products derived from this software without specific prior written
 * permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

//#define _DEBUG_QUEUE_

#include <queue>

#include "EXTMutex.h"
#include "Task.h"
#include "BranchPrediction.h"

namespace extemp {

template<typename T>
class PriorityQueue
{
private:
    typedef std::pair<uint64_t, T*>                                                      key_type;
    typedef std::priority_queue<key_type, std::vector<key_type>, std::greater<key_type>> queue_type;
private:
    queue_type  m_queue;
public:
    ~PriorityQueue()
    {
        clear();
    }

    void add(T* Val)
    {
        m_queue.push(key_type(Val->getStartTime(), Val));
    }
    void clear()
    {
        while (!m_queue.empty()) {
            delete m_queue.top().second;
            m_queue.pop();
        }
    }
    T* pop()
    {
        if (unlikely(m_queue.empty())) {
            return nullptr;
        }
        auto element(m_queue.top().second);
        m_queue.pop();
        return element;
    }
    T* peek()
    {
        if (unlikely(m_queue.empty())) {
            return nullptr;
        }
        return m_queue.top().second;
    }
    size_t size() { return m_queue.size(); }
};

} //End Namespace
#endif
