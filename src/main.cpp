#include "secrets.key" //wow, that worked!
#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <qglobal.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qnetworkrequest.h>
#include <qstringview.h>

int main(int argc, char* argv[]) {
  QCoreApplication app(argc, argv);

  QNetworkAccessManager* manager;

  QNetworkRequest request(QUrl(LOBBY));
  QNetworkReply* reply = manager.get(request); // catches the response

  connect(reply, &QNetworkReply::finished, [reply]() {
    if (reply->error() == QNetworkReply::NoError) {
      QByteArray msg = reply->readAll();
      qDebug() << msg;
    }
  });

  return app.exec();
}
