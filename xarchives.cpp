// copyright (c) 2020 hors<horsicq@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include "xarchives.h"

XArchives::XArchives(QObject *parent) : QObject(parent)
{

}

QList<XArchive::RECORD> XArchives::getRecords(QIODevice *pDevice, qint32 nLimit)
{
    QList<XArchive::RECORD> listResult;

    QSet<XArchive::AT> stAT=XArchive::getArchiveTypes(pDevice);

    if(stAT.contains(XArchive::AT_ZIP))
    {
        XZip xzip(pDevice);

        listResult=xzip.getRecords(nLimit);
    }

    return listResult;
}

QList<XArchive::RECORD> XArchives::getRecords(QString sFileName, qint32 nLimit)
{
    QList<XArchive::RECORD> listResult;

    QFile file;

    file.setFileName(sFileName);

    if(file.open(QIODevice::ReadOnly))
    {
        listResult=getRecords(&file,nLimit);

        file.close();
    }

    return listResult;
}
