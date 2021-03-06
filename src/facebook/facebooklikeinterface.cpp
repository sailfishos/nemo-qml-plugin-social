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

#include "facebooklikeinterface.h"
#include "facebookinterface.h"
#include "facebookontology_p.h"
#include "contentiteminterface_p.h"
// <<< include
// >>> include

class FacebookLikeInterfacePrivate: public ContentItemInterfacePrivate
{
public:
    explicit FacebookLikeInterfacePrivate(FacebookLikeInterface *q);
    void emitPropertyChangeSignals(const QVariantMap &oldData, const QVariantMap &newData);
private:
    Q_DECLARE_PUBLIC(FacebookLikeInterface)
};

FacebookLikeInterfacePrivate::FacebookLikeInterfacePrivate(FacebookLikeInterface *q)
    : ContentItemInterfacePrivate(q)
{
}

void FacebookLikeInterfacePrivate::emitPropertyChangeSignals(const QVariantMap &oldData,
                                                             const QVariantMap &newData)
{
    Q_Q(FacebookLikeInterface);
    QVariant oldUserIdentifier = oldData.value(FACEBOOK_ONTOLOGY_LIKE_USERIDENTIFIER);
    QVariant newUserIdentifier = newData.value(FACEBOOK_ONTOLOGY_LIKE_USERIDENTIFIER);
    QVariant oldUserName = oldData.value(FACEBOOK_ONTOLOGY_LIKE_USERNAME);
    QVariant newUserName = newData.value(FACEBOOK_ONTOLOGY_LIKE_USERNAME);

    if (newUserIdentifier != oldUserIdentifier)
        emit q->userIdentifierChanged();
    if (newUserName != oldUserName)
        emit q->userNameChanged();

    // Call super class implementation
    ContentItemInterfacePrivate::emitPropertyChangeSignals(oldData, newData);
}

//-------------------------------

/*!
    \qmltype FacebookLike
    \instantiates FacebookLikeInterface
    \inqmlmodule org.nemomobile.social 1
    \brief A FacebookLike represents a like from the Facebook OpenGraph API
    
    FacebookLike is a specialized ContentItem that is used
    to hold data that represents a like in the Facebook OpenGraph API.
    
    \sa{ContentItem} 
    
*/
FacebookLikeInterface::FacebookLikeInterface(QObject *parent)
    : ContentItemInterface(*(new FacebookLikeInterfacePrivate(this)), parent)
{
}

/*! \reimp */
int FacebookLikeInterface::type() const
{
    return FacebookInterface::Like;
}


/*!
    \qmlproperty string FacebookLike::userIdentifier
    Holds the identifier of the user who liked an entry
*/
QString FacebookLikeInterface::userIdentifier() const
{
    Q_D(const FacebookLikeInterface);
    return d->data().value(FACEBOOK_ONTOLOGY_LIKE_USERIDENTIFIER).toString();
}

/*!
    \qmlproperty string FacebookLike::userName
    Holds the name of the user who liked an entry
*/
QString FacebookLikeInterface::userName() const
{
    Q_D(const FacebookLikeInterface);
    return d->data().value(FACEBOOK_ONTOLOGY_LIKE_USERNAME).toString();
}

