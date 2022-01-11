#include "dbhandler.h"
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QVariantMap>
#include <QDebug>

DBHandler::DBHandler(QObject *parent)
    : QObject{parent}
{
    m_networkManager = new QNetworkAccessManager(this);
    m_networkReply = m_networkManager->get(QNetworkRequest(QUrl("https://qt-dbintegration-default-rtdb.europe-west1.firebasedatabase.app/Pets.json")));
    connect(m_networkReply, &QNetworkReply::readyRead,this,&DBHandler::networkReplyReadyRead);

    // add into DB
    QVariantMap newPet;
    newPet["Type"]  = "Dog";
    newPet["Name"]  = "Szarik";
    newPet["Food"]  = "Wurst";
    QJsonDocument jsonDoc = QJsonDocument::fromVariant(newPet);

    QNetworkRequest newPetRequest(QUrl("https://qt-dbintegration-default-rtdb.europe-west1.firebasedatabase.app/Pets.json"));
    newPetRequest.setHeader(QNetworkRequest::ContentTypeHeader,QString("application/json"));
    m_networkManager->post(newPetRequest,jsonDoc.toJson());
}

DBHandler::~DBHandler()
{
    if(m_networkManager)
        m_networkManager->deleteLater();
}

void DBHandler::networkReplyReadyRead()
{
    qDebug() << m_networkReply->readAll();
}
