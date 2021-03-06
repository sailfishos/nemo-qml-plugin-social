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

#include "facebookcommentinterface_p.h"
#include "facebookinterface.h"
#include "facebookontology_p.h"
// <<< include
#include <QtCore/QDebug>
// >>> include

FacebookCommentInterfacePrivate::FacebookCommentInterfacePrivate(FacebookCommentInterface *q)
    : IdentifiableContentItemInterfacePrivate(q)
    , action(FacebookInterfacePrivate::NoAction)
// <<< custom
    , from(0)
    , parent(0)
    , liked(false)
// >>> custom
{
}

void FacebookCommentInterfacePrivate::finishedHandler()
{
// <<< finishedHandler
    Q_Q(FacebookCommentInterface);
    if (!reply()) {
        // if an error occurred, it might have been deleted by the error handler.
        qWarning() << Q_FUNC_INFO << "network request finished but no reply";
        return;
    }

    QByteArray replyData = reply()->readAll();
    deleteReply();
    bool ok = false;
    QVariantMap responseData = ContentItemInterfacePrivate::parseReplyData(replyData, &ok);
    if (!ok)
        responseData.insert("response", replyData);

    if (action == FacebookInterfacePrivate::LikeAction || action == FacebookInterfacePrivate::DeleteLikeAction) {
        // user initiated a "like" or "unlike" request.
        if (responseData.value(QLatin1String("success")).toBool()) {
            status = SocialNetworkInterface::Idle;
            liked = (action == FacebookInterfacePrivate::LikeAction);
            emit q->statusChanged();
            emit q->likedChanged();
            emit q->responseReceived(responseData);
        } else {
            error = SocialNetworkInterface::RequestError;
            errorMessage = action == FacebookInterfacePrivate::LikeAction
                ? QLatin1String("Comment like request failed")
                : QLatin1String("Comment unlike request failed");
            status = SocialNetworkInterface::Error;
            emit q->statusChanged();
            emit q->errorChanged();
            emit q->errorMessageChanged();
            emit q->responseReceived(responseData);
        }
    } else {
        error = SocialNetworkInterface::OtherError;
        errorMessage = QLatin1String("Request finished but no action currently in progress");
        status = SocialNetworkInterface::Error;
        emit q->statusChanged();
        emit q->errorChanged();
        emit q->errorMessageChanged();
        emit q->responseReceived(responseData);
    }
// >>> finishedHandler
}
void FacebookCommentInterfacePrivate::emitPropertyChangeSignals(const QVariantMap &oldData,
                                                                const QVariantMap &newData)
{
    Q_Q(FacebookCommentInterface);
    QVariant oldMessage = oldData.value(FACEBOOK_ONTOLOGY_COMMENT_MESSAGE);
    QVariant newMessage = newData.value(FACEBOOK_ONTOLOGY_COMMENT_MESSAGE);
    QVariant oldCreatedTime = oldData.value(FACEBOOK_ONTOLOGY_COMMENT_CREATEDTIME);
    QVariant newCreatedTime = newData.value(FACEBOOK_ONTOLOGY_COMMENT_CREATEDTIME);
    QVariant oldLikeCount = oldData.value(FACEBOOK_ONTOLOGY_COMMENT_LIKECOUNT);
    QVariant newLikeCount = newData.value(FACEBOOK_ONTOLOGY_COMMENT_LIKECOUNT);
    QVariant oldCanComment = oldData.value(FACEBOOK_ONTOLOGY_COMMENT_CANCOMMENT);
    QVariant newCanComment = newData.value(FACEBOOK_ONTOLOGY_COMMENT_CANCOMMENT);
    QVariant oldCommentCount = oldData.value(FACEBOOK_ONTOLOGY_COMMENT_COMMENTCOUNT);
    QVariant newCommentCount = newData.value(FACEBOOK_ONTOLOGY_COMMENT_COMMENTCOUNT);

    if (newMessage != oldMessage)
        emit q->messageChanged();
    if (newCreatedTime != oldCreatedTime)
        emit q->createdTimeChanged();
    if (newLikeCount != oldLikeCount)
        emit q->likeCountChanged();
    if (newCanComment != oldCanComment)
        emit q->canCommentChanged();
    if (newCommentCount != oldCommentCount)
        emit q->commentCountChanged();

// <<< emitPropertyChangeSignals
    // TODO parent is not updated
    QVariantMap oldFromMap = oldData.value(FACEBOOK_ONTOLOGY_COMMENT_FROM).toMap();
    QString oldFromId = oldFromMap.value(FACEBOOK_ONTOLOGY_OBJECTREFERENCE_OBJECTIDENTIFIER).toString();
    QString oldFromName = oldFromMap.value(FACEBOOK_ONTOLOGY_OBJECTREFERENCE_OBJECTNAME).toString();
    QVariantMap newFromMap = newData.value(FACEBOOK_ONTOLOGY_COMMENT_FROM).toMap();
    QString newFromId = newFromMap.value(FACEBOOK_ONTOLOGY_OBJECTREFERENCE_OBJECTIDENTIFIER).toString();
    QString newFromName = newFromMap.value(FACEBOOK_ONTOLOGY_OBJECTREFERENCE_OBJECTNAME).toString();

    // Update the from object if required
    if (newFromId != oldFromId || newFromName != oldFromName) {
        QVariantMap newFromData;
        newFromData.insert(FACEBOOK_ONTOLOGY_OBJECTREFERENCE_OBJECTTYPE, FacebookInterface::User);
        newFromData.insert(FACEBOOK_ONTOLOGY_OBJECTREFERENCE_OBJECTIDENTIFIER, newFromId);
        newFromData.insert(FACEBOOK_ONTOLOGY_OBJECTREFERENCE_OBJECTNAME, newFromName);
        qobject_cast<FacebookInterface*>(q->socialNetwork())->setFacebookContentItemData(from, newFromData);
        emit q->fromChanged();
    }

    // Update like if needed
    bool newLiked = newData.value(FACEBOOK_ONTOLOGY_COMMENT_USERLIKES).toString() == QLatin1String("true");
    if (liked != newLiked) {
        liked = newLiked;
        emit q->likedChanged();
    }
// >>> emitPropertyChangeSignals

    // Call super class implementation
    QVariantMap oldDataWithId = oldData;
    oldDataWithId.insert(NEMOQMLPLUGINS_SOCIAL_CONTENTITEMID,
                         oldData.value(FACEBOOK_ONTOLOGY_METADATA_ID));
    QVariantMap newDataWithId = newData;
    newDataWithId.insert(NEMOQMLPLUGINS_SOCIAL_CONTENTITEMID,
                         newData.value(FACEBOOK_ONTOLOGY_METADATA_ID));
    IdentifiableContentItemInterfacePrivate::emitPropertyChangeSignals(oldDataWithId, newDataWithId);
}

