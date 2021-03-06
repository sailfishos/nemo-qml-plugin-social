/*
 * Copyright (C) 2013 Jolla Ltd. <chris.adams@jollamobile.com>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Nemo Mobile nor the names of its contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
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
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */

#include "sorterinterface.h"
#include "contentiteminterface.h"

/*!
    \qmltype Sorter
    \instantiates SorterInterface
    \inqmlmodule org.nemomobile.social 1
    \brief A sorter used to sort data in a SocialNetworkModel

    The \c Sorter type should never be used directly by clients. Instead
    clients should use more specialized implementations of the \c Sorter
    interface.

    \c Filter is used by SocialNetworkModel to sort the related
    data. Several sorters can be set to a given SocialNetworkModel
    in order to perform more refined sorting using a stable sort
    algorithm.
 */

SorterInterface::SorterInterface(QObject *parent)
    : QObject(parent)
{
}

SorterInterface::~SorterInterface()
{
}

// The default sorting algorithm is to sort by type.
bool SorterInterface::firstLessThanSecond(const QVariantMap &first, const QVariantMap &second) const
{
    if (first.empty() && !second.empty()) {
         return true;
    }

    if (second.empty()) {
         return false;
    }

    return first.value(NEMOQMLPLUGINS_SOCIAL_CONTENTITEMTYPE).toInt()
           < second.value(NEMOQMLPLUGINS_SOCIAL_CONTENTITEMTYPE).toInt();
}
