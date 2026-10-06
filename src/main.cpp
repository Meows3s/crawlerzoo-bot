// Placeholder entry point — replace with the real bot.
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QNetworkAccessManager manager;
    QObject::connect(&manager, &QNetworkAccessManager::finished,
                     [](QNetworkReply *reply) {
                         qInfo() << "reply:" << reply->url().toString()
                                 << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
                         reply->deleteLater();
                     });
    manager.get(QNetworkRequest(QUrl(QStringLiteral("https://example.com"))));

    return app.exec();
}