//-------------------------------

/*!
    \qmltype FacebookComment
    \instantiates FacebookCommentInterface
    \inqmlmodule org.nemomobile.social 1
    \brief A FacebookComment represents a comment from the Facebook OpenGraph API
    
    FacebookComment is a specialized IdentifiableContentItem that is used
    to hold data that represents a comment in the Facebook OpenGraph API.
    
    \sa{IdentifiableContentItem}
    
*/
FacebookCommentInterface::FacebookCommentInterface(QObject *parent)
    : IdentifiableContentItemInterface(*(new FacebookCommentInterfacePrivate(this)), parent)
{
// <<< constructor
    Q_D(FacebookCommentInterface);
    d->from = new FacebookObjectReferenceInterface(this);
// >>> constructor
}

/*! \reimp */
int FacebookCommentInterface::type() const
{
    return FacebookInterface::Comment;
}

/*! \reimp */
bool FacebookCommentInterface::remove()
{
// <<< remove
    return IdentifiableContentItemInterface::remove();
// >>> remove
}

/*! \reimp */
bool FacebookCommentInterface::reload(const QStringList &whichFields)
{
// <<< reload
    return IdentifiableContentItemInterface::reload(whichFields);
// >>> reload
}

/*!
    \qmlmethod bool FacebookComment::like()
    Initiates a "like" operation on the comment.
    
    If the network request was started successfully, the function
    will return true and the status of the comment will change to
    \c SocialNetwork::Busy.  Otherwise, the function will return
    false.*/

