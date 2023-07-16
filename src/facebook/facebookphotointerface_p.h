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

#ifndef FACEBOOKPHOTOINTERFACE_P_H
#define FACEBOOKPHOTOINTERFACE_P_H

#include "facebookphotointerface.h"
#include "facebookinterface_p.h"
#include "identifiablecontentiteminterface_p.h"
#include <QtCore/QList>

class FacebookPhotoInterfacePrivate: public IdentifiableContentItemInterfacePrivate
{
public:
    explicit FacebookPhotoInterfacePrivate(FacebookPhotoInterface *q);
    void finishedHandler();
    void emitPropertyChangeSignals(const QVariantMap &oldData, const QVariantMap &newData);
    FacebookInterfacePrivate::FacebookAction action;
    FacebookObjectReferenceInterface *from;
    QList<FacebookPhotoTagInterface *> tags;
    QList<FacebookNameTagInterface *> nameTags;
    QList<FacebookPhotoImageInterface *> images;
    bool liked;
    int likesCount;
    int commentsCount;
private:
    Q_DECLARE_PUBLIC(FacebookPhotoInterface)
    static void tags_append(QQmlListProperty<FacebookPhotoTagInterface> *list,
                            FacebookPhotoTagInterface *data);
    static FacebookPhotoTagInterface * tags_at(QQmlListProperty<FacebookPhotoTagInterface> *list,
                                               long long int index);
    static void tags_clear(QQmlListProperty<FacebookPhotoTagInterface> *list);
    static long long int tags_count(QQmlListProperty<FacebookPhotoTagInterface> *list);
    static void name_tags_append(QQmlListProperty<FacebookNameTagInterface> *list,
                                 FacebookNameTagInterface *data);
    static FacebookNameTagInterface * name_tags_at(QQmlListProperty<FacebookNameTagInterface> *list,
                                                   long long int index);
    static void name_tags_clear(QQmlListProperty<FacebookNameTagInterface> *list);
    static long long int name_tags_count(QQmlListProperty<FacebookNameTagInterface> *list);
    static void images_append(QQmlListProperty<FacebookPhotoImageInterface> *list,
                              FacebookPhotoImageInterface *data);
    static FacebookPhotoImageInterface * images_at(QQmlListProperty<FacebookPhotoImageInterface> *list,
                                                   long long int index);
    static void images_clear(QQmlListProperty<FacebookPhotoImageInterface> *list);
    static long long int images_count(QQmlListProperty<FacebookPhotoImageInterface> *list);
private:
    int pendingTagToRemoveIndex;
};

#endif // FACEBOOKPHOTOINTERFACE_P_H
