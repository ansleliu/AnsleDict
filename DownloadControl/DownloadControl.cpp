#include "DownloadControl.h"
#include <QDebug>

DownloadControl::DownloadControl(QObject *parent) :
    QObject(parent)
{  
    m_DownloadCount = 0;
    m_FinishedNum = 0;

    newName ="";
    m_FileSize = 0;
    m_File = NULL;
}

void DownloadControl::StartFileDownload(const QString &url, int count ,QFile *file)
{
    m_DownloadCount = count;
    m_FinishedNum = 0;
    m_Url = QUrl(url);
    m_FileSize = GetFileSize(m_Url);
    if(m_FileSize <= 0)
    {
        emit DownloadFail();
    }
    else
    {
        //�Ȼ���ļ�������
        QFileInfo urlFileInfo(m_Url.encodedPath());
        QString fileName = urlFileInfo.fileName();
        if (fileName.isEmpty())
        {
            fileName = "index.html";
        }

        m_File = file;
//        m_File = new QFile(filePath);
    //    QFileInfo fileInfo(filePath);
    //    QString filename = fileInfo.fileName();
    //    m_File->setFileName(filename);
        //���ļ�
//        if(!m_File->open(QIODevice::WriteOnly))
//        {
//            qDebug() << "file open error";
//            delete m_File;
//            m_File = 0;
//            return;
//        }

        Download *tempDownload;
        //���ļ��ֳ�PointCount�Σ����첽�ķ�ʽ����
        for(int i=0; i<m_DownloadCount; i++)
        {
            //�����ÿ�εĿ�ͷ�ͽ�β��HTTPЭ������Ҫ����Ϣ��
            int startPoint = m_FileSize * i / m_DownloadCount;
            int endPoint = m_FileSize * (i+1) / m_DownloadCount;
            if( i != 0 )
            {
                startPoint--;
            }
            //�ֶ����ظ��ļ�
            tempDownload = new Download(i+1, this);

            connect(tempDownload, SIGNAL(DownloadFinished()),
                    this, SLOT(SubPartFinished()));
            connect(tempDownload, SIGNAL(DownloadFinished()),
                    tempDownload, SLOT(deleteLater()));

            tempDownload->StartDownload(m_Url, m_File, startPoint, endPoint);
        }
    }
}

qint64 DownloadControl::GetFileSize(QUrl url)
{
    //�������ķ�ʽ��ȡ�����ļ��ĳ���
    QNetworkAccessManager manager;
    QEventLoop loop;
    //�������󣬻�ȡĿ���ַ��ͷ����Ϣ
    QNetworkReply *reply = manager.head(QNetworkRequest(url));
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()),
                     Qt::DirectConnection);
    QObject::connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), &loop, SLOT(quit()),
                     Qt::DirectConnection);
    loop.exec();
    QVariant var = reply->header(QNetworkRequest::ContentLengthHeader);
    delete reply;
    qint64 size = var.toLongLong();

    qDebug() << "The file size is: " << size;
    return size;
}

void DownloadControl::SubPartFinished()
{
    m_FinishedNum++;
    //�������������ļ���������˵���ļ�������ϣ��ر��ļ��������ź�
    if( m_FinishedNum == m_DownloadCount )
    {
        m_File->close();
        if(newName != "")
        {
            m_File->rename(newName);
        }
        emit FileDownloadFinished();
        qDebug() << "Download finished";
    }
}