bool FacebookCommentInterface::like()
{
// <<< like
    Q_D(FacebookCommentInterface);
    bool requestMade = d->request(IdentifiableContentItemInterfacePrivate::Post,
                                  identifier(), QLatin1String("likes"));

    if (!requestMade)
        return false;

    d->action = FacebookInterfacePrivate::LikeAction;
    d->connectFinishedAndErrors();
    return true;
// >>> like
}
/*!
    \qmlmethod bool FacebookComment::unlike()
    Initiates a "delete like" operation on the comment.
    
    If the network request was started successfully, the function
    will return true and the status of the comment will change to
    \c SocialNetwork::Busy.  Otherwise, the function will return
    false.*/

bool FacebookCommentInterface::unlike()
{
// <<< unlike
    Q_D(FacebookCommentInterface);
    bool requestMade = d->request(IdentifiableContentItemInterfacePrivate::Delete,
                                  identifier(), QLatin1String("likes"));

    if (!requestMade)
        return false;

    d->action = FacebookInterfacePrivate::DeleteLikeAction;
    d->connectFinishedAndErrors();
    return true;
// >>> unlike
}

/*!
    \qmlproperty FacebookObjectReference FacebookComment::from
    Holds a reference to the user or profile which uploaded this comment.
*/
FacebookObjectReferenceInterface * FacebookCommentInterface::from() const
{
    Q_D(const FacebookCommentInterface);
    return d->from;
}

/*!
    \qmlproperty string FacebookComment::message
    Holds the message text of the comment.
*/
QString FacebookCommentInterface::message() const
{
    Q_D(const FacebookCommentInterface);
    return d->data().value(FACEBOOK_ONTOLOGY_COMMENT_MESSAGE).toString();
}

/*!
    \qmlproperty string FacebookComment::createdTime
    Holds the creation time of the comment in an ISO8601-formatted string.
*/
QString FacebookCommentInterface::createdTime() const
{
    Q_D(const FacebookCommentInterface);
    return d->data().value(FACEBOOK_ONTOLOGY_COMMENT_CREATEDTIME).toString();
}

/*!
    \qmlproperty int FacebookComment::likeCount
    Holds the number of times this comment has been liked.
*/
int FacebookCommentInterface::likeCount() const
{
    Q_D(const FacebookCommentInterface);
    QString numberString = d->data().value(FACEBOOK_ONTOLOGY_COMMENT_LIKECOUNT).toString();
    bool ok;
    int number = numberString.toInt(&ok);
    if (ok) {
        return number;
    }
    return -1;
}

/*!
    \qmlproperty FacebookComment FacebookComment::parent
    Hold the parent comment.
*/
FacebookCommentInterface * FacebookCommentInterface::parent() const
{
    Q_D(const FacebookCommentInterface);
    return d->parent;
}

/*!
    \qmlproperty bool FacebookComment::canComment
    Whether the current user can reply to this comment.
*/
bool FacebookCommentInterface::canComment() const
{
    Q_D(const FacebookCommentInterface);
    return d->data().value(FACEBOOK_ONTOLOGY_COMMENT_CANCOMMENT).toString() == QLatin1String("true");
}

/*!
    \qmlproperty int FacebookComment::commentCount
    Holds the number of replies that this comment have.
*/
int FacebookCommentInterface::commentCount() const
{
    Q_D(const FacebookCommentInterface);
    QString numberString = d->data().value(FACEBOOK_ONTOLOGY_COMMENT_COMMENTCOUNT).toString();
    bool ok;
    int number = numberString.toInt(&ok);
    if (ok) {
        return number;
    }
    return -1;
}

/*!
    \qmlproperty bool FacebookComment::liked
    Whether the comment has been liked by the current user.
*/
bool FacebookCommentInterface::liked() const
{
    Q_D(const FacebookCommentInterface);
    return d->liked;
}